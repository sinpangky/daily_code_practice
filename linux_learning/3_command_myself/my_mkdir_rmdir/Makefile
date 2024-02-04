CC:=gcc
SRCS:=$(wildcard *.c)
BINS:=$(SRCS:%.c=%)
all:$(BINS)
%:%.c
	$(CC) $< -o $@
.PHONY:clean
clean:
	rm  $(BINS)