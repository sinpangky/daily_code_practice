#include <func.h>
#include <sys/ioctl.h>

// Function to print a message right-aligned in the terminal
void printRightAligned(char* message) {
  struct winsize w;
  // Get the window size of the terminal
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int i = strlen(message) - 1;
  message[i] = 0;
  // Calculate the number of spaces required for right alignment
  int padding = w.ws_col - i;
  if (padding < 0) padding = 0;

  // Move the cursor up one line and clear the line
  printf("\033[A\033[2K");
  // Output the right-aligned message
  printf("%*s%s\n", padding, "", message);
}

// Function to add a file descriptor to the epoll instance
int EpollAdd(int epoll_fd, int fd, struct epoll_event* event) {
  event->data.fd = fd;
  event->events = EPOLLIN;
  int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, event);
  ERROR_CHECK(ret, -1, "epoll_ctl");
  return 0;
}

int main(int argc, char const* argv[]) {
  int listen_sockfd;
  // Create a socket
  listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(listen_sockfd, -1, "socket");

  struct sockaddr_in server_address, client_address;
  int address_length = sizeof(server_address);
  // Initialize server_address to zeros
  memset(&server_address, 0, address_length);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_address.sin_port = htons(7234);

  int opt = 1;
  // Set socket option to reuse address
  int ret =
      setsockopt(listen_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  ERROR_CHECK(ret, -1, "setsockopt");

  // Bind the socket to the address
  ret = bind(listen_sockfd, (struct sockaddr*)&server_address,
             sizeof(server_address));
  ERROR_CHECK(ret, -1, "bind");
  // Listen for incoming connections
  listen(listen_sockfd, 3);

  // Create an epoll instance
  int epoll_fd = epoll_create(1);
  struct epoll_event event;
  // Add stdin and the listening socket to the epoll instance
  EpollAdd(epoll_fd, STDIN_FILENO, &event);
  EpollAdd(epoll_fd, listen_sockfd, &event);

  struct epoll_event events[3];
  int ready_fd_count, i;
  char buffer[1024] = {0};
  int client_sockfd;
  // Accept a new connection
  // int client_sockfd = accept(listen_sockfd, (struct sockaddr*)&client_address,
  //                            (socklen_t*)&address_length);
  // ERROR_CHECK(client_sockfd, -1, "accept");
  // printf("------Connected: IP = %s, Port = %d------\n",
  //        inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

  // // Add the new connection to the epoll instance
  // EpollAdd(epoll_fd, client_sockfd, &event);

  while (1) {
    // Wait for an event on the epoll instance
    ready_fd_count = epoll_wait(epoll_fd, events, 3, -1);
    for (i = 0; i < ready_fd_count; i++) {
      // If a new connection is ready to be accepted
      if (events[i].data.fd == listen_sockfd) {
        client_sockfd = accept(listen_sockfd, (struct sockaddr*)&client_address,
                               (socklen_t*)&address_length);
        ERROR_CHECK(client_sockfd, -1, "accept");
        printf("------Connected: IP = %s, Port = %d------\n",
               inet_ntoa(client_address.sin_addr),
               ntohs(client_address.sin_port));

        // Add the new connection to the epoll instance
        EpollAdd(epoll_fd, client_sockfd, &event);
      } else if (events[i].data.fd ==
                 STDIN_FILENO) {  // If stdin is ready to be read
        memset(buffer, 0, sizeof(buffer));
        read(STDIN_FILENO, buffer, sizeof(buffer));
        printRightAligned(buffer);
        // Send the input from stdin to the client
        send(client_sockfd, buffer, strlen(buffer), 0);
      } else if (events[i].data.fd ==
                 client_sockfd) {  // If the client sent data
        memset(buffer, 0, sizeof(buffer));
        ret = recv(client_sockfd, buffer, sizeof(buffer), 0);
        if (0 == ret) {  // If the client disconnected
          printf("------Client disconnected------\n");
          event.data.fd = client_sockfd;
          event.events = EPOLLIN;
          // Remove the client from the epoll instance
          ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_sockfd, &event);
          ERROR_CHECK(ret, -1, "epoll_ctl");

          // Close the client socket
          close(client_sockfd);
          break;
        }
        // Print the data received from the client
        printf("%s\n", buffer);
      }
    }
  }
  // Close the listening socket
  close(listen_sockfd);
  return 0;
}