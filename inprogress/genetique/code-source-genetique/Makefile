#Options
CC=g++
INC_PATH=include
SRC_PATH=src
LIB_PATH=lib

CFLAGS=-W -Wall -ansi -pedantic -I$(INC_PATH)
LFLAGS=

EXEC=test

#Liste des fichiers sources:
SRC=$(wildcard $(SRC_PATH)/*.cpp)
#Liste des fichiers objets correspondants:
OBJ=$(SRC:.cpp=.o);

all: $(EXEC)

#Linkage:
$(EXEC): $(OBJ)
	$(CC) -o $@ -c $^ $(CFLAGS)

#Dependances:

#Compilation:
%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean allclean

clean:
	@rm -rf *.o

allclean: clean
	@rm -rf $(EXEC)

