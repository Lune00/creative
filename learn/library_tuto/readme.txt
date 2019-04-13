iiCréer une librairie dynamique:

1) Faire les .o: g++ -c *.cpp
2) Les lier avec g++ -shared *.o libXXXX.so

La librairie libXXXX.so est crée. Ici libHouse.so 

Utilisation: avec une librairie libHouse.so et un main.cpp qui l'appelle:

//Donner le repertoir où trouver -L/ et le nom de la librairie -lHouse

1) Cree un fichier objet de main.cpp: g++ -c main.cpp. 

2) Linker le fichier main.o avec la librairie: g++ -L$(pwd) -lHouse main.o 
