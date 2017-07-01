COMPILER = g++
OBJECTS = main.o xterm_display.o fragment_buffer.o colour.o fragment.o vector.o square_matrix.o
DEBUG = -g
COMPILER_FLAGS = -Wall -std=c++14 -I/usr/include/ -I../include/ -c $(DEBUG)
LINKER_FLAGS = -Wall $(DEBUG)

demo: $(OBJECTS) 
	$(COMPILER) $(LINKER_FLAGS) $(OBJECTS) -o demo -lncursesw

main.o: ../src/main.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../src/main.cpp

xterm_display.o: ../src/xterm_display.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../src/xterm_display.cpp

fragment_buffer.o: ../src/fragment_buffer.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../src/fragment_buffer.cpp

colour.o: ../src/colour.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../src/colour.cpp	

fragment.o: ../src/fragment.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../src/fragment.cpp	

vector.o: ../src/vector.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../src/vector.cpp

square_matrix.o: ../src/square_matrix.cpp
	$(COMPILER) $(COMPILER_FLAGS) ../src/square_matrix.cpp

clean:
	rm -f $(OBJECTS) demo