CC := gcc
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%.out)

all: $(BINS)

%.out: %.c
	$(CC) $< -o $@ -lpthread

.PHONY: clean
clean:
	rm -f $(BINS)