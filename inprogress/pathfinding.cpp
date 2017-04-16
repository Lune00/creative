#include<sstream>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <sstream>


using namespace std;


class Point{
  private:
    double x_ , y_ ;
    bool walkable_ ;
  public:
    Point(){x_ = 0. ; y_ = 0. ; walkable_ = true ;}
    ~Point(){};
    double getX(){return x_;};
    double getY(){return y_;};
    bool getW() {return walkable_;}
    void setX(double x){x_ = x ;};
    void setY(double y){y_ = y ;};
    void unsetW() { walkable_ = false ; }
    void setW() {walkable_ = true ; }

};

class Grid{
  private :
    int nx_ , ny_ ;
    double dx_ , dy_ ;
    double xmin_,ymin_,xmax_,ymax_;
    Point * array_ ;
  public :
    Grid(int,int,double,double,double,double) ;
    ~Grid();
    double getX(int,int);
    double getY(int,int);
    bool getW(int,int);
    double getdx() {return dx_ ; }
    double getdy() {return dy_ ; }
    void setcoordinates();
    void makeobstacle(int,int,int,int);
    Point getPoint(int,int);
    void writeWGrid(string);

};

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


void Grid::setcoordinates()
{
  //Set coordinates:
  double x = xmin_;
  double y = ymin_;

  for(int j = 0 ; j!= ny_ ; j++)
  {
    for(int i = 0 ; i != nx_ ; i++)
    {
      array_[ i * ny_ + j ].setX(x);
      array_[ i * ny_ + j ].setY(y);
      x+=dx_;
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


int main()
{
  cout<<"Hello world !"<<endl;
  Grid grid(20,20,0.,0.,10.,10.);
  grid.makeobstacle(5,5,5,5);
  grid.writeWGrid("grid.txt");
  return 0 ;
}

