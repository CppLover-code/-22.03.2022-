#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

using namespace std;

void replace_word(char* str, char* strnew, size_t SIZE, int *px)
{
    size_t length = strlen(str);

    char* str1 = new char[50];
    puts("\nEnter the word to be replaced: \n");
    cin.getline(str1, 50);
    size_t len1 = strlen(str1);

    char* str2 = new char[50];
    puts("\nEnter the word to be inserted: \n");
    cin.getline(str2, 50);
    size_t len2 = strlen(str2);
    cout << len2 << "\n";

    
    char* pos;
    pos = strstr(str, str1);
    cout << "pos " << strstr(str, str1) << "\n";
    size_t ind = 0;

    if (pos != NULL)
    {     
        ind = pos - str; // индекс элемента, с которого начинаем замену (адрес подстроки минус нулевой индекс строки)
       
        for (size_t i = 0; i < length; i++)         // первоначальный массив
        {
            if (i != ind)                           // если индекс первоначального массива не совпал с индексом начала замены
            {
                strnew[*px] = str[i];               // записываем в новый массив элементы первоначального массива
                *px = *px + 1;
            }
            else                                    // иначе, если индексы совпали, 
            {
                for (size_t x = 0; x < len2; x++)   // масссив с символами, которые необходимо вставить вместо введенного пользователем слова
                {
                    strnew[*px] = str2[x];          // записываем в новый массив элементы замены
                    *px = *px + 1;
                }
                i = i + len1 - 1;                   // возвращаемся в первоначальный массив, перескочив индексы слова, которое нужно было заменить
            }
        }
    }

    size_t lennew = strlen(strnew);
    for (size_t i = 0; i < *px; i++)
    {
        cout << "\n" << i << "-" << strnew[i] << "\n";
    }
    cout << "\n";
    for (size_t i = 0; i < *px; i++)
    {
        cout << strnew[i];
    }


}
int main()
{
    const size_t SIZE = 100;  // размер массива с запасом
    char* str = new char[SIZE];  // массив, который будет хранить символы, введенные пользователем

    puts("Enter text: \n");
    cin.getline(str, SIZE);  // ввод всего текста

    int p = 0;
    int* px = &p;
    char* strnew = new char[SIZE];

    replace_word(str, strnew, SIZE, px);


    return 0;
}
