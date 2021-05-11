CC = gcc
CFLAGS += -Wall -Wextra -g3 #-Werror
CFLAGS_MEM = ${CFLAGS} -fsanitize=address
NAME = my_blockchain

all: my_blockchain

${NAME}: my_blockchain.o my_c_functions.o linked_list.o
	${CC} -o $@ $^ ${CFLAGS}

%.o: %.c %.h
	${CC} ${CFLAGS} -c $< 

clean:
	rm -f *.o core.* 

re: clean ${NAME}