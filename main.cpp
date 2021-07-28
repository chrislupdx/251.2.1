#include <iostream>
//#include <set>
#include <iterator>
#include <algorithm> //not sure
#include <sstream> //this one is for istringstream i believe
#include <string>
#include <vector>
#include <cmath>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;
vector<string> slice(vector<string> const &v, int  m, int n);
bool inbounds(int val);
int main()
{

  bool good = false;

  int n; //between 1 < n < 2^500
  while(!good)
  {
    cout << "specify n:" << endl;
    cin >> n;
    cin.ignore(100, '\n');
    if(inbounds(n)) //i think this is imperfect
    {
      good = true; 
    }
    else
    {
      cout << "out of bounds, re-specify" << endl;
    }
  }

  //1. accept a list of n elements of a single line (seperated by space). The elements are strings) with no embeded spaces). this is set a.
  cout << "specify " << n << " number items for set A:" << endl;
  string lineval;
  std::getline(cin, lineval);
  vector<string> first = {};
  istringstream iss(lineval);
  copy(istream_iterator<string>(iss),
      istream_iterator<string>(),
      back_inserter(first));
  vector<string> cleaned_first = slice(first, 0, n);

  vector<string>::iterator itr;
  cout << "first: " << endl;
  for(itr = cleaned_first.begin(); itr < cleaned_first.end(); itr++)
  {
    cout << *itr << " ";
  }

  cout << endl;
  //2. accept a second list of n elements on a single line (separted by space). The elements are strings (with no embedded spaces). The is set B.
  cout << "specify " << n << " number items for set B:" << endl;
  string valtwo;
  std::getline(cin,valtwo);
  vector<string> two = {};
  istringstream tss(valtwo);
  copy(istream_iterator<string>(tss),
      istream_iterator<string>(),
      back_inserter(two));
  vector<string> cleaned_two = slice(two, 0, n);

  vector<string>::iterator sitr;
  cout << "second: " << endl;
  for(sitr = cleaned_two.begin(); sitr < cleaned_two.end(); sitr++)
  {
    cout << *sitr << " ";
  }

  //3. display each:
  //1. cardinality and roster of teh intersection of A and B
  vector<string> d1;
  set_intersection(cleaned_first.begin(), cleaned_first.end(), 
      cleaned_two.begin(), cleaned_two.end(), 
      back_inserter(d1));
  cout << endl;
  cout << "Intersection of A and B:" << d1.size() << endl;
  vector<string>::iterator it1;
  for(it1 = d1.begin(); it1 < d1.end(); it1++)
  {
    cout << *it1 << " ";
  }
  cout << endl;

  //2. cardinality and roster of union of a and b
  vector<string> d2;
  set_union(cleaned_first.begin(), cleaned_first.end(),
      cleaned_two.begin(), cleaned_two.end(),
      back_inserter(d2));
  cout << endl;
  cout << "Union of A and B:" << d2.size() << endl;
  vector<string>::iterator it2;
  for(it2 = d2.begin(); it2 < d2.end(); it2++)
  {
    cout << *it2 << " ";
  }
  cout << endl;

  //3. cardinality and roster of the relative complement of a and b aka result of  (a - b) 
  vector<string> d3;
  set_difference(cleaned_first.begin(), cleaned_first.end(), 
      cleaned_two.begin(), cleaned_two.end(), 
      back_inserter(d3));
  cout << endl;
  cout << "Relative complement of A and B:" << d3.size() << endl;
  vector<string>::iterator it3;
  for(it3 = d3.begin(); it3 < d3.end(); it3++)
  {
    cout << *it3 << " ";
  }
  cout << endl;

  //4. cardinality and roster of the relative complement of B and A aka result of  (b - a)
  vector<string> d4;
  set_difference(cleaned_two.begin(), cleaned_two.end(), 
      cleaned_first.begin(), cleaned_first.end(), 
      back_inserter(d4));
  cout << endl;
  cout << "Relative complement of A and B:" << d4.size() << endl;
  vector<string>::iterator it4;
  for(it4 = d4.begin(); it4 < d4.end(); it4++)
  {
    cout << *it4 << " ";
  }
  cout << endl;

  //5. cardinatliy and roster of teh symmetric differenf of a and b 
  vector<string> d5;
  set_symmetric_difference(cleaned_first.begin(), cleaned_first.end(),
      cleaned_two.begin(), cleaned_two.end(),
      back_inserter(d5));
  cout << "Symmetric difference between A and B:" << d5.size() << endl;
  vector<string>::iterator it5;
  for(it5 = d5.begin(); it5 < d5.end(); it5++)
  {
    cout << *it5 << " ";
  }
  cout << endl;

  //6. cardinatliy and roster of the cross product of a and b
  vector<string> d6, d7;
  vector<string>::iterator it6, it7;

  int total = cleaned_first.size() * cleaned_two.size();
  cout << "The cross product between A and B:" << total << endl;
  for(it6 = cleaned_first.begin(); it6 < cleaned_first.end(); it6++)
  {
    for(it7 = cleaned_two.begin(); it7 < cleaned_two.end(); it7++)
    {
      cout << "(" << *it6 << "," << *it7 << ")" << endl;
    }
  }

  //7. cardinatliy of the power set of the cross product of a and b 
  int val = pow(2, (cleaned_first.size() + cleaned_two.size()));
  cout << "The cardinality of the power set of the cross product A and B is " << val << endl; 

  return 1;
}

vector<string> slice(vector<string> const &v, int  m, int n)
{
  auto first = v.cbegin() + m;
  auto last = v.cbegin() + n; //took off the + 1

  std::vector<string> vec(first, last);
  return vec;
}

bool inbounds(int val) //this one acts out
{
  mpz_class temp(val), MAX, MIN;

  //temp = val; //TODO this is not correct
  mpz_ui_pow_ui (MAX.get_mpz_t(), 2, 500);
  MIN = 1;
  if(temp >= MIN && temp <= MAX)
  {
    return true;
  }
  return false;
}

