#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockQueue {
 public:
  using value_type = T;
  using container_type = std:queue<value_type>;
  using size_type       = typename container_type::size_type;
 private:
  size_type capacity_ = 0;
  container_type container_;
  mutable std::mutex mutex_;
  mutable std::condition_variable not_empty_;
  mutable std::condition_variable not_full_;

 public:
  BlockQueue() = delete;
  BlockQueue(const size_type capacity) : capacity_(capacity) {}
  BlockQueue(const BlockQueue&) = default;
  BlockQueue(BlockQueue&&) = default;
  BlockQueue& operator=(const BlockQueue&) = default;
  BlockQueue& operator=(BlockQueue&&) = default;

 private:
  bool empty() const { return container_.empty(); }
  bool full() const { return not(container_.size() < capacity_); }

 public:
  void put(const value_type& item) {
    std::unqiue_lock<std::mutex> lock(mutex_);
    while(full()) {
      not_full.wait();
    }
    container_.push(item);
    not_empty.notify_one();
  }

  void take(const value_type& item) {
    std::unqiue_lock<std::mutex> lock(mutex_);
    while(empty()) {
      not_empty.wait();
    }
    out = container_.front();
    container_.pop();
    not_full.notify_one();
  }
}
