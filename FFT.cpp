#include "FFT.h"

void FFT::SetN(int countOfValues)
{
	m_N = countOfValues;
}

void FFT::AllocateMemory()
{
	m_tValIn = new c_double[m_N]{};
	m_fValIn = new c_double[m_N]{};
	m_tValOut = new c_double[m_N]{};
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

void FFT::SetModulVectorByVector(const c_double* inputVector, double* modulVector, int size)
{
	for (int k = 0; k < size; k++)
	{
		modulVector[k] = std::sqrt(
			inputVector[k].imag() * inputVector[k].imag() + inputVector[k].real() * inputVector[k].real());
	}
}

void FFT::SetAverageErrorValues()
{
	for (int k = 0; k < m_N; k++)
	{
		m_erFreqRe += std::abs(m_fValIn[k].real() - m_fValOut[k].real());
		m_erFreqIm += std::abs(m_fValIn[k].imag() - m_fValOut[k].imag());

		m_erTimeRe += std::abs(m_tValIn[k].real() - m_tValOut[k].real());
		m_erTimeIm += std::abs(m_tValIn[k].imag() - m_tValOut[k].imag());
	}

	m_erFreqRe = m_erFreqRe / static_cast<double>(m_N);
	m_erFreqIm = m_erFreqIm / static_cast<double>(m_N);
	
	m_erTimeRe = m_erTimeRe / static_cast<double>(m_N);
	m_erTimeIm = m_erTimeIm / static_cast<double>(m_N);

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

void FFT::MakeInverseFFTOfVector(c_double* resultVector, int sizeVector)
{
	bool isInterVect = false; // for write result in m_fValOut or m_iterVect

	if (m_primeNumbers[0] == 0)
	{
		ChangeFFTVector(resultVector, m_interVect, m_N, m_N, 1);
		isInterVect = !isInterVect;
		return;
	}

	int curSizeOutVect = 1; // current size of a out vector

	for (int i = 0; i < (m_endPosPrime + 1); i++)
	{
		curSizeOutVect = curSizeOutVect * m_primeNumbers[m_endPosPrime - i];

		if (isInterVect)
			ChangeFFTVector(m_interVect, resultVector,
				m_primeNumbers[m_endPosPrime - i], curSizeOutVect, 1);
		else
			ChangeFFTVector(resultVector, m_interVect,
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

FFT::FFT(const c_vector vectorValueOfTimeFunc, const c_vector vectorValueOfFrequencyfunc)
{
	SetN(vectorValueOfTimeFunc.size());
	AllocateMemory();
	FillTheInputVectors(vectorValueOfTimeFunc, vectorValueOfFrequencyfunc);
	FindAllPrimeNumbers();

	MakePermutationForFFT(m_tValIn, m_fValOut, m_N);
	MakePermutationForFFT(m_fValIn, m_tValOut, m_N);

	MakeFFTOfVector(m_fValOut, m_N);
	MakeInverseFFTOfVector(m_tValOut, m_N);

	SetAverageErrorValues();
}

FFT::FFT(const c_double* vectorValueOfTimeFunc, const c_double* vectorValueOfFrequencyfunc, int sizeOfData)
{
	SetN(sizeOfData);
	AllocateMemory();
	FillTheInputVectors(vectorValueOfTimeFunc, vectorValueOfFrequencyfunc);
	FindAllPrimeNumbers();

	MakePermutationForFFT(m_tValIn, m_fValOut, m_N);
	MakePermutationForFFT(m_fValIn, m_tValOut, m_N);

	MakeFFTOfVector(m_fValOut, m_N);
	MakeInverseFFTOfVector(m_tValOut, m_N);

	SetAverageErrorValues();
}

void FFT::PrintAllData()
{
	std::cout << "========================FFT data========================\n";

	std::cout << "timeInReal\t\ttimeInImag\t\ttimeOutReal\t\ttimeOutImag\n";
	for (int k = 0; k < m_N; k++)
	{
		std::cout << m_tValIn[k].real() << "\t\t" << m_tValIn[k].imag() << "\t\t" << m_tValOut[k].real() << "\t\t" << m_tValOut[k].imag() << "\n";
	}

	std::cout << "freqInReal\t\tfreqInImag\t\tfreqOutReal\t\tfreqOutImag\n";
	for (int k = 0; k < m_N; k++)
	{
		std::cout << m_fValIn[k].real() << "\t\t" << m_fValIn[k].imag() << "\t\t" << m_fValOut[k].real() << "\t\t" << m_fValOut[k].imag() << "\n";
	}
	std::cout << "========================FFT data========================\n";


	std::cout << "========================FFT value eror========================\n";
	
	std::cout << "The Average Eror of forward FFT for Real frequency components: " << m_erFreqRe << "\n";
	std::cout << "The Average Eror of forward FFT for Imag frequency components: " << m_erFreqIm << "\n";

	std::cout << "The Average Eror of inverse FFT for Real time components: " << m_erTimeRe << "\n";
	std::cout << "The Average Eror of inverse FFT for Imag time components: " << m_erTimeIm << "\n";

	std::cout << "========================FFT value eror========================\n";
}

c_double* FFT::GetResultOutputTimeData()
{
	return m_tValOut;
}

c_double* FFT::GetResultOutputFrequencyData()
{
	return m_fValOut;
}

int FFT::GetSizeOfData()
{
	return m_N;
}

double FFT::GetAverageFrequencyEror(bool isRealEror)
{
	if (isRealEror)
		return m_erFreqRe;
	else
		return m_erFreqIm;
}

double FFT::GetAverageTimeEror(bool isRealEror)
{
	if (isRealEror)
		return m_erTimeRe;
	else
		return m_erTimeIm;
}

FFT::~FFT()
{
	delete[] m_tValIn;
	delete[] m_fValIn;

	delete[] m_tValOut;
	delete[] m_fValOut;

	delete[] m_interVect;

	delete[] m_primeNumbers;
}