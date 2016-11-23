#include <Individuo.h>
#include <eoEvalFunc.h>

class localizacionEvalPenal : public eoEvalFunc<Individuo>
{
    double DisReal[200][200];
    double vecAnclas[40];
    double radio;
    int NoAnclas; //Cantidad nodos anclas
    int nodos; //Total de nodos

public:
    void operator()(Individuo & _Individuo);
    void guardarDisReal(double _DisReal[200][200], int _NoAnclas, int _nodos, double _radio);
    void guardarAnclas(double _vecAnclas[40]);
    void muestraDisReal();
    void muestraAnclas();
};
