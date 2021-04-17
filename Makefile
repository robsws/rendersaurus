COMPILER := g++
DEBUG := -g
COMPILER_FLAGS := -Wall -std=c++14 -I/usr/include/ -I./dependencies/include/ -I./include/ -c -fconcepts $(DEBUG)
LINKER_FLAGS := -Wall $(DEBUG)
LIBS := -lncursesw
BIN := ./bin
SRC := ./src
SRC_FILES := $(wildcard ./src/*.cpp)
SRC_FILES := $(filter-out ./src/main.cpp, $(SRC_FILES))
OBJECTS := $(patsubst ./src/%.cpp, ./bin/%.o, $(SRC_FILES))
TEST_OBJECTS := $(patsubst ./src/test/%.cpp,./bin/test/%.o,$(wildcard ./src/test/*.cpp))

demo: $(BIN)/demo

test: $(BIN)/tester

$(BIN)/demo: $(OBJECTS) $(BIN)/main.o
	$(COMPILER) $(LINKER_FLAGS) $(OBJECTS) $(BIN)/main.o -o $(BIN)/demo $(LIBS)

$(BIN)/tester: $(OBJECTS) $(TEST_OBJECTS)
	$(COMPILER) $(LINKER_FLAGS) $(OBJECTS) $(TEST_OBJECTS) -o $(BIN)/tester $(LIBS)
	$(BIN)/tester

$(BIN)/%.o: $(SRC)/%.cpp
	$(COMPILER) $(COMPILER_FLAGS) $< -o $@

$(BIN)/test/%.o: $(SRC)/test/%.cpp
	$(COMPILER) $(COMPILER_FLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(BIN)/demo $(BIN)/tester

debug:
	echo $(SRC_FILES)