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
    static float Determinant(const Matrix& mat);
    static float Cofactor(const Matrix& mat, int m, int n);
    static void Inverse(const Matrix& mat);

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
