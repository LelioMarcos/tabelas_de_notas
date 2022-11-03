CC = gcc
FLAGS = -Wall -std=c99
NAME_ZIP = trabalho2_lelio.zip
BIN = ./torneio_alunos

all: media

media: readline.o aluno.o main.o
	$(CC) $(FLAGS) *.o -o $(BIN)

main.o: main.c aluno.h
	$(CC) $(FLAGS) -c main.c

aluno.o: aluno.h aluno.c
	$(CC) $(FLAGS) -c aluno.c

readline.o: readline.c readline.h
	$(CC) $(FLAGS) -c readline.c

run:
	$(BIN)

zip:
	zip $(NAME_ZIP) *.c *.h Makefile

clean:
	rm $(BIN) *.o $(NAME_ZIP)