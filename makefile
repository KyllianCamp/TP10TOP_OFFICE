all : main.c
	gcc main.c -o main

clean :	
	rm ./factures/*.txt