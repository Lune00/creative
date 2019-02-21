#Variables
CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=maison
#Liste des fichiers sources
SRC= $(wildcard *.cpp)
#Liste des fichiers objets correspondants
OBJ=$(SRC:.cpp=.o)

#cible: dependances
#	commandes
#Si dépendance est plus recente que cible alors commandes sont executées

#Pour chaque regle:
# $@ -> nom de la cible
# $^ -> nom premiere dépendance
# $< -> liste despendances
# $? -> liste dep plus recentes que cible
# $* -> nom fichier sans suffixe

all:: $(EXEC)

#Linkage:
maison: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

#Dependances:
#On doit toujours manuellement ajouter les dependances implicites
main.o: maison.h

#Compilation:
%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

#En placant un @ devant une commande elle devient silencieuse:
clean:
	@rm -rf *.o
mrproper: clean
	@rm -rf $(EXEC)
