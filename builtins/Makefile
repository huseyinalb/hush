CC = gcc
SRC_FILES = builtins.c cd.c
FLAGS = -g -Wall
OBJECTS = $(SRC_FILES:%.c=%.o)
all: objects
	ar rv builtins.a $(OBJECTS)
objects: $(SRC_FILES)
	$(CC) -c $(FLAGS) $(SRC_FILES)
clean:
	rm -f *.o *.out builtins.a
test_all: CC += -DDEBUG -DTEST -g
test_all: all
	ls test*.c| xargs -I%file sh -c '{ $(CC) %file builtins.a -o %file.out; ./%file.out; }'
