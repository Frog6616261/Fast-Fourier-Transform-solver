#pragma once
#include <complex>
#include <vector>
#include <iostream>
#define c_double std::complex <double>
#define c_vector std::vector<c_double>
#define PI 	std::acos(-1);

//Discrete Fourier Transfom
class DFT
{
public:

	DFT();

	void SetArrayOfDFT(c_double* fillingArray, c_double* timeArray, int sizeOfArrays);
	void SetArrayOfDFT(c_vector& fillingArray, const c_vector timeArray);

private:

	int m_sizeOfArrays = 0;

	c_double GetTheComplexExp(int numberOfTheFrequency,
		int countOfTheValues,  int numberOftheValue);

	c_double GetTheAmplitude(int numberOfTheFrequency, const c_double* valueArray);
	c_double GetTheAmplitude(int numberOfTheFrequency, const c_vector valueArray);

	void DoDiscreteFourierTransfom(c_double* fillingArray,
		const c_double* timeArray, int sizeOfArrays);
	void DoDiscreteFourierTransfom(c_vector& fillingArray,
		const c_vector timeArray, int sizeOfArrays);


};

