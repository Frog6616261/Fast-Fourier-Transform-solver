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


class IFFT
{
public:

	IFFT(int sizeOFInputVectors);
	IFFT(const c_vector vectorValueOfFrequencyfunc);
	IFFT(const c_double* vectorValueOfFrequencyfunc, int sizeOfData);

	void PrintTimeDataResult();

	template<typename array>
	void FillTheInputVectors(array vectorValueOfFrequencyfunc);
	void MakeInverseFFT();


	c_double* GetResultOutputTimeData();
	int GetSizeOfData();


	~IFFT(); // delete m_tValIn, m_fValIn, m_tValOut, m_fValOut, m_primeNumbers


private:

	int m_N; //a number of all values of time function

	c_double* m_fValIn; // frequency value inputd
	c_double* m_tValOut; //time value output

	c_double* m_interVect; // intermediate vector for intermediate solve

	int* m_primeNumbers; // the vector of prime nimbers of number N
	int m_endPosPrime = 0; // end position of exsisting prime number in prime numbers array


	void SetN(int countOfValues);
	void AllocateMemory();
	void FindAllPrimeNumbers();


	c_double GetComplexExp(double N, double k, double n, double sign); // get the function exp(sign * j * TWO_PI * n * k / N)
	void SetArrayOfExp(c_double** array, int currentPrime, int currentSizeOfOutVector, int sign);

	void MakePermutationForFFT(c_double* inputVector, c_double* resultVector, int size);
	int GetPermutatonPosition(int inputPos);

	void MakeInverseFFTOfVector(c_double* resultVector, int sizeVector); // inverse Fast Fourier Transform for permutation vector

	void ChangeIFFTVector(c_double* inputVector, c_double* resultVector,
		int currentPrime, int sizeOfOutVectors, int sign); //multiplication input vector and array of exp for a current prime number 

	c_double GetComponentOfOutVector(int numberOfComponent, c_double** arrayOfExp,
		c_double* inputVector, int currentSizeOutVector, int currentPrime);

};

template<typename array>
inline void IFFT::FillTheInputVectors(array vectorValueOfFrequencyfunc)
{
	for (int number = 0; number < m_N; number++)
	{
		m_fValIn[number] = vectorValueOfFrequencyfunc[number];
	}
}


