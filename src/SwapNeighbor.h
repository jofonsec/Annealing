#ifndef _SwapNeighbor_h
#define _SwapNeighbor_h

#include <neighborhood/moBackableNeighbor.h>

/**
 * Swap Neighbor
 */
template<class EOT, class Fitness = typename EOT::Fitness>
class SwapNeighbor: public moBackableNeighbor<EOT, Fitness> {
public:

	/**
	 * Apply the swap
	 * @param _solution the solution to move
	 */
	virtual void move(EOT& _solution) {
		//std::cout << "indice "<< indices.first << " Valor de la posicion "<< _solution[indices.first] <<'\n';
		//std::cout << "indice "<< indices.second << " Valor de la posicion "<< _solution[indices.second] <<'\n';
		k++;
		//std::cout << "Ejecucion Numero de Neighbor.move: " << k << '\n';
		//EOT tmp(1);
		//tmp[0] = _solution[indices.first];
		//_solution[indices.first] = _solution[indices.second];
		//_solution[indices.second] = tmp[0];
		//_solution.invalidate();
		std::swap(_solution[indices.first],_solution[indices.second]);

		//std::cout << "indice "<< indices.first << " Valor de la posicion "<< _solution[indices.first] <<'\n';
		//std::cout << "indice "<< indices.second << " Valor de la posicion "<< _solution[indices.second] <<'\n';
	}

	/**
	 * apply the swap to restore the solution (use by moFullEvalByModif)
	 * @param _solution the solution to move back
	 */
	virtual void moveBack(EOT& _solution) {
		move(_solution);
	}

	/**
	 * Setter to fix the two indexes to swap
	 * @param _first first index
	 * @param _second second index
	 */
	void setIndices(unsigned int _first, unsigned int _second) {
		indices.first = _first;
		indices.second = _second;
	}

	/**
	 * Get the two indexes to swap
	 * @param _first first index
	 * @param _second second index
	 */
	void getIndices(unsigned int & _first, unsigned int & _second) {
		_first = indices.first;
		_second = indices.second;
	}

	/**
	 * @param _neighbor a neighbor
	 * @return if _neighbor and this one are equals
	 */
	virtual bool equals(SwapNeighbor<EOT,Fitness>& _neighbor) {
		unsigned f, s;
		_neighbor.getIndices(f, s);
		return (((indices.first == f) && (indices.second == s)) || ((indices.first == s) && (indices.second == f)));
	}

	/**
	 * Print the Neighbor
	 */
	void print() {
		std::cout << "[" << indices.first << ", " << indices.second << "] -> "
				<< (*this).fitness() << std::endl;
	}

private:
	std::pair<unsigned int, unsigned int> indices;
	unsigned k;
};

#endif
