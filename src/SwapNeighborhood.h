#ifndef _SwapNeighborhood_h
#define _SwapNeighborhood_h

#include <SwapNeighbor.h>
#include <neighborhood/moNeighborhood.h>

/**
 * Swap Neighborhood
 */
template< class Neighbor >
class SwapNeighborhood : public moNeighborhood<Neighbor>
{
public:

    typedef typename Neighbor::EOT EOT;

    /**
     * @return true if there is at least an available neighbor
     */
    virtual bool hasNeighbor(EOT& _solution) {
        return (_solution.size() > 1);
    };

    /**
     * Initialization of the neighborhood
     * @param _solution the solution to explore
     * @param _current the first neighbor
     */
    virtual void init(EOT& _solution, Neighbor& _current) {
        //Debe ser una solucion aleatoria en el vecindario
        // indices.first=0;
        // indices.second=1;
        // _current.setIndices(0,1)
        unsigned i, j;
        k++;
        i=eo::rng.random(_solution.size());
        do j = eo::rng.random(_solution.size()); while (i == j);
        //std::cout << "Ejecucion Numero de Neighborhood.init: " << k << '\n';
        _current.setIndices(i,j);
    }

    /**
     * Give the next neighbor
     * @param _solution the solution to explore
     * @param _current the next neighbor
     */
    virtual void next(EOT& _solution, Neighbor& _current) {
        if (indices.second==_solution.size()-1) {
            indices.first++;
            indices.second=indices.first+1;
        }
        else
            indices.second++;
        _current.setIndices(indices.first, indices.second);
    }

    /**
     * Test if there is again a neighbor
     * @param _solution the solution to explore
     * @return true if there is again a neighbor not explored
     */
    virtual bool cont(EOT& _solution) {
        return !((indices.first == (_solution.size()-2)) && (indices.second == (_solution.size()-1)));
    }

    /**
     * Return the class Name
     * @return the class name as a std::string
     */
    virtual std::string className() const {
        return "SwapNeighborhood";
    }

    bool isRandom() {
        return true;
    }

private:
    std::pair<unsigned int, unsigned int> indices;
    unsigned k;

};

#endif
