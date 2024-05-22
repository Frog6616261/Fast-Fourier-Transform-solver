#include "FileParser.h"


FileParser::FileParser(const char* oldDataArray, const int oldDataSizeOFArray)
{
	MakeCopyDataArray(oldDataArray, oldDataSizeOFArray);
	ParseTheData();
}

c_double* FileParser::GetTimeArray()
{
	return m_timeArray;
}

c_double* FileParser::GetFrequencyArray()
{
	return m_frequencyArray;
}

int FileParser::GetSizeOfTheArrrays()
{
	return m_size;
}

void FileParser::MakeCopyDataArray(const char* oldData, int oldDataSize)
{
	m_data = new char[oldDataSize] {};
	m_dataSize = oldDataSize;

	for (int i = 0; i < oldDataSize; i++)
		*(m_data + i) = *(oldData + i);
}

void FileParser::ParseTheData()
{
	SetTheSizeForArrays();
	AllocateMemoryForArrays();

	std::string wordFirst = "";
	std::string wordSecond = "";

	bool isTimeWord = true;
	int columNumb = 0;

	for (int i = 0; i < m_dataSize; i++)
	{
		if (((int)m_data[i] <= 57 && (int)m_data[i] >= 45)
			&& (int)m_data[i] != 47)
		{
			switch (columNumb)
			{
			case 0:
				wordFirst += m_data[i];
				break;
			case 1:
				wordFirst += m_data[i];
				break;
			case 2:
				wordSecond += m_data[i];
				break;
			}
		}
		else if ((wordFirst != "" && wordSecond == "" && isTimeWord)
			|| (wordFirst != "" && wordSecond != "" && !isTimeWord))
		{
			AddTimeOrValueToArray(isTimeWord, wordFirst, wordSecond);
			columNumb = (columNumb + 1) % 3;
		}
		else if (wordFirst != "" && wordSecond == "")
		{
			columNumb = (columNumb + 1) % 3;
		}
	}
}

void FileParser::PrintData()
{
	std::cout << "===============data===============\n";
	for (int i = 0; i < m_dataSize; i++)
		std::cout << m_data[i];
	std::cout << "\n===============data===============\n";
}

void FileParser::PrintTime()
{
	std::cout << "===============time===============\n";
	std::cout << "Real\t\tImag\n";
	for (int i = 0; i < m_size; i++)
		std::cout << m_timeArray[i].real() << "\t" << m_timeArray[i].imag() << std::endl;
	std::cout << "===============time===============\n";
}

void FileParser::PrintValue()
{
	std::cout << "===============value===============\n";
	std::cout << "Real\t\tImag\n";
	for (int i = 0; i < m_size; i++)
		std::cout << m_frequencyArray[i].real() << "\t" << m_frequencyArray[i].imag() << std::endl;
	std::cout << "===============value===============\n";
}

FileParser::~FileParser()
{
	delete[] m_timeArray;
	delete[] m_frequencyArray;
	delete[] m_data;
}


void FileParser::AllocateMemoryForArrays()
{
	m_timeArray = new c_double[m_size]{};
	m_frequencyArray = new c_double[m_size]{};
}

void FileParser::AddTimeOrValueToArray(bool& isTimeWord, std::string& wordFirst, std::string& wordSecond)
{
	if (isTimeWord)
	{
		*(m_timeArray + m_FirstNotNullTimeIndex) = c_double(std::stod(wordFirst), 0);
		m_FirstNotNullTimeIndex++;
	}
	else
	{
		*(m_frequencyArray + m_FirstNotNullValueIndex) = c_double(std::stod(wordFirst), std::stod(wordSecond));
		m_FirstNotNullValueIndex++;
	}

	isTimeWord = !isTimeWord;
	wordFirst = "";
	wordSecond = "";
}

void FileParser::SetTheSizeForArrays()
{
	std::string word = "";
	int countOfWords = 0;

	for (int i = 0; i < m_dataSize; i++)
	{
		if (((int)m_data[i] <= 57 && (int)m_data[i] >= 45)
			&& (int)m_data[i] != 47)
		{
			word += m_data[i];
		}
		else if (word != "")
		{
			countOfWords++;
			word = "";
		}
	}

	m_size = countOfWords / 3;
}