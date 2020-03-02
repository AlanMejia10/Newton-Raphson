#include <iostream>
#include "Matrix.h"

int main(){
    int m, n;
    std::cout<<"Metodo de Newton Raphson"<<std::endl;
    std::cout<<"Ingresa el numero de filas: ";
    std::cin>>m;
    std::cout<<"Ingresa el numero de columnas: ";
    std::cin>>n;
    Matrix matA(m,n);
    matA.Init();
    matA.PrintMatrix();
    std::cout<<std::endl;
    float result = Matrix::Determinant(matA);
    std::cout<<"el det es: "<<result<<std::endl;
    Matrix::Inverse(matA);
    std::cout<<std::endl;
    Matrix::Transpose(matA);
    return 0;
}
