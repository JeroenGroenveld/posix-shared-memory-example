.PHONY : clean

all: process_1 process_2

process_1:
	gcc -Wall -Wextra -o process_1 process_1.c -lrt

process_2:
	gcc -Wall -Wextra -o process_2 process_2.c -lrt

clean:
	$(RM) process_1 process_1.o process_2 process_2.o