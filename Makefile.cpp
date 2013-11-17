#Directories and files
SRCDIR=src/
INCDIR=inc/
LIBDIR=lib/
CPPFILES=$(wildcard $(SRCDIR)*.cpp)
_OFILES=$(patsubst %.cpp,%.cpp.o,$(CPPFILES))
ODIR=obj/
OFILES = $(patsubst src/%,$(ODIR)%,$(_OFILES))
PRECOMPILEDOFILES=
INC=-I $(INCDIR)
LIBPATH=-L lib
LIB=
TARGET=final

#compilers, linkers etc
CPP=g++
CC=gcc
LD=g++

#compiling and linking options
LDFLAGS=
CFLAGS=-std=c++11 $(INC) -Wall

.PHONY: all clean debug profile

all: CFLAGS+=-O2
all: pre-build $(TARGET)

debug: CFLAGS +=-DDEBUG -g 
debug: LDFLAGS +=-g 
debug: pre-build $(TARGET)

profile: CFLAGS +=-DPROFILE -g -pg 
profile: LDFLAGS +=-g -pg 
profile: pre-build $(TARGET)


pre-build: 
	@mkdir -p $(ODIR)
	 
obj/%.cpp.o: src/%.cpp
	$(CPP) $(CFLAGS) -o $@ -c $< 

$(TARGET): $(OFILES) $(PRECOMPILEDOFILES)
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIB) 

clean:
	@rm -rf $(ODIR)
	@rm $(TARGET)
