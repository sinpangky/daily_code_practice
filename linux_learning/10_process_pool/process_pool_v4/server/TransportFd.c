#include "head.h"

int SendFd(int pipefd, int fd) {
  struct msghdr msg;
  bzero(&msg, sizeof(msg));
  struct iovec iov[1];
  char buf[1];
  iov[0].iov_base = buf;
  iov[0].iov_len = 1;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  struct cmsghdr *cmsg;
  int cmsglen = CMSG_LEN(sizeof(int));
  cmsg = (struct cmsghdr *)calloc(1, cmsglen);
  cmsg->cmsg_len = cmsglen;
  cmsg->cmsg_level = SOL_SOCKET;
  cmsg->cmsg_type = SCM_RIGHTS;
  *(int *)CMSG_DATA(cmsg) = fd;
  msg.msg_control = cmsg;
  msg.msg_controllen = cmsglen;
  int ret = sendmsg(pipefd, &msg, 0);
  ERROR_CHECK(ret, -1, "sendmsg");
  return 0;
}

int RecvFd(int pipefd, int *fd) {
  struct msghdr msg;
  bzero(&msg, sizeof(msg));
  struct iovec iov[1];
  char buf[1];
  iov[0].iov_base = buf;
  iov[0].iov_len = 1;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  struct cmsghdr *cmsg;
  int cmsglen = CMSG_LEN(sizeof(int));
  cmsg = (struct cmsghdr *)calloc(1, cmsglen);
  cmsg->cmsg_len = cmsglen;
  cmsg->cmsg_level = SOL_SOCKET;
  cmsg->cmsg_type = SCM_RIGHTS;
  msg.msg_control = cmsg;
  msg.msg_controllen = cmsglen;
  int ret = recvmsg(pipefd, &msg, 0);
  ERROR_CHECK(ret, -1, "recvmsg");
  *fd = *(int *)CMSG_DATA(cmsg);
  return 0;
}