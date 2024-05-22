#include <iostream>
#include "FFT.h"
#include "FileReader.h"
#include "FileParser.h"



//#define PRINT_FILE_PARSER_DATA 
//#define PRINT_FILE_READER_DATA
#define PRINT_FFT_DATA


void SetFileNamePath(std::string& line, std::string readersFileName);


int main(int argc, char* argv[])
{
    //ep::init(&argc, argv);


    setlocale(LC_ALL, "ru");
    setlocale(LC_NUMERIC, "eng");

    std::string line = argv[0];
    if (argc < 2)
    {
        std::cout << "Для работы кода, требуется указать файл с данными" << std::endl;

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


    FFT Solver{ Parser.GetTimeArray(), Parser.GetFrequencyArray(), Parser.GetSizeOfTheArrrays() };

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
