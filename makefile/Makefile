CC=cc -std=c17 -g3 -Wall -o $@		#make some optimization here
HEADER=include
COMPILE=-I ${HEADER} -c $<      #compile most left .c file into intermediate
INTERMEDIATE=implement/TCPSocket.o implement/Configuration.o implement/ArrayList.o implement/String.o
SERVER=server
CLIENT=client

all: ${SERVER} ${CLIENT}

${SERVER}: ${INTERMEDIATE} ${SERVER}.o
	${CC} $^
${CLIENT}: ${INTERMEDIATE} ${CLIENT}.o
	${CC} $^
%.o: %.c
	${CC} ${COMPILE}

# test: ${SERVER} ${CLIENT}
# 	valgrind --leak-check=full --show-leak-kinds=all ./${EXECUTABLE}

clean:
	rm -rf *.so
	rm -rf *.o
	rm -rf ${SERVER} ${CLIENT}
