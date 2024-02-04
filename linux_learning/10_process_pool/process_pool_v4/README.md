# NOTE

The `postion` in early versions can be wrong!

## Version 4:

- Use `sendfile` and `splice` to accelerate file-transporting rate
  position:
  - ./server/transport_file.c: line 57
  - ./client/transport_file.c: line 39～51
- Achieve graceful exit
  position:
  - 

## Version 3:

- Client send the filename to download, server can see whether it exists
  position:
  - ./server/transport_file.c: line 7~26
  - ./client/transport_file.c: line 20~41
- Use `mmap` to take advantage of "zero-copy" tech to increase the send and recv rate during file transport
  position:
  - ./server/transport_file.c: line 37~45
  - ./client/transport_file.c: line 52~58


## Version 2:

- Change the transport part to send only file content (in the early version I use content with head to direct file block size)
  position:
  - ./server/transport_file.c: line 21~22
  - ./client/transport_file.c: line 35~47
- Add the download-time count
  positon:
  - ./client/transport_file.c: line 32~33, 50~51

## Version 1:

- Transport file with TCP protocal
- Use `socketpair` to connect parent process and child processes through the producer-consumer model
  position: 
  - ./server/worker.c
  - ./server/transport_fd.c
- Use "loop download" to avoid the inconsistent client-recv and server-send rates
  position: 
  - ./client/transport_file.c
- Show the real-time downloading percentage
  position:
  - ./client/transport_file.c
