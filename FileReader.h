#pragma once
#include <string>

class FileReader
{
public:

	void ReadFile(std::string fileName);

	char* GetDataArray();

	int GetSizeOfArray();

	void PrintData();

	~FileReader();// delete *data

private:
	int m_SizeOfDataArray;
	char* m_data = nullptr;

	void SetSizeOfDataArray(std::ifstream& file);

	void SetALocateMemory();

};
