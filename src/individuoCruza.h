#ifndef INDIVIDUOCRUZA_H_
#define INDIVIDUOCRUZA_H_

#include <algorithm>    // swap_ranges
#include <utils/eoParser.h>
#include <utils/eoRNG.h>
#include <es/eoReal.h>
#include <utils/eoRealBounds.h>
#include <utils/eoRealVectorBounds.h>

#include <Individuo.h>
#include <eoOp.h>


class individuoCruza : public eoQuadOp<Individuo>
{
    public:
        individuoCruza(const double& _eta = 1.0) :
        bounds(eoDummyVectorNoBounds), eta(_eta), range(1) {}

        individuoCruza(eoRealVectorBounds & _bounds, const double& _eta = 1.0) :
        bounds(_bounds), eta(_eta), range(1) {}

        individuoCruza(eoParser & _parser) :
        bounds (_parser.getORcreateParam(eoDummyVectorNoBounds, "objectBounds", "Bounds for variables", 'B', "Variation Operators").value()) , eta (_parser.getORcreateParam(1.0, "eta", "SBX eta parameter", '\0', "Variation Operators").value()) ,
        range(1) {}

        void setNoAnclas(int _NoAnclas);
//        void setGen(eoIncrementorParam<unsigned> * gen)
//        {
//        nbGenerations = gen;
//        }

        bool operator()(Individuo & _individuo1, Individuo & _individuo2);
    protected:
        eoRealVectorBounds & bounds;
//        eoIncrementorParam<unsigned>  * nbGenerations; /*!< number of generations */
        double eta;
        double range;
        int NoAnclas;
        int contador;                    // == 1
};

#endif // INDIVIDUOCRUZA_H
