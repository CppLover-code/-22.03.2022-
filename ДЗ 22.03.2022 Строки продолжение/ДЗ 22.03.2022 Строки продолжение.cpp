#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

using namespace std;

void replace_word(char* str, char* strnew, size_t SIZE, int *px)  // функция, выполняющая замену одного слова на другое
{
    if (str == NULL || strnew == NULL) return;

    size_t length = strlen(str);                                 // определение реального размера исходного массива

    char* str1 = new char[50];                                   // массив символов, которые нужно заменить
    puts("\nEnter the word to be replaced: \n");
    cin.getline(str1, 50);
    size_t len1 = strlen(str1);                                  // определение реального размера массива

    char* str2 = new char[50];                                   // массив символов, которые нужно вставить
    puts("\nEnter the word to be inserted: \n");
    cin.getline(str2, 50);
    size_t len2 = strlen(str2);                                  // определение реального размера массива

    char* pos;
    pos = strstr(str, str1);                                     // указатель на первое совпадение подстроки в строке

    size_t ind = 0;

    if (pos != NULL)                                // если совпадение найдено
    {          
        for (size_t i = 0; i < length; i++)         // исходный массив
        {
            ind = pos - str;                        // индекс элемента, с которого начинаем замену (адрес подстроки минус нулевой индекс строки)

            if (i != ind)                           // если индекс исходного массива не совпал с индексом начала замены
            {
                strnew[*px] = str[i];               // записываем в новый массив элементы исходного массива
                *px = *px + 1;
            }
            else                                    // иначе, если индексы совпали, 
            {
                for (size_t x = 0; x < len2; x++)   // масссив с символами, которые необходимо вставить вместо введенного пользователем слова
                {
                    strnew[*px] = str2[x];          // записываем в новый массив элементы нового слова
                    *px = *px + 1;
                }
                i = i + len1 - 1;                   // возвращаемся в исходный массив, перескочив индексы слова, которое нужно было заменить
                pos = strstr(pos + 1, str1);        // продолжаем искать совпадения
            }
        }
    }

    for (size_t i = 0; i < *px; i++)                // новый массив со всеми изменениями
    {
        cout << strnew[i];
    }
}

void uppercase(char* strnew, char* symb, int p, size_t size)
{
    for (size_t i = 0; i < p; i++)          // массив строк
    {
        if (i == 0 && (int(strnew[i]) >= 97 && int(strnew[i]) <= 122))  // если первый символ начинается с буквы нижнего регистра,
        {
            strnew[i] = char(int(strnew[i]) - 32);                      // то меняем его на букву верхнего регистра
        }
        for (size_t x = 0; x < size; x++)   // массив знаков окончания предложения
        {
            if (strnew[i] == symb[x] &&                                     // если в строке найден символ конца предложения
                (int(strnew[i + 1]) >= 97 && int(strnew[i + 1]) <= 122))    // и следующий символ в строке начинается с буквы нижнего регистра,
            {
                strnew[i + 1] = char (int(strnew[i + 1]) - 32);             // то меняем его на букву верхнего регистра
            }
            else if (strnew[i] == symb[x] && int(strnew[i + 1]) == 32 &&    // если в строке найден символ конца предложения и след. символ - пробел, 
                (int(strnew[i + 2]) >= 97 && int(strnew[i + 2]) <= 122))    // и следующий символ в строке после пробела начинается с буквы нижнего регистра,
                 {
                    strnew[i + 2] = char(int(strnew[i + 2]) - 32);          // то меняем его на букву верхнего регистра
                 }
        }
    }
    cout << "\n\n";
    for (size_t i = 0; i < p; i++)                // новый массив со всеми изменениями
    {
        cout << strnew[i];
    }
}
int main()
{
    const size_t SIZE = 100;        // размер массива с запасом
    char* str = new char[SIZE];     // массив, который будет хранить символы, введенные пользователем

    const size_t size = 3;        
    char* symb = new char[size] {'.', '!', '?'};     // массив, который будет хранить знаки окончания предложения

    puts("Enter text: \n");
    cin.getline(str, SIZE);         // ввод всего текста

    int p = 0;      // переменная, которая будет хранить реальный размер нового массива
    int* px = &p;   // указатель на переменную p, который будет меняться
    char* strnew = new char[SIZE];



    replace_word(str, strnew, SIZE, px);  //  функция, выполняющая замену одного слова на другое
    uppercase(strnew, symb, p, size);

    return 0;
}
