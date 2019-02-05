.PHONY: all clean

CFLAGS += -Wall -Wextra -Werror -O2
OUT = swappy

all:
	gcc $(CFLAGS) swappy.c -o $(OUT)
	strip $(OUT)

clean:
	rm -f $(OUT)
