/******************************************
Template prepared by Kazumi Slott
CS311

Description of this program: Housing price calculator using matrix transposition and multiplication

Your name: JJ Hoffmann
Your programmer number: 16
Number of hours you spent: 1.5
Any difficulties?: I wrote a transposition operator in matrix.h so I could write both sets of source data left-to-right
without having to transpose it manually, but then I realized that the source data probably would be in the other format 
so I ended up not using it, but I left it in matrix.h.
*******************************************/
#include <iostream>
using namespace std;

#include "matrix.h"

int main()
{
  Matrix<double> house_info(4, 4); // 4 rows x 4 columns (sq ft, bedrooms, age, and constant 1)
  Matrix<double> house_func(4, 3); // 3 rows (house 1, house 2, house 3) x 4 columns (coefficients for sq ft, bedrooms, age, and constant 1) 
  ifstream fin;

  fin.open("house_info.in");
  fin >> house_info;
  fin.close();

  fin.open("house_func.in");
  fin >> house_func;
  fin.close();

  try
  {
    Matrix<double> result = house_info * house_func;
    cout << result << endl;
  }
  catch(Matrix<double>::size_error)
  {
    cout << "SIZE ERROR" << endl;
  }

  return 0;
}
