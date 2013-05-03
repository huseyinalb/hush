cc = gcc
SRC_FILES = tree.c treenode.c list.c listnode.c
FLAGS = -g -Wall
OBJECTS = $(SRC_FILES:%.c=%.o)
all: objects
	ar rv datatypes.a $(OBJECTS)
objects: $(SRC_FILES)
	$(cc) -c $(FLAGS) $(SRC_FILES)
clean:
	rm -f *.o datatypes.a
