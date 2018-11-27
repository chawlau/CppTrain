#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

struct Node {
  int data;
  Node* next;
  Node(int data_) : data(data_) , next(NULL) {}
};

void InsertNode(Node** head, int data) {
  Node* p  = new Node(data);
  p->next = *head;
  *head = p;
}

void PrintLinkList(Node* head) {
  while (head) {
    printf("node val %d ", head->data);
    head = head->next;
  }
  printf("\n");
}

void reverse(Node** head) {
  if (head == NULL) {
    return ;
  }

  Node* p_pre = NULL;
  Node* p = *head;
  while(p) {
    Node* p_next = p->next;
    if (p_next == NULL) {
      *head = p;
    }
    p->next = p_pre;
    p_pre = p;
    p = p_next;
  }
}

bool circle(Node* head) {
  if (head == NULL) return 0;
  Node* fast = head;
  Node* slow = head;
  while(fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) {
      return true;
    }
  }
  return false;
}

void MakeCircleLinkList(Node** head) {
  Node* cur = NULL;
  for (int i = 0; i < 4; ++i) {
    Node* node = new Node(i);
    node->next = *head;
    *head = node;
    if (i == 0) {
      cur = node;
    }
  }
  cur->next = *head;
}

int main(int argc, char** argv) {
  Node* head = NULL;
  InsertNode(&head, 1);
  InsertNode(&head, 2);
  InsertNode(&head, 3);
  PrintLinkList(head);
  reverse(&head);
  PrintLinkList(head);
  printf("circle %d\n", circle(head));
  Node* circle_list = NULL;
  MakeCircleLinkList(&circle_list);
  printf("circle %d\n", circle(circle_list));
  PrintLinkList(circle_list);
}
