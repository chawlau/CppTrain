#include <iostream>
#include <stdio.h>
#include <stdlib.h>

struct Queue {
  int n;
  int* items;
  int tail;
  int head;

  Queue(int capacity): n(capacity), tail(0), head(0) {
    items = new int(capacity);
  }

  bool Push(int data) {
    if ((tail + 1) % n == head) return false;
    items[tail] = data;
    tail = (tail + 1) % n;
    return true;
  }

  int Pop() {
    if (tail == head) return -1;
    int data = items[head];
    head = (head + 1) % n;
    return data;
  }

  void Scan() {
    for (int i = head ; i < tail;i ++) {
      printf("data %d ", items[i]);
    }
    printf("\n");
  }
};

int main() {
  Queue que(10);
  que.Pop();
  que.Push(5);
  que.Push(5);
  que.Pop();
  que.Scan();
}
