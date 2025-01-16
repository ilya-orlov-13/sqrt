#include "Header.h"

// Функция для переворота строки
void ReverseString(string& str) {
    int n = str.size();
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}