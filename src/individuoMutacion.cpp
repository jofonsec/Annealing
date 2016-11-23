#include <individuoMutacion.h>


individuoMutacion::individuoMutacion(){}

bool individuoMutacion::operator()(Individuo& _Individuo){
/**
  *
  *
  */

    double s = pow(_max-_min, 2); //Calculo del area de trabajo, es fijo
    double idealDistance = sqrt(s/nodos); // es la distancia ideal, es fijo
    double r; //Es el radio aproximado, se calcula por generacion
    double f, theta=0;

    //Obtiene la generación actual
    int t = atoi(nbGenerations->getValue().c_str());

    r = idealDistance * (1-(t/T));

    for(int i=noAnclas; i<nodos; i++){
	//generar numeros aleatorios
//	f = (double)rand() / RAND_MAX;
//	theta = 0 + f * (360-0);
    theta = eo::rng.uniform(0.0,360.0);
        _Individuo[i*2] = _Individuo[i*2] + r * cos(theta);
        _Individuo[i*2+1] = _Individuo[i*2+1] + r * sin(theta);
    }

    return true;
}

individuoMutacion::individuoMutacion(int _noAnclas, int _geneTotal, int _nodos, double minimo, double maximo){
    noAnclas = _noAnclas;
    T = _geneTotal;
    nodos = _nodos;
    _min = minimo;
    _max = maximo;
}

void individuoMutacion::setGen(eoIncrementorParam<unsigned> * gen){
    nbGenerations = gen;
}
