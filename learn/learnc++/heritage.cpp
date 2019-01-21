#include<iostream>
#include<string>
#include<vector>

using namespace std;


class Animal{
  public:
    Animal(){taille_ = petit; cout<<"Animal apparait: ";}
    virtual ~Animal(){};
    void virtual sayHello() = 0 ;
    void virtual boire(){cout<<"*boit*"<<endl;}
  protected:
    //Accesible directement par les classes filles
    enum Taille {petit,grand};
    Taille taille_;
  private:
};

class Chat : public Animal{
  public:
    Chat(){cout<<"c'est un chat"<<endl;}
    ~Chat(){cout<<"*le chat disparait"<<endl;}
    void sayHello() {cout<<"Miaou!"<<endl;}
    void boire() {cout<<"*le chat boit du lait ("<<taille_<<")"<<endl;}
    void chasser() {cout<<"*le chat chasse."<<endl;}
    void changerTaille();
  private:
};

void Chat::changerTaille(){
  if(taille_ == petit){
    taille_ = grand;
  }
  else
    taille_ = petit;
  return;
}

class Chien : public Animal{
  public:
    void sayHello() {cout<<"Waf!"<<endl;}
    void boire() {cout<<"*le chien boit de l'eau"<<endl;}
  private:
};


void makeSayJello(Animal * a){
  a->sayHello();
  a->boire();

  //Pour appeler une méthode de child (chat ou chien) il faut caster:
  //Child * p = dynamic_cast<Child *>(pParent)
  //dynamic_cast verifie: si pParent peut etre cast en securité vers Child* 
  //il renvoie l'adresse de l'objet s'il peut , 0 sinon (un pointeur Null)

  //"The need for dynamic_cast generally arises because we want perform derived class operation 
  //on a derived class object, but we have only a pointer-or reference-to-base."


  //Un chat est un animal mais un animal n'est pas forcement un chat

  //la ligne du dessous verifie que l'animal est un chat
  Chat * p = dynamic_cast<Chat *>(a) ;
  if(p){
    cout<<"C'est bien un chat!"<<endl;
    p->chasser();
  }
  else
    cout<<"C'est pas un chat!"<<endl;
  return;
}

//Impossible car Animal est une classe abstraite
//void makeSayHello(Animal a){
//  a.sayHello();
//  return;
//}

int main(){


  cout<<"Hello heritage!"<<endl;

  Animal * animal = new Chat();
  makeSayJello(animal);
  Animal * animal2 = new Chien();
  makeSayJello(animal2);

  delete animal;


  return 0;
}
