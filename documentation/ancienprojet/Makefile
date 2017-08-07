CC = g++
DEBUG = -g
CFLAGS = -c -Wall $(DEBUG) 
LFLAGS= -Wall $(DEBUG)
INC_PATH  = ../include

OBJS = generateur-perso-fiche.o arithmetique.o datalist.o functions.o name-generator.o personnage.o visage.o initperso.o story-generator.o

gen: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o gen

generateur-perso-fiche.o: generateur-perso-fiche.cpp arithmetique.h
	$(CC) $(CFLAGS) generateur-perso-fiche.cpp

name-generator.o: name-generator.cpp name-generator.h datalist.h arithmetique.h
	$(CC) $(CFLAGS) name-generator.cpp

initperso.o: initperso.cpp initperso.h datalist.h arithmetique.h
	$(CC) $(CFLAGS) initperso.cpp

personnage.o: personnage.cpp personnage.h visage.h functions.h initperso.h
	$(CC) $(CFLAGS) personnage.cpp

datalist.o: datalist.cpp datalist.h
	$(CC) $(CFLAGS) datalist.cpp

arithmetique.o: arithmetique.cpp arithmetique.h
	$(CC) $(CFLAGS) arithmetique.cpp

functions.o: functions.cpp arithmetique.h
	$(CC) $(CFLAGS) functions.cpp

visage.o: visage.cpp visage.h initperso.h functions.h
	$(CC) $(CFLAGS) visage.cpp

story-generator.o: story-generator.cpp story-generator.h datalist.h
	$(CC) $(CFLAGS) story-generator.cpp
	
clean:
	rm *.o gen