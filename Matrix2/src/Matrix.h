/*
 * Matrix.h
 *
 *  Created on: 24 Jan 2017
 *      Author: Dave
 */

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#define VERBOSE 1

#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>     /* srand, rand */
//namespace DavesMatrix {

template <class T>
class Matrix {
	private:
		unsigned int rows;
		unsigned int cols;
		T **mat;
		static int matrix_cnt;
		
	public:
	//constructors
		Matrix();
		Matrix(T num);
		Matrix(unsigned int row, unsigned int col);
		Matrix(const Matrix&);
		~Matrix();
	// Functions
		unsigned int getRows() const { return rows; }
		unsigned int getCols() const { return cols; }
		int getMatrixCnt() const { return matrix_cnt; }

		T getElement(unsigned int row, unsigned int col) const;
		void setElement(unsigned int row, unsigned int col, T i);
	//	friend std::ostream &operator<<(std::ostream &, const Matrix &);
		Matrix& operator=(const Matrix &matrix);
		void operator+=(const Matrix &matrix);
		void operator-=(const Matrix &matrix);
		const bool operator==(const Matrix &matrix);
		const bool operator!=(const Matrix &matrix);
		const Matrix operator+(const Matrix &matrix) const;
		const Matrix operator-(const Matrix &matrix) const;
		const Matrix operator*(const Matrix &matrix) const;
		const T operator()(unsigned int, unsigned int);

	};
template <class T>
int Matrix<T>::matrix_cnt = 0;

template <class T>
Matrix<T>::Matrix() : rows(0), cols(0), mat(nullptr) {

	#if VERBOSE
		std::cout << "Default Constructor" << std::endl;
	#endif
	matrix_cnt++;
}

template <class T>
Matrix<T>::Matrix(T num) : rows(10), cols(10), mat(nullptr) {
	#if VERBOSE
		std::cout << "Initialising Constructor" << std::endl;
	#endif
	srand((unsigned int)num);

	unsigned int i,j;

	mat = new T* [rows];	// New is an operator that can be overloaded, or to add to an existing class
	for(i=0;i<rows;i++) {
		mat[i] = new T [cols];
		for(j=0;j<cols;j++) {
			mat[i][j] = rand()%100 +1;
		}
	}
	matrix_cnt++;
}

template <class T>
Matrix<T>::Matrix(unsigned int row, unsigned int col) : rows(row), cols(col), mat(nullptr) {

	#if VERBOSE
		std::cout << "Custom Matrix Constructor" << std::endl;
	#endif
	//rows=row;
	//cols=col;

	unsigned int i,j;
	unsigned int k=1;
	mat = new T* [rows];
	for(i=0;i<rows;i++) {
		mat[i] = new T[cols];
		for(j=0;j<cols;j++) {
			mat[i][j] = k;
			k++;
		}
	}
	matrix_cnt++;
}

template <class T>
Matrix<T>::Matrix(const Matrix& matCopy) : rows(0), cols(0), mat(nullptr) {

	#if VERBOSE
		std::cout << "Copy Constructor" << std::endl;
	#endif

	rows=matCopy.getRows();
	cols=matCopy.getCols();

	unsigned int i,j;

	mat = new T* [rows];
	for(i=0;i<rows;i++) {
		mat[i] = new T[cols];
		for(j=0;j<cols;j++) {
			mat[i][j] = matCopy.getElement(i,j);
		}
	}
	matrix_cnt++;

}

template <class T>
Matrix<T>::~Matrix() {
	#if VERBOSE
		std::cout << "Default Destructor" << std::endl;
	#endif
	if(mat != nullptr){
		for(unsigned int i=0; i<rows; i++) {
			delete [] mat[i];
		}
		delete [] mat;
	}
	matrix_cnt--;
}

template <class T>
T Matrix<T>::getElement(unsigned int row, unsigned int col) const {
	try {
		if (row <= rows && col <= cols) {
			return mat[row][col];
		} else {
			throw std::out_of_range("number out of range");

		}
	}
	catch (std::out_of_range & e) {
		std::cout <<"Exception: "<< e.what() << std::endl;
	}
	return 0;
}

template <class T>
void Matrix<T>::setElement(unsigned int row, unsigned int col, T i){
	// sets the element located at [row,col]
	try {
		if (row <= rows && col <= cols) {
			mat[row][col] = (T) i;
		} else {
			throw std::out_of_range("number out of range");
		}
	}
	catch (std::out_of_range & e) {
		std::cout <<"Exception: "<< e.what() << std::endl;
	}
}
// DavesMatrix::operator<<(std::ostream&, DavesMatrix::Matrix<double> const&)
template <class T>
std::ostream& operator<<(std::ostream &output, const Matrix<T> &m) {
	// Generate a formatted string for the matrix and return it
	unsigned int i,j;
	for(i=0; i<m.getRows();i++) {
		for(j=0;j<m.getCols();j++) {
			output << (m.getElement(i,j)) << " ";
		}
		output << std::endl;
	}
	return output;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &matrix) {

	// Check for self assignment
	if(this != &matrix){

		// If it's not null delete whatever it has
		if(mat != nullptr){
			for(unsigned int i=0; i<rows; i++) {
				delete [] mat[i];
			}
			delete [] mat;
		}

		// Reassign the rows and cols
		rows = matrix.getRows();
		cols = matrix.getCols();

		unsigned int i,j; // elements
		// Allocate memory for a new matrix and assign it's elements the correct values

		mat = new T* [rows];
		for(i=0;i<rows;i++) {
			mat[i] = new T[cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = matrix.getElement(i,j);
			}
		}
	}
	return *this;
}

template <class T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) const {
	Matrix result(*this);
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				result.setElement(i,j, (mat[i][j] + matrix.getElement(i,j)));
			}
		}
	}
	return result;
}

template <class T>
const Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix) const {
	Matrix<T> result(*this);
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				result.setElement(i,j, (mat[i][j] - matrix.getElement(i,j)));
			}
		}
	}
	return result;
}

template <class T>
void Matrix<T>::operator+=(const Matrix<T> &matrix) {
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				mat[i][j] += matrix.getElement(i,j);
			}
		}
	}
}

template <class T>
void Matrix<T>::operator-=(const Matrix<T> &matrix) {
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				mat[i][j] -= matrix.getElement(i,j);
			}
		}
	}
}

template <class T>
const bool Matrix<T>::operator==(const Matrix<T> &matrix) {
	if(matrix.getCols() == cols && matrix.getRows() == rows) {
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				if(mat[i][j] != matrix.getElement(i,j)) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

template <class T>
const bool Matrix<T>::operator!=(const Matrix<T> &matrix) {
	return !(*this==matrix);
}

template <class T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const {
	std::cout << "Compare rows to cols: " << matrix.getRows() << " " << cols << std::endl;
	if(matrix.getRows() == cols) {
		T temp = 0;
		Matrix<T> result(rows, matrix.getCols());
		for(unsigned int i=0;i<rows;i++) {
			for(unsigned int j=0;j<matrix.getCols();j++) {
				for(unsigned int m=0; m<cols; m++) {
					temp += mat[i][m] * matrix.getElement(m,j);
				}
				result.setElement(i,j,temp);
				temp=0;
			}
		}
		return result;
	} else {
		return *this;
	}
}

template <class T>
const T Matrix<T>::operator()(unsigned int i, unsigned int j) {
	return (T) (*(*mat +i) +j);
}

//}
#endif //SRC_MATRIX_H_
