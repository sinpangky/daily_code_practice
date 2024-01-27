CC := gcc
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%.out)

all: $(BINS)

%.out: %.c
	$(CC) -Wall $< -o $@

.PHONY: clean
clean:
	rm -f $(BINS)