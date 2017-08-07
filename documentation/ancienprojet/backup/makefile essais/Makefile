CC = g++
DEBUG = -g
CFLAGS = -c -Wall $(DEBUG) 
LFLAGS= -Wall $(DEBUG)
INC_PATH  = ../include
OBJS = generator.o functions.o arithmetique.o displaytexte.o

gen: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o gen

generator.o: generateur-perso-fiche.cpp arithmetique.h functions.h displaytexte.h 	
	$(CC) $(CFLAGS) generateur-perso-fiche.cpp

functions.o: functions.cpp arithmetique.h displaytexte.h functions.h
	$(CC) $(CFLAGS) functions.cpp

arithmetique.o: arithmetique.cpp arithmetique.h functions.h displaytexte.h
	$(CC) $(CFLAGS) arithmetique.cpp	

displaytexte.o: displaytexte.cpp functions.h displaytexte.h functions.h
	$(CC) $(CFLAGS) displaytexte.cpp

clean:
	\rm *.o *~ gen