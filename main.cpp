#include <iostream>
#include "FFT.h"
#include "IFFT.h"
#include "FileReader.h"
#include "FileParser.h"
#include "ErorCalculator.h"
#include "Randomizer.h"



//#define PRINT_FILE_PARSER_DATA 
//#define PRINT_FILE_READER_DATA
//#define READ_FILE
#define PRINT_FFT_DATA


void SetFileNamePath(std::string& line, std::string readersFileName);


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    setlocale(LC_NUMERIC, "eng");


#ifdef READ_FILE
    std::string line = argv[0];
    if (argc < 2)
    {
        std::cout << "��� ������ ����, ��������� ������� ���� � �������" << std::endl;

        return -1;
    }

    SetFileNamePath(line, argv[1]);

    std::cout << line << std::endl;

    FileReader Reader;
    Reader.ReadFile(line);

#ifdef PRINT_FILE_READER_DATA
    Reader.PrintData();
#endif    


    FileParser Parser{ Reader.GetDataArray(), Reader.GetSizeOfArray() };
#ifdef PRINT_FILE_PARSER_DATA
    Parser.PrintTime();
    Parser.PrintValue();
#endif     
#endif //READ_FILE


#ifndef READ_FILE
    Randomizer Rand;

    c_vector frequencyIn = { 1, 2, 3, 4 };
    //frequencyIn.resize(100);

    //Rand.SetRandomComplexNumbers(frequencyIn, 50);

#endif // !READ_FILE


 FFT Solver{frequencyIn};
 




#ifdef PRINT_FFT_DATA
    Solver.PrintAllData();
#endif 

    return 0;
}

void SetFileNamePath(std::string& line, std::string readersFileName)
{
    int sizeLine = line.size();
    int sizeName = readersFileName.size();
    int lastPosition = 0;

    for (int i = 0; i < sizeLine; i++)
    {
        if (line[i] == '\\')
            lastPosition = i;
    }

    line.erase(lastPosition, sizeLine - lastPosition);
    line = line + "\\" + readersFileName;
}
