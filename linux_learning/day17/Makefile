SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:%.c=%.o)
CC:=gcc
CFLAGS:=-g
ELF:=main
$(ELF):$(OBJS)
	gcc -o $@ $^

rebuild:clean $(ELF)
clean:
	rm -rf $(OBJS) $(ELF)
