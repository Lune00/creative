#Options
CXX=clang++ -std=c++11 -stdlib=libc++
INC_PATH=include
SRC_PATH=src
OBJ_PATH=obj
CXXFLAGS= -W -Wall -pedantic -Wno-c++98-compat -I$(INC_PATH)

#En attendant que ce soit une librairie SOURCE_USER est le fichier main de l'utilisateur
SOURCE_USER=main
EXEC=test
LIBS=-lconfig++

#Liste des fichiers sources:
SRC=$(wildcard $(SRC_PATH)/*.cpp)
#Liste des fichiers objets correspondants:
OBJ = $(SRC:$(SRC_PATH)/%.cpp=$(OBJ_PATH)/%.o)
all: $(EXEC)

#Linkage:
$(EXEC): $(OBJ) $(SOURCE_USER).o
	$(CXX) $^ -o $@ $(LIBS)


$(OBJ_PATH)/chromosomes.o : $(INC_PATH)/gene.h
$(OBJ_PATH)/chromosomes.o : $(INC_PATH)/gene.h

#Compilation:

#1) fichier main (fichier utilisateur a la racine du projet, comme ca on peut utiliser les sources en etant ailleurs)
$(SOURCE_USER).o: $(SOURCE_USER).cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

#2) sources de la bibliotheque
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

#Pas encore dependance automatique (refabrication du .o si dependance header modifié)
#Dependances manuelles:
main.o : $(INC_PATH)/rng.h
main.o : $(INC_PATH)/config.h
main.o : $(INC_PATH)/feature.h

#Pas encore tres clair pour moi PHONY...
.PHONY: clean allclean

clean:
	@rm -rf $(OBJ_PATH)/*.o main.o test

allclean: clean
	@rm -rf $(EXEC)

