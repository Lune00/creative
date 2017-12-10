#include "adjectif.hpp"

using namespace std;

Adjectif::Adjectif(string lemme, string phon, int nsyll, char genre, char nombre): Mot(lemme,phon,nsyll), genre_(genre), nombre_(nombre)
{

}

Adjectif::~Adjectif()
{

}
