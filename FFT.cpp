#include "FFT.h"

void FFT::SetN(int countOfValues)
{
	m_N = countOfValues;
}

void FFT::AllocateMemory()
{
	m_tValIn = new c_double[m_N]{};
	m_fValOut = new c_double[m_N]{};
	m_primeNumbers = new int[m_N] {};
	m_interVect = new c_double[m_N]{};
}

void FFT::FindAllPrimeNumbers()
{
	int divisor = 2;
	int divisible = m_N;

	for (int i = 0; i < ((int)(std::sqrt(m_N)) + 2); i++)
	{
		if (divisible % divisor == 0)
		{
			m_primeNumbers[m_endPosPrime] = divisor;
			divisible = divisible / divisor;
			m_endPosPrime++;
		}
		else
		{
			divisor++;
		}
	}

	m_endPosPrime--;
}

c_double FFT::GetComplexExp(double N, double k, double n, double sign)
{
	double angle = sign * TWO_PI * k * n / N;
	return c_double(std::cos(angle), std::sin(angle));
}

void FFT::MakePermutationForFFT(c_double* inputVector, c_double* resultVector, int size)
{
	if (m_primeNumbers[0] == 0) //m_N is this prime number, we doesn't have a permutations
	{
		for (int i = 0; i < size; i++)
			resultVector[i] = inputVector[i];
	}
	else
	{
		for (int i = 0; i < size; i++)
			resultVector[GetPermutatonPosition(i)] = inputVector[i];
	}
}

int FFT::GetPermutatonPosition(int inputPos)
{
	int result = inputPos;
	int currentPos = inputPos;
	int currentStep = m_N;
	int startNumb = 0;

	for (int i = 0; i < m_N; i++)
	{
		currentStep = currentStep / m_primeNumbers[i];

		if (currentStep == 1)
			break;

		if (currentPos % m_primeNumbers[i] == 0)
		{
			currentPos = currentPos / m_primeNumbers[i];
			result = startNumb + currentPos;
		}
		else
		{
			startNumb += currentStep * (currentPos % m_primeNumbers[i]);
			currentPos = currentPos / m_primeNumbers[i];
			result = startNumb + currentPos;
		}
	}

	return result;
}

void FFT::MakeFFTOfVector(c_double* outputVector, int sizeVector)
{
	bool isInterVect = false; // for write result in m_fValOut or m_iterVect

	if (m_primeNumbers[0] == 0)
	{
		ChangeFFTVector(outputVector, m_interVect, m_N, m_N, -1.0);
		isInterVect = !isInterVect;
		return;
	}

	int curSizeOutVect = 1; // current size of a out vector

	for (int i = 0; i < (m_endPosPrime + 1); i++)
	{
		curSizeOutVect = curSizeOutVect * m_primeNumbers[m_endPosPrime - i];

		if (isInterVect)
			ChangeFFTVector(m_interVect, outputVector,
				m_primeNumbers[m_endPosPrime - i], curSizeOutVect, -1.0);
		else
			ChangeFFTVector(outputVector, m_interVect,
				m_primeNumbers[m_endPosPrime - i], curSizeOutVect, -1.0);

		isInterVect = !isInterVect;
	}

	if (isInterVect)
		for (int k = 0; k < m_N; k++)
			outputVector[k] = m_interVect[k];
}

void FFT::ChangeFFTVector(c_double* inputVector, c_double* resultVector, int currentPrime, int sizeOfOutVectors, int sign)
{
	c_double** expArray = new c_double * [sizeOfOutVectors] {};

	for (int line = 0; line < sizeOfOutVectors; line++)
		expArray[line] = new c_double[currentPrime]{};

	SetArrayOfExp(expArray, currentPrime, sizeOfOutVectors, sign);

	for (int k = 0; k < m_N; k++)
		resultVector[k] = GetComponentOfOutVector(k, expArray,
			inputVector, sizeOfOutVectors, currentPrime);

	for (int line = 0; line < sizeOfOutVectors; line++)
		delete[] expArray[line];
	delete[] expArray;
}

void FFT::SetArrayOfExp(c_double** array, int currentPrime, int currentSizeOfOutVectors, int sign)
{
	for (int k = 0; k < currentSizeOfOutVectors; k++)
	{
		for (int n = 0; n < currentPrime; n++)
			array[k][n] = GetComplexExp(currentSizeOfOutVectors, k, n, sign);
	}
}

c_double FFT::GetComponentOfOutVector(int numberOfComponent, c_double** arrayOfExp, c_double* inputVector, int currentSizeOutVector, int currentPrime)
{
	c_double result = 0;
	int step = currentSizeOutVector / currentPrime;
	int numberInExpArray = numberOfComponent % currentSizeOutVector;
	int startIndex = (numberOfComponent - (numberInExpArray)) +
		(numberOfComponent % step);
	int currentPos = startIndex;

	for (int n = 0; n < currentPrime; n++)
	{
		result += arrayOfExp[numberInExpArray][n] * inputVector[currentPos];
		currentPos += step;
	}

	return result;
}

FFT::FFT(int sizeOFInputVectors)
{
	SetN(sizeOFInputVectors);
	AllocateMemory();
}

FFT::FFT(const c_vector vectorValueOfTimeFunc)
{
	SetN(vectorValueOfTimeFunc.size());
	AllocateMemory();
	FillTheInputVectors(vectorValueOfTimeFunc);
	
	MakeForwardFFT();
}

FFT::FFT(const c_double* vectorValueOfTimeFunc, int sizeOfData)
{
	SetN(sizeOfData);
	AllocateMemory();
	FillTheInputVectors(vectorValueOfTimeFunc);

	MakeForwardFFT();
}

void FFT::PrintAllData()
{
	std::cout << "========================FFT data========================\n";

	std::cout << "time Input Real\t\ttime Input Imag\n";
	for (int k = 0; k < m_N; k++)
	{
		std::cout << m_tValIn[k].real() << "\t\t" << m_tValIn[k].imag() << "\n";
	}

	std::cout << "frequency Output Real\t\tfrequency Output Imag\n";
	for (int k = 0; k < m_N; k++)
	{
		std::cout << m_fValOut[k].real() << "\t\t" << m_fValOut[k].imag() << "\n";
	}
	std::cout << "========================FFT data========================\n";

}

void FFT::MakeForwardFFT()
{
	FindAllPrimeNumbers();

	MakePermutationForFFT(m_tValIn, m_fValOut, m_N);

	MakeFFTOfVector(m_fValOut, m_N);
}

c_double* FFT::GetResultOutputFrequencyData()
{
	return m_fValOut;
}

int FFT::GetSizeOfData()
{
	return m_N;
}

FFT::~FFT()
{
	delete[] m_tValIn;

	delete[] m_fValOut;

	delete[] m_interVect;

	delete[] m_primeNumbers;
}