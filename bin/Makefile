COMPILER = g++
OBJECTS = main.o
DEBUG = -g
COMPILER_FLAGS = -Wall -I/usr/include/ -c $(DEBUG)
LINKER_FLAGS = -Wall $(DEBUG)

demo: $(OBJECTS) 
	$(COMPILER) $(LINKER_FLAGS) $(OBJECTS) -o demo -lncursesw

main.o: ../src/main.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../src/main.cpp

clean:
	rm -f $(OBJECTS) demo