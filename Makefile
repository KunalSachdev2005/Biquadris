# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++17

# Targets
TARGET = biquadris
SOURCES = main.cc commandinterpreter.cc
HEADERS = commandinterpreter.h
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
