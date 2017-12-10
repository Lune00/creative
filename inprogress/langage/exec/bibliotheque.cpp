#include<list>
#include<cmath>
#include<algorithm>
#include<string>
#include<vector>
#include<map>

#include "verbe.hpp"
#include "accord.hpp"

using namespace std;

int main()
{

  Verbe mot("hair");
  Verbe mot2("mourir");
  Verbe mot3("s'envoler");

  cerr<<"On conjuguer le verbe : "<<mot.getInfinitif()<<endl;
  cerr<<"Il "<<mot.conjuguer("il",present)<<endl;
  cerr<<"Il "<<mot.conjuguer("il",futur)<<endl;
  cerr<<"On conjugue le verbe : "<<mot2.getInfinitif()<<endl;
  cerr<<"Il "<<mot2.conjuguer("il",present)<<endl;

  NomC nc("bijou",'m');
  NomC nc1("eau",'f');
  NomC nc2("cheval",'m');
  NomC nc3("vis",'f');
  NomC nc4("ciel",'m');
  NomC nc5("festival",'m');
  NomC nc6("oiseau",'m');

  cerr<<"Des "<<nc1.accorder("des")<<endl;
  cerr<<"Des "<<nc3.accorder("des")<<endl;
  cerr<<"Des "<<nc6.accorder("des")<<" "<<mot3.conjuguer("ils",futur)<<" dans les "<<nc4.accorder("les")<<"."<<endl;
  cerr<<"Ils nous "<<mot.conjuguer("ils",present)<<"."<<endl;

  return 0;
}
