#include "GraphPloter.h"

#if 0
GraphPloter::GraphPloter(const c_double* frequencyArrayIn, const c_double* timeArrayIn, const c_double* frequencyArrayOut, const c_double* timeArrayOut, const int arraysSize)
{
	m_arraysSize = arraysSize;

	FillTheArrayNumbers(m_arraysSize);

	FillTheArray(frequencyArrayIn, m_frequencyInReal, m_frequencyInImag, arraysSize);
	FillTheArray(frequencyArrayOut, m_frequencyOutReal, m_frequencyOutImag, arraysSize);

	FillTheArray(timeArrayIn, m_timeInReal, m_timeInImag, arraysSize);
	FillTheArray(timeArrayOut, m_timeOutReal, m_timeOutImag, arraysSize);


	ShowTwoGrafTogether(m_frequencyInImag, m_frequencyOutImag,
		"Frequency imag graph, red - input data, blue - FFT data");
	ShowTwoGrafTogether(m_frequencyInReal, m_frequencyOutReal,
		"Frequency real graph, red - input data, blue - FFT data");

	ShowTwoGrafTogether(m_timeInImag, m_timeOutImag,
		"Time imag graph, red - input data, blue - inverse FFT data");
	ShowTwoGrafTogether(m_timeInReal, m_timeOutReal,
		"Time real graph, red - input data, blue - inverse FFT data");
}

void GraphPloter::ShowTwoGrafTogether(v_double firstGraf, v_double secondGraf, std::string message)
{
	ep::WindowSpec wstyle;
	ep::plot<double>(message, wstyle, 2, firstGraf, ep::LineSpec(1, 0, 0), secondGraf, ep::LineSpec(0, 0, 1));
}

GraphPloter::~GraphPloter()
{

}

void GraphPloter::FillTheArray(const c_double* dataArray, v_double& fillingArrayReal, v_double& fillingArrayImag, const int arraysSize)
{
	fillingArrayReal.resize(arraysSize, 0);
	fillingArrayImag.resize(arraysSize, 0);

	for (int i = 0; i < arraysSize; i++)
	{
		fillingArrayReal[i] = dataArray[i].real();
		fillingArrayImag[i] = dataArray[i].imag();
	}
}

void GraphPloter::FillTheArrayNumbers(int arraySize)
{
	m_arrayNumbers.resize(arraySize, 0);

	for (int k = 0; k < arraySize; k++)
	{
		m_arrayNumbers[k] = k;
	}
}
#endif