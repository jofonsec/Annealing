#include <Individuo.h>
#include <eoOp.h>
//Desde
class individuoMutacion : public eoMonOp<Individuo>
{
    public:
        bool operator()(Individuo & _Individuo);

        /// Constructor vacio
        individuoMutacion();

        /// Constructor principal
        individuoMutacion(int _noAnclas, int _geneTotal, int _nodos, double minimo, double maximo);


        /// Nombre de la clase
        virtual std::string className() const { return "Single-vertex-neighborhood-mutation"; }

        ///Cargar parametros
        //void setDatos(int _noAnclas, int _geneTotal, int _nodos, double _min, double _max);
        void setGen(eoIncrementorParam<unsigned> * gen);

    private:
        double _min, _max;
        int t; //generación actual
        int T; //total de generaciones, es fijo
        int noAnclas;
        int nodos; //Total de nodos, es fijo
        eoIncrementorParam<unsigned>  * nbGenerations; /*!< numero de generaciones */

};
