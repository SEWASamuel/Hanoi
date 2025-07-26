CC=gcc

INCLUDE_DIR=include/
SRC_DIR=src/
OBJ_DIR=obj/

#j'a besoin de :
#	- compiler les fichiers source en fichiers objet
#	- compiler les fichier objet en un executable
# tou cela, pour le main et le test	

main : objets
	$(CC) -c main.c
	$(CC) bool.o evenements.o hanoi.o sequence.o main.o -o main

test : objets
	$(CC) -c test.c
	$(CC) bool.o evenements.o hanoi.o sequence.o test.o -o test

objets :
	$(CC) -c $(SRC_DIR)bool.c
	$(CC) -c $(SRC_DIR)evenements.c
	$(CC) -c $(SRC_DIR)sequence.c
	$(CC) -c $(SRC_DIR)hanoi.c

clean :
	rm *.o

