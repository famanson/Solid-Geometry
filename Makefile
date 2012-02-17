# Makefile to compile simple svlis applications

CXX = g++
CXXFLAGS = -DSV_UNIX -pedantic -Wno-write-strings -I/usr/include/svlis
OPTFLAGS = -g -O3
LIBS = -lsvlis 
PROGRAMS = CSGmug

LIBS = -L/usr/lib64 -L/lib64 -L$(HOME)/SvLiS/lib -lsvlis -lglut -lGLU -lGL -lpthread

CXXFLAGS = -DSV_UNIX -pedantic -Wno-write-strings -I/usr/include/svlis -I$(HOME)/SvLiS/include


.SUFFIXES: .cxx .o

all: $(PROGRAMS)

.PRECIOUS: %.o
.cxx.o:
	$(CXX) -c $(OPTFLAGS) $(CXXFLAGS) -o $@ $<

.o:
	$(CXX) $(OPTFLAGS) -o $@ $< $(LIBS)
clean:
	/bin/rm -f *.o *.mod *.ppm *~
cleanest: clean
	/bin/rm -f CSGmug difference

