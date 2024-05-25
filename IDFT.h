#pragma once
#include <complex>
#include <vector>
#include <iostream>
#define c_double std::complex <double>
#define c_vector std::vector<c_double>
#define PI 	std::acos(-1);

//Discrete Fourier Transfom
class IDFT
{
public:

	IDFT();

	void SetArrayOfIDFT(c_double* fillingArray, c_double* freqArray, int sizeOfArrays);
	void SetArrayOfIDFT(c_vector& fillingArray, const c_vector freqArray);

private:

	int m_sizeOfArrays = 0;

	c_double GetTheComplexExp(const int numberOfTheFrequency,
		const int countOfTheValues, const int numberOftheValue);

	c_double GetTheAmplitude(const int numberOfTheFrequency, const c_double* freqArray);
	c_double GetTheAmplitude(const int numberOfTheFrequency, const c_vector freqArray);

	void DoInverseDiscreteFourierTransfom(c_double* fillingArray,
		const c_double* freqArray, const int sizeOfArrays);
	void DoInverseDiscreteFourierTransfom(c_vector& fillingArray,
		const c_vector freqArray, const int sizeOfArrays);


};

