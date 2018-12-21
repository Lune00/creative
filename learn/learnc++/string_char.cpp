#include<iostream>
#include<string>

using namespace std;

int main(){
  cout<<"Hello string/char"<<endl;
  string s="Hello";
  char c = s[0];
  char last= s.back();
  string cas(1,last);
  cout<<s<<" "<<last<<endl;
  return 0;
}
