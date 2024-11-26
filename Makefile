# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++17

# Targets
TARGET = biquadris
SOURCES = main.cc commandinterpreter.cc block.cc cell.cc board.cc iblock.cc
HEADERS = commandinterpreter.h block.h cell.h board.h iblock.h
OBJECTS = $(SOURCES:.cc=.o)

# Build the main executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile .cc files to .o files
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build
clean:
	rm -f $(TARGET) $(OBJECTS)
