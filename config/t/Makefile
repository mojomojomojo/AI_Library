CXX=g++
CXXFLAGS=-I.. 
LDFLAGS=-L..
LDLIBS=

BINARIES=djikstra.o RectangularGraph.o

%.exe:%.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


get_test.exe:LDLIBS=../get.o
get_test.exe: