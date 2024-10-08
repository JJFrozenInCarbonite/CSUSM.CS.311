/**********************************
Template prepared by Kazumi Slott
CS311

matrix class

Replace the ?????s

For examples of matrix multiplication
https://matrix.reshish.com/multCalculation.php 

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent?: 1
Any difficulties?: Empress ran out of storage
***********************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

//This forward declaration of Matrix class is necessary because the following operator>> and << are using Matrix as a parameter
template <class T>
class Matrix;

//This forward declaration of operator>> is necessary Since operator<< is a template function.
template<class T>
ifstream& operator>>(ifstream& o, Matrix<T>& m);

//This forward declaration of operator<< is necessary Since operator<< is a template function.
template <class T>
ostream& operator<<(ostream& o, const Matrix<T> & m);

//Template class so we can have a matrix of any data types, int or double
template <class T>
class Matrix
{
  //friend functions so they can access the private members 
  friend ostream& operator<< <T>(ostream& o, const Matrix<T> & m);
  friend ifstream& operator>> <T>(ifstream& o, Matrix<T>& m);

private: 
  T** m; //2 dimensional dynamic array
  const int R; //number of rows
  const int C; //number of columns

public: 
  Matrix(int R, int C);
  Matrix();
  ~Matrix();
  Matrix operator*(const Matrix& other);// matrix multiplication
  Matrix operator~(); // matrix transposition

  // Exception class for size errors
  class size_error : public std::exception {
  private:

    // Error message
    const char* message; 
  public:

  // Constructor to set the error message
    explicit size_error(const char* msg) : message(msg) {}

    // Override the what function to return the error message
    const char* what() const noexcept override {
      return message;
    }
  };
};

//default constructor
template<class T>
Matrix<T>::Matrix() : R(0), C(0) //setting const R and C to initial value, 0.
{
  m = NULL;
}

//constructor to create a matrix, row x col 
template<class T>
Matrix<T>::Matrix(int row, int col) : R(row), C(col) //setting const R and C 
{
  if(row <= 0 || col <= 0)
    {
      m = NULL;
      return;
    }

  //m = new T[R][C]; //this doesn't compile
  m = new T*[R]; //create a single dimensional array of pointers of the T type
  for (int i=0; i<R; i++) //create a single dimensional array for each slot of m
    m[i] = new T[C];

  //initialize each element to 0
  for(int rw = 0; rw < R; rw++)
    for(int cl = 0; cl < C; cl++)
	m[rw][cl] = 0;
}

//fill a matrix using an input file
template<class T>
ifstream& operator>>(ifstream& fin, Matrix<T>& mrx)
{
  // Loop over the rows of the matrix
  for(int i = 0; i < mrx.R; i++) {
    
    // Iterate over columns of the matrix
    for(int j = 0; j < mrx.C; j++) {

      // Read the element and store it in the matrix
      fin >> mrx.m[i][j];
    }
  }

  // Return the stream
  return fin;
}

  /*output the matrix to screen in the following format. Allocate 10 spaces for each value.
         1          1          1
         2          2          2
         3          3          3
         4          4          4 
  */
template<class T>
ostream& operator<<(ostream& o, const Matrix<T>& mrx)
{
  // Loop over the rows of the matrix
  for(int i = 0; i < mrx.R; i++) {

    // Iterate over columns of the matrix
    for(int j = 0; j < mrx.C; j++) {

      // Add an element with 10 space width to the stream
      o << std::setw(10) << mrx.m[i][j];
    }
    // Send a new line to the stream
    o << std::endl;
  }
  // Return the stream
  return o;
}

//matrix multiplication
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
  // Check if the matrices are compatible for multiplication
  if (C != other.R) {

    // Throw an exception if the matrices are incompatible
    throw size_error("Matrices have incompatible dimensions for multiplication");
  }

  // Create a result matrix with dimensions R x other.C
  Matrix<T> result(R, other.C);

  // Loop over the rows of the result matrix
  for (int i = 0; i < R; ++i) {

    // Iterate over columns of the result matrix
    for (int j = 0; j < other.C; ++j) {

      // Initialize the element to 0
      result.m[i][j] = 0; 

      // Perform matrix multiplication
      for (int k = 0; k < C; ++k) {

        // Perform matrix multiplication
        result.m[i][j] += m[i][k] * other.m[k][j];
      }
    }
  }

  // Return the result matrix
  return result;
}

// Matrix transposition
template<class T>
Matrix<T> Matrix<T>::operator~()
{
  // Create a result matrix with dimensions C x R
  Matrix<T> result(C, R);

  // Loop over the rows of the original matrix
  for (int i = 0; i < R; ++i) {

    // Loop over the columns of the original matrix
    for (int j = 0; j < C; ++j) {

      // Assign the element at (i, j) in the original matrix to (j, i) in the result matrix
      result.m[j][i] = m[i][j];
    }
  }

  // Return the result matrix
  return result;
}

//destructor                                                                                                                                                                                        
template<class T>
Matrix<T>::~Matrix()
{
  // Delete the matrix
  if (m != nullptr) {

    // Delete each row
    for (int i = 0; i < R; ++i) {

      // Delete each row
      delete[] m[i]; 
    }
    // Delete the array of row pointers
    delete[] m; 

    // Set the matrix pointer to nullptr
    m = nullptr; 
  }
}