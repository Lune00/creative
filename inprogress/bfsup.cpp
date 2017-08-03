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

#define nx 20
#define ny 20

//Est ce que les diago je les ai avec 8 voisins, si non, envoyer mail a redbloblgames
//L'algo est bon, compris. C'est juste le pattern qui n'est pas optimal, il me faut des diagonales comme lui?

using namespace std;

struct Point{
  int i;
  int j;
  //A remplacer ensuite par un id (seule une variable, utile pour autre chose, comparaison== etc...)
  int ifrom;
  int jfrom;
  unsigned int id;
  bool w ;
  bool v ;
  bool camefrom ;
};

bool operator==(const Point& a, const Point& b)
{
  return ( a.i == b.i && a.j == b.j);
}
bool operator!=(const Point& a, const Point& b)
{
  return ( a.i != b.i || a.j != b.j);
}

void makewall(Point* grid, int i, int j, int di, int dj)
{
  for(unsigned int k = i  ; k < i + di ; k++)
  {
    for(unsigned int l = j ; l < j + dj ; l++)
    {
      grid[ k * ny + l ].w = false ;
    }
  }
}

//Marque un point de la grille visite
void markv(Point* grid,Point p)
{
  grid[p.i*ny + p.j].v = true ;
  grid[p.i*ny + p.j].ifrom = p.ifrom ;
  grid[p.i*ny + p.j].jfrom = p.jfrom ;
}

Point getPoint(Point* grid,int i, int j)
{
  if(grid[i*ny+j].w) return grid[i*ny+j];
}

int pointvisites(Point* grid)
{
  int v = 0 ;
  for(unsigned int i = 0 ; i < nx ; i++)
  {
    for(unsigned int j = 0 ; j < ny ; j++)
    {
      if(grid[i*ny+j].v) v++;
    }
  }
  return v;
}


//Breadth first search : arret si pas de chemin, arret quand le but est trouve

int main(){


  Point * grid = new Point [nx * ny];
  //contient les points de la frontiere
  std::vector<Point> frontier ;
  int max_size_frontier = 0 ;

  //Initialise la grille ;
  int u = 0 ;
  for(unsigned int i = 0 ; i < nx ; i++)
  {
    for(unsigned int j = 0 ; j < ny ; j++)
    {
      grid[ i * ny + j ].i = i ;
      grid[ i * ny + j ].j = j ;
      grid[ i * ny + j ].w = true ;
      grid[ i * ny + j ].v = false ;
      grid[ i * ny + j ].id = u ;
      grid[ i * ny + j ].camefrom = false ;
      u++;
    }
  }

  //On fixe un point de depart
  Point start = { 2 , 10 , 10 , 10 , true, true};
  Point end = { 18 , 5 , 0 , 0 , true, false};

  //On marque la grille avec le point de depart
  markv(grid,start);

  makewall(grid,5,0,2,18);
  makewall(grid,10,5,2,7);
  makewall(grid,15,5,2,7);
  //makewall(grid,9,5,12,6);
  //makewall(grid,15,5,1,10);
  //  makewall(grid,ny,10,15,1,12);
  //  makewall(grid,ny,0,13,8,1);
  //  makewall(grid,ny,20,20,3,12);
  //  makewall(grid,ny,20,0,3,12);

  //On initialise la frontiere
  frontier.push_back(start);

  bool goalvisited = false ;

  int test=0;

  while(frontier.size() != 0 )
  {
    test++;
    frontier.size() > max_size_frontier ? max_size_frontier = frontier.size() : max_size_frontier = max_size_frontier ;

    //On prend le premier point de la frontiere
    Point current = frontier[0]; 
    //On retire le point de la frontiere
    frontier.erase(frontier.begin());
    //contient les voisins de current
    std::vector<Point> voisins ; 

    int i = current.i ;
    int j = current.j ;

    //On marque ce point visite
    grid[i*ny+j].v = true;

    cerr<<"Nombre de points visites : "<<pointvisites(grid)<<endl;

    //Voisins:
    //Faire des logiques haut bas gauche droite et construire a partir de ca
    //Haut
    bool haut = false;
    bool bas = false ;
    bool gauche = false ;
    bool droite = false ;

    if( (j+1) >= 0 && (j+1)<ny && !grid[i*ny+j+1].camefrom) {
      if(grid[i*ny+j+1].w) haut = true ;
    } 
    //Bas
    if( (j-1) >= 0 && (j-1)<ny && !grid[i*ny+j-1].camefrom) {
      if(grid[i*ny+j-1].w) bas = true ;
    } 
    //Droite
    if( (i+1) >= 0 && (i+1)<nx && !grid[(i+1)*ny+j].camefrom) {
      if(grid[(i+1)*ny+j].w) droite = true ;
    } 
    //Gauche
    if( (i-1) >= 0 && (i-1)<nx && !grid[(i-1)*ny+j].camefrom) {
      if(grid[(i-1)*ny+j].w) gauche =true ;
    } 
    //Mettre les voisins dans un ordre aleatoire?
    cout<<"Nombre de voisins non visites:"<<voisins.size()<<endl;
    if( haut) voisins.push_back(grid[i*ny+j+1]);
    if (bas) voisins.push_back(grid[i*ny+j-1]) ;
    if( droite) voisins.push_back(grid[(i+1)*ny+j]) ;
    if( gauche) voisins.push_back(grid[(i-1)*ny+j]);
    if(haut && droite) voisins.push_back(grid[(i+1)*ny+j+1]);
    if(bas && gauche) voisins.push_back(grid[(i-1)*ny+j-1]);
    if(haut && gauche) voisins.push_back(grid[(i-1)*ny+j+1]);
    if(bas && droite) voisins.push_back(grid[(i+1)*ny+j-1]);

    //On parcourt les voisins
    for(std::vector<Point>::iterator it = voisins.begin(); it != voisins.end(); it++)
    {
      if( *it == end) goalvisited = true ;

      grid[it->i*ny+it->j].camefrom = true;
      grid[it->i*ny+it->j].ifrom = current.i;
      grid[it->i*ny+it->j].jfrom = current.j;

      frontier.push_back( *it );
    }
    //Si le point d arrivee est visite, on arrete de rechercher
    if(goalvisited ) break;
  }

  cerr<<"Nombre de points visites : "<<pointvisites(grid)<<endl;
  //On check si le point d arrivee est dans la liste des points visites, si non, pas de chemin
  if(!goalvisited)
  {
    cerr<<"Il n'y a pas de chemin."<<endl;
     return 0 ;
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
  cerr<<"Max size frontier : "<<max_size_frontier<<endl;

  //On print les paths
  ofstream opath("paths.txt");
  ofstream grille("grid.txt");
  ofstream lechemin("chemin.txt");

  for(unsigned int i = 0 ; i < nx ; i++)
  {
    for(unsigned int j = 0 ; j < ny ; j++)
    {
      Point p = getPoint(grid,i,j);
      if( p.i==1 && p.j==1) cerr<<p.ifrom<<" - "<<p.jfrom<<endl;
      double s = 0.5 ;
      if(p.v) opath<<p.i+0.5<<" "<<p.j+0.5<<" "<<(p.ifrom-p.i)*s<<" "<<(p.jfrom-p.j)*s<<endl;
    }
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
  int color = 0 ;

  for(std::vector<Point>::iterator it2 = path.begin(); it2 != path.end(); it2++)
  {
    lechemin<<it2->i+0.5<<" "<<it2->j+0.5<<" "<<color<<endl;
    color++;
  }
  lechemin.close();

  delete [] grid;

  return 0;
}
