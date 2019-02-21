#Options
CXX=g++
INC_PATH=include
SRC_PATH=src
OBJ_PATH=obj

CXXFLAGS=-W -Wall -ansi -pedantic -I$(INC_PATH)

#En attendant que ce soit une librairie USERF est le fichier main de l'utilisateur
SOURCE_USER=main
EXEC=test

#Liste des fichiers sources:
SRC=$(wildcard $(SRC_PATH)/*.cpp)
#Liste des fichiers objets correspondants:
OBJ = $(SRC:$(SRC_PATH)/%.cpp=$(OBJ_PATH)/%.o)

all: $(EXEC)

#J'aimerais bien découpler le main (le placer a la racine) des autres sources, pour cela il faut ecrire une depandace speciale


#Linkage:
$(EXEC): $(OBJ) $(SOURCE_USER).o
	$(CXX) $^ -o $@ 

#Pas encore dependance automatique (refabrication du .o si dependance header modifié)
#Dependances manuelles:
$(OBJ_PATH)/main.o : $(INC_PATH)/rng.h
$(OBJ_PATH)/chromosome.o : $(INC_PATH)/gene.h
$(OBJ_PATH)/geneticien.o : $(INC_PATH)/gene.h
$(OBJ_PATH)/geneticien.o : $(INC_PATH)/chromosome.h

#Compilation:

#1) fichier main (fichier utilisateur a la racine du projet, comme ca on peut utiliser les sources en etant ailleurs)
$(SOURCE_USER).o: $(SOURCE_USER).cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

#2) sources de la bibliotheque
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

#Pas encore tres clair pour moi PHONY...
.PHONY: clean allclean

clean:
	@rm -rf $(OBJ_PATH)/*.o

allclean: clean
	@rm -rf $(EXEC)

