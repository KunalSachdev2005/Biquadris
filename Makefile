# Compiler and flags # add -fsanitize=address after -g
CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -I/usr/include -L/usr/lib/X11
LDFLAGS = -lX11 #-lasan

# Targets
TARGET = biquadris
SOURCES = score.cc main.cc commandinterpreter.cc block.cc cell.cc board.cc iblock.cc jblock.cc sblock.cc tblock.cc zblock.cc lblock.cc oblock.cc level.cc level0.cc level1.cc level2.cc level3.cc level4.cc player.cc game.cc textdisplay.cc specialaction.cc blind.cc heavy.cc force.cc specialblock.cc graphicdisplay.cc xwindow.cc
HEADERS = score.h commandinterpreter.h block.h cell.h board.h iblock.h jblock.h sblock.h tblock.h zblock.h lblock.h oblock.h level.h level0.h level1.h level2.h level3.h level4.h player.h game.h textdisplay.h specialaction.h blind.h heavy.h force.h specialblock.h graphicdisplay.h xwindow.h
OBJECTS = $(SOURCES:.cc=.o)

# Build the main executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Compile .cc files to .o files
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build
clean:
	rm -f $(TARGET) $(OBJECTS)
