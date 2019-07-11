#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>
#include<fstream>

#include "functions.h"
#include "arithmetique.h"
#include "datalist.h"
#include "displaytexte.h"

using namespace std;

int main(){

  
  CALCULUS maths; 
  DATA set;
  
  
    std::string word,DESCRIPTEURS;
    std::vector<std::string> ID;
   ID.push_back("QUALIF1");
   DESCRIPTEURS="*";
   std::vector<std::string> OPTIONS;
   OPTIONS.push_back("NEGATIF");
   std::vector<string> words;
   //set.print_all_index();
   const string path=set.makepath("data","visage","oeil");
   //cout<<path<<endl;
   words=set.getData(path,ID,OPTIONS,DESCRIPTEURS);
    word=set.pickup_word(words,3);
    cout<<"word:"<<word<<endl;
   
   //cout<<"Il a les yeux "<<word<<endl;
  
  
  
  return 0;
  
  
}
