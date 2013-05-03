cc = gcc
SRC_FILES = main.c
ARCHIVES = datatypes/datatypes.a
FLAGS = -g -Wall
OBJECTS = $(SRC_FILES:%.c=%.o)
all: datatypes.a objects
	$(cc) $(FLAGS) $(OBJECTS) $(ARCHIVES) -o hush
datatypes.a:
	make -C datatypes
objects: $(SRC_FILES)
	$(cc) -c $(FLAGS) $(SRC_FILES)
clean:
	make -C datatypes clean
	rm -f *.o hush
