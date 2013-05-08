CC = gcc
SRC_FILES = parser.c interpreter.c
FLAGS = -g -Wall
OBJECTS = $(SRC_FILES:%.c=%.o)
all: objects
	ar rv parser.a $(OBJECTS)
objects: $(SRC_FILES)
	$(CC) -c $(FLAGS) $(SRC_FILES)
clean:
	rm -f *.o *.out parser.a
test_all: CC += -DDEBUG -g
test_all: all
	ls test*.c| xargs -I%file sh -c '{ $(CC) %file parser.a -o %file.out; ./%file.out; }'
