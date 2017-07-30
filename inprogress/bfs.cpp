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


//Ca marche toujours pas bien. On devrait avoir des diagonales. A mediter...

int main(){

  int nx = 40 ;
  int ny = 40 ;

  //On fixe un point de depart
  Point start = { 2 , 25 , 2 , 25 , true};
  Point end = { 33 , 34 , 33 , 33 , true};

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

  //Obstacle:
  int obstracle = 0 ;
  int width = 5 ;
  for(unsigned int i = nx /4 - width  ; i < nx/4 + width ; i++)
  {
    for(unsigned int j = ny/4 -width ; j < ny/4 + width ; j++)
    {
      grid[ i * ny + j ].w = false ;
      obstracle++;
    }
  }
  for(unsigned int i = nx /2 - 2  ; i < nx/2 +2 ; i++)
  {
    for(unsigned int j = ny/2 -2 ; j < ny/2+2 ; j++)
    {
      grid[ i * ny + j ].w = false ;
      obstracle++;
    }
  }

  //On initialise la frontiere
  frontier.push_back(start);
  came_from.push_back(start);

  //Algorithme
  //On cree une liste de tous les points visites en leur associant un point
  //Une fois cette liste contenant tous les points on s'en sert pour mettre a jour la grille

  while(frontier.size() != 0 )
  {
    //cerr<<"Frontier size = "<<frontier.size()<<endl;

    //On prend le premier point de la frontiere

    Point current = frontier[0]; 

   // cerr<<"Le point courrant est "<<current.i<<" "<<current.j<<endl;
    //On retire le point de la frontiere
    frontier.erase(frontier.begin());

    //contient les voisins de current
    std::vector<Point> voisins ; 

    int i = current.i ;
    int j = current.j ;

    //On prend ses voisin
    for(int k = i - 1 ; k < i + 2 ; k++  )
    {
      for(int l = j - 1 ; l < j + 2 ; l++  )
      {

	if ( (k == i && l == j) || (grid[ k * ny + l].w == false) ) continue ;

	if ( (k >= 0 && k < nx ) && ( l >= 0 && l < ny ) ) 
	{
	  Point p = { k , l } ;
	  voisins.push_back(p);
	}

      }
    }

  //  cerr<<"Le point "<<i<<" "<<j<<" a "<<voisins.size()<<" voisins:"<<endl;

  //  for(std::vector<Point>::iterator it = voisins.begin(); it != voisins.end(); it++)
  //  {
  //    cerr<<it->i<<" "<<it->j<<endl;
  //  }

    //On parcourt les voisins
    for(std::vector<Point>::iterator it = voisins.begin(); it != voisins.end(); it++)
    {
      bool alreadyvisited = false;
      //On verifie qu'il n'est pas deja dans la liste camefrom (deja visite)
      for(std::vector<Point>::iterator it2 = came_from.begin(); it2 != came_from.end(); it2++)
      {
	if( *it == *it2){
	  //cerr<<"Ce point a deja ete visite, on passe au suivant."<<endl;
	  alreadyvisited = true ;
	  break;
	}
      }

      if(alreadyvisited) continue; 

      //S'il n'a pas ete visite on l'ajoute a la frontiere en lui associant le point d ou on vient
      it->ifrom = current.i ;
      it->jfrom = current.j ;

      frontier.push_back( *it );
      came_from.push_back( *it) ;
    }
  }

  cerr<<"Nombre de points visites : "<<came_from.size()<<endl;
  cerr<<"Taille obstacle : "<<obstracle<<endl;
  
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
    cerr<<"Point suivant :" <<next.i<<" "<<next.j<<endl;
    cerr<<"Ce point est lie a :" <<next.ifrom<<" "<<next.jfrom<<endl;
    path.push_back(next);
    cerr<<"Path.size : "<<path.size()<<endl;
    //Next element
    it = path.begin() + (path.size()- 1);
  }

  cerr<<"Nombre de points a parcourir pour arriver a destination : "<<path.size()<<endl;
  
  //On print les paths
  ofstream opath("paths.txt");
  ofstream grille("grid.txt");
  ofstream lechemin("chemin.txt");

  //A la fin pour chaque point on a le point d'ou il vient
  for(std::vector<Point>::iterator it2 = came_from.begin(); it2 != came_from.end(); it2++)
  {
    double s = 1. ;
   // cerr<<it2->i<<" "<<it2->j<<" attache a "<<it2->ifrom<<" "<<it2->jfrom<<endl;
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
    //cerr<<it2->i<<" "<<it2->j<<endl;
    lechemin<<it2->i+0.5<<" "<<it2->j+0.5<<endl;
  }

  lechemin.close();

  delete [] grid;

  return 0;
}



