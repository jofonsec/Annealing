#include "individuoCruza.h"

bool individuoCruza::operator()(Individuo & _individuo1, Individuo & _individuo2)
{
    double r1, r2, beta;

    for (unsigned i=NoAnclas*2; i<_individuo1.size(); i++)
    {
        double u = rng.uniform(range);

        if ( u <= 0.5 )
            beta = exp( (1/(eta+1))*log(2*u));
        else
            beta = exp((1/(eta+1))*log(1/(2*(1-u))));

        r1=_individuo1[i];
        r2=_individuo2[i];
        _individuo1[i] =0.5*((1+beta)*r1+(1-beta)*r2);
        _individuo2[i] =0.5*((1-beta)*r1+(1+beta)*r2);

        if(!(bounds.isInBounds(i,_individuo1[i]))) //Verifica si elemento se encuentra dentro de los limites especificados
            bounds.foldsInBounds(i,_individuo1[i]); //Ingresa un valor dentro de los limites
        if(!(bounds.isInBounds(i,_individuo2[i])))
            bounds.foldsInBounds(i,_individuo2[i]);
    }
}

void individuoCruza::setNoAnclas(int _NoAnclas){
    NoAnclas = _NoAnclas;
}

//void individuoCruza::setContinuator(eoGenContinue<Individuo> & _eoGenContinuador){
//
//    nbGenerations = gen;
//}

