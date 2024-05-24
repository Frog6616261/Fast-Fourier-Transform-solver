#pragma once
#include <cstdlib>
#include <complex>
#include <vector>

#define c_double std::complex<double>
#define c_vector std::vector<c_double>


class Randomizer
{
public:

	void SetRandomComplexNumbers(c_vector& fillingArray, int seed);
	void SetRandomComplexNumbers(c_double* fillingArray, int arraySize, int seed);

private:

	double GetRandNumb();

};

