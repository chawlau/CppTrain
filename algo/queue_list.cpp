#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define queue_is_empty(array_queue) (array_queue->num ==0)
#define queue_is_full(array_queue) ((array_queue->num) == (array_queue->size))

struct Node {
  int data_;
  Node* next;
  Node(int data) : data_(data), next(NULL) {}
};

struct Queue {
  int num;
  Node* head;
  Node* tail;
  Queue() : num (0), head(NULL), tail(NULL) {}

  bool Push(int data) {
    Node* node = new Node(data);
    if (head == NULL) {
      head = node;
    } else {
      tail->next = node;
    }
    tail = node;
    num++;
    return true;
  }

  int Pop(int* data) {
    if (head == NULL || data == NULL || num == 0) return -1;
    *data = head->data_;
    Node* ret = head;
    head= head->next;
    num--;
    delete ret;
    return 0;
  }

  void Scan() {
    Node* scn = head;
    while (scn != NULL) {
      printf("Node data %d \n", scn->data_);
      scn = scn->next;
    }
  }
};

int main() {
  Queue que;
  que.Push(1);
  que.Push(2);
  que.Push(3);
  que.Push(4);
  int data;
  que.Pop(&data);
  que.Pop(&data);
  que.Scan();
}


