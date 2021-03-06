/*
 * Matrix.cpp
 *
 *  Created on: 24 Jan 2017
 *      Author: Dave
 */
#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Matrix.h"

namespace DavesMatrix {

int Matrix::matrix_cnt = 0;
Matrix::Matrix() : rows(0), cols(0), mat(nullptr) {

	#if VERBOSE
		std::cout << "Default Constructor" << std::endl;
	#endif
	matrix_cnt++;
}

Matrix::Matrix(double num) : rows(10), cols(10), mat(nullptr) {
	#if VERBOSE
		std::cout << "Initialising Constructor" << std::endl;
	#endif
	srand((unsigned int)num);
	
	unsigned int i,j;

	mat = new double* [rows];	// New is an operator that can be overloaded, or to add to an existing class
	for(i=0;i<rows;i++) {
		mat[i] = new double [cols];
		for(j=0;j<cols;j++) {
			mat[i][j] = rand()%100 +1;
		}
	}
	matrix_cnt++;
}

Matrix::Matrix(unsigned int row, unsigned int col) : rows(row), cols(col), mat(nullptr) {

	#if VERBOSE
		std::cout << "Custom Matrix Constructor" << std::endl;
	#endif
	//rows=row;
	//cols=col;
	
	unsigned int i,j;
	unsigned int k=1;
	mat = new double* [rows];
	for(i=0;i<rows;i++) {
		mat[i] = new double[cols];
		for(j=0;j<cols;j++) {
			mat[i][j] = k;
			k++;
		}
	}
	matrix_cnt++;
}

Matrix::Matrix(const Matrix& matCopy) : rows(0), cols(0), mat(nullptr) {

	#if VERBOSE
		std::cout << "Copy Constructor" << std::endl;
	#endif

	rows=matCopy.getRows();
	cols=matCopy.getCols();

	unsigned int i,j;

	mat = new double* [rows];
	for(i=0;i<rows;i++) {
		mat[i] = new double[cols];
		for(j=0;j<cols;j++) {
			mat[i][j] = matCopy.getElement(i,j);
		}
	}
	matrix_cnt++;

}

Matrix::~Matrix() {
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


double Matrix::getElement(unsigned int row, unsigned int col) const {
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

void Matrix::setElement(unsigned int row, unsigned int col, double i){
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

std::ostream& operator<<(std::ostream &output, const Matrix &m) {
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

Matrix& Matrix::operator=(const Matrix &matrix) {

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

		mat = new double* [rows];
		for(i=0;i<rows;i++) {
			mat[i] = new double[cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = matrix.getElement(i,j);
			}
		}
	}
	return *this;
}

const Matrix Matrix::operator+(const Matrix &matrix) const {
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

const Matrix Matrix::operator-(const Matrix &matrix) const {
	Matrix result(*this);
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

void Matrix::operator+=(const Matrix &matrix) {
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				mat[i][j] += matrix.getElement(i,j);
			}
		}
	}
}

void Matrix::operator-=(const Matrix &matrix) {
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				mat[i][j] -= matrix.getElement(i,j);
			}
		}
	}
}

const bool Matrix::operator==(const Matrix &matrix) {
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

const bool Matrix::operator!=(const Matrix &matrix) {
	return !(*this==matrix);
}

const Matrix Matrix::operator*(const Matrix &matrix) const {
	std::cout << "Compare rows to cols: " << matrix.getRows() << " " << cols << std::endl;
	if(matrix.getRows() == cols) {
		double temp = 0;
		Matrix result(rows, matrix.getCols());
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

const double Matrix::operator()(unsigned int i, unsigned int j) {
	return *(*mat +i) +j;
}

}
