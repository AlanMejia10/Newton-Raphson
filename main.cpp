#include <iostream>
#include "Matrix.h"

int main(){
    std::cout<<"Metodo de Newton Raphson"<<std::endl;
    Matrix matA(2,2);
    matA.Init();
    matA.PrintMatrix();
    std::cout<<std::endl;
    matA.Determinant();
    return 0;
}
