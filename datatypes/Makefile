CC = gcc
SRC_FILES = tree.c treenode.c list.c listnode.c hashmap.c hashmapnode.c
FLAGS = -g -Wall
OBJECTS = $(SRC_FILES:%.c=%.o)
all: objects
	ar rv datatypes.a $(OBJECTS)
objects: $(SRC_FILES)
	$(CC) -c $(FLAGS) $(SRC_FILES)
clean:
	rm -f *.o *.out datatypes.a
test_all: CC += -DDEBUG -g
test_all: all
	ls test*.c| xargs -I%file sh -c '{ $(CC) %file datatypes.a -o %file.out; ./%file.out; }'
