#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

#define mylibrary "mylibrary.txt"

using namespace std;

//Les doublons sont gérés (normalement) par la librairie elle-meme.
//Inutile donc en pratique de devoir traiter le cas des doublons ici.

//TODO
//Travailler sur infover (comment il fonctionne, comment on le splitte)
//Brancher le travail sur la conjugaison pour les verbes

//Creer des systmes de templates de phrase, vers
//Unite phrase, reliees les unes aux autres mais pas completement random
//Le registre doit etre attachee a des formes de vers, ou enchainements
//Reflechir a un systeme de probabilité conditionelle (je tire cette phrase, quelle chance de tirer l'autre)
//Commencer simple avec des paragraphes (4 phrases, vers max) fixés
//Ne pas oublier de partir du titre (un nom + un adjectif + un registre + un theme)
//Chercher synonymes, lies, et random

// Global functions
vector<std::string> parsestring(string, string);
vector<std::string> parsestring(string stringtoparse, string delimiter)
{
  vector<std::string> tokens;
  size_t pos = 0 ;
  string token;
  while( (pos = stringtoparse.find(delimiter)) != std::string::npos)
  {
    token = stringtoparse.substr(0, pos);
    stringtoparse.erase(0, pos + delimiter.length());
    tokens.push_back(token);
  }
  //On rajoute la derniere entree (ce qu'il reste)
  tokens.push_back(stringtoparse);

  //On retire les caracteres vides (dus au formatage en bash)
  //On place tous les caracteres vides a la fin de string et on se place au premier caractere vide
  //puis on supprime jusqu'a la fin (algorithm)
  for(vector<std::string>::iterator it = tokens.begin() ; it != tokens.end() ; it++ ){
    it->erase(std::remove_if(it->begin(), it->end(), ::isspace), it->end());
  }

  return tokens;
}


// Class / Templates
class Mot{

  private:
    string mot_;
    string lemme_;
    string phon_;
    string infover_;
    string genre_;
    string nombre_;
    int nsyll_;

    std::vector<string> grammar_;
    std::vector<string> registre_;
    std::vector<string> syn_;
    std::vector<string> ass_;
    std::vector<string> themes_;

  public:
    Mot();
    Mot(string);
    ~Mot();
    string getmot() const {return mot_;}
    string getgenre() {return genre_;}
    bool isNOM();
    bool startVoyelle();
    bool start(string);
    bool startAccent(); // Provisoire: si commence par accent, cast en int est negatif
    string getnombre() {return nombre_;}
    vector<string> getgrammar() { return grammar_;}
    vector<string> getthemes() { return themes_;}
    vector<string> getsynonymes() { return syn_;}
    string getlastphoneme() { return string (1,phon_.back());}
    string getfirstletter() { return string (1,mot_[0]);}
};

Mot::Mot(){};
//Constructeur d'un mot avec une entree de la bib
//L'ordre des champs est donne par le formatage de la librairie (libconfig.sh)
//Il doit y avoir 12 champs!
//Chaine vide pour nombre par defaut est SINGULIER (erreur au debut du formattage de la sortie de libconfig)
Mot::Mot(string entree)
{
  vector<string> tokens = parsestring(entree,"\t");

  if( tokens.size() < 12 ) {
    cerr<<"Entrée -"<<entree<<"- ne contient pas 12 champs!"<<endl;
    return;
  }
  mot_  = tokens[0];
  lemme_= tokens[1];
  phon_ = tokens[2];
  infover_ = tokens[4];
  genre_ = tokens[5];
  nombre_= tokens[6];

  if(tokens[7].length() == 0 ) 
  {
    nsyll_ = 0 ; //WTF, ca ne devrait pas etre autorise dans librairie!
  }
  else
  {
    nsyll_ = stoi(tokens[7]);
  }
  //Vecteur et split
  string delimiter = ";";
  grammar_ = parsestring(tokens[3],",");
  registre_ = parsestring(tokens[8],delimiter);
  syn_ = parsestring(tokens[9],delimiter);
  ass_ = parsestring(tokens[10],delimiter);
  themes_ = parsestring(tokens[11],delimiter);
};

Mot::~Mot(){};

//REnvoie vrai si le mot commence par lettre,faux sinon
bool Mot::start(string lettre)
{
  if(string(1,mot_[0])==lettre) return true;
  else
    return false;
}

bool Mot::startAccent()
{
  if( (int)mot_[0]<0 ) return true;
  else
    return false;
}

//Fonction qui renvoie vrai si le mot est un NOM
bool Mot::isNOM(){
  for(vector<string>::const_iterator it = grammar_.begin(); it != grammar_.end(); it++)
  {
    if (*it == "NOM") { return true ; break ;}
  }
  return false;
}

//On range des attributs et des fonctions generales dans une classe
//La classe bib est une classe Bibliotheque, elle sert a manipuler les Mots

class bib
{
  private:
    //Contient la bilbiotheque
    static std::vector<Mot> corpus_;
  public:
    bib();
    //Variables:
    static const string phon_table[];
    static const string grammar_table[];
    static const string voyelles[];
    static const string VOYELLES[];
    static const string consonnes[];
    static const string CONSONNES[];
    static const string definis[];
    static const string indefinis[];
    //Fonctions:
    //Initialise la librairie a partir du fichier mylib
    static void initlib(string mylib);

    // -- --------  -- - - 
    //Fonctions utlisateur:
    // -- --------  -- - - 
    static bool check_phonetique(string);
    static bool check_grammar(string);

    //Fonctions globales ( travaillent a partir de coprus_ par defaut)
    //Le dernier argument est la liste de Mots sur laquelle on travaille, si elle n'est pas précisée on travaille directement sur corpus_(ensemble)
    static Mot randomMot(vector<Mot>&);
    static vector<Mot> return_grammar_liste(string, vector<Mot>&);
    static vector<Mot> return_last_phon_liste(string, vector<Mot>&);
    static vector<Mot> return_theme_liste(string, vector<Mot>& );

    //Fonction qui renvoie un vecteur de Mots de type grammaticl GRAM et d un theme THEME
    //On utilisera des parametres par defaut: vide pour GRAM et vide pour THEME veut dire "n'impote lesquels"
    static vector<Mot> return_words(string GRAM, string THEME, vector<Mot>& );
    static string return_adjectif(Mot,vector<Mot>&);
    static string returnArticle(Mot&,string);
    static string returnPartitif(Mot&);

    //Renvoie un vecteur de Mots contenant les synonymes de Mot qui ont une entree dans la bibliotheque
    //Il analyse le vecteur string de syn du Mot(cree au constructeur par lecture bib)
    //Ne prend que les syn qui ont également une entree dans bib
    static vector<Mot> return_synonymes(Mot&);

    //Renvoie vrai si le mot_ existe comme entree dans la librairie
    static bool findentry(string mot_);
};

vector<Mot> bib::corpus_;

//Attributs constants de la bilbliotheque:
const string bib::phon_table[]={ "a","i","y","u","o","O","e","E","°","2","9","5","1","@","§","3","j","8","w","p","b","t","d","k","g","f","v","s","z","Z","m","n","N","I","R","x","G","S","l"};
const string bib::grammar_table[]={"NOM","VER","ADJ"};
//Code(format): 0 masculin singulier/ 1 feminin singulier / 2 pluriel
const string bib::definis[]= {"le","la","les"};
const string bib::indefinis[]= {"un","une","des"};
//Toutes les fonctions relatives consonnes/voyelles fonctionneront sur le fait que les éléments sont dans le meme ordre
//Relfechir a comment gerer les accents dans les comparaisons, les opérations.
//IL va falloir Unicode, une syntaxe.
const string bib::voyelles[]= {"a","e","i","o","u","y"};
const string bib::VOYELLES[]= {"A","E","I","O","U","Y"};
const string bib::consonnes[]= {"z","r","t","p","q","s","d","f","g","h","j","k","l","m","w","x","v","b","n"};
const string bib::CONSONNES[]= {"Z","R","T","P","Q","S","D","F","G","H","J","K","L","M","W","X","V","B","N"};

//Constructeur de la librairie (initialise corpus_)
void bib::initlib(string filelib){
  //Lecture de la librairie et construction du corpus_
  ifstream mylib(filelib);
  while(true){
    string entree;
    getline(mylib,entree);
    if (mylib.eof() ) break;
    //Chaque entree (entree) de la librairie est contenue dans entree
    Mot mot = Mot(entree);
    corpus_.push_back(mot); };
}

//Renvoie vrai si le mot mot est une entree de la bilbiotheque
bool bib::findentry(string mot){
  for(vector<Mot>::const_iterator it = corpus_.begin() ; it != corpus_.end(); it++){
    //Comment gerer les homonymes sans classe grammaticale? effet indésirible a surveiller
    if(mot == it->getmot()){
      return  true;
    }
  }
  return false;
}

//TODO
//Renvoie un vecteur de Mots contenant les synonymes AYANT UNE ENTREE DANS LA BIB du Mot M passé en argument
vector<Mot> bib::return_synonymes(Mot& M){
  vector<Mot> Synonymes;
  vector<string> synonymes = M.getsynonymes();
  if( synonymes.size() == 0 ) return Synonymes;
  for(std::vector<string>::const_iterator it = synonymes.begin(); it != synonymes.end(); it++){
    for(std::vector<Mot>::const_iterator itcorp = corpus_.begin() ; itcorp != corpus_.end(); itcorp++){
      if( (*it)  == itcorp->getmot()) Synonymes.push_back(*itcorp);
    }
  }
  return Synonymes;
}

//Cette fonction sert juste a verifier la phoneme mise en input par l'utilisateur
//Checker la phonetique pour une phoneme donee (la phonetique de la librairie est deja checkee par la librairie)
//en comparant a phon_table (39 phonemes, a verifier)
bool bib::check_phonetique(string phoneme){
  bool isfound = false;
  for(unsigned int i = 0 ; i != 39 ; i++)
  {
    if ( phoneme == bib::phon_table[i] ) { isfound = true; break ;}
  }
  return isfound;
}

//Verifie input utilisateur quand il interroge bib
//Check classe grammaticale
bool bib::check_grammar(string grammar){
  bool isfound = false;
  for(unsigned int i = 0 ; i != 3 ; i++)
  {
    if ( grammar == bib::grammar_table[i] ) { isfound = true; break ;}
  }
  return isfound;
}

//Fonction qui renvoie un vecteur de mots qui se terminent par la phoneme phoneme
//Si la dernier phoneme est "e" il y a un porbleme, il faut aussi l'avant derniere
vector<Mot> bib::return_last_phon_liste(string phoneme, vector<Mot>& mots = corpus_)
{
  vector<Mot> liste;
  if( !bib::check_phonetique(phoneme) ) return liste;
  for(vector<Mot>::iterator it = mots.begin(); it != mots.end() ; it++){
    if( it->getlastphoneme() == phoneme) liste.push_back(*it);
  }
  return liste;
}

//Renvoie les mots d'une classe grammaticale donnee
vector<Mot> bib::return_grammar_liste(string grammar,vector<Mot>& mots = corpus_)
{
  vector<Mot> liste;
  if( !bib::check_grammar(grammar) ) return liste;
  for(vector<Mot>::iterator it = mots.begin(); it != mots.end() ; it++){
    //Recupere vector grammar
    vector<string> vgrammar = it->getgrammar();
    for(vector<string>::const_iterator it2 = vgrammar.begin() ; it2 != vgrammar.end(); it2++){
      if( *it2 == grammar){
	liste.push_back(*it);
	break;
      }
    }
  }
  return liste;
}

//Renvoie les mots correspondant a un theme donne en argument
vector<Mot> bib::return_theme_liste(string theme,vector<Mot>& mots = corpus_)
{
  vector<Mot> liste;
  for(vector<Mot>::iterator it = mots.begin(); it != mots.end() ; it++){
    //Recupere vector grammar
    vector<string> themes = it->getthemes();
    for(vector<string>::const_iterator it2 = themes.begin() ; it2 != themes.end(); it2++){
      if( *it2 == theme || theme.empty()){
	liste.push_back(*it);
	break;
      }
    }
  }
  return liste;
}

//Renvoie un vecteur de mots correspondant a GRAM (pour l'instant a specifier par utilisateur) et au themes theme(option)
//Plus tard on fera une fonction qui prend GRAM aussi en defaut (si les deux en defaut, tous les mots)
//Juste du test pour le moment
vector<Mot> bib::return_words(string gram , string theme = "",vector<Mot>& mots= corpus_)
{
  vector<Mot> liste = bib::return_grammar_liste(gram,mots);
  liste = bib::return_theme_liste(theme,liste);
  return liste;
}

//Renvoie un adjectif au hasard accordé en genre et nombre
//Si le genre n'est pas précisé (genre="") alors c'est masculin ET feminin (ex: aristocratique)
string bib::return_adjectif(Mot mot, vector<Mot>& mots = corpus_ )
{
  string genre = mot.getgenre();
  string nombre = mot.getnombre();
  vector<Mot> A_adj;
  //Fais la liste des adj respectant la consigne
  for(vector<Mot>::iterator it = mots.begin(); it != mots.end() ; it++){
    if( (it->getgenre() == genre || (it->getgenre()).empty()) && (it->getnombre()==nombre)){
      A_adj.push_back(*it);
    }
  }
  if(A_adj.size() == 0) return string();
  //En prendre un au hasard
  int randomIndex = rand () % A_adj.size() ;
  return (A_adj[randomIndex]).getmot();
}

//Affiche sur la sortie standard les mots d'un vecteur de mots
void affiche_mots(vector<Mot> liste){
  for(vector<Mot>::iterator it = liste.begin(); it != liste.end() ; it++){
    cout<<it->getmot()<<endl;
  }
}
//Renvoie un mot au hasard dans un vecteur de mot
//WARNING pas un bon hasard (provisoire)
Mot bib::randomMot(vector<Mot>& liste){
  if(liste.size()==0) return Mot();
  int randomIndex = rand () % liste.size() ;
  return liste[randomIndex];
}

//Prend le mot et le type (défini, indéfini, partitif, démonstratif...)
// Defini: le la les
// Indefini: un une des
// Partitif (a faire): du de la des
//Si defini, regarde premiere lettre du mot, si voyelle ou h eliser
string bib::returnArticle(Mot& mot, string type){

  string article = string();
  if( ! mot.isNOM() )
  {
    return article;
  }

  else
  {
    //Genre et nombre
    //Si genre vide : m et f
    //Singulier (s ou chaine vide par defaut), Pluriel (p)
    string nombre = mot.getnombre();
    string genre = mot.getgenre();

    //Article defini (le,la,les)
    if( type == "def" )
    {
      if(nombre == "p")
      {
	article= bib::definis[2];
      }
      else //singulier
      {
	if( genre == "f")
	{
	  article= bib::definis[1];
	}
	else
	{
	  article= bib::definis[0];
	}
      }
    }   

    else if (type == "ind")
    {
      if(nombre == "p")
      {
	article= bib::indefinis[2];
      }
      else //singulier
      {
	if( genre == "f")
	{
	  article= bib::indefinis[1];
	}
	else
	{
	  article= bib::indefinis[0];
	}
      }
    }
    article+=" ";
    //Gerer l'elision: voyelle (h a faire), le dernier cast en int check si accent (donc voyelle)
    if( (nombre == "s" || nombre == "") && (mot.startVoyelle() || mot.getfirstletter()=="h" || mot.startAccent()) && type == "def" )
    {
      //le/la en l'
      article = "l'";
    }
    return article;
  }
}

string bib::returnPartitif(Mot& mot)
{
  if(!mot.isNOM()) return string();
  if(mot.getnombre()=="p") return "des";
  if(mot.startVoyelle() || mot.start("h")) return "de l'";
  if(mot.getgenre()=="f")
  {
    return "de la";
  }
  else
  {
    return "du";
  }
}

//Fonction qui renvoie vrai si le mot commence par une voyelle
bool Mot::startVoyelle(){
  string firstLetter(1,mot_[0]);
  for(unsigned int i = 0 ; i != 7 ; i++){
    if( firstLetter == bib::voyelles[i]) { return true ; break ;}
  }
  return false;
}


//   % % %               %              %         %

// ESSAIS

// MAIN

int main(){

  srand (time(NULL));

  cout<<"Bonjour poésie."<<endl;
  //Initialisation mylib:
  bib::initlib(mylibrary);

  //Tests:
  //vector<Mot> liste_ver = bib::return_grammar_liste("VER");
  //IL faudrait pouvoir donner plusieurs themes
  vector<Mot> liste_nom = bib::return_words("NOM","navigation");
  vector<Mot> liste_adj = bib::return_words("ADJ","navigation");
  cout<<liste_nom.size()<<endl;
  cout<<liste_adj.size()<<endl;
  Mot nom1 = bib::randomMot(liste_nom);
  cout<<"*"<<endl;
  Mot adj = bib::return_adjectif(nom1,liste_adj);
  cout<<"*"<<endl;

  //Pour les mots se terminant en "s" il faut regarder les 2 dernieres phonemes pour voir une rime
  //ex: ambiance / colosse non clairvoyance / distance oui
  //liste_nom = bib::return_last_phon_liste("e",liste_nom);
  //liste_adj = bib::return_last_phon_liste("5",liste_adj);

  //Faire une classe qui gere les articles (fem/mas/demonstratifs/L' au lieu de l'...)
  //IL prend en entree la Mot (genre, le nombre et premiere lettre) et la nature(défini par l'utilisateur)
  for(unsigned int i = 0 ; i < 10 ; i++){

    Mot nom1, nom2, adj ;

    while( nom1.getmot() == nom2.getmot()){
    nom1 = bib::randomMot(liste_nom);
    nom2 = bib::randomMot(liste_nom);
    }    
    cout<<bib::returnArticle(nom1,"def")+ nom1.getmot() +" et "+bib::returnArticle(nom2,"def") + nom2.getmot()<<endl;
    cout<<bib::returnArticle(nom1,"def")+ nom1.getmot()<< " "<<adj.getmot()<<endl;
    //cout<<bib::returnArticle(nom1,"def")+ nom1.getmot() +" dans "+bib::returnArticle(nom2,"def") + nom2.getmot()<<endl;

    //cout<<"Synonymes de "<<nom1.getmot()<<endl;
    //affiche_mots(bib::return_synonymes(nom1));

    //string adj1 = bib::return_adjectif("m", "s", liste_adj);
    //string adj2 = bib::return_adjectif("m", "s", liste_adj);

    //string s1 = bib::returnArticle(nom1,"def") + nom1.getmot() ;
    //string s2 = bib::returnArticle(nom2,"def") + nom2.getmot() ;

    //cout<<"        -        "<<endl;
    //cout<<"Qui n'a jamais vu "<<s1<<","<<endl;
    //cout<<"Jamais ne sera "<<adj1<<","<<endl;
    //cout<<"Qui n'a jamais vu "<<s2<<","<<endl;
    //cout<<"Jamais ne sera "<<adj2<<"."<<endl;
    //cout<<"        -        "<<endl;

  }

}
