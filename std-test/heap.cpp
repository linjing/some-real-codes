// range heap example
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main (){
  int myints[]={10,20,30,5,15};
  vector<int> v(myints,myints+5);
  vector<int>::iterator it;

  make_heap (v.begin(),v.end());
  cout<<"initial max heap : "<< v.front()<< endl;

  cout<< "after make_heap: ";
  for(unsigned i=0; i<v.size(); i++)cout<<" "<< v[i];
  cout<< endl;

  pop_heap (v.begin(),v.end());
  cout<< "after pop_heap: ";
  for(unsigned i=0; i<v.size(); i++)cout<<" "<< v[i];
  cout<< endl;
  v.pop_back();
  cout<<"max heap after pop : "<< v.front()<< endl;

  v.push_back(99); push_heap (v.begin(),v.end());
  cout<<"max heap after push: "<< v.front()<< endl;
  cout<< "after push_heap: ";
  for(unsigned i=0; i<v.size(); i++)cout<<" "<< v[i];
  cout<< endl;
  v.pop_back();

  sort_heap (v.begin(),v.end());

  cout<<"final sorted range :";
  for(unsigned i=0; i<v.size(); i++)cout<<" "<< v[i];

  cout<< endl;

  return 0;
}
