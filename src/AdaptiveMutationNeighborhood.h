#ifndef _AdaptiveMutationNeighborhood_h
#define _AdaptiveMutationNeighborhood_h

#include <AdaptiveMutationNeighbor.h>
#include <neighborhood/moNeighborhood.h>

template< class Neighbor >
class AdaptiveMutationNeighborhood : public moNeighborhood<Neighbor>
{
public:
  typedef typename Neighbor::EOT EOT;

  virtual bool hasNeighbor(EOT& _solution) {
      return (_solution.size() > 1);
  };

/* Selecciona los indices de la solucion a intervenir*/

  virtual void init(EOT& _solution, Neighbor& _current) {
    indices.first=NoAnclas*2;
    indices.second=NoAnclas*2+1;
    _current.setIndices(indices.first,indices.second);
  }

  virtual void next(EOT& _solution, Neighbor& _current) {
    std::cout << "Se ejecuto y debo revisar" << '\n';
  }

  virtual bool cont(EOT& _solution) {
      return !((indices.first == (_solution.size()-2)) && (indices.second == (_solution.size()-1)));
  }

  virtual std::string className() const {
      return "AdaptiveMutationNeighborhood";
  }
private:
  std::pair<unsigned int, unsigned int> indices;
  int NoAnclas;

};

#endif
