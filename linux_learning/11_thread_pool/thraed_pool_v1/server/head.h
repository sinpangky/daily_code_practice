#ifndef __HEAD_H__
#define __HEAD_H__
#define _GNU_SOURCE
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
// #include <mysql/mysql.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <sys/select.h>
#include <sys/sem.h>
#include <sys/sendfile.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#define ARGS_CHECK(argc, num) \
  {                           \
    if (argc != num) {        \
      printf("error args\n"); \
      return -1;              \
    }                         \
  }
#define ERROR_CHECK(ret, retval, func_name)  \
  {                                          \
    if (ret == retval) {                     \
      printf("errno=%d,", errno);            \
      fflush(stdout);                        \
      perror(func_name);                     \
      printf("%s:%d\n", __FILE__, __LINE__); \
      return -1;                             \
    }                                        \
  }
#define THREAD_ERR_CHECK(ret, func_name)                          \
  {                                                               \
    if (ret != 0) {                                               \
      printf("%s failed,%d %s\n", func_name, ret, strerror(ret)); \
      return -1;                                                  \
    }                                                             \
  }

#endif