CXX=g++

CPPFLAGS=-I..

test_r1.exe: CXXFLAGS=-g
test_r1.exe: test_r1.cpp ../graph.hpp ../RectangularGraph.hpp ../djikstra.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LOADLIBES) $(LDLIBS) $^ -o $@