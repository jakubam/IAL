all: main.c graph.c
	gcc -o ialproject main.c graph.c file_read.c -I.
clean: 
	rm -f .o ialproject
