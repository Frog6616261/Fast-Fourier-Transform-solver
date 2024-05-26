# FFT Solver (Fast Fourier Transform)

## Описание
Алгоритм быстрого прямого и обратного преобразования Фурье (БПФ и ОБПФ), основанный на алгоритме Кули-Тьюки, реализован в классах `FFT` и `IFFT`. Методы классов `FFT` и `IFFT` преобразуют вектора временных и частотных значений, состоящие из комплексных значений. Алгоритм может работать с векторами любой длины и кратности.

## Принцип работы алгоритма
- **Описание принципа работы алгоритма Кули-Тьюки**
  
Алгоритм данной программы основан на алгоритме Кулю-Тьюки, в котором происходит разбиение ряда для определенного номера частоты на два новых подряда с четными и нечетными компонентами. В итоге для получения частотной компоненты определенного номера следует из этих двух рядов получить частотные компоненты и перемножить их на соответствуещие компонентам экспоненты (которые появляются из-за рабиения изначатьного ряда, не путать с экспонентами ряда). Более подробно про этот алгоритм можно посмотреть тут https://en.wikipedia.org/wiki/Cooley–Tukey_FFT_algorithm или же вот хорошее видео по теме https://youtu.be/htCj9exbGo0?si=ZRCJ8j7qCybK4uOj.
- **Идея реализованного алгоритма**
 
Алгоритм реализованный в программе берет основную идею Кули-Тьюки. Только теперь это алгоритм не только по основанию 2, но и по любым основаниям. Т.е. у нас есть исходный вектор данных длинной N = N_1 * N_2 * ... N_m. Первый ряд разбиваем на N_1 рядов (N_1 частотных компонент для векторов длинной N / N_1). Теперь каждый N_1 ряд разбиваем на N_2 рядов. Далее каждый N_2 на N_3 и т.д.
В итоге мы полчучаем N рядов длиной 1. 

Если длина ряда равна 1, то получаемый частотный компонент равен исходной временной компоненте.
Теперь чтобы получить из рядов длинной 1 ряды длинной N_m следует сделать домножение каждого члена ряда, длиной равной 1, на определенную экспоненту или же комплексную единицу W_{L}^{-nK} = exp(2 * PI * (-n*K) / (L)) (L - длинна получаемого вектора, n - текущий компонент (если разбиение равно двум, то n принимает значения 0 и 1, если трем то 0 и 1 и 2) k - номер частотного компонента получаемого ряда).
Формула:
```
X(k) = X_{0}(k) * W_{N_m}^{- 0 * k} + X_{1}(k) * W_{N_m}^{- 1 * k} + ... + X_{N_m}(k) * W_{N_m}^{- N_m * k}
```
Для следующих рядов длиной P = N_m * N_{m-1} формула имеет вид:
```
X(k) = X_{0}(k) * W_{P}^{- 0 * k} + X_{1}(k) * W_{P}^{- 1 * k} + ... + X_{N_{m-1}}(k) * W_{P}^{- N_{m-1} * k}
```
Следует заметить, что даная формула дает нахождение P компонент одного из (N / P) рядов.
Прелесть алгоритма в том, что нам не следует находить матрицу W_{L}^{-nK} (k - строки, n - столбцы. Матрица двумерная) для каждого ряда, следует получить матрицу один раз и использовать ее для каждого ряда.

- **Описание работы реализованного алгоритма**

1. Для начала нам нужно найти все простые множители длины и записать в отделный массив. 
2. Делаем перестановку временных компонент в Output вектор, тем самым имитируя последовательное деление изначального ряда на подряды.
3. Находим компоненты для рядов размером N_m и повторяем тот-же принцип для следующих векторов вплоть до результирующего Output вектора.
 Для ОБПФ надо проделать тоже самое, только в комплексной еденице убрать минус (W_{L}^{-nK} -> W_{L}^{nK}) и в конце занормировать все получившиеся компоненты X(k) = X(k) / N.

## Использование FFT/IFFT

### Конструкторы

1.0 **Конструктор с комплексными массивами и размером массива:**
    ```cpp
    FFT/IFFT(const std::complex<double>* inputArray, size_t size);
    ```
    При вызове этого конструктора алгоритм автоматически выполняет БПФ, и данные можно получить через геттеры.
   
1.1 **Конструктор с комплексными массивами и размером массива:**
    ```cpp
    FFT/IFFT(const std::vector<std::complex<double>> inputVector);
    ```
    При вызове этого конструктора алгоритм автоматически выполняет БПФ, и данные можно получить через геттеры.

3. **Конструктор с размером векторов:**
    ```cpp
    FFT/IFFT(size_t size);
    ```
    Этот конструктор создает объект, но требует заполнения данных методом `FillTheInputVectors()`.

### Методы

- **Заполнение входных векторов:**
    ```cpp
    void FillTheInputVectors(const std::vector<std::complex<double>> inputArray);
    ```
    Заполняет временные и частотные вектора для дальнейшей обработки.

- **Выполнение прямого/обратного БПФ:**
    ```cpp
    void MakeForwardFFT();
    void MakeInverseFFT()
    ```
    Выполняет прямое быстрое преобразование Фурье с данными загруженными в объект.

- **Вывод всех данных в консоль:**
    ```cpp
    void PrintAllData() const;
    ```
    Выводит все данные в консоль.

## Дополнительные классы

### FileReader

Класс `FileReader` предназначен для чтения данных из файла, который должен находиться рядом с исполняемым файлом (.exe). Файл должен содержать три столбца:
1. Временные действительные значения вектора
2. Частотные действительные значения вектора
3. Частотные мнимые значения вектора

### FileParser

Класс `FileParser` используется для обработки данных, прочитанных из файла, и подготовки их к использованию в классе `FFT`. Данные можно некоректно обработать, если не соблюдать порядок и значения столбцов для класса `FileReader`. Т.е. используя данный етод записи данных, мы не используем временные мнимые значения. 

### ErorCalculator

Класс `ErorCalculator` предназначен для нахождения средней ошибки между двумя массивами комплексных данных.

### DFT/IDFT

Классы `DFT/IDFT` предназначены для нахождения компоненты прямого дискретного преобразования Фурье и обратного дискретного преоброзавния Фурье. Результат рвботы методов этих классов использован для сравнения корректности полученных данных БПФ и ОБПФ.

### Randomazier

Классы `Randomazier` служит для заполнения вектора случайными комплексными или действительными значениями. Модуль этих значений не превышает некоторого числа (см. код). А также фиксировано количество знаков после запятой (см. код).

## Пример использования

```cpp
#include <iostream>
#include "FFT.h"
#include "IFFT.h"
#include "DFT.h"
#include "ErorCalculator.h"
#include "Randomizer.h"
#include <iomanip>

int main() {
    setlocale(LC_ALL, "ru");
    setlocale(LC_NUMERIC, "eng");
    std::cout << std::fixed << std::setprecision(15);

    Randomizer Rand;
    DFT D;

    int N = 10;

    c_vector tIn;
    c_vector fIn;

    tIn.resize(N, 0);
    fIn.resize(N, 0);

    Rand.SetRandomComplexNumbers(tIn, 1, true);
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

    return 0;
}
```
## Результаты
- **Результаты работы алгоритма**
  
Результаты работы алгоритма для длин N = 81, 128, 450, 500 и 625  можно посмотреть в тут - https://docs.google.com/spreadsheets/d/1Ey2IYNjhD6xFPBMeT1K3bisNAsXLWyxEx9WTgyxABa4/edit?usp=sharing.

- **Анализ ошибки**
Как мы видими, ошибка очень мала для любых N. Это говорит о том, что точность алгоритма БПФ схожа с точностью ДПФ. Но сами алгоритмы все-равно вычисляются с некой погрешностью. Если бы мы сравнивали среднюю ошибку БПФ и данными посчитанными абсолютно точно, то средняя ошибка была бы во много раз больше. 
По сути мы должны увидеть, что чем больше в N простых множителей, тем больше ошибка, т.к. происходит большее накоплениее ошибки из-за операции получения новых компонент. Но мы сравниваем БПФ с данными полученными аналогичными арифметическими операциями и получаем почти одинаковые ошибки.

  
- **Как увеличить точность получаемых данных**
  
1. В каждом умножении или сложении или делении надо учитывать погрешность при операциях с числами с плавающей запятой. Только от этого возможно будет страдать скорость вычислений.
2. Можно ввести комплексную единицу с дробным показателем в степени, тогда exp(j * PI / 2) = j, а не exp(j * PI / 2) ~ j.

  
- **Принципиальное различие работы алгоритма по осонованию 2, 3 и 5**
  
Принцип работы алгоритма по основанию 2, 3 и 5 ничем друг от друга не оличается, просто происходит разделение текущего ряда на 2, 3 или 5 рядов, из которых получаются нужные компоненты, которые в свою очередь домножаются на комплексные единицы и суммируются для получения исходной компоненты.



