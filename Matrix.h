#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
public:
    Matrix(int m, int n);
    ~Matrix();
    void Init();
    float** GetMatrixPtr()const;
    int GetRows()const;
    int GetColumns()const;
    void PrintMatrix();
    float Determinant();
    void Cofactor(int m, int n);

private:
    //Helper functions       
    void CreateMatrix();
    void FillMatrix();
    //Size of the matrix
    int m_rows;
    int m_cols;
    float** m_matrix;
};

#endif
