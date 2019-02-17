#include<random>
#include<iostream>
#include<fstream>

//Test de la bibliotheque random: distribution normale, uniforme
//Ouverture d'un fichier et selection d'une ligne au hasard

using namespace std;


int main(){

  //Engine: cree une sequence de nombres uniformement distribues
  //Random seed (random integer)
  std::random_device rd;
  std::default_random_engine generator(rd());
  //Defautls seed
  //std::default_random_engine generator;
  //Ou choose an integer seed
  //std::default_random_engine generator(5);


  //Distrbibution: prend la sequence de nombres en entree pour la distribuer selon une densite de proba definie:

  //Distribution en -1 et +1
  std::uniform_real_distribution<double> distribution1(-1.,1.);

  for(int i = 0 ; i < 10 ; i++){
    //cout<<distribution1(generator)<<endl;
  }

  //Distribution entre -5 et 5 de int
  std::uniform_int_distribution<int> distribution2(-5,5);

  for(int i = 0 ; i < 10 ; i++){
    //cout<<distribution2(generator)<<endl;
  }

  //Chercher une ligne au hasard dans un fichier texte:
  ifstream myfile("data/prenoms/prenom_homme.txt");
  string line;
  std::vector<std::string> lines;
  if(myfile){
    while(getline(myfile,line)){
      lines.push_back(line);
    }
    myfile.close();
  }

  //Distribution entre 0 et lines.size()-1
  std::uniform_int_distribution<int> distribution3(0,lines.size()-1);
  int random_index = distribution3(generator);
  cout<<lines[random_index]<<endl;

  return 0;
}
