#include<iterator>
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


// Y a toujours un detail qui marche pas, je n'arrive pas avoir de ligne droite, de lignes de courant qui convergent vers le point de depart

using namespace std;

struct Point{
  int i;
  int j;
  //A remplacer ensuite par un id (seule une variable, utile pour autre chose, comparaison== etc...)
  int ifrom;
  int jfrom;
  bool w ;
};

bool operator==(const Point& a, const Point& b)
{
  return ( a.i == b.i && a.j == b.j);
}
bool operator!=(const Point& a, const Point& b)
{
  return ( a.i != b.i || a.j != b.j);
}

void makewall(Point* grid, int ny, int i, int j, int di, int dj)
{
  for(unsigned int k = i  ; k < i + di ; k++)
  {
    for(unsigned int l = j ; l < j + dj ; l++)
    {
      grid[ k * ny + l ].w = false ;
    }
  }
}

//Breadth first search : arret si pas de chemin, arret quand le but est trouve

int main(){

  int nx = 10 ;
  int ny = 10 ;

  //On fixe un point de depart
  Point start = { 5 , 5 , 5 , 5 , true};
  Point end = { 0 , 0 , 0 , 0 , true};

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
      grid[ i * ny + j ].w = true ;
    }
  }

//  makewall(grid,ny,0,25,nx-1,2);
//  makewall(grid,ny,10,15,1,12);
//  makewall(grid,ny,0,13,8,1);
//  makewall(grid,ny,20,20,3,12);
//  makewall(grid,ny,20,0,3,12);

  //On initialise la frontiere
  frontier.push_back(start);
  came_from.push_back(start);

  //Algorithme
  //On cree une liste de tous les points visites en leur associant un point
  //Une fois cette liste contenant tous les points on s'en sert pour mettre a jour la grille

  bool goalvisited = false ;
  while(frontier.size() != 0 )
  {
    //On prend le premier point de la frontiere
    Point current = frontier[0]; 
    //On retire le point de la frontiere
    frontier.erase(frontier.begin());
    //contient les voisins de current
    std::vector<Point> voisins ; 
    int i = current.i ;
    int j = current.j ;
    //On prend ses voisins
    //Essayer commencer voisin de droite, bas, gauche, haut
    //for(int k = i + 1 ; k > i - 2 ; k--  )
    //{
    //  for(int l = j + 1 ; l > j - 2 ; l--  )
    //  {
    //    if ( (k == i && l == j) || (grid[ k * ny + l].w == false) ) continue ;
    //    if ( (k >= 0 && k < nx ) && ( l >= 0 && l < ny ) ) 
    //    {
    //      Point p = { k , l } ;
    //      voisins.push_back(p);
    //    }
    //  }
    //}

    //Droite
    if( (i+1) >= 0 && (i+1)<nx ) {
      Point p = { i+1 , j } ;
      voisins.push_back(p);
    } 
    //Bas
    if( (j-1) >= 0 && (j-1)<ny ) {
      Point p = { i , j-1 } ;
      voisins.push_back(p);
    } 
    //Gauche
    if( (i-1) >= 0 && (i-1)<nx ) {
      Point p = { i-1 , j } ;
      voisins.push_back(p);
    } 
    //Haut
    if( (j+1) >= 0 && (j+1)<ny ) {
      Point p = { i, j+1 } ;
      voisins.push_back(p);
    } 

    //On parcourt les voisins
    for(std::vector<Point>::iterator it = voisins.begin(); it != voisins.end(); it++)
    {
      bool alreadyvisited = false;
      //On verifie qu'il n'est pas deja dans la liste camefrom (deja visite)
      for(std::vector<Point>::iterator it2 = came_from.begin(); it2 != came_from.end(); it2++)
      {
	if( *it == *it2){
	  alreadyvisited = true ;
	  break;
	}
	if( *it == end) goalvisited = true ;
      }
      if(alreadyvisited) continue; 
      //S'il n'a pas ete visite on l'ajoute a la frontiere en lui associant le point d ou on vient
      it->ifrom = current.i ;
      it->jfrom = current.j ;
      frontier.push_back( *it );
      came_from.push_back( *it) ;
    }
    //Si le point d arrivee est visite, on arrete de rechercher
    if(goalvisited ) break;
  }

  cerr<<"Nombre de points visites : "<<came_from.size()<<endl;

  //On check si le point d arrivee est dans la liste des points visites, si non, pas de chemin
  if(!goalvisited)
  {
    cerr<<"Il n'y a pas de chemin."<<endl;
    return 0 ;
  }

  //On met a jour la grille
  cerr<<"Mise a jour de la grille."<<endl;
  for(std::vector<Point>::iterator it = came_from.begin() ; it != came_from.end() ; it++)
  {
    grid[ it->i * ny + it->j].ifrom = it->ifrom ; 
    grid[ it->i * ny + it->j].jfrom = it->jfrom ; 
  }

  //On trace le chemin du depart a la destination:
  cerr<<"Calcul du chemin entre start et end."<<endl;

  std::vector<Point> path ;
  path.push_back(grid[end.i * ny + end.j]);
  std::vector<Point>::iterator it = path.begin();

  while( *it != start)
  {
    Point next = grid[it->ifrom * ny + it->jfrom];
    path.push_back(next);
    it = path.begin() + (path.size()- 1);
  }

  cerr<<"Nombre de points a parcourir pour arriver a destination : "<<path.size()<<endl;

  //On print les paths
  ofstream opath("paths.txt");
  ofstream grille("grid.txt");
  ofstream lechemin("chemin.txt");

  for(std::vector<Point>::iterator it2 = came_from.begin(); it2 != came_from.end(); it2++)
  {
    double s = 0.5 ;
    opath<<it2->i+0.5<<" "<<(it2->j)+0.5<<" "<<(it2->ifrom -it2->i)*s<<" "<<(it2->jfrom - it2->j)*s<<endl;
  }
  opath.close();

  for(unsigned int i = 0 ; i < nx ; i++)
  {
    for(unsigned int j = 0 ; j < ny ; j++)
    {
      if(grid[i*ny+j].w) grille<<grid[ i * ny + j ].i+0.5<<" "<<grid[ i * ny + j ].j+0.5<<endl ;
    }
  }
  grille.close();

  for(std::vector<Point>::iterator it2 = path.begin(); it2 != path.end(); it2++)
  {
    lechemin<<it2->i+0.5<<" "<<it2->j+0.5<<endl;
  }
  lechemin.close();

  delete [] grid;

  return 0;
}
