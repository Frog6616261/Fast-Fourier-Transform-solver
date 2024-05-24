#pragma once
class ErorCalculator
{
public:

	void SetAverageErrorValues()
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

	std::cout << "========================FFT value eror========================\n";

	std::cout << "The Average Eror of forward FFT for Real frequency components: " << m_erFreqRe << "\n";
	std::cout << "The Average Eror of forward FFT for Imag frequency components: " << m_erFreqIm << "\n";

	std::cout << "The Average Eror of inverse FFT for Real time components: " << m_erTimeRe << "\n";
	std::cout << "The Average Eror of inverse FFT for Imag time components: " << m_erTimeIm << "\n";

	std::cout << "========================FFT value eror========================\n";

private:
	//the average error between the input and output variables
	double m_erFreqRe = 0;
	double m_erFreqIm = 0;

	double m_erTimeRe = 0;
	double m_erTimeIm = 0;

};

