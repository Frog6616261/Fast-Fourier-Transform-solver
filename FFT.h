#pragma once
#include <complex>
#include <vector>
#include <iostream>

#define c_double std::complex <double>
#define c_vector std::vector <c_double>
#define d_vector std::vector <double>
#define j std::complex <double>(0, 1)
#define PI std::acos(-1)
#define TWO_PI (2 * PI) 


class FFT
{
public:

	FFT(const c_vector vectorValueOfTimeFunc, const c_vector vectorValueOfFrequencyfunc);
	FFT(const c_double* vectorValueOfTimeFunc, const c_double* vectorValueOfFrequencyfunc, int sizeOfData);

	void PrintAllData();

	c_double* GetResultOutputTimeData();
	c_double* GetResultOutputFrequencyData();
	int GetSizeOfData();
	double GetAverageFrequencyEror(bool isRealEror);
	double GetAverageTimeEror(bool isRealEror);

	~FFT(); // delete m_tValIn, m_fValIn, m_tValOut, m_fValOut, m_primeNumbers


private:

	int m_N; //a number of all values of time function

	c_double* m_tValIn; //time value input
	c_double* m_fValIn; // frequency value input

	c_double* m_tValOut; //time value output
	c_double* m_fValOut; //frequency value output

	c_double* m_interVect; // intermediate vector for intermediate solve

	int* m_primeNumbers; // the vector of prime nimbers of number N
	int m_endPosPrime = 0; // end position of exsisting prime number in prime numbers array

	//the average error between the input and output variables
	double m_erFreqRe = 0;
	double m_erFreqIm = 0;

	double m_erTimeRe = 0;
	double m_erTimeIm = 0;


	void SetN(int countOfValues);
	void AllocateMemory();
	void FindAllPrimeNumbers();

	void SetModulVectorByVector(const c_double* inputVector, double* modulVector, int size);
	void SetAverageErrorValues();

	template<typename array>
	void FillTheInputVectors(array vectorValueOfTimeFunc, array vectorValueOfFrequencyfunc);


	c_double GetComplexExp(double N, double k, double n, double sign); // get the function exp(sign * j * TWO_PI * n * k / N)
	void SetArrayOfExp(c_double** array, int currentPrime, int currentSizeOfOutVector, int sign);

	void MakePermutationForFFT(c_double* inputVector, c_double* resultVector, int size);
	int GetPermutatonPosition(int inputPos);

	void MakeFFTOfVector(c_double* resultVector, int sizeVector); // Fast Fourier Transform for permutation vector

	void MakeInverseFFTOfVector(c_double* resultVector, int sizeVector); // inverse Fast Fourier Transform for permutation vector

	void ChangeFFTVector(c_double* inputVector, c_double* resultVector,
		int currentPrime, int sizeOfOutVectors, int sign); //multiplication input vector and array of exp for a current prime number 

	c_double GetComponentOfOutVector(int numberOfComponent, c_double** arrayOfExp,
		c_double* inputVector, int currentSizeOutVector, int currentPrime);

};

template<typename array>
inline void FFT::FillTheInputVectors(array vectorValueOfTimeFunc, array vectorValueOfFrequencyfunc)
{
	for (int number = 0; number < m_N; number++)
	{
		m_fValIn[number] = vectorValueOfFrequencyfunc[number];
		m_tValIn[number] = vectorValueOfTimeFunc[number];
	}
}

