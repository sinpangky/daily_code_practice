#include "head.h"

/**
 * Sends a file descriptor through a pipe.
 *
 * @param pipefd The file descriptor of the pipe.
 * @param fd The file descriptor to be sent.
 * @return Returns 0 on success, or -1 on failure.
 */
int SendFd(int pipefd, int fd) {
  struct msghdr msg;         // Create a message header structure.
  bzero(&msg, sizeof(msg));  // Clear the message header structure.
  struct iovec iov[1];       // Create an I/O vector structure.
  char buf[10] = "hello";    // Create a buffer with the message to be sent.
  iov[0].iov_base =
      buf;             // Set the base address of the I/O vector to the buffer.
  iov[0].iov_len = 5;  // Set the length of the I/O vector.
  msg.msg_iov = iov;   // Set the I/O vector in the message header.
  msg.msg_iovlen =
      1;  // Set the length of the I/O vector in the message header.
  struct cmsghdr* cmsg;  // Create a control message structure.
  int cmsglen =
      CMSG_LEN(sizeof(int));  // Calculate the length of the control message.
  cmsg = (struct cmsghdr*)calloc(
      1, cmsglen);                // Allocate memory for the control message.
  cmsg->cmsg_len = cmsglen;       // Set the length of the control message.
  cmsg->cmsg_level = SOL_SOCKET;  // Set the level of the control message.
  cmsg->cmsg_type = SCM_RIGHTS;   // Set the type of the control message.
  *(int*)CMSG_DATA(cmsg) =
      fd;                  // Set the file descriptor in the control message.
  msg.msg_control = cmsg;  // Set the control message in the message header.
  msg.msg_controllen =
      cmsglen;  // Set the length of the control message in the message header.
  int ret =
      sendmsg(pipefd, &msg,
              0);  // Send the message using the specified pipe file descriptor.
  ERROR_CHECK(ret, -1, "sendmsg");  // Check for errors in the sendmsg function.
  return 0;                         // Return 0 to indicate success.
}
/**
 * Receives a file descriptor through a pipe.
 */
int RecvFd(int pipefd, int* fd) {
  struct msghdr msg;         // Create a message header structure.
  bzero(&msg, sizeof(msg));  // Clear the message header structure.
  struct iovec iov[1];       // Create an I/O vector structure.
  char buf[10];              // Create a buffer to store the message.
  iov[0].iov_base =
      buf;             // Set the base address of the I/O vector to the buffer.
  iov[0].iov_len = 5;  // Set the length of the I/O vector.
  msg.msg_iov = iov;   // Set the I/O vector in the message header.
  msg.msg_iovlen =
      1;  // Set the length of the I/O vector in the message header.
  struct cmsghdr* cmsg;  // Create a control message structure.
  int cmsglen =
      CMSG_LEN(sizeof(int));  // Calculate the length of the control message.
  cmsg = (struct cmsghdr*)calloc(
      1, cmsglen);                // Allocate memory for the control message.
  cmsg->cmsg_len = cmsglen;       // Set the length of the control message.
  cmsg->cmsg_level = SOL_SOCKET;  // Set the level of the control message.
  cmsg->cmsg_type = SCM_RIGHTS;   // Set the type of the control message.
  msg.msg_control = cmsg;  // Set the control message in the message header.
  msg.msg_controllen =
      cmsglen;  // Set the length of the control message in the message header.
  int ret = recvmsg(
      pipefd, &msg,
      0);  // Receive the message using the specified pipe file descriptor.
  ERROR_CHECK(ret, -1, "recvmsg");  // Check for errors in the recvmsg function.
  *fd = *(int*)CMSG_DATA(
      cmsg);  // Set the file descriptor from the control message.
  return 0;   // Return 0 to indicate success.
}