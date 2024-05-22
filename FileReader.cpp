#include "FileReader.h"
#include <fstream>
#include <iostream>


void FileReader::ReadFile(std::string fileName)
{
	std::ifstream file(fileName, std::ios::binary);

	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		auto size = file.tellg();
		file.seekg(0, std::ios::beg);

		//SetSizeOfDataArray(file);
		m_SizeOfDataArray = size;
		SetALocateMemory();

		file.read(m_data, m_SizeOfDataArray);
	}
	else
	{
		std::cerr << "you're fool, file cann't open";
	}

	file.close();
}

char* FileReader::GetDataArray()
{
	return m_data;
}

int FileReader::GetSizeOfArray()
{
	return m_SizeOfDataArray;
}

void FileReader::PrintData()
{
	for (int i = 0; i < m_SizeOfDataArray; i++)
	{
		std::cout << *(m_data + i);
	}
	std::cout << "\n";
}

FileReader::~FileReader()
{
	delete[] m_data;
}

void FileReader::SetSizeOfDataArray(std::ifstream& file)
{
	file.seekg(0, std::ios_base::end);
	m_SizeOfDataArray = file.tellg();
}

void FileReader::SetALocateMemory()
{
	if (m_data != nullptr)
		delete[] m_data;

	m_data = new char[m_SizeOfDataArray];
}
