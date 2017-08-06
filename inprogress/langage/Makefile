bibliotheque: bibliotheque.o verbe.o accord.o adjectif.o categorie.o
	g++ -o bibliotheque bibliotheque.o verbe.o accord.o adjectif.o categorie.o

bibliotheque.o: bibliotheque.cpp verbe.hpp accord.hpp adjectif.hpp
	g++ -Wall -c bibliotheque.cpp

categorie.o: categorie.cpp categorie.hpp accord.hpp verbe.hpp adjectif.hpp
	g++ -Wall -c categorie.cpp

verbe.o: verbe.cpp verbe.hpp
	g++ -Wall -c verbe.cpp

accord.o: accord.cpp accord.hpp
	g++ -Wall -c accord.cpp

adjectif.o: adjectif.cpp adjectif.hpp
	g++ -Wall -c adjectif.cpp

clean:
	rm -f *~

