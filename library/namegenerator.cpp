#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

//Le but est de générer des noms en utilisant les phonemes.
//On cree des chaines de phonemes qu'on remplit de templates pré-écrits
//On regarde ce que ca donne
//On fera la meme chose ensuite en utlisant des lettres et des chaines de markov

using namespace std;


class bib
{
  public:
    bib();
    static const string phon_table[];
    static const string voyelles[];
    static const string VOYELLES[];
    static const string consonnes[];
    static const string CONSONNES[];
};

const string bib::phon_table[]={ "a","i","y","u","o","O","e","E","°","2","9","5","1","@","§","3","j","8","w","p","b","t","d","k","g","f","v","s","z","Z","m","n","N","I","R","x","G","S","l"};

const string bib::voyelles[]= {"a","e","i","o","u","y"};
const string bib::VOYELLES[]= {"A","E","I","O","U","Y"};
const string bib::consonnes[]= {"z","r","t","p","q","s","d","f","g","h","j","k","l","m","w","x","v","b","n"};
const string bib::CONSONNES[]= {"Z","R","T","P","Q","S","D","F","G","H","J","K","L","M","W","X","V","B","N"};

int main(){

  cout<<"Hello, name-generator."<<endl;

  return 0;

}
