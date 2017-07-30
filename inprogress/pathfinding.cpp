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

//Bon c'est le gros bordel, a reecrire de maniere plus succinte
//Le nombre d'iteration est bon, les camefrom sont bien determines mais on dirait qu'il y a un probleme avec les pointeurs
//Camefrom ne marche pas quand on le rappelle
//Ca marche pas cette histoire de pointeur, et c'est trop le bordel !!!!

using namespace std;


class Point{
  private:
    double x_ , y_ ;
    int i_ , j_ ;
    bool walkable_ ;
    bool visited_ ;
    int id_ ;
    Point * camefrom_ ;
    int icf_ , jcf_ ;
  public:
    Point(){x_ = 0. ; y_ = 0. ; walkable_ = true ; visited_ = false; camefrom_ = NULL; icf_ = 0 ; jcf_ = 0;}

    ~Point(){};
    double getX(){return x_;};
    double getY(){return y_;};
    int getid() {return id_ ;}
    void setid(int id){id_ = id;}
    bool getW() {return walkable_;}
    bool getV() {return visited_;}
    void setX(double x){x_ = x ;};
    void setY(double y){y_ = y ;};
    void setI(int i) {i_ = i ; }
    void setJ(int j) {j_ = j ;}
    int getI() {return i_ ; }
    int getJ() {return j_ ;}
    void setV() {visited_ = true ; }
    void unsetW() { walkable_ = false ; }
    void setW() {walkable_ = true ; }
    void setCameFrom(Point a) { camefrom_ = &a ; }
    int geticf() {return icf_ ;}
    void seticf(int icf) {icf_ = icf ;}
    void setjcf(int jcf) {jcf_ = jcf ;}
    int getjcf() {return jcf_ ;}
    Point * getCameFrom() { return camefrom_ ; };

    bool operator==(const Point&a) const{
      if( id_ == a.id_ ) return true;
      else
	return false;
    }
    bool operator<(const Point&a) const{
      return id_ < a.id_;
    }
};


class Grid{
  private :
    int nx_ , ny_ ;
    double dx_ , dy_ ;
    double xmin_,ymin_,xmax_,ymax_;
    Point * array_ ;
    std::vector<Point> frontier_;
  public :
    Grid(int,int,double,double,double,double) ;
    ~Grid();
    double getX(int,int);
    double getY(int,int);
    bool getW(int,int);
    bool getV(int,int);
    void setPointV(int,int);
    void setPointCameFrom(int,int,int,int);
    double getdx() {return dx_ ; }
    double getdy() {return dy_ ; }
    void setcoordinates();
    void makeobstacle(int,int,int,int);
    Point getPoint(int,int);
    void writeWGrid(string);
    std::vector<Point> getvoisins(int,int);
    void cleanfrontier();
    void setStartPointFrontier(Point);
    void expandFrontier();
    void explore(Point);
    void writePath(string);
};

void Grid::cleanfrontier()
{
  frontier_.clear();
}
//Construit la map des fleches a partir du point a

void Grid::explore(Point a)
{
  cleanfrontier();
  frontier_.push_back(a);
  expandFrontier();
}

void Grid::expandFrontier()
{
  //On se place a l'origine
  std::vector<Point>::iterator it = frontier_.begin();

  int i = 0 ;
  while ( !frontier_.empty())
  {	
    cerr<<"---------"<<endl;
    cerr<<"Iteration "<<i<<endl;
    cerr<<"---------"<<endl;
    cerr<<" "<<endl;
    cerr<<"+ Point considere de la frontiere : "<<it->getI()<<" "<<it->getJ()<<endl;
    //On check qu'on la pas deja visite
    if(getPoint(it->getI(),it->getJ()).getV())
    {
      //On passe au suivant;
      it = frontier_.begin(); 
      frontier_.erase(frontier_.begin());
    }
    else
    {

      //On recupere les voisins qui n'ont pas ete visite du point de reference
      std::vector<Point> voisins = getvoisins(it->getI(),it->getJ());

      //On marque ce point de la frontiere comme visite
      //*** ON AFFECTE LA GRILLE ICI
      setPointV(it->getI(),it->getJ());

      for(std::vector<Point>::iterator it2 = voisins.begin(); it2 != voisins.end();it2++)
      {
	cerr<<"--On regarde les points "<<it2->getI()<<" "<<it2->getJ()<<endl;
	Point nouveau = getPoint(it2->getI(),it2->getJ());
	frontier_.push_back(nouveau); 
      }

      //Je supprime le point de reference i de la fronteire
      it = frontier_.begin(); 
      frontier_.erase(frontier_.begin());

      cerr<<"Taille de la nouvelle frontiere :" <<frontier_.size()<<endl;
      cerr<<"* Liste des points dans la frontiere :"<<endl;
      for(std::vector<Point>::iterator it = frontier_.begin(); it != frontier_.end();it++)
      {
	cerr<<it->getI()<<" "<<it->getJ()<<endl;
      }
      //On erase les doublons
      sort(frontier_.begin(),frontier_.end());
      frontier_.erase(unique(frontier_.begin(),frontier_.end()),frontier_.end());

      cerr<<"Iteration "<<i<<" termine."<<endl;
      cerr<<endl;
      cerr<<"** Bilan :"<<endl;

      for(int j = 0 ; j != ny_ ; j++)
      {
	for(int i = 0 ; i!= nx_ ; i++)
	{
	  Point current = getPoint(i,j);

	  if(current.getCameFrom()!=NULL){
	    double x =getX(i,j); 
	    double y =getY(i,j); 
	    double xfrom = current.getCameFrom()->getX(); 
	    double yfrom = current.getCameFrom()->getY();
	    cerr<<"Le point "<<i<<" "<<j<<" a ete rattache au point "<<getPoint(i,j).getCameFrom()->getI()<<" "<<getPoint(i,j).getCameFrom()->getJ()<<endl;
	  }
	}
      }
    }
    i++;
  }
}

void Grid::setPointCameFrom(int i,int j,int icf,int jcf)
{
  array_[ i * ny_ + j].setCameFrom( array_[ icf * ny_ + jcf] );
  array_[ i * ny_ + j].seticf( array_[ icf * ny_ + jcf].getI() );
  array_[ i * ny_ + j].setjcf( array_[ icf * ny_ + jcf].getJ() );
  cerr<<"Le point "<<i<<" "<<j<<" a ete rattache au point "<<getPoint(i,j).getCameFrom()->getI()<<" "<<getPoint(i,j).getCameFrom()->getJ()<<endl;
}

//prends tous les voisins meme les obstacles
std::vector<Point> Grid::getvoisins(int i, int j)
{
  cerr<<"- getvoisins de "<<i<<" "<<j<<endl;
  std::vector<Point> voisins;

  if( (i-1) >= 0 && (i-1) < nx_ ) {
    if(!getPoint(i-1,j).getV()){
      voisins.push_back(getPoint(i-1,j));
      cerr<<"On ajoute "<<i-1<<" "<<j<<endl;
      cerr<<"On a ajoute en vrai "<<getPoint(i-1,j).getI()<<" "<<getPoint(i-1,j).getJ()<<endl;
    }
  }

  if( (i+1) >= 0 && (i+1) < nx_ ){
    if(!getPoint(i+1,j).getV()){
      voisins.push_back(getPoint(i+1,j));
      cerr<<"On ajoute "<<i+1<<" "<<j<<endl;
      cerr<<"On a ajoute en vrai "<<getPoint(i+1,j).getI()<<" "<<getPoint(i+1,j).getJ()<<endl;
    }
  }

  if( (j+1) >= 0 && (j+1) < ny_ ){
    if(!getPoint(i,j+1).getV()){
      voisins.push_back(getPoint(i,j+1));
      cerr<<"On ajoute "<<i<<" "<<j+1<<endl;
      cerr<<"On a ajoute en vrai "<<getPoint(i,j+1).getI()<<" "<<getPoint(i,j+1).getJ()<<endl;
    }
  }

  if( (j-1) >= 0 && (j-1) < ny_ ){
    if(!getPoint(i,j-1).getV()){
      voisins.push_back(getPoint(i,j-1));
      cerr<<"On ajoute "<<i<<" "<<j-1<<endl;
      cerr<<"On a ajoute en vrai "<<getPoint(i,j-1).getI()<<" "<<getPoint(i,j-1).getJ()<<endl;
    }
  }
  cerr<<"- Il a "<<voisins.size()<<" voisins"<<endl;

  //On dit d'ou on arrive a chaque voisin (le noeud original)
  for(std::vector<Point>::iterator it = voisins.begin(); it != voisins.end();it++)
  {
    int a = it->getI() ;
    int b = it->getJ() ;
    cerr<<"Voisin : "<<it->getI()<<" "<<it->getJ()<<endl;
    //S'il n'a pas ete visite deja on lui assigne une fleche
    //*** ON AFFECTE LA GRILLE ICI
    setPointCameFrom(a,b,i,j);
  }

  return voisins;
}



Grid::Grid(int nx, int ny, double xmin, double ymin, double xmax, double ymax)
{
  nx_ = nx ;
  ny_ = ny ;
  xmin_ = xmin;
  xmax_ = xmax;
  ymin_ = ymin;
  ymax_ = ymax;
  dx_ = (xmax_ - xmin_) / nx_ ;
  dy_ = (ymax_ - ymin_) / ny_ ;

  array_ = new Point [ nx_ * ny_ ];

  setcoordinates();
}

Grid::~Grid()
{
  cerr<<"Delete Grid."<<endl;
  delete[] array_;
}

double Grid::getX(int i,int j)
{
  return array_[ i * ny_ + j].getX();
}

double Grid::getY(int i,int j)
{
  return array_[ i * ny_ + j].getY();
}

bool Grid::getW(int i, int j)
{
  return array_[ i * ny_ + j].getW();
}

bool Grid::getV(int i, int j)
{
  return array_[ i * ny_ + j].getV();
}

Point Grid::getPoint(int i,int j)
{
  return array_[ i * ny_ + j];
}

void Grid::setPointV(int i,int j)
{
  array_ [ i * ny_ + j].setV();
}

void Grid::setcoordinates()
{
  //Set coordinates:
  double x = xmin_;
  double y = ymin_;
  int id = 0 ;

  for(int j = 0 ; j!= ny_ ; j++)
  {
    for(int i = 0 ; i != nx_ ; i++)
    {
      //cerr<<"Set coordinates:"<<i<<" "<<j<<"to "<<i*ny_ + j<<" element."<<endl;
      array_[ i * ny_ + j ].setX(x);
      array_[ i * ny_ + j ].setY(y);
      array_[ i * ny_ + j ].setI(i);
      array_[ i * ny_ + j ].setJ(j);
      array_[ i * ny_ + j ].setid(id);
      x+=dx_;
      id++;
    }
    y+=dy_;
    x = xmin_;
  }
  cerr<<"Metrics done."<<endl;
}

//Fais un obstacle de i0,j0 de longueur DX et de largeur DY
void Grid::makeobstacle(int i0,int j0,int DX , int DY)
{
  for(int j = j0; j!= j0+DY; j++)
  {
    for(int i = i0; i!= i0+DX; i++ )
    {
      array_[ i * ny_ + j ].unsetW();
    }
  }

}

void Grid::writeWGrid(string filename)
{
  ofstream gridout (filename,ios::out);
  for(int j = 0 ; j != ny_ ; j++)
  {
    for(int i = 0 ; i!= nx_ - 1 ; i++)
    {
      if(getW(i,j)) gridout<<getX(i,j)<<" "<<getY(i,j)<<" "<<dx_<<" 0."<<" "<<endl;
    }
  }

  for(int i = 0 ; i != nx_ ; i++)
  {
    for(int j = 0 ; j!= ny_ - 1 ; j++)
    {
      if(getW(i,j)) gridout<<getX(i,j)<<" "<<getY(i,j)<<" 0. "<<dy_<<" "<<endl; 
    }
  }

  gridout.close();
}	

void Grid::writePath(string filename)
{
  cerr<<"writePath"<<endl;
  ofstream gridout (filename,ios::out);
  for(int j = 0 ; j != ny_ ; j++)
  {
    for(int i = 0 ; i!= nx_ ; i++)
    {
      Point current = getPoint(i,j);

      if(current.getCameFrom()!=NULL){
	double x =getX(i,j); 
	double y =getY(i,j); 
	double xfrom = current.getCameFrom()->getX(); 
	double yfrom = current.getCameFrom()->getY();
	cerr<<"Le point "<<i<<" "<<j<<" a ete rattache au point "<<getPoint(i,j).getCameFrom()->getI()<<" "<<getPoint(i,j).getCameFrom()->getJ()<<endl;
	gridout<<x<<" "<<y<<" "<<xfrom-x<<" "<<yfrom-y<<endl;
      }
    }
  }
  gridout.close();
}	

int main()
{
  Grid grid(1,4,0.,0.,1.,1.);
  Point start = grid.getPoint(0,0);
  grid.explore(start);
  //grid.makeobstacle(5,5,5,5);
  grid.writeWGrid("grid.txt");
  grid.writePath("path.txt");
  return 0 ;
}

