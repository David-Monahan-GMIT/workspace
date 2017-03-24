/*
 * Matrix.h
 *
 *  Created on: 14 Mar 2017
 *      Author: Dave
 */

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#define VERBOSE 1

#include <iostream>
#include <stdlib.h>
#include <vector>

namespace DavesMatrix {
template <class T>
	class Matrix {
		private:
			unsigned int rows;
			unsigned int cols;
			std::vector<std::vector<double> > mat;
			static int matrix_cnt;

		public:
			//constructors
					Matrix();
					Matrix(double num);
					Matrix(unsigned int row, unsigned int col);
					Matrix(const Matrix&);
					~Matrix();
				// Functions
					unsigned int getRows() const { return rows; }
					unsigned int getCols() const { return cols; }
					int getMatrixCnt() const { return matrix_cnt; }
					double getElement(unsigned int row, unsigned int col) const;
					void setElement(unsigned int row, unsigned int col, double i);
					std::vector<std::vector<double> > getMatrix() const { return mat; }
					//friend std::ostream &operator<<(std::ostream &, const Matrix &);
					Matrix& operator=(const Matrix &matrix);
					void operator+=(const Matrix &matrix);
					void operator-=(const Matrix &matrix);
					const bool operator==(const Matrix &matrix);
					const bool operator!=(const Matrix &matrix);
					const Matrix operator+(const Matrix &matrix) const;
					const Matrix operator-(const Matrix &matrix) const;
					const Matrix operator*(const Matrix &matrix) const;
					const double operator()(unsigned int, unsigned int);
	};
template <class T>
int Matrix<T>::matrix_cnt = 0;

template <class T>
Matrix<T>::Matrix() : rows(0), cols(0) {
	#if VERBOSE
		std::cout << "Default Constructor" << std::endl;
	#endif
	matrix_cnt++;
}

template <class T>
Matrix<T>::Matrix(double num) : rows(10), cols(10){
	#if VERBOSE
		std::cout << "Initialising Constructor" << std::endl;
	#endif


	mat.resize(rows);
	for(unsigned int i=0; i < mat.size(); i++)  {
		mat[i].resize(cols);
	}

	srand((unsigned int)num);
	for(unsigned int i=0;i<rows;i++) {
		for(unsigned int j=0;j<cols;j++) {
			mat[i][j] = rand()%100 +1;
		}
	}
	matrix_cnt++;
}

template <class T>
Matrix<T>::Matrix(unsigned int row, unsigned int col) : rows(row), cols(col) {

	#if VERBOSE
		std::cout << "Custom Matrix Constructor" << std::endl;
	#endif

	unsigned int k=1;
	mat.resize(rows);
	for(unsigned int i=0; i < mat.size(); i++)  {
		mat[i].resize(cols);
	}



	for(unsigned int i=0;i<rows;i++) {
		for(unsigned int j=0;j<cols;j++) {
			mat[i][j] = k;
			k++;
		}
	}
	matrix_cnt++;
}

template <class T>
Matrix<T>::Matrix(const Matrix& matCopy) : rows(0), cols(0) {

	#if VERBOSE
		std::cout << "Copy Constructor" << std::endl;
	#endif

	rows=matCopy.getRows();
	cols=matCopy.getCols();

	mat = matCopy.mat;
	matrix_cnt++;
}

template <class T>
Matrix<T>::~Matrix() {
	#if VERBOSE
		std::cout << "Default Destructor" << std::endl;
	#endif
	matrix_cnt--;
}

template <class T>
double Matrix<T>::getElement(unsigned int row, unsigned int col) const {
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
void Matrix<T>::setElement(unsigned int row, unsigned int col, double i){
	// sets the element located at [row,col]
	try {
		if (row <= rows && col <= cols) {
			mat[row][col] = i;
		} else {
			throw std::out_of_range("number out of range");
		}
	}
	catch (std::out_of_range & e) {
		std::cout <<"Exception: "<< e.what() << std::endl;
	}
}

template <class T>
std::ostream& operator<<(std::ostream &output, const Matrix<T> &m) {
	// Generate a formatted string for the matrix and return it
	unsigned int i,j;
	for(i=0; i<m.getRows();i++) {
		for(j=0;j<m.getCols();j++) {
			output << m.getElement(i,j) << " ";
		}
		output << std::endl;
	}
	return output;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &matrix) {

	// Check for self assignment
	if(this != &matrix){

		// Reassign the rows and cols
		rows = matrix.getRows();
		cols = matrix.getCols();
		mat = matrix.mat;
	}
	return *this;
}

template <class T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) const {
	Matrix<T> result(*this);
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
	if (mat == matrix.mat) {
		return true;
	} else {
		return false;
	}
}

template <class T>
const bool Matrix<T>::operator!=(const Matrix<T> &matrix) {
	return !(*this==matrix);
}

template <class T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const {
	std::cout << "Compare rows to cols: " << matrix.getRows() << " " << cols << std::endl;
	if(matrix.getRows() == cols) {
		double temp = 0;
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
const double Matrix<T>::operator()(unsigned int i, unsigned int j) {
	return mat[i][j];
}


}
#endif /* SRC_MATRIX_H_ */
