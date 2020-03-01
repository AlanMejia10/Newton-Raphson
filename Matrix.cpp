#include <iostream>
#include <cmath>
#include "Matrix.h"

Matrix::Matrix(int m, int n) : m_rows(m), m_cols(n) {}

Matrix::~Matrix(){
    for(int i = 0; i < m_rows; ++i)
        delete[] m_matrix[i];

    delete[] m_matrix;
}

float** Matrix::GetMatrixPtr()const { return m_matrix; }

int Matrix::GetRows()const { return m_rows; }

int Matrix::GetColumns()const{ return m_cols; }

void Matrix::Init(){
    CreateMatrix();
    FillMatrix();
}

void Matrix::CreateMatrix(){
    m_matrix = new float*[m_rows];

    for(int i = 0; i < m_rows; i++)
        m_matrix[i] = new float[m_cols];
}

void Matrix::FillMatrix(){
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_cols; ++j){
            std::cout<<"matrix["<<i+1<<"]["<<j+1<<"]: ";
            std::cin>>m_matrix[i][j];
    }
}

void Matrix::PrintMatrix(){
    for(int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_cols; ++j)
            std::cout<<m_matrix[i][j]<<"\t";

        std::cout<<std::endl;
    }
}

float Matrix::Determinant(){
    float det;
    // for(int j = 0; j < m_cols; ++j)
    // det = m_matrix[0][j] * Cofactor(0, j);
    Cofactor(0,0);
    return 0;
}

void Matrix::Cofactor(int m, int n){
    int k = 0, l = 0;
    Matrix cofMat(m_rows-1, m_cols-1);
    cofMat.CreateMatrix();
    float** subMat = cofMat.GetMatrixPtr();

    for(int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_cols; ++j){
            if(i != m && j != n){
                if(l < 2){
                    subMat[k][l] = m_matrix[i][j];
                    ++l;
                }else{
                    ++k;
                    l=0;
                    subMat[k][l] = m_matrix[i][j];
                    ++l;
                }
            }
        }
    }

    cofMat.PrintMatrix();
}

























