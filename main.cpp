#include <iostream>
#include <algorithm> 
#include <string>
#include <gmpxx.h>
#include <gmp.h>
#include <set>
#include <iterator>
//#include <sstream> //is this one needed
#include <vector>
//#include <cmath>

using namespace std;
vector<string> slice(vector<string> const &v, int  m, int n);
//bool inbounds(int val); //TODO gmp intger here
void getandFillSet(string &input, const mpz_t &n, const mpz_t &halt, set<string> &set1); //TODO GRAFT PATTERN
void printSet(set<string> & set1);
int main()
{
   string input;
   mpz_t n, halt;
   set<string> set1;
   set<string> set2;
   set<string> setOpcontainer;

   //init gmp
   mpz_init(n);
   mpz_init(halt);
   mpz_set_ui(halt, 0);
   cout << "Enter the set cardinatiy n(a positive int between 0 and 2 and 2^500: " << endl; //#TODO CHECK IS TRUE
   getline(cin, input); 

   mpz_set_str(n, input.c_str(), 10);
   gmp_printf("print output GMP style. \ninput size - %Zd\n", n);
   getandFillSet(input, n, halt, set1);
   getandFillSet(input, n, halt, set2);
   cout << endl << "Set 1 elements are: ";
   printSet(set1);
   cout << endl << "Set 2 elements are: ";
   printSet(set2);
  
  //1
   set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
            inserter(setOpcontainer, setOpcontainer.begin()));
   cout << endl << "Union of A and B has " << setOpcontainer.size() << "elements: ";
   printSet(setOpcontainer);
   setOpcontainer.clear();
   mpz_clear(n);
   mpz_clear(halt);
   
   //2
   set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
      inserter(setOpcontainer, setOpcontainer.begin()));

   cout << endl << "Intersection of A nd B has" << setOpcontainer.size() << "elements: ";
   printSet(setOpcontainer);
   setOpcontainer.clear();
   mpz_clear(n);
   mpz_clear(halt);

   //3
   set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
      inserter(setOpcontainer, setOpcontainer.begin()));

   cout << endl << "Relative Complement of A nd B has" << setOpcontainer.size() << "elements: ";
   printSet(setOpcontainer);
   setOpcontainer.clear();
   mpz_clear(n);
   mpz_clear(halt);


    set_difference(set2.begin(), set2.end(), set1.begin(), set1.end(),
      inserter(setOpcontainer, setOpcontainer.begin()));

    cout << endl << "Relative Complement of B nd A has" << setOpcontainer.size() << "elements: ";
    printSet(setOpcontainer);
    setOpcontainer.clear();
    mpz_clear(n);
    mpz_clear(halt);
    
    //4
    set_symmetric_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
      inserter(setOpcontainer, setOpcontainer.begin()));

    cout << endl << "Symmetric differnce between A and B has" << setOpcontainer.size() << "elements: ";
    printSet(setOpcontainer);
    setOpcontainer.clear();
    mpz_clear(n);
    mpz_clear(halt);

    //cardinality and roster of the cross product a and b
   
    mpz_t total, a;
    mpz_init(total);
    mpz_set_ui(total, 100);
    gmp_printf("\n Total is %s is an mpz %Zd \n", total);
    //mpz_init(a); 
    //mpz_set_ui(a, set1.size());
    //mpz_mul_si(total, a ,set2.size());
    //int total = set1.size() * set2.size(); //TODO should this be in gmp SEG FAUILT
    
    //gmp_printf("Cardinality and roster of teh cross product of A and B: %s is an mpz %Zd\n", total);
    //cout << endl << "Cardinality and roster of the cross prodcut of A and B:" << total << endl; 
    for( string const& A: set1)
    {
      for(string const& B: set2)
      {
        cout << "(" << A << "," << B << ")" << endl;
      }
    }

    mpz_clear(total);
    mpz_clear(a);

    //the cardinality of the power set of the cross product of a and b

    //mpz_t pow;
    //mpz_init(pow);
    //whats the base
    //mpz_ui_pow_ui(pow, unsigned long int base, unsinged long int exp);

    //, set1s, set2s,base, exp;
    //mpz_init(base);
    //mpz_init(exp);
    //mpz_init(set1s);
    //mpz_init(set2s);
    //mpz_set_ui(pow, 0); //TODO
    //mpz_set_ui(set1s, set1.size());
    //mpz_set_ui(set2s, set2.size());
    //mpz_set_ui(exp, 0); //douuno if necessary
    //mpz_set_ui(base, 2);
    //mpz_add(exp, set1s, set2s); //set1s = set1s + set2s?
    //int val = set1.size() + set2.size();
    //mpz_ui_pow_ui(pow, 2, val);
    //mpz_pow_ui(pow, base, val);  
    //mpz_pow_ui(pow,2,set1.size() + set2.size());  
    //mpz_pow_ui(pow,2,set1.size() + set2.size());  //
    //cout << "The cardinality of the power set of the cross product of A and B is " << pow << endl;
    //mpz_clear(set1s);
    //mpz_clear(set2s);
    //mpz_clear(base);

    //int val = pow(3, (set1.size() + set2.size()));
    //cout << "The cardinality of the power set of the cross product of A and B is " << pow << endl;
    //mpz_clear(pow);
  return 1;
}

void printSet(set<string>&set1) {
  cout << endl;
  for (string const& A: set1)
  {
    cout << A << ' ';
  }
}

//gmp style gather+insert into vector
void getandFillSet(string &input, const mpz_t &ctr, const mpz_t &halt, set<string> &set1)
{
    mpz_t n;
    mpz_init(n);
    mpz_set(n, ctr);
    cout << endl << "Enter a set of strings separated by space. No more than " << n << " elements would be taken -> ";
    do
    {
      cin >> input;
      set1.insert(input);
      mpz_sub_ui(n,n,1); //n = n - 1 GMP style
    }while(mpz_cmp(n, halt) != 0); //n != 0
    cin.ignore(80, '\n');
    cin.clear();
    mpz_clear(n);
}
