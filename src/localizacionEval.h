#include <Individuo.h>
#include <eoEvalFunc.h>

class localizacionEval : public eoEvalFunc<Individuo>
{
    double DisReal[100][100];
    double vecAnclas[20];
    int NoAnclas; //Cantidad nodos anclas
    int nodos; //Total de nodos
public:
    void operator()(Individuo & _Individuo);
    void guardarDisReal(double _DisReal[100][100], int _NoAnclas, int _nodos);
    void guardarAnclas(double _vecAnclas[20]);
    void muestraDisReal();
    void muestraAnclas();
};
