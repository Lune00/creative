#include<iostream>
#include<exception>

using namespace std;

//Je cree ma propre exception qui herite de la classe exception de la librairie standard

struct MyException : public exception {
  const char * what ( ) const throw () {
    return "Divide by zero, no no no" ;
  }
};

// divide a by b
double division (int a , int b) {

  if ( b == 0 ) {
    throw MyException() ;
  }
  return ((double)a/(double)b) ;
}

void make_division ( ) {
  double a = division ( 3 , 0 ) ;
}

int main() {

  cout << "Exceptions" << endl;

  try {
    //division( 2 ,0 ) ;
    make_division( ) ;
  }
  catch ( MyException& e ) {
    cerr << e.what() << endl;
    return EXIT_FAILURE ;
  }
  cerr << "Suite du programme " << endl;

  return 0 ;
}
