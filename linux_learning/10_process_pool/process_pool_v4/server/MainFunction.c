#include "head.h"

void ClientFdQueueInit(ClientFdList* list) {
  list->head = list->tail = NULL;
  list->size = 0;
}

void ClientFdQueuePush(ClientFdList* list, int fd) {
  ClientFdNode* new_node = (ClientFdNode*)malloc(sizeof(ClientFdNode));
  new_node->fd = fd;
  new_node->next = NULL;
  if (list->size == 0) {
    list->head = list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
  }
  list->size++;
}

int ClientFdQueuePop(ClientFdList* list) {
  if (ClientFdQueueIsEmpty(list)) {
    return -1;
  }
  ClientFdNode* temp = list->head;
  list->head = list->head->next;
  if (list->head == NULL) {
    list->tail = NULL;
  }
  int fd = temp->fd;
  free(temp);
  list->size--;
  return fd;
}

int ClientFdQueueIsEmpty(const ClientFdList* list) { 
  return list->size == 0; 
}

int EpollAdd(int epoll_fd, int fd) {
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = fd;
  int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
  ERROR_CHECK(ret, -1, "epoll_ctl");
  return 0;
}
