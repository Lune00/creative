CC = g++
DEBUG = -g
CFLAGS = -c -Wall $(DEBUG) 
LFLAGS= -Wall $(DEBUG)
INC_PATH  = ../include
OBJS = generateur-perso-fiche.o arithmetique.o displaytexte.o datalist.o

gen: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o gen

generateur-perso-fiche.o: generateur-perso-fiche.cpp arithmetique.h functions.h displaytexte.h datalist.h 	
	$(CC) $(CFLAGS) generateur-perso-fiche.cpp

arithmetique.o: arithmetique.cpp arithmetique.h
	$(CC) $(CFLAGS) arithmetique.cpp	

displaytexte.o: displaytexte.cpp displaytexte.h functions.h datalist.h arithmetique.h
	$(CC) $(CFLAGS) displaytexte.cpp

datalist.o: datalist.cpp datalist.h
	$(CC) $(CFLAGS) datalist.cpp


clean:
	\rm *.o *~ gen