CC=gcc

INCLUDE_DIR=include/
SRC_DIR=src/
OBJ_DIR=obj/

#j'a besoin de :
#	- compiler les fichiers source en fichiers objet
#	- compiler les fichier objet en un executable
# tou cela, pour le main et le test	

all : main test

main : objets
	$(CC) -c main.c
	$(CC) bool.o evenements.o hanoi.o main.o -o main

test : objets
	$(CC) -c test.c
	$(CC) bool.o evenements.o hanoi.o test.o -o test

objets :
	$(CC) -c $(SRC_DIR)*.c

clean :
	rm *.o

cleanTest :
	rm test

cleanMain :
	rm main

