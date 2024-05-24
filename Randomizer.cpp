#include "Randomizer.h"

void Randomizer::SetRandomComplexNumbers(c_vector& fillingArray, int seed)
{
	std::srand(seed);
	int size = fillingArray.size();

	for (int k = 0; k < size; k++)
		fillingArray[k] = c_double(GetRandNumb(), GetRandNumb());
}

void Randomizer::SetRandomComplexNumbers(c_double* fillingArray, int arraySize, int seed)
{
	std::srand(seed);

	for (int k = 0; k < arraySize; k++)
		fillingArray[k] = c_double(GetRandNumb(), GetRandNumb());
}

double Randomizer::GetRandNumb()
{
	double result = (std::rand() % 1000);

	if (std::rand() > result)
		result *= (-1.0);

	result += (std::rand() % 1000) * 0.001;

	return result;
}


