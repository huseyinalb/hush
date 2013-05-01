cc = gcc -g
SRC_FILES=tree.c treenode.c list.c listnode.c main.c
FLAGS=-g -Wall
OBJECTS=$(SRC_FILES:%.c=%.o)
all: $(OBJECTS)
	$(cc) $(OBJECTS) $(FLAGS) -o main.out
objects: $(SRC_FILES)
	$(cc) -c $(FLAGS) $(SRC_FILES)
clean:
	rm *.o *.out
