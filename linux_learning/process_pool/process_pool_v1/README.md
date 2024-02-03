# NOTE

- Use `socketpair` to connect parent process and child processes through the producer-consumer model
  position: 
  - ./server/worker.c: line 21
  - ./server/transport_fd.c
- Use "loop download" to avoid the inconsistent client-recv and server-send rates
  position: 
  - ./client/transport_file.c: line 3
- Show the real-time downloading percentage
  position:
  - ./client/transport_file.c: line 36
