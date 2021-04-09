CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS_MEM = -Wall -Wextra -Werror -g3 -fsanitize=address

all: my_blockchain

my_blockchain: my_blockchain.o my_c_functions.o
	${CC} -o $@ $^ ${CFLAGS_MEM}

%.o: %.c %.h
	${CC} -c $<

clean:
	rm *.o core.* 