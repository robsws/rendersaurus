COMPILER = g++
OBJECTS = main.o
DEBUG = -g
COMPILER_FLAGS = -Wall -c $(DEBUG)
LINKER_FLAGS = -Wall $(DEBUG)

demo: $(OBJS) 
	$(COMPILER) $(LINKER_FLAGS) $(OBJECTS) -o demo

main.o: src/main.cpp
	$(COMPILER) $(COMPILER_FLAGS) src/main.cpp

clean:
	rm -f $(OBJECTS) demo