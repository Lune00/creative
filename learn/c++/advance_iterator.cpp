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
};

bool operator==(const Point& a, const Point& b)
{
  return ( a.i == b.i && a.j == b.j);
}
bool operator!=(const Point& a, const Point& b)
{
  return ( a.i != b.i || a.j != b.j);
}


int main(){


  std::vector<int> v;
  for(unsigned int i = 0 ; i < 10 ; i++)
  {
    v.push_back(i);
  }
  std::vector<int>::iterator it = v.begin();
  //Soit on en utilise un autre
  std::vector<int>::iterator it2 = it+1;

  cout<<*it<<endl;
  cout<<*it2<<endl;
  //Soit on avance le premier
  std::advance(it,2);
  cout<<*(it)<<endl;
  cout<<*(it+1)<<endl;

  //Comparaison de deux points
  Point a = { 1 , 1 };
  Point b = { 2 , 2 };
  Point c = { 1 , 2 };


  if (a != b) cerr<<"a != b"<<endl;
  if (a != c) cerr<<"a != c"<<endl;


  return 0 ;
}
