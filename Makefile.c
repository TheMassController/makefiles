CC=gcc
SRCDIR=src/
CFILES=$(wildcard $(SRCDIR)*.c)
_OFILES=$(patsubst %.c,%.o,$(CFILES))
INC= -I inc/
LIB=
LIBDIR= -L lib/
#LDFLAGS=-s $(LIB)
LDFLAGS=
CFLAGS=-Wall -std=c99 $(INC)
ODIR=obj/
OFILES = $(patsubst src/%,$(ODIR)%,$(_OFILES))
TARGET=final

.PHONY: all clean debug

all: pre-build $(TARGET)
all: CFLAGS += -O2 -fopenmp
all: LDFLAGS += -fopenmp

debug: CFLAGS +=-DDEBUG -g -pg -fopenmp
debug: LDFLAGS +=-g -pg -fopenmp
debug: pre-build $(TARGET)

profile: CFLAGS +=-DPROFILE -g -pg -fopenmp
profile: LDFLAGS +=-g -pg -fopenmp
profile: pre-build $(TARGET)


pre-build:
	@mkdir -p $(ODIR)
	 
$(ODIR)%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(TARGET): $(OFILES) 
	$(CC) -o $@ $^ $(LDFLAGS)	

clean:
	@rm -rf $(ODIR)
	@rm $(TARGET)
