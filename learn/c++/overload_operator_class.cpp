#include<iostream>
#include<vector>

using namespace std;


class A{

  private:
    int value_;

  public:
    A();
    A(int value) { value_ = value ;}
    ~A(){};
    int value() const { return value_ ;}
};

inline bool operator==(const A& a, const A& b) { cout<<"operator called"<<endl; return a.value() == b.value() ; }


int main(){

  //Operator:
  A a(3);
  A b(3);

  if( a == b ) cout << " a = b"<<endl;

  A* c = new A(3);
  A* d = new A(3);

  //Pas possible d'overloader == entre pointeurs (ils ont deja leur == operator, il faut le déférencer
  if( *c == *d ) cout << " c = d"<<endl;

  A* e = new A(1);
  A* f = new A(2);
  A* g = new A(3);

  vector<A*> values;

  values.push_back(e);
  values.push_back(g);
  values.push_back(f);

  std::vector<A*>::const_iterator it = values.begin();

  while( it != values.end()){
    if( *(*it) == (*g)) {
      cout<<"trouvé"<<endl;
      break;
    }
    it++;
  }
  return 0 ;
}
