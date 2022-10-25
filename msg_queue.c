#include <stdio.h>
#include <stdlib.h>
typedef void (*event)(char* s);
struct event_q {
  char name[10];
  event e;
  struct event_q* next;
};
typedef struct event_q event_q;
event_q* msg_q;

void queue_reg(char* node_name, event_q** list, event e) {
  event_q* q = (event_q*)malloc(sizeof(event_q));
  q->e = e;
  q->next = NULL;

  if ((*list) == NULL) {
    (*list) = q;
  } else {
    while ((*list)->next != NULL) {
      (*list) = (*list)->next;
    }
    (*list)->next = q;
  }
}
void publish(char* s) {
  do {
    if (msg_q != NULL) {
      msg_q->e(s);
      msg_q = msg_q->next;
    }
  } while (msg_q != NULL);
}
void printa(char* s) {
  printf("printa:%s\n", s);
}
void printb(char* s) {
  printf("printb:%s\n", s);
}
int main(int argc, char** argv) {
  msg_q = NULL;
  queue_reg((char*)"pa", &msg_q, printa);
  queue_reg((char*)"pb", &msg_q, printb);
  publish((char*)"hello");
  return 0;
}

