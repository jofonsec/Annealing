#include <localizacionEval.h>
using namespace std;

void localizacionEval::operator()(Individuo & _Individuo){

double ErrorFit = 0.0, DisEstimada = 0.0;
//vector<double> _NoAncla;
//double DisReal[8][8];

//Iniciar los vectores de prueba
//double noancla[]={4,3,8,2.7};
//_NoAncla.insert(_NoAncla.begin(), noancla, noancla+4);

//Iniciar la Matriz de Distancias Reales
//    for (int i=0; i < 8; i++){
//        for (int j=0; j<8 ; j++){
//            DisReal[i][j]=0; // Se genera una matriz con puros ceros para luego reemplazar los valores correspondientes
//        }
//    }
//    DisReal[0][1]=4; DisReal[0][2]=2.5; DisReal[0][6]=2.5; DisReal[0][7]=2.1;
//    DisReal[1][2]=2.6; DisReal[1][3]=2.1; DisReal[1][4]=2.2; DisReal[0][5]=4.0;
//    DisReal[3][4]=2.1; DisReal[3][5]=2.0; DisReal[4][5]=1.5; DisReal[6][7]=1.8;

    for (int i= 0; i< NoAnclas; i++){
        for (int j= 0; j < _Individuo.size()/2; j++){
            if (DisReal[i][j] != 0){
                DisEstimada = sqrt(pow(vecAnclas[i*2] - _Individuo[j*2],2) + pow(vecAnclas[i*2+1] - _Individuo[j*2+1],2));
                ErrorFit = abs (DisEstimada - DisReal[i][j]) + ErrorFit;
            }
        }
    }

    for (int i= NoAnclas; i<_Individuo.size()/2;i++){
        for(int j=0; j< _Individuo.size()/2; j++){
            if (DisReal[i][j] != 0){
                        DisEstimada = sqrt(pow(_Individuo[i*2] - _Individuo[j*2],2) + pow(_Individuo[i*2+1] - _Individuo[j*2+1],2));
                        ErrorFit = abs(DisEstimada - DisReal[i][j]) + ErrorFit;
            }
        }
    }
    // Finalmente se debe agregar el fitness al cromosoma
    _Individuo.fitness(ErrorFit);
}

void localizacionEval::guardarDisReal(double _DisReal[100][100], int _NoAnclas, int _nodos){
    nodos = _nodos;
    NoAnclas = _NoAnclas;

    for (int i=0; i<nodos ; i++){
        for (int j=0; j<nodos; j++){
            DisReal[i][j] = _DisReal[i][j];
        }
    }
}

void localizacionEval::guardarAnclas(double _vecAnclas[20]){

     for (int i=0 ; i<NoAnclas*2 ; i++){
        vecAnclas[i] = _vecAnclas[i];
     }

}

void localizacionEval::muestraDisReal(){
   for (int i=0; i < nodos; i++){
        for (int j=0; j < nodos ; j++){
            std::cout << DisReal[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void localizacionEval::muestraAnclas(){
       for (int i=0; i < NoAnclas*2; i++){
            std::cout << vecAnclas[i] << "  ";
        }
}
