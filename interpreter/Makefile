OBJS	= ActionBundle.o Argument.o Callable.o Command.o Debug.o Exceptions.o Instruction.o Interpreter.o Package.o Packageable.o Parser.o DataBuilder.o LZBool.o LZDataType.o LZFloat.o LZInteger.o LZPrimitive.o LZString.o LizzyApi.o main.o
SOURCE	= ActionBundle.cpp Argument.cpp Callable.cpp Command.cpp Debug.cpp Exceptions.cpp Instruction.cpp Interpreter.cpp Package.cpp Packageable.cpp Parser.cpp DataBuilder.cpp LZBool.cpp LZDataType.cpp LZFloat.cpp LZInteger.cpp LZPrimitive.cpp LZString.cpp LizzyApi.cpp main.cpp
HEADER	= ActionBundle.hpp Argument.hpp Callable.hpp Command.hpp Debug.hpp Exceptions.hpp Instruction.hpp Interpreter.hpp Package.hpp Packageable.hpp Parser.hpp DataBuilder.hpp LZBool.hpp LZDataType.hpp LZFloat.hpp LZInteger.hpp LZPrimitive.hpp LZString.hpp LizzyApi.hpp
OUT	= lizzy
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++2a
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

lizzy: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)
ActionBundle.o: ActionBundle.cpp
	$(CC) $(FLAGS) ActionBundle.cpp 

Argument.o: Argument.cpp
	$(CC) $(FLAGS) Argument.cpp 

Callable.o: Callable.cpp
	$(CC) $(FLAGS) Callable.cpp 

Command.o: Command.cpp
	$(CC) $(FLAGS) Command.cpp 

Debug.o: Debug.cpp
	$(CC) $(FLAGS) Debug.cpp 

Exceptions.o: Exceptions.cpp
	$(CC) $(FLAGS) Exceptions.cpp 

Instruction.o: Instruction.cpp
	$(CC) $(FLAGS) Instruction.cpp 

Interpreter.o: Interpreter.cpp
	$(CC) $(FLAGS) Interpreter.cpp 

Package.o: Package.cpp
	$(CC) $(FLAGS) Package.cpp 

Packageable.o: Packageable.cpp
	$(CC) $(FLAGS) Packageable.cpp 

Parser.o: Parser.cpp
	$(CC) $(FLAGS) Parser.cpp 

DataBuilder.o: DataBuilder.cpp
	$(CC) $(FLAGS) DataBuilder.cpp 

LZBool.o: LZBool.cpp
	$(CC) $(FLAGS) LZBool.cpp 

LZDataType.o: LZDataType.cpp
	$(CC) $(FLAGS) LZDataType.cpp 

LZFloat.o: LZFloat.cpp
	$(CC) $(FLAGS) LZFloat.cpp 

LZInteger.o: LZInteger.cpp
	$(CC) $(FLAGS) LZInteger.cpp 

LZPrimitive.o: LZPrimitive.cpp
	$(CC) $(FLAGS) LZPrimitive.cpp 

LZString.o: LZString.cpp
	$(CC) $(FLAGS) LZString.cpp 

LizzyApi.o: LizzyApi.cpp
	$(CC) $(FLAGS) LizzyApi.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)