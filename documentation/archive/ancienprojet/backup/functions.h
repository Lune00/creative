#ifndef H_FUNCTIONS_H
#define H_FUNCTIONS_H


#include<string>
#include<vector>

//fonctions generales sur les lettres et les mots
char randomVoyelle(); 
char randomConsonne();
char consonnesRules(char c,bool firstOne); 
char voyellesRules(char c,bool firstOne);
char getFirstLetterSyll(std::string syll);
char returnlast(std::string name);
char probabilityCV(double p);
bool checkAny(std::string name);
bool MajOrmin(char c);
bool letterType(char c);
bool followingLetters(char a,char b);
bool followingLettersBEG(char a,char b);
int charLabel(char c);
std::string CapitalFirst(std::string Name);



#endif