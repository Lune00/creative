#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Mot{

  //Private mais accessible aux classes filles
  protected:
    //base du mot
    std::string lemme_;

  public:
    Mot(std::string lemme) { lemme_ = lemme; }
    //Un constructeur n'est jamais virtuel
    Mot(){lemme_="chocolat";};
    //Un destructeur est toujours virtuel
    virtual ~Mot(){cout<<"Mot destructor."<<endl;};

    std::string getlemme() const { return lemme_;} 
    //Resolution dynamique: fonction virtuelle uniquement dans la declaration de la fonction
    virtual void affiche() const { cout<<"Le lemme du mot est "<<lemme_;}
    //Methode virtuelle pure: la classe Mot est a present virtuelle
    virtual std::string nature() const = 0 ;


};

//Adjectif herite de Mot
class Adjectif: public Mot{

  private:
    //Genre: masculin m - feminin f
    char genre_;
    //Nombre: singulier s - pluriel p
    char nombre_;

  public:
    Adjectif(std::string lemme): Mot(lemme){};
    //Appel destructeur classe fille puis automatiquement appel destructeur classe mere
    virtual ~Adjectif(){cout<<"Adjectif destructor."<<endl;} ;
    //Masquage:           Appel de la fonction de la classe mere puis specificité
    //Ici virtual n'est pas obligatoire car auto virtual heritee de Mot mais on peut le mettre pour se souvenir
    virtual void affiche() const {Mot::affiche(); cout<<": c'est un "<<nature()<<"."<<endl;}
    virtual std::string nature() const { return  "adjectif" ; }

    void accorder() const {cout<<"Je suis un adjectif donc je peux m'accorder"<<endl;}


};

//Class Verbe herite de Mot
class Verbe: public Mot{

  private:
    int groupe_;

  public:
    Verbe(std::string lemme): Mot(lemme){};
    virtual ~Verbe(){cout<<"Verbe destructor."<<endl;};
    void accorder();
    virtual void affiche() const {Mot::affiche(); cout<<": c'est un "<<nature()<<"."<<endl;}
    virtual std::string nature() const { return  "verbe" ; }
    void conjuguer () const { cout<<"Je suis un verbe donc je peux me conjuguer"<<endl;}
};

void presenter(const Mot* m){
  m->affiche();
}


int main(){

  cout<<"Heritage test"<<endl;

  vector<Mot*> liste;
  liste.push_back(new Adjectif("beau"));
  liste.push_back(new Verbe("manger"));

  for(vector<Mot*>::const_iterator it = liste.begin(); it != liste.end(); it++){
    presenter(*it);
    (*it)->affiche();
    //Downcast pointer to derived class to call derived type function
    if(Adjectif* p = dynamic_cast<Adjectif*>(*it)) p->accorder();
    if(Verbe* p = dynamic_cast<Verbe*>(*it)) p->conjuguer();
    delete *it;
  }

  return 0;

}
