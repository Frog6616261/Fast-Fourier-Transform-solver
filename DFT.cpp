#include "DFT.h"


DFT::DFT()
{
	AllocateMemoryForArrays();
}

DFT::DFT(const double* valueArray, const double* timeArray, const int sizeOfArrays)
{
	m_sizeOfArrays = sizeOfArrays;

	AllocateMemoryForArrays();
	SetConstValues(valueArray, timeArray, sizeOfArrays);
	DoDiscreteFourierTransfom(valueArray, timeArray, sizeOfArrays);
}

void DFT::DoDiscreteFourierTransfom(const double* valueArray, const double* timeArray, const int sizeOfArrays)
{
	for (int k = 0; k < m_sizeOfArrays; k++)
	{
		m_amplitude[k] = GetTheAmplitude(k, valueArray);

		m_amplitudeImag[k] = m_amplitude[k].imag();
		m_amplitudeReal[k] = m_amplitude[k].real();
	}
}

int DFT::GetsizeOfTheArrays()
{
	return m_sizeOfArrays;
}

double* DFT::GetArrayOfFrequencies()
{
	return m_frequency;
}


void DFT::PrintTheResultData()
{
	std::cout << "==================== DFT data ====================\n";
	std::cout << "Frequency\tAmplitude Real\tAmplitude Imag\n";
	for (int i = 0; i < m_sizeOfArrays; i++)
	{
		std::cout << m_frequency[i] << "\t\t" << m_amplitudeReal[i] << "\t\t" << m_amplitudeImag[i] << "\n";
	}

	std::cout << "==================== DFT data ====================\n";
}

DFT::~DFT()
{
	delete[] m_amplitude;
	delete[] m_frequency;
	delete[] m_amplitudeImag;
	delete[] m_amplitudeReal;
}

void DFT::AllocateMemoryForArrays()
{
	m_amplitude = new c_double[m_sizeOfArrays]{};
	m_frequency = new double[m_sizeOfArrays] {};
	m_amplitudeImag = new double[m_sizeOfArrays] {};
	m_amplitudeReal = new double[m_sizeOfArrays] {};
}

void DFT::SetConstValues(const double* valueArray,
	const double* timeArray, const int sizeOfArrays)
{
	m_sizeOfArrays = sizeOfArrays;
}

c_double DFT::GetTheComplexExp(const int numberOfTheFrequency,
	const int countOfTheValues, const int numberOftheValue)
{
	double k = numberOfTheFrequency;
	double n = numberOftheValue;
	double N = countOfTheValues;

	double Arg = (-2) * PI * k * n / N;
	double cos = std::cos(Arg);
	double sin = std::sin(Arg);

	return c_double(cos, sin);
}

c_double DFT::GetTheAmplitude(const int numberOfTheFrequency, const double* valueArray)
{
	int N = m_sizeOfArrays;
	int k = numberOfTheFrequency;

	c_double result = c_double(0, 0);

	for (int n = 0; n < N; n++)
	{
		c_double a = valueArray[n] * GetTheComplexExp(k, N, n);
		result += a;
	}

	return result;
}

