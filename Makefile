LIB = libglthread.a
SRCS = $(shell find -type f \( -name '*.c' -a \( -not -name 'main.c' \) \))
OBJS = $(patsubst ./%.c, %.o, $(SRCS))
TEST = exe
TEST_SRCS = main.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

all: $(LIB) $(TEST)

$(LIB): $(OBJS)
	ar rcs $@ $^

$(TEST): $(OBJS) $(TEST_OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean test re

re: clean all

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TEST) $(LIB)

test: $(TEST)
	./$(TEST)
