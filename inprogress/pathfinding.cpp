#include<sstream>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>


using namespace std;


class Point{
  private:
    double x_ , y_ ;
  public:
    Point(){x_ = 0. ; y_ = 0. ;}
    ~Point(){};
    double getX(){return x_;};
    double getY(){return y_;};
    void setX(double x){x_ = x ;};
    void setY(double y){y_ = y ;};

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
    double getdx() {return dx_ ; }
    double getdy() {return dy_ ; }
    void setcoordinates();
    Point getPoint(int,int);

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


int main()
{
  cout<<"Hello world !"<<endl;
  Grid grid(20,20,0.,0.,10.,10.);
  return 0 ;
}

