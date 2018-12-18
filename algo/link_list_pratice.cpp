#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

struct Node {
  int data;
  Node* next;
  Node(int data_ = 1) : data(data_) , next(NULL) {}
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

void createSortList(Node** a, Node** b) {
  InsertNode(a, 2);
  InsertNode(a, 1);
  InsertNode(a, 0);
  InsertNode(b, 6);
  InsertNode(b, 5);
  InsertNode(b, 3);
}

void moveNode(Node** desc, Node** src) {
  if (src == NULL) return;
  Node* new_node = *src;
  *src = new_node->next;
  new_node->next = *desc;
  *desc = new_node;
}

void deleteLastKth(Node** head, int k) {
  if (*head == NULL || k == 0) return;

  Node* fast = *head;
  int i = 0;
  while(i < k - 1 && fast != NULL) {
    fast = fast->next;
    i++;
  }

  if (fast == NULL) return;

  Node* slow = *head;
  Node* pre = NULL;
  while (slow != NULL && fast->next != NULL) {
    pre = slow;
    slow = slow->next;
    fast = fast->next;
  }

  if (!pre) {
    (*head) = (*head)->next;
  } else {
    pre->next = slow->next;
  }
  free(slow);
}

void testDeleteLastKth() {
  Node* head = NULL;
  InsertNode(&head, 3);
  InsertNode(&head, 2);
  InsertNode(&head, 1);
  PrintLinkList(head);
  deleteLastKth(&head, 2);
  PrintLinkList(head);
}

Node* mergeSortedLinkList(Node* a, Node* b) {
  Node dummy(1);
  Node* tail = &dummy;

  while (true) {
    if (a == NULL) {
      tail->next = b;
      break;
    } else if (b == NULL) {
      tail->next = a;
      break;
    }

    if (a->data <= b->data) {
      moveNode(&(tail->next), &a);
    } else {
      moveNode(&(tail->next), &b);
    }
    tail = tail->next;
  }
  return dummy.next;
}

void testMergeSortedList() {
  Node* a = NULL;
  Node* b = NULL;
  createSortList(&a, &b);
  PrintLinkList(a);
  PrintLinkList(b);
  Node* ret = mergeSortedLinkList(a, b);
  PrintLinkList(ret);
}

Node* findMiddleNode(Node* head) {
  Node* slow = head;
  Node* fast = head;
  while (fast->next != NULL && fast->next->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

void testFindMiddleNode() {
  Node* head = NULL;
  InsertNode(&head, 5);
  InsertNode(&head, 4);
  InsertNode(&head, 3);
  InsertNode(&head, 2);
  InsertNode(&head, 1);
  PrintLinkList(head);
  Node* middle = findMiddleNode(head);
  printf("middel node data %d", middle->data);
}

void testReverse() {
  Node* head = NULL;
  InsertNode(&head, 1);
  InsertNode(&head, 2);
  InsertNode(&head, 3);
  PrintLinkList(head);
  reverse(&head);
  PrintLinkList(head);
}

void testCircle() {
  Node* circle_list = NULL;
  MakeCircleLinkList(&circle_list);
  printf("circle %d\n", circle(circle_list));
  PrintLinkList(circle_list);
}

int main(int argc, char** argv) {
  //testMergeSortedList();
  //testDeleteLastKth();
  //testCircle();
  //testReverse();
  testFindMiddleNode();
}
