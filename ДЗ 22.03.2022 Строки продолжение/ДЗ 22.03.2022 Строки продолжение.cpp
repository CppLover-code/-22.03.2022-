/*
  Задание. Есть некоторый текст. Необходимо найти и заменить вхождение некоторого слова 
  на заданое пользователем слово. Заменить текст так, чтоб каждое предложение начиналось 
  с большой буквы. Посчитать сколько раз каждая буква встречается в тексте. Посчитать 
  сколько раз цифры встречаются в тексте.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string.h>

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);  // дескриптор окна консоли
enum Colors { DARKGREEN = 2, WHITE = 15, BLUE = 9, DARKYELLOW = 6, DARKRED = 4, MAGENTA = 5 };  // перечисление цветов, исп. в программе

void replace_word(char* str, char* strnew, size_t SIZE, int* px);   // функция, выполняющая замену одного слова на другое
void uppercase(char* strnew, char* symb, int p, size_t size);       //  функция, которая заменяет первую букву каждого предложения на букву верхнего регистра
void numbers(char* strnew, int p);                                  // функция, подсчитывающая кол-во цифр в тексте
void letters(char* strnew, char* alph, int p, size_t s);            // функция, подсчитывающая сколько раз каждая буква повторяется в тексте 

int main()
{
    const size_t SIZE = 100;        // размер массива с запасом
    char* str = new char[SIZE];     // массив, который будет хранить символы, введенные пользователем

    const size_t size = 3;        
    char* symb = new char[size] {'.', '!', '?'};     // массив, который будет хранить знаки окончания предложения

    const size_t s = 26;
    char* alph = new char[s];       // массив букв нижнего регистра
    int start = 97;                 // 97 - первая буква англ алфавита
    for (size_t i = 0; i < s; i++)  // массив букв алфавита
    {
        alph[i] = char(start);      // заполняем массив буквами от a до z
        start++;
    }

    SetConsoleTextAttribute(h, Colors::DARKRED);
    cout << " Editing text entered by the user\n\n";

    SetConsoleTextAttribute(h, Colors::DARKYELLOW);
    puts("Enter text: \n");
    SetConsoleTextAttribute(h, Colors::WHITE);
    cin.getline(str, SIZE);         // ввод всего текста

    int p = 0;      // переменная, которая будет хранить реальный размер нового массива
    int* px = &p;   // указатель на переменную p, который будет меняться
    char* strnew = new char[SIZE];  // массив, который будет хранить текст после замены слова

    replace_word(str, strnew, SIZE, px);    // функция, выполняющая замену одного слова на другое
    uppercase(strnew, symb, p, size);       // функция, которая заменяет первую букву каждого предложения на букву верхнего регистра
    numbers(strnew, p);                     // функция, подсчитывающая кол-во цифр в тексте
    letters(strnew, alph, p, s);            // функция, подсчитывающая сколько раз каждая буква повторяется в тексте

    return 0;
}

void replace_word(char* str, char* strnew, size_t SIZE, int* px)  // функция, выполняющая замену одного слова на другое
{
    if (str == NULL || strnew == NULL) return;                    // проверка динамического массива на NULL

    size_t length = strlen(str);                                  // определение реального размера исходного массива

    char* str1 = new char[50];                                    // массив символов, которые нужно заменить
    SetConsoleTextAttribute(h, Colors::DARKYELLOW);
    puts("\nEnter the word to be replaced: \n");
    SetConsoleTextAttribute(h, Colors::WHITE);

    cin.getline(str1, 50);
    size_t len1 = strlen(str1);                                  // определение реального размера массива

    char* str2 = new char[50];                                   // массив символов, которые нужно вставить
    SetConsoleTextAttribute(h, Colors::DARKYELLOW);
    puts("\nEnter the word to be inserted: \n");
    SetConsoleTextAttribute(h, Colors::WHITE);

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
    SetConsoleTextAttribute(h, Colors::DARKYELLOW);
    cout << "\n Replacing a word in a sentence: \n\n";
    SetConsoleTextAttribute(h, Colors::WHITE);

    for (size_t i = 0; i < *px; i++)                // новый массив со всеми изменениями
    {
        cout << strnew[i];
    }
    cout << "\n---------------------------------------\n";
}

void uppercase(char* strnew, char* symb, int p, size_t size)  //  функция, которая заменяет первую букву каждого предложения на букву верхнего регистра
{
    if (strnew == NULL || symb == NULL) return;  // проверка динамического массива на NULL

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
                strnew[i + 1] = char(int(strnew[i + 1]) - 32);              // то меняем его на букву верхнего регистра
            }
            else if (strnew[i] == symb[x] && int(strnew[i + 1]) == 32 &&    // если в строке найден символ конца предложения и след. символ - пробел, 
                (int(strnew[i + 2]) >= 97 && int(strnew[i + 2]) <= 122))    // и следующий символ в строке после пробела начинается с буквы нижнего регистра,
                 {
                     strnew[i + 2] = char(int(strnew[i + 2]) - 32);          // то меняем его на букву верхнего регистра
                 }
        }
    }

    SetConsoleTextAttribute(h, Colors::MAGENTA);
    cout << "\n\n Checking and editing a sentence for the correct spelling\n";
    cout << " of the first letter of the first word:\n\n";
    SetConsoleTextAttribute(h, Colors::WHITE);

    for (size_t i = 0; i < p; i++)                // новый массив со всеми изменениями
    {
        cout << strnew[i];
    }
    cout << "\n---------------------------------------\n";
}

void numbers(char* strnew, int p)  // функция, подсчитывающая кол-во цифр в тексте
{
    if (strnew == NULL) return;  // проверка динамического массива на NULL

    SetConsoleTextAttribute(h, Colors::DARKGREEN);
    cout << "\n\n Counting the number of letters that occur in a text: \n";
    SetConsoleTextAttribute(h, Colors::WHITE);

    int count = 0;  // счетчик цифр

    for (size_t i = 0; i < p; i++)
    {
        if (int(strnew[i]) >= 48 && int(strnew[i] <= 57))  //  если номер символа по таблице ascii входит в диапазон 48-57(цифры),
        {
            count++;                                       //  то увеличиваем счётчик на 1
        }
    }
    cout << "\n" << count << " - digits found in text.";
    cout << "\n---------------------------------------\n";
}

void letters(char* strnew, char* alph, int p, size_t s)  // функция, подсчитывающая сколько раз каждая буква повторяется в тексте 
{
    if (strnew == NULL || alph == NULL) return;  // проверка динамического массива на NULL

    SetConsoleTextAttribute(h, Colors::BLUE);
    cout << "\n\n Counting the number of letters that occur in a text: \n";
    SetConsoleTextAttribute(h, Colors::WHITE);

    int amount;  // счётчик кол-ва букв

    for (size_t i = 0; i < s; i++)  // перебираем массив англ алфавита
    {
        amount = 0;
        for (size_t x = 0; x < p; x++)  // перебираем массив символов отредактированного введенного текста
        {
            if (int(alph[i]) == int(strnew[x]) || int(alph[i]) == int(strnew[x] + 32))  // если буква нижнего регистра совпала с буквой нижнего или верхнего регистра в тексте  
            {
                amount++;                                           // то увеличиваем на 1
            }
        }
        if (amount != 0)  // если счётчик в цикле сработал,
        {
            cout << alph[i] << " - " << amount << "\n";  // то выводим результат на экран
        }
    }
    cout << "---------------------------------------\n";
}