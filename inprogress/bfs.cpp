#include<sstream>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Point{

  int i;
  int j;

  //A remplacer ensuite par un id (seule une variable, utile pour autre chose, comparaison== etc...)
  int ifrom;
  int jfrom;

};

bool operator==(const Point& a, const Point& b)
{
  return ( a.i == b.i && a.j == b.j);
}

int main(){

  int nx = 3 ;
  int ny = 3 ;

  Point * grid = new Point [nx * ny];
  //contient les points de la frontiere
  std::vector<Point> frontier ;
  //contient les points deja visite
  std::vector<Point> came_from;

  //Initialise la grille ;
  for(unsigned int i = 0 ; i < nx ; i++)
  {
    for(unsigned int j = 0 ; j < ny ; j++)
    {
      grid[ i * ny + j ].i = i ;
      grid[ i * ny + j ].j = j ;
    }
  }
  //On fixe un point de depart
  Point start = { 0 , 0 , 0 , 0 };
  //On initialise la frontiere
  frontier.push_back(start);
  came_from.push_back(start);

  //Algorithme
  //On cree une liste de tous les points visites en leur associant un point
  //Une fois cette liste contenant tous les points on s'en sert pour mettre a jour la grille

  while(frontier.size() != 0 )
  {
    cerr<<"Frontier size = "<<frontier.size()<<endl;
    //On prend le premier point de la frontiere
    Point current = frontier[0]; 
    //On retire le point de la frontiere
    frontier.erase(frontier.begin());

    //contient les voisins de current
    std::vector<Point> voisins;

    int i = current.i ;
    int j = current.j ;

    //On prend ses voisin
    if( (i-1) >= 0 && (i-1) < nx ) {
      Point voisin = { i-1 , j } ;
      voisins.push_back(voisin);
    }

    if( (i+1) >= 0 && (i+1) < nx ) {
      Point voisin = { i+1 , j } ;
      voisins.push_back(voisin);
    }

    if( (j+1) >= 0 && (j+1) < ny ) {
      Point voisin = { i , j+1 } ;
      voisins.push_back(voisin);
    }

    if( (j-1) >= 0 && (j-1) < ny ) {
      Point voisin = { i , j-1 } ;
      voisins.push_back(voisin);
    }

    cerr<<"Le point "<<i<<" "<<j<<" a "<<voisins.size()<<" voisins:"<<endl;
    for(std::vector<Point>::iterator it = voisins.begin(); it != voisins.end(); it++)
    {
      cerr<<it->i<<" "<<it->j<<endl;
    }

    //On parcourt les voisins
    for(std::vector<Point>::iterator it = voisins.begin(); it != voisins.end(); it++)
    {
      bool alreadyvisited = false;
      //On verifie qu'il n'est pas deja dans la liste camefrom (deja visite)
      for(std::vector<Point>::iterator it2 = came_from.begin(); it2 != came_from.end(); it2++)
      {
	if( *it == *it2){
	  cerr<<"Ce point a deja ete visite, on passe au suivant."<<endl;
	  alreadyvisited = true ;
	  break;
	}
      }

      if(alreadyvisited) continue; 
      //S'il n'a pas ete visite on l'ajoute a la frontiere en lui associant le point d ou on vient
      cerr<<"Process."<<endl;

      it->ifrom = current.i ;
      it->jfrom = current.j ;

      frontier.push_back( *it );
      came_from.push_back( *it) ;
    }
  }

  cerr<<"Nombre de points visites : "<<came_from.size()<<endl;

  //A la fin pour chaque point on a le point d'ou il vient
  for(std::vector<Point>::iterator it2 = came_from.begin(); it2 != came_from.end(); it2++)
  {
    cerr<<it2->i<<" "<<it2->j<<" attache a "<<it2->ifrom<<" "<<it2->jfrom<<endl;
  }

  delete [] grid;

  return 0;
}



