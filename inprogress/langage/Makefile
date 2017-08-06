bibliotheque: bibliotheque.o verbe.o
	g++ -o bibliotheque bibliotheque.o verbe.o

bibliotheque.o: bibliotheque.cpp verbe.hpp
	g++ -Wall -c bibliotheque.cpp

verbe.o: verbe.cpp verbe.hpp
	g++ -Wall -c verbe.cpp

clean:
	rm -f *~

