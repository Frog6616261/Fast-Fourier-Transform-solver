#pragma once
#include <complex>
//#include <math.h>
#include <iostream>
#define c_double std::complex <double>
#define PI 	std::acos(-1);

//Discrete Fourier Transfom
class DFT
{
public:

	DFT();
	DFT(const double* valueArray, const double* timeArray, const int sizeOfArrays);

	void DoDiscreteFourierTransfom(const double* valueArray,
		const double* timeArray, const int sizeOfArrays);

	void SetArrayOfDFT(c_double* fillingArray, c_double* timeArray, int sizeOfArrays);

	int GetsizeOfTheArrays();
	c_double* GetArrayOfFrequencies();


	void PrintTheResultData();

	~DFT(); // delete arrays: value, time, frequency, amplitude

private:

	int m_sizeOfArrays = 10;


	double* m_frequency;
	c_double* m_amplitude;
	double* m_amplitudeReal;
	double* m_amplitudeImag;

	void AllocateMemoryForArrays();

	c_double GetTheComplexExp(const int numberOfTheFrequency,
		const int countOfTheValues, const int numberOftheValue);

	c_double GetTheAmplitude(const int numberOfTheFrequency, const double* valueArray);



};

