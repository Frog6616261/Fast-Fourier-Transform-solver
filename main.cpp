#include <iostream>
#include "FFT.h"
#include "IFFT.h"
#include "DFT.h"
#include "IDFT.h"
#include "FileReader.h"
#include "FileParser.h"
#include "ErorCalculator.h"
#include "Randomizer.h"



//#define PRINT_FILE_PARSER_DATA 
//#define PRINT_FILE_READER_DATA
//#define READ_FILE
//#define PRINT_FFT_DATA


void SetFileNamePath(std::string& line, std::string readersFileName);


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    setlocale(LC_NUMERIC, "eng");


#ifdef READ_FILE
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
#endif //READ_FILE


#ifndef READ_FILE
    Randomizer Rand;
    DFT D;

    int n = 128;

    c_vector tIn;
    c_vector fIn;

    tIn.resize(n, 0);
    fIn.resize(n, 0);

    Rand.SetRandomComplexNumbers(tIn, 20, true);
    D.SetArrayOfDFT(fIn, tIn);

    FFT F(tIn);
    IFFT IF(fIn);

    F.PrintAllData();
    IF.PrintTimeDataResult();

    ErrorCalculator timeError(F.GetInputTimeData(),  IF.GetResultOutputTimeData(), F.GetSizeOfData());
    ErrorCalculator freqError(IF.GetInputFrequencyData(), F.GetResultOutputFrequencyData(), IF.GetSizeOfData());

    std::cout << "time erro\n";
    timeError.PrintError();
    std::cout << "frequncy erro\n";
    freqError.PrintError();


#endif // !READ_FILE


 
 




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
