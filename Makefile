INCL    := $(wildcard include/*.h)
SRC     := src/main.c $(subst include/,,$(INCL:%.h=src/%.c))
OBJ     := $(subst src/,,$(SRC:%.c=bin/%.o))
EXE     := tempsreel
CC      := gcc
CFLAGS  := -ansi -Wall -Wextra
LIBPATH := -L.
LDFLAGS := -o $(EXE) $(LIBPATH) 
RM      := rm -f

all: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS)


bin/%.o: src/%.c include/%.h
	$(CC) -c $(CFLAGS) src/$*.c include/$*.h
	@mv $*.o bin/$*.o

bin/main.o: src/main.c
	$(CC) -c $(CFLAGS) src/main.c
	@mv main.o bin/main.o

$(OBJ): $(INCL)


clean:
	$(RM) $(EXE) $(OBJ) $(INCL:.h=.h.gch)