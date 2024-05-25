#include "IFFT.h"


void IFFT::SetN(int countOfValues)
{
	m_N = countOfValues;
}

void IFFT::AllocateMemory()
{
	m_fValIn = new c_double[m_N]{};
	m_tValOut = new c_double[m_N]{};
	m_primeNumbers = new int[m_N]{};
	m_interVect = new c_double[m_N]{};
}

void IFFT::FindAllPrimeNumbers()
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

c_double IFFT::GetComplexExp(double N, double k, double n, double sign)
{
	double angle = sign * TWO_PI * k * n / N;
	return c_double(std::cos(angle), std::sin(angle));
}

void IFFT::MakePermutationForFFT(c_double* inputVector, c_double* resultVector, int size)
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

int IFFT::GetPermutatonPosition(int inputPos)
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

void IFFT::MakeInverseFFTOfVector(c_double* resultVector, int sizeVector)
{
	bool isInterVect = false; // for write result in m_fValOut or m_iterVect

	if (m_primeNumbers[0] == 0)
	{
		ChangeIFFTVector(resultVector, m_interVect, m_N, m_N, 1);
		isInterVect = !isInterVect;
		return;
	}

	int curSizeOutVect = 1; // current size of a out vector

	for (int i = 0; i < (m_endPosPrime + 1); i++)
	{
		curSizeOutVect = curSizeOutVect * m_primeNumbers[m_endPosPrime - i];

		if (isInterVect)
			ChangeIFFTVector(m_interVect, resultVector,
				m_primeNumbers[m_endPosPrime - i], curSizeOutVect, 1);
		else
			ChangeIFFTVector(resultVector, m_interVect,
				m_primeNumbers[m_endPosPrime - i], curSizeOutVect, 1);

		isInterVect = !isInterVect;
	}

	double double_m_N = static_cast<double>(m_N);

	if (isInterVect)
		for (int k = 0; k < m_N; k++)
			resultVector[k] = m_interVect[k] / double_m_N;
	else
		for (int k = 0; k < m_N; k++)
			resultVector[k] = resultVector[k] / double_m_N;
}

void IFFT::ChangeIFFTVector(c_double* inputVector, c_double* resultVector, int currentPrime, int sizeOfOutVectors, int sign)
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

void IFFT::SetArrayOfExp(c_double** array, int currentPrime, int currentSizeOfOutVectors, int sign)
{
	for (int k = 0; k < currentSizeOfOutVectors; k++)
	{
		for (int n = 0; n < currentPrime; n++)
			array[k][n] = GetComplexExp(currentSizeOfOutVectors, k, n, sign);
	}
}

c_double IFFT::GetComponentOfOutVector(int numberOfComponent, c_double** arrayOfExp, c_double* inputVector, int currentSizeOutVector, int currentPrime)
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

IFFT::IFFT(int sizeOFInputVectors)
{
	SetN(sizeOFInputVectors);
	AllocateMemory();
}

IFFT::IFFT(const c_vector vectorValueOfFrequencyFunc)
{
	SetN(vectorValueOfFrequencyFunc.size());
	AllocateMemory();
	FillTheInputVectors(vectorValueOfFrequencyFunc);
	
	MakeInverseFFT();
}

IFFT::IFFT(const c_double* vectorValueOfFrequencyfunc, int sizeOfData)
{
	SetN(sizeOfData);
	AllocateMemory();
	FillTheInputVectors(vectorValueOfFrequencyfunc);

	MakeInverseFFT();
}

void IFFT::PrintTimeDataResult()
{
	std::cout << "========================IFFT data========================\n";

	std::cout << "time Output Real\n";
	for (int k = 0; k < m_N; k++)
	{
		std::cout << m_tValOut[k].real()  << "\n";
	}
	std::cout << "time Output Imag\n";
	for (int k = 0; k < m_N; k++)
	{
		std::cout << m_tValOut[k].imag() << "\n";
	}


	std::cout << "frequency Input Real\n";
	for (int k = 0; k < m_N; k++)
	{
		std::cout << m_fValIn[k].real() << "\n";
	}
	std::cout << "frequency Input Imag\n";
	for (int k = 0; k < m_N; k++)
	{
		std::cout  << m_fValIn[k].imag() << "\n";
	}

	std::cout << "========================IFFT data========================\n";
}

void IFFT::MakeInverseFFT()
{
	FindAllPrimeNumbers();

	MakePermutationForFFT(m_fValIn, m_tValOut, m_N);

	MakeInverseFFTOfVector(m_tValOut, m_N);
}

c_double* IFFT::GetResultOutputTimeData()
{
	return m_tValOut;
}

c_double* IFFT::GetInputFrequencyData()
{
	return m_fValIn;
}

int IFFT::GetSizeOfData()
{
	return m_N;
}

IFFT::~IFFT()
{
	delete[] m_fValIn;

	delete[] m_tValOut;

	delete[] m_interVect;

	delete[] m_primeNumbers;
}