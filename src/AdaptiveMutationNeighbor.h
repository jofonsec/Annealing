#ifndef _AdaptiveMutationNeighbor_h
#define _AdaptiveMutationNeighbor_h

#include <neighborhood/moBackableNeighbor.h>
#include <utils/eoRNG.h>

template<class EOT, class Fitness = typename EOT::Fitness>
class AdaptiveMutationNeighbor: public moBackableNeighbor<EOT, Fitness>
{
public:
  AdaptiveMutationNeighbor(double _desplazaProbabi, const double _FitnessIni, unsigned int& _NoAnclas) :
  desplazaProbabi(_desplazaProbabi), FitnessIni(_FitnessIni), NoAnclas(_NoAnclas) {}

  virtual void move(EOT& _solution) {
    unsigned i=0;
    double desplazamiento;
    do {
      i++;
      if ( rng.flip(desplazaProbabi) ) {
        desplazamiento = CalcularD(_solution);
        _solution[i] = _solution[i] + desplazamiento;
      }
    } while(i != _solution.size());
  }

  virtual void moveBack(EOT& _solution) {
    move(_solution);
  }

  void setIndices(unsigned int _first, unsigned int _second) {
		indices.first = _first;
		indices.second = _second;
	}

  void getIndices(unsigned int & _first, unsigned int & _second) {
    _first = indices.first;
    _second = indices.second;
  }

  void print() {
    std::cout << "[" << indices.first << ", " << indices.second << "] -> "
        << (*this).fitness() << std::endl;
  }

private:
  std::pair<unsigned int, unsigned int> indices;
  double desplazaProbabi;
  double FitnessIni;
  int NoAnclas;

  double CalcularD (EOT& _solution) {
    double FitnessAct;
    double Peso;
    double D;

    FitnessAct = _solution.fitness();
    /*Peso del desplazamiento*/
    Peso = FitnessIni/FitnessAct;

    /*Generar un numero aleatorio dentro del rango permitido*/
    D = rng.normal(0,90);

    /*Calculo del desplazamiento*/
    return(D*Peso);
};

#endif
