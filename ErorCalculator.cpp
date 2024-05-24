#include "ErorCalculator.h"

ErrorCalculator::ErrorCalculator(const c_double* firstVector, const c_double* secondVector, int sizeOfVectors)
{
	CalculateAverageError(firstVector, secondVector, sizeOfVectors);
}

void ErrorCalculator::CalculateAverageError(const c_double* firstVector, const c_double* secondVector, int sizeOfVectors)
{
	for (int k = 0; k < sizeOfVectors; k++)
	{
		m_erRe += std::abs(firstVector[k].real() - secondVector[k].real());
		m_erIm += std::abs(firstVector[k].imag() - secondVector[k].imag());
	}

	m_erRe = m_erRe / static_cast<double>(sizeOfVectors);
	m_erIm = m_erIm / static_cast<double>(sizeOfVectors);
}

double ErrorCalculator::GetRealError()
{
	return m_erRe;
}

double ErrorCalculator::GetImagError()
{
	return m_erIm;
}
