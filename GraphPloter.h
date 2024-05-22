#pragma once

#include <vector>
#include <complex>
#include <string>
#include <GL/freeglut.h>
#include "easy_plot.hpp"

  



class GraphPloter
{
#if 0
public:

	GraphPloter(const std::complex<double>* frequencyArrayIn, const std::complex<double>* timeArrayIn,
		const std::complex<double>* frequencyArrayOut, const std::complex<double>* timeArrayOut,
		const int arraysSize);


	void ShowTwoGrafTogether(std::vector<double> firstGraf, std::vector<double> secondGraf, std::string message);


	~GraphPloter();

private:

	int m_arraysSize;
	std::vector<double> m_arrayNumbers;

	std::vector<double> m_frequencyInReal;
	std::vector<double> m_frequencyInImag;

	std::vector<double> m_timeInReal;
	std::vector<double> m_timeInImag;

	std::vector<double> m_frequencyOutReal;
	std::vector<double> m_frequencyOutImag;

	std::vector<double> m_timeOutReal;
	std::vector<double> m_timeOutImag;

	void FillTheArray(const std::complex<double>* dataArray,
		std::vector<double>& fillingArrayReal, std::vector<double>& fillingArrayImag, const int arraysSize);

	void FillTheArrayNumbers(int arraySize);
#endif
};


