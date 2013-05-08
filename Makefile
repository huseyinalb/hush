cc = gcc
SRC_FILES = main.c
ARCHIVES = datatypes/datatypes.a builtins/builtins.a parser/parser.a
FLAGS = -g -Wall
OBJECTS = $(SRC_FILES:%.c=%.o)
all: datatypes.a builtins.a parser.a objects
	$(cc) $(FLAGS) $(OBJECTS) $(ARCHIVES) -o mangalsh
datatypes.a:
	make -C datatypes
builtins.a:
	make -C builtins
parser.a:
	make -C parser
objects: $(SRC_FILES)
	$(cc) -c $(FLAGS) $(SRC_FILES)
test_all: CC += -DDEBUG -g
test_all:
	make -C datatypes test_all
clean:
	make -C datatypes clean
	make -C builtins clean
	make -C parser clean
	rm -f *.o hush
