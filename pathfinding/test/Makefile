CXX=g++
CXXFLAGS=-I.. -D_DEBUG
LDLIBS=

BINARIES=test_r1.exe

%.exe:%.cpp
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

test_r1.exe: CXXFLAGS+=-g
test_r1.exe: test_r1.cpp ../graph.hpp ../RectangularGraph.hpp ../djikstra.o


#../djikstra.o:CXXFLAGS+=-D_VERBOSE_DEBUG

clean:
	cmd /c del /q $(BINARIES)