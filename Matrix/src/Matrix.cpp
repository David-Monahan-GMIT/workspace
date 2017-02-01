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

Matrix::Matrix() {

	#if VERBOSE
		std::cout << "Default Constructor" << std::endl;
	#endif
	rows=10;
	cols=10;
	
	unsigned int i,j;
	unsigned int k =0;
	srand(time(NULL));
	
	if(mat != nullptr) {
		mat = new double* [rows];
		for(i=0;i<rows;i++) {
			mat[i] = new double[cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = k;
				k=rand()%100; // random number between 1-100
			}
		}	
	}
}
Matrix::Matrix(double num) {
	#if VERBOSE
		std::cout << "Initialising Constructor" << std::endl;
	#endif
	
	rows=10;
	cols=10;
	
	unsigned int i,j;
	
	if(mat != nullptr) {
		mat = new double* [rows];	// New is an operator that can be overloaded, or to add to an existing class
		for(i=0;i<rows;i++) {
			mat[i] = new double [cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = num;
			}
		}
	}	
}

Matrix::Matrix(unsigned int row, unsigned int col) {

	#if VERBOSE
		std::cout << "Custom Matrix Constructor" << std::endl;
	#endif
	rows=row;
	cols=col;
	
	unsigned int i,j;
	unsigned int k=1;
	if(mat != nullptr) {
		mat = new double* [rows];
		for(i=0;i<rows;i++) {
			mat[i] = new double[cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = k;
				k++;
			}
		}
	}	
}

Matrix::Matrix(Matrix& matCopy) {

	#if VERBOSE
		std::cout << "Copy Constructor" << std::endl;
	#endif

	rows=matCopy.getRows();
	cols=matCopy.getCols();

	unsigned int i,j;
	if(mat != nullptr) {
		mat = new double* [rows];
		for(i=0;i<rows;i++) {
			mat[i] = new double[cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = matCopy.getElement(i,j);
			}
		}
	}
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
}

unsigned int Matrix::getRows() {
	return rows;
}
unsigned int Matrix::getCols() {
	return cols;
}
double Matrix::getElement(unsigned int row, unsigned int col){
	// returns the element located at [row,col]
	return mat[row][col];
}

std::ostream& operator<<(std::ostream &output, Matrix &m) {
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
void Matrix::operator=(Matrix &matrix) {

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
		rows=matrix.getRows();
		cols=matrix.getCols();

		unsigned int i,j; // elements
		// Allocate memory for a new matrix and assign it's elements the correct values
		if(mat != nullptr) {
			mat = new double* [rows];
			for(i=0;i<rows;i++) {
				mat[i] = new double[cols];
				for(j=0;j<cols;j++) {
					mat[i][j] = matrix.getElement(i,j);
				}
			}
		}
	}
}
