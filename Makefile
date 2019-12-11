all: main.c graph.c
	gcc -o ialproject main.c graph.c file_read.c -I.
clean: 
	rm -f .o ialproject
test:
	./ialproject graph_simple.txt 1 5 "JEDNODUCHÝ NEORIENTOVANÝ NEOHODNOCENÝ GRAF"
	./ialproject graph_no_connection.txt 1 4 "JEDNODUCHÝ NEORIENTOVANÝ NEOHODNOCENÝ GRAF - NEEXISTUJÍCÍ SPOJENÍ"
	./ialproject graph_two_paths.txt 1 8 "JEDNODUCHÝ NEORIENTOVANÝ NEOHODNOCENÝ GRAF -- EXISTUJÍ DVĚ NEJKRATŠÍ CESTY"
	./ialproject graph_unoriented_weightless.txt 1 17 "NEORIENTOVANÝ NEOHODNOCENÝ GRAF"
	./ialproject graph_unoriented_weighted.txt 1 17 "NEORIENTOVANÝ OHODNOCENÝ GRAF"
	./ialproject graph_oriented_weightless.txt 1 17 "ORIENTOVANÝ NEOHODNOCENÝ GRAF"
	./ialproject graph_oriented_weighted.txt 1 17 "ORIENTOVANÝ OHODNOCENÝ GRAF"