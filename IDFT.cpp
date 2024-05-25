#include "IDFT.h"

IDFT::IDFT()
{
}

void IDFT::SetArrayOfIDFT(c_double* fillingArray, c_double* freqArray, int sizeOfArrays)
{
	m_sizeOfArrays = sizeOfArrays;

	DoInverseDiscreteFourierTransfom(fillingArray, freqArray, m_sizeOfArrays);
}

void IDFT::SetArrayOfIDFT(c_vector& fillingArray, const c_vector freqArray)
{
	m_sizeOfArrays = freqArray.size();

	DoInverseDiscreteFourierTransfom(fillingArray, freqArray, m_sizeOfArrays);
}

c_double IDFT::GetTheComplexExp(const int numberOfTheFrequency, const int countOfTheValues, const int numberOftheValue)
{
	double k = numberOfTheFrequency;
	double n = numberOftheValue;
	double N = countOfTheValues;

	double Arg = 2 * PI;
	Arg = Arg * k;
	Arg = Arg * (n / N);

	double cos = std::cos(Arg);
	double sin = std::sin(Arg);

	return c_double(cos, sin);
}

c_double IDFT::GetTheAmplitude(const int numberOfTheFrequency, const c_double* freqArray)
{
	int N = m_sizeOfArrays;
	int k = numberOfTheFrequency;

	c_double result = c_double(0, 0);

	for (int n = 0; n < N; n++)
	{
		c_double a = freqArray[n] * GetTheComplexExp(k, N, n);
		result += a;
	}

	return ( result / static_cast<double>(m_sizeOfArrays));
}

c_double IDFT::GetTheAmplitude(const int numberOfTheFrequency, const c_vector freqArray)
{
	int N = m_sizeOfArrays;
	int k = numberOfTheFrequency;

	c_double result = c_double(0, 0);

	for (int n = 0; n < N; n++)
	{
		c_double a = freqArray[n] * GetTheComplexExp(k, N, n);
		result += a;
	}

	return (result / static_cast<double>(m_sizeOfArrays));
}

void IDFT::DoInverseDiscreteFourierTransfom(c_double* fillingArray, const c_double* freqArray, const int sizeOfArrays)
{
	for (int k = 0; k < sizeOfArrays; k++)
	{
		fillingArray[k] = GetTheAmplitude(k, freqArray);
	}
}

void IDFT::DoInverseDiscreteFourierTransfom(c_vector& fillingArray, const c_vector freqArray, const int sizeOfArrays)
{
	for (int k = 0; k < sizeOfArrays; k++)
	{
		fillingArray[k] = GetTheAmplitude(k, freqArray);
	}
}
