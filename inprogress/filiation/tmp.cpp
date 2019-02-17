#include<random>
#include<iostream>
#include<fstream>

//Test de la bibliotheque random: distribution normale, uniforme
//Ouverture d'un fichier et selection d'une ligne au hasard

using namespace std;


int main(){

  std::random_device rd;
  std::default_random_engine generator(rd());

  //Chercher une ligne au hasard dans un fichier syllabe avec l'appel d'une lettre (chercher dans la categorie correspondante):o
  //@START:a#/* -> @END si "a" est appelé, ensuite prendre une syllabe au hasard

  string letter_called = "b";
  string balise_called = "@START:"+letter_called+"#/*";
  string balise_end = "@END";
  bool inside = false ;

  ifstream myfile("data/noms/endsyll.txt");
  string line;
  std::vector<std::string> lines;
  if(myfile){

    while(getline(myfile,line)){
      if(line == balise_end ) inside = false ;
      if(inside) lines.push_back(line);
      if(line == balise_called) inside = true ;
      }
    myfile.close();
  }

  for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end() ; it++){
    cout<<*it<<endl;
  }


  //Distribution entre 0 et lines.size()-1
  //std::uniform_int_distribution<int> distribution3(0,lines.size()-1);
  //int random_index = distribution3(generator);
  //cout<<lines[random_index]<<endl;

  return 0;
}
