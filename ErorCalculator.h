#pragma once

#include <complex>
#include <iostream>

#define c_double std::complex<double>

class ErrorCalculator
{
public:

	ErrorCalculator();
	ErrorCalculator(const c_double* firstVector, const c_double* secondVector, int sizeOfVectors);

	void CalculateAverageError(const c_double* firstVector, const c_double* secondVector, int sizeOfVectors);

	template <typename vector>
	double GetAveregeErrorByVectors(const vector firstVector, const vector secondVector, int sizeOfVectors);

	double GetRealError();
	double GetImagError();

	void PrintError();


private:

	//the average error between the input and output variables
	double m_erRe = 0; // average error of real values
	double m_erIm = 0; // average erroe of imaginary values

};

template<typename vector>
inline double ErrorCalculator::GetAveregeErrorByVectors(const vector firstVector, const vector secondVector, int sizeOfVectors)
{
	double result = 0;

	for (int k = 0; k < sizeOfVectors; k++)
		result += std::abs(firstVector[k] - secondVector[k]);
	
	return (result / static_cast<double>(sizeOfVectors));
}
