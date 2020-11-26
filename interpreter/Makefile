#
# In order to execute this "Makefile" just type "make"
#	A. Delis (ad@di.uoa.gr)
#

OBJS	= main.o Packageable.o Package.o Command.o Parser.o
SOURCE	= main.cpp Packageable.cpp Package.cpp Command.cpp Parser.cpp
HEADER	= Packageable.hpp Package.hpp Command.hpp Parser.hpp
OUT	= executable
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread -lm
# -g option enables debugging mode 
# -c flag generates object code for separate files


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

executable: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<<
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++17

Packageable.o: Packageable.cpp
	$(CC) $(FLAGS) Packageable.cpp -std=c++17

Package.o: Package.cpp
	$(CC) $(FLAGS) Package.cpp -std=c++17

Command.o: Command.cpp
	$(CC) $(FLAGS) Command.cpp -std=c++17

Parser.o: Parser.cpp
	$(CC) $(FLAGS) Parser.cpp -std=c++17


# clean house
clean:
	rm -f $(OBJS) $(OUT)

# run the program
run: $(OUT)
	./$(OUT)