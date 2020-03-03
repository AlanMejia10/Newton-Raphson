#include <iostream>
#include <cmath>
#include "Matrix.h"

void Portada();
void Menu();
void Sistema1();
void Sistema2();
void Sistema3();
void Sistema4();
bool Tolerance(const Matrix& mat, float tol);

int main(){
    int opc;
    char decision;
    Portada();
    do{
    Menu();
    std::cout<<"Elige el sistema de ecuaciones a resolver: ";
    std::cin>>opc;

    switch (opc){
        case 1:
            Sistema1();
            break;
        case 2:
            Sistema2();
            break;
        case 3:
            Sistema3();
            break;
        case 4:
            Sistema4();
            break;
        default:
            std::cout<<"Opcion incorrecta"<<std::endl;
    }
    std::cout<<"¿Te gustaria resolver otro sistema? (y/n)";
    std::cin>>decision;
    }while(decision == 'y');
    return 0;
}

void Portada(){
    std::cout<<"Metodos Numericos II"<<std::endl;
    std::cout<<"Metodo de Newton Raphson (Sistemas no lineales)"<<std::endl;
    std::cout<<"Profesora: Carrillo Ramirez Teresa"<<std::endl;
    std::cout<<"Integrantes:"<<std::endl;
    std::cout<<"Diaz Lopez Alan Fernando"<<std::endl;
    std::cout<<"Mejia Espinosa Ruben Alan"<<std::endl;
    std::cout<<"Grupo: 2401\n"<<std::endl;
}

void Menu(){
    std::cout<<"Metodo de Newton Raphson\n"<<std::endl;
    std::cout<<"1) f1(x, y) = x^2+xy-10=0\n   f2(x, y) = y+3xy^2-50=0\n\n"
    <<"2) f1(x, y) = x^2+y^2-9=0\n   f2(x, y) = -e^x-2y-3=0\n\n"
    <<"3) f1(x, y, z) = 2x^2-4x+y^2+3z^2+6z+2=0\n   f2(x, y, z) = x^2+y^2-2y+2z^2-5=0\n   f3(x, y, z) = 3x^2-12x+y^2-3z^2+8=0\n\n"
    <<"4) f1(x, y, z) = x^2-4x+y^2=0\n   f2(x, y, z) = x^2-x-12y+1=0\n   f3(x, y, z) = 3x^2-12x+y^2-3z^2+8=0\n\n";
}

void Sistema1(){
    int numItr;
    float tolerancia;
    // Creacion de meoria dinamica de la matriz jacobiana y la matriz de la funcion
    Matrix f(2,1);
    f.CreateMatrix();
    float** fPtr= f.GetMatrixPtr();

    Matrix j(2,2);
    j.CreateMatrix();
    float** jPtr = j.GetMatrixPtr();

    //Creacion del punto inicial x
    Matrix x(2,1);
    std::cout<<"Ingresa el valor del vector incial x: "<<std::endl;
    x.Init();
    float** xPtr = x.GetMatrixPtr();

    std::cout<<"Ingresa el numero de iteraciones: ";
    std::cin>>numItr;
    std::cout<<"\nSi se llega a la tolerancia el programa terminara \ny ya no se ejecutaran las siguientes iteraciones\n"<<std::endl;
    std::cout<<"Ingresa el valor de la tolerancia: ";
    std::cin>>tolerancia;
    
    for(int i=0; i<numItr; ++i){
        //Evaluacion de la matriz funcion
        //f1(x, y) = x²+xy-10=0
        fPtr[0][0]= pow(xPtr[0][0],2) + xPtr[0][0]*xPtr[1][0]-10;
        //f2(x, y) = y+3xy²-50=0
        fPtr[1][0] = xPtr[1][0] + 3*xPtr[0][0]*pow(xPtr[1][0],2)-50;

        //Evaluacion de la matriz jacobiana (derivadas parciales)
        jPtr[0][0] = 2*xPtr[0][0]+xPtr[1][0];
        jPtr[0][1] = xPtr[0][0];
        jPtr[1][0] = 3*pow(xPtr[1][0],2);
        jPtr[1][1] = 6*xPtr[0][0]*xPtr[1][0]+1;

        //Algoritmo de Newton Raphson
        Matrix matJacInv = Matrix::Inverse(j);
        Matrix jInvFunc = Matrix::Mult(matJacInv, f);
        Matrix newX = Matrix::Subtract(x, jInvFunc);
        float** newXPtr = newX.GetMatrixPtr();

        xPtr[0][0] = newXPtr[0][0];
        xPtr[1][0] = newXPtr[1][0];
        
        if(Tolerance(f, tolerancia) || i==numItr-1){
            if(Tolerance(f, tolerancia))
                std::cout<<"Tolerancia alcanzada en iteracion: "<<i<<std::endl;
            std::cout<<"Vector solucion: "<<std::endl;
            x.PrintMatrix();
            break;
        }
    }
}

void Sistema2(){
    int numItr;
    float tolerancia;
    // Creacion de meoria dinamica de la matriz jacobiana y la matriz de la funcion
    Matrix f(2,1);
    f.CreateMatrix();
    float** fPtr= f.GetMatrixPtr();

    Matrix j(2,2);
    j.CreateMatrix();
    float** jPtr = j.GetMatrixPtr();

    //Creacion del punto inicial x
    Matrix x(2,1);
    std::cout<<"Ingresa el valor del vector incial x: "<<std::endl;
    x.Init();
    float** xPtr = x.GetMatrixPtr();

    std::cout<<"Ingresa el numero de iteraciones: ";
    std::cin>>numItr;

    std::cout<<"\nSi se llega a la tolerancia el programa terminara \ny ya no se ejecutaran las siguientes iteraciones\n"<<std::endl;
    std::cout<<"Ingresa el valor de la tolerancia: ";
    std::cin>>tolerancia;
    
    for(int i=0; i<numItr; ++i){
        //Evaluacion de la matriz funcion
        //f1(x, y) = x²+y²-9=0
        fPtr[0][0]= pow(xPtr[0][0],2) + pow(xPtr[1][0],2) - 9;
        //f2(x, y) = -e^x-2y-3=0
        fPtr[1][0] = -exp(xPtr[0][0])-2*xPtr[1][0]-3;

        //Evaluacion de la matriz jacobiana (derivadas parciales)
        jPtr[0][0] = 2*xPtr[0][0];
        jPtr[0][1] = 2*xPtr[1][0];
        jPtr[1][0] = -exp(xPtr[0][0]);
        jPtr[1][1] = -2;

        //Algoritmo de Newton Raphson
        Matrix matJacInv = Matrix::Inverse(j);
        Matrix jInvFunc = Matrix::Mult(matJacInv, f);
        Matrix newX = Matrix::Subtract(x, jInvFunc);
        float** newXPtr = newX.GetMatrixPtr();

        xPtr[0][0] = newXPtr[0][0];
        xPtr[1][0] = newXPtr[1][0];
    
        if(Tolerance(f, tolerancia) || i==numItr-1){
            if(Tolerance(f, tolerancia))
                std::cout<<"Tolerancia alcanzada en iteracion: "<<i<<std::endl;
            std::cout<<"Vector solucion: "<<std::endl;
            x.PrintMatrix();
            break;
        }
    }
}

void Sistema3(){
int numItr;
    float tolerancia;
    // Creacion de meoria dinamica de la matriz jacobiana y la matriz de la funcion
    Matrix f(3,1);
    f.CreateMatrix();
    float** fPtr= f.GetMatrixPtr();

    Matrix j(3,3);
    j.CreateMatrix();
    float** jPtr = j.GetMatrixPtr();

    //Creacion del punto inicial x
    Matrix x(3,1);
    std::cout<<"Ingresa el valor del vector incial x: "<<std::endl;
    x.Init();
    float** xPtr = x.GetMatrixPtr();

    std::cout<<"Ingresa el numero de iteraciones: ";
    std::cin>>numItr;

    std::cout<<"\nSi se llega a la tolerancia el programa terminara \ny ya no se ejecutaran las siguientes iteraciones\n"<<std::endl;
    std::cout<<"Ingresa el valor de la tolerancia: ";
    std::cin>>tolerancia;
    
    for(int i=0; i<numItr; ++i){
        //Evaluacion de la matriz funcion
        //f1(x, y, z) = 2x²-4x+y²+3z²+6z+2=0
        fPtr[0][0]= 2*pow(xPtr[0][0],2)-4*xPtr[0][0]+pow(xPtr[1][0],2)+3*pow(xPtr[2][0],2)+6*xPtr[2][0]+2;
        //f2(x, y, z) = x²+y²-2y+2z²-5=0
        fPtr[1][0] = pow(xPtr[0][0],2) + pow(xPtr[1][0],2) -2*xPtr[1][0] + 2*pow(xPtr[2][0],2)-5;
        //f3(x, y, z) = 3x²-12x+y²-3z²+8=0
        fPtr[2][0] = 3*pow(xPtr[0][0],2)-12*xPtr[0][0]+pow(xPtr[1][0],2)-3*pow(xPtr[2][0],2)+8;

        //Evaluacion de la matriz jacobiana (derivadas parciales)
        jPtr[0][0] = 4*xPtr[0][0]-4;
        jPtr[0][1] = 2*xPtr[1][0];
        jPtr[0][2] = 6*4*xPtr[0][0]+6;
        jPtr[1][0] = 2*xPtr[0][0];
        jPtr[1][1] = 2*xPtr[1][0]-2;
        jPtr[1][2] = 4*xPtr[2][0];
        jPtr[2][0] = 6*xPtr[0][0]-12;
        jPtr[2][1] = 2*xPtr[1][0];
        jPtr[2][2] = -6*xPtr[2][0];

        //Algoritmo de Newton Raphson
        Matrix matJacInv = Matrix::Inverse(j);
        Matrix jInvFunc = Matrix::Mult(matJacInv, f);
        Matrix newX = Matrix::Subtract(x, jInvFunc);
        float** newXPtr = newX.GetMatrixPtr();

        xPtr[0][0] = newXPtr[0][0];
        xPtr[1][0] = newXPtr[1][0];
        xPtr[2][0] = newXPtr[2][0];
        
        if(Tolerance(f, tolerancia) || i==numItr-1){
            if(Tolerance(f, tolerancia))
                std::cout<<"Tolerancia alcanzada en iteracion: "<<i<<std::endl;
            std::cout<<"Vector solucion: "<<std::endl;
            x.PrintMatrix();
            break;
        }
    }
}

void Sistema4(){
    int numItr;
    float tolerancia;
    // Creacion de meoria dinamica de la matriz jacobiana y la matriz de la funcion
    Matrix f(3,1);
    f.CreateMatrix();
    float** fPtr= f.GetMatrixPtr();

    Matrix j(3,3);
    j.CreateMatrix();
    float** jPtr = j.GetMatrixPtr();

    //Creacion del punto inicial x
    Matrix x(3,1);
    std::cout<<"Ingresa el valor del vector incial x: "<<std::endl;
    x.Init();
    float** xPtr = x.GetMatrixPtr();

    std::cout<<"Ingresa el numero de iteraciones: ";
    std::cin>>numItr;

    std::cout<<"\nSi se llega a la tolerancia el programa terminara \ny ya no se ejecutaran las siguientes iteraciones\n"<<std::endl;
    std::cout<<"Ingresa el valor de la tolerancia: ";
    std::cin>>tolerancia;
    
    for(int i=0; i<numItr; ++i){
        //Evaluacion de la matriz funcion
        //f1(x, y, z) = x²-4x+y²=0
        fPtr[0][0]= pow(xPtr[0][0],2)-4*xPtr[0][0]+pow(xPtr[1][0],2);
        //f2(x, y, z) = x²-x-12y+1=0
        fPtr[1][0] = pow(xPtr[0][0],2)-xPtr[0][0]-12*xPtr[1][0]+1;
        //f3(x, y, z) = 3x²-12x+y²-3z²+8=0
        fPtr[2][0] = 3*pow(xPtr[0][0],2)-12*xPtr[0][0]+pow(xPtr[1][0],2)-3*pow(xPtr[2][0],2)+8;

        //Evaluacion de la matriz jacobiana (derivadas parciales)
        jPtr[0][0] = 2*xPtr[0][0]-4;
        jPtr[0][1] = 2*xPtr[1][0];
        jPtr[0][2] = 0;
        jPtr[1][0] = 2*xPtr[0][0]-1;
        jPtr[1][1] = -12;
        jPtr[1][2] = 0;
        jPtr[2][0] = 6*xPtr[0][0]-12;
        jPtr[2][1] = 2*xPtr[1][0];
        jPtr[2][2] = -6*xPtr[2][0];

        //Algoritmo de Newton Raphson
        Matrix matJacInv = Matrix::Inverse(j);
        Matrix jInvFunc = Matrix::Mult(matJacInv, f);
        Matrix newX = Matrix::Subtract(x, jInvFunc);
        float** newXPtr = newX.GetMatrixPtr();

        xPtr[0][0] = newXPtr[0][0];
        xPtr[1][0] = newXPtr[1][0];
        xPtr[2][0] = newXPtr[2][0];
        
        if(Tolerance(f, tolerancia) || i==numItr-1){
            if(Tolerance(f, tolerancia))
                std::cout<<"Tolerancia alcanzada en iteracion: "<<i<<std::endl;
            std::cout<<"Vector solucion: "<<std::endl;
            x.PrintMatrix();
            break;
        }
    }
}

bool Tolerance(const Matrix& mat, float tol){
    float** matPtr = mat.GetMatrixPtr();
    for(int i=0; i<mat.GetRows(); ++i){
        if(fabs(matPtr[i][0]) > tol){
            return false;
        }
    }
    return true;
}