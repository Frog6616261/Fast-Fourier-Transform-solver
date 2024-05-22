#pragma once
#include <string>
#include <iostream>
#include <complex>

#define c_double std::complex <double>

class FileParser
{
public:

	FileParser(const char* oldDataArray, const int oldDataSizeOFArray);

	c_double* GetTimeArray();
	c_double* GetFrequencyArray();
	int GetSizeOfTheArrrays();

	void PrintData();
	void PrintTime();
	void PrintValue();

	~FileParser();// delete data, timeArray, valueArray

private:

	int m_size; // size of arrays;

	c_double* m_timeArray;
	int m_FirstNotNullTimeIndex = 0;

	c_double* m_frequencyArray;
	int m_FirstNotNullValueIndex = 0;

	char* m_data;
	int m_dataSize;

	void MakeCopyDataArray(const char* oldData, int oldDataSize);// don't delete oldData array, only copy

	void ParseTheData();

	void AllocateMemoryForArrays();

	void AddTimeOrValueToArray(bool& isTimeWord, std::string& wordFirst, std::string& wordSecond);

	void SetTheSizeForArrays();

};

