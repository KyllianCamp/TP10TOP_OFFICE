all : main.c
	gcc main.c -o main

clean :	
	rm -f ./factures/*.txt
	rm -f alerte.txt 