bibliotheque: bibliotheque.o verbe.o accord.o
	g++ -o bibliotheque bibliotheque.o verbe.o accord.o

bibliotheque.o: bibliotheque.cpp verbe.hpp accord.hpp
	g++ -Wall -c bibliotheque.cpp

verbe.o: verbe.cpp verbe.hpp
	g++ -Wall -c verbe.cpp

accord.o: accord.cpp accord.hpp
	g++ -Wall -c accord.cpp

clean:
	rm -f *~

