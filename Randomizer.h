#pragma once
#include <cstdlib>
#include <complex>
#include <vector>

#define c_double std::complex<double>
#define c_vector std::vector<c_double>


class Randomizer
{
public:

	void SetRandomComplexNumbers(c_vector& fillingArray, int seed, bool isOnlyReal);
	void SetRandomComplexNumbers(c_double* fillingArray, int arraySize, int seed, bool isOnlyReal);

private:

	double GetRandNumb();

};

