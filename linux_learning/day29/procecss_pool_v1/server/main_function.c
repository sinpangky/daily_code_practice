#include "head.h"

/**
 * @brief Add a file descriptor to an epoll instance.
 *
 * This function adds a file descriptor to the specified epoll instance.
 *
 * @param epoll_fd The file descriptor of the epoll instance.
 * @param fd The file descriptor to be added.
 * @return 0 on success, -1 on failure.
 */
int EpollAdd(int epoll_fd, int fd) {
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = fd;
  int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
  ERROR_CHECK(ret, -1, "epoll_ctl");
  return 0;
}

/**
 * Initializes the client file descriptor queue.
 *
 * @param list The pointer to the ClientFdList structure to be initialized.
 */
void ClientFdQueueInit(ClientFdList* list) {
  list->head = list->tail = NULL;
  list->size = 0;
}

/**
 * Pushes a new client file descriptor to the end of the client file descriptor
 * list.
 *
 * @param list The client file descriptor list.
 * @param fd The file descriptor to be pushed.
 */
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

/**
 * @brief Removes and returns the file descriptor from the front of the client
 * file descriptor queue.
 *
 * @param list The client file descriptor list.
 * @return int The file descriptor that was removed from the queue, or -1 if the
 * queue is empty.
 */
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

int ClientFdQueueIsEmpty(ClientFdList* list) { return list->size == 0; }
