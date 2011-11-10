CXX=g++
CXXFLAGS=-I.. -D_DEBUG -g
LDLIBS=

BINARIES=djikstra.o RectangularGraph.o

%.exe:%.cpp
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


all: $(BINARIES)

clean:
	del /q $(BINARIES)

djikstra.o:CXXFLAGS+=-D_VERBOSE_DEBUG
djikstra.o: graph.hpp pathfinding.hpp djikstra.cpp

RectangularGraph.o: graph.hpp RectangularGraph.hpp


