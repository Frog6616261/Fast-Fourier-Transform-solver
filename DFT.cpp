#include "DFT.h"


DFT::DFT()
{

}

void DFT::SetArrayOfDFT(c_double* fillingArray, c_double* timeArray, int sizeOfArrays)
{
	m_sizeOfArrays = sizeOfArrays;

	DoDiscreteFourierTransfom(fillingArray, timeArray, m_sizeOfArrays);
}

void DFT::SetArrayOfDFT(c_vector& fillingArray, const c_vector timeArray)
{
	m_sizeOfArrays = timeArray.size();

	DoDiscreteFourierTransfom(fillingArray, timeArray, m_sizeOfArrays);
}

void DFT::DoDiscreteFourierTransfom(c_double* fillingArray, const c_double* timeArray, int sizeOfArrays)
{
	for (int k = 0; k < sizeOfArrays; k++)
	{
		fillingArray[k] = GetTheAmplitude(k, timeArray);
	}
}

void DFT::DoDiscreteFourierTransfom(c_vector& fillingArray, const c_vector timeArray, int sizeOfArrays)
{
	for (int k = 0; k < sizeOfArrays; k++)
	{
		fillingArray[k] = GetTheAmplitude(k, timeArray);
	}
}

c_double DFT::GetTheComplexExp(int numberOfTheFrequency,
	int countOfTheValues, int numberOftheValue)
{
	double k = numberOfTheFrequency;
	double n = numberOftheValue;
	double N = countOfTheValues;

	double Arg = (-2) * PI;
	Arg = Arg * k;
	Arg = Arg * (n/N);

	double cos = std::cos(Arg);
	double sin = std::sin(Arg);

	return c_double(cos, sin);
}

c_double DFT::GetTheAmplitude(int numberOfTheFrequency, const c_double* timeArray)
{
	int N = m_sizeOfArrays;
	int k = numberOfTheFrequency;

	c_double result = c_double(0, 0);

	for (int n = 0; n < N; n++)
	{
		c_double a = timeArray[n] * GetTheComplexExp(k, N, n);
		result += a;
	}

	return result;
}

c_double DFT::GetTheAmplitude(int numberOfTheFrequency, const c_vector timeArray)
{
	int N = m_sizeOfArrays;
	int k = numberOfTheFrequency;

	c_double result = c_double(0, 0);

	for (int n = 0; n < N; n++)
	{
		c_double a = timeArray[n] * GetTheComplexExp(k, N, n);
		result += a;
	}

	return result;
}

