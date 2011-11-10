CXX=g++
CXXFLAGS=-I.. -D_DEBUG
LDLIBS=

BINARIES=test_r1.exe test_r2.exe

%.exe:%.cpp
	$(MAKE) -C .. 
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@


test_r2.exe: CXXFLAGS+=-g
test_r2.exe: LDLIBS+=../RectangularGraph.o ../djikstra.o
test_r2.exe:

debug: test_r2.exe
	gdb --args test_r2.exe --start-x 2 --start-y 8 --end-x 9 --end-y 4

argtest: test_r2.exe
	test_r2 --rows 20 --columns 20 --start-x 5 --start-y 8 --end-x 13 --end-y 18

test_r1.exe: CXXFLAGS+=-g
test_r1.exe: LDLIBS+=../RectangularGraph.o ../djikstra.o
test_r1.exe: test_r1.cpp ../graph.hpp


#../djikstra.o:CXXFLAGS+=-D_VERBOSE_DEBUG

clean:
	cmd /c del /q $(BINARIES)

../RectangularGraph.o: libs

../djikstra.o: libs


# keep the libraries up-to-date
GrLIBS=../djikstra.o ../RectangularGraph.o
libs:
	$(MAKE) -C ..