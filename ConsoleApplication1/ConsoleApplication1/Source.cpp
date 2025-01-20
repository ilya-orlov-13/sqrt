#include "Header.h"
using namespace std;

// Функция для переворота строки
void ReverseString(string& str) {
    int n = str.size();
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}


//удаление ведущих нулей
string RemoveZeros(string& result, int& i, int& k) {

    while (result[i] == '0') {
        k++; i++;
    }

    string res(result.length() - k, '0');
    for (int j = i; j < result.length(); j++) {
        res[j - k] = result[j];
    }

    if (result[i] == '.' or result[i] == ',') {
        res = '0' + res;
    }

    return res;
}

// Сравнение строковых чисел
bool LessThanOrEqual(string a, string b) {
    int pA = -1, pB = -1;

    for (int i = 0; i < a.size(); i++) {
        if (a[i] == '.' or a[i] == ',') {
            pA = i;
            break;
        }
    }

    for (int i = 0; i < b.size(); i++) {
        if (b[i] == '.' or b[i] == ',') {
            pB = i;
            break;
        }
    }

    //если точки нет, добавляем в конец строки
    if (pA == -1) {
        pA = a.size();
        a += ".0";
    }

    if (pB == -1) {
        pB = b.size();
        b += ".0";
    }

    if (pA < pB) return true;
    if (pA > pB) return false;


    int i = 0;
    if (pA == pB) {
        //сравнение целых частей
        while (i < pA and i < pB) {
            if (a[i] < b[i]) return true; //a<b
            if (a[i] > b[i]) return false; //a>b
            i++;
        }
    }

    if ((a.size() - 1 - i) > (b.size() - 1 - i)) return true; //a<b
    else if ((a.size() - 1 - i) < (b.size() - 1 - i)) return false; //a>b
    else {
        //сравнение дробных частей
        i = pA + 1;
        while (i < a.size() and i < b.size()) {
            if (a[i] < b[i]) return true; //a<b
            if (a[i] > b[i]) return false; //a>b
            i++;
        }
    }
    return true;

}

// Функция для вычитания двух вещественных чисел
string SubtractFloat(string a, string b) {
    if (LessThanOrEqual(b, a)) {

        int aLen = a.length(), bLen = b.length();

        //запятые в строке a
        int kA = 0,      //количество запятых
            indexA = 0;  //индекс

        CountCommas(kA, indexA, a);

        //запятые в строке b
        int kB = 0,      //количество запятых
            indexB = 0;  //индекс

        CountCommas(kB, indexB, b);

        int diffB = bLen - 1 - indexB; //индекс запятой в строке b с конца
        int diffA = aLen - 1 - indexA; //индекс запятой в строке a с конца

        if (kA > 1 or kB > 1) return "Некорректный ввод";

        //вещественное число
        else if (kA == 1 and kB == 1) {

            int iA = indexA; kA = 0;
            int iB = indexB; kB = 0;

            while (iA < iB or iA > iB) {
                if (iA > iB) {
                    b = '0' + b;
                    CountCommas(kB, iB, b);

                    //cout << iA << ' ' << iB<<endl;
                }
                else if (iA < iB) {
                    a = '0' + a;
                    CountCommas(kA, iA, a);

                    //cout << iA << ' ' << iB << endl;
                }
            }
            //количесвто нулей, которые нужно добавить в строку с меньшим индексом

            while (a.size() != b.size()) {
                if (diffA <= diffB) a += '0';
                else b += '0';
                //cout << a << endl << b << endl;
            }

            //cout << indexA << ' ' << iA << endl;

            ShiftForDBT(a, iA);
            Del(a);
            ShiftForDBT(b, iB);
            Del(b);
            kA = 1; kB = 1;
            //cout << a << endl << b << endl;
            aLen = a.size();
        }

        string result(a.size(), '0');
        int carry = 0;

        for (int i = 0; i < a.size(); i++) {
            //цифры
            int digitA = a[a.size() - 1 - i] - '0';
            int digitB = (i < b.size()) ? (b[b.size() - 1 - i] - '0') : 0;
            //вычитание из текущей цифры первого числа текущей цифры второго и переноса
            int diff = digitA - digitB - carry;
            //перенос
            if (diff < 0) {
                diff += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            //добавление цифры в результат
            result[result.size() - 1 - i] = diff + '0';
        }


        if (kA >= 1 and kB >= 1) {

            int index = diffA >= diffB ? diffA : diffB;
            //cout << index<<endl;

            //переворот строки и добавление точки
            ReverseString(result);
            result = '.' + result;
            //сдвиг запятой на индекс, в котором она была в исходной строке
            for (int i = 0; i < index + 1; i++) {
                char temp = result[i];
                result[i] = result[i + 1];
                result[i + 1] = temp;
            }

            ReverseString(result);
            result = Del(result);

            //удаление ведущих нулей
            if (result[0] == '0') {
                int i = 0, k = 0;
                return RemoveZeros(result, i, k);
            }
            else return result;
        }

    }


    return "0";
}

// Функция для вычитания двух целых чисел, для функций деления
string Subtract(string a, string b) {
    if (LessThanOrEqual(b, a)) {


        string result(a.size(), '0');
        int carry = 0;

        for (int i = 0; i < a.size(); i++) {
            //цифры
            int digitA = a[a.size() - 1 - i] - '0';
            int digitB = (i < b.size()) ? (b[b.size() - 1 - i] - '0') : 0;
            //вычитание из текущей цифры первого числа текущей цифры второго и переноса
            int diff = digitA - digitB - carry;
            //перенос
            if (diff < 0) {
                diff += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            //добавление цифры в результат
            result[result.size() - 1 - i] = diff + '0';
        }


            //удаление ведущих нулей
            if (result[0] == '0') {
                int i = 0, k = 0;
                return RemoveZeros(result, i, k);
            }
            else return result;

    }


    return "0";
}

//удаление запятой
string Del(string num) {
    string n(num.size() - 1, '0');
    for (int i = 0; i < num.size() - 1; i++) {
        n[i] = num[i];
    }
    return n;
}

//сдвиг запятой без добавления нулей в строку с результатом
//для функции деления на 2
void ShiftForDBT(string& num, int i) {
    while (i != num.size() - 1) {
        char temp = num[i];
        num[i] = num[i + 1];
        num[i + 1] = temp;
        if (num[i + 1]) i++;
    }
}

//сдвиг запятой с добавлением нулей в строку с результатом
void Shift(string& num, string& n, int& i) {
    while (i != num.size() - 1) {
        char temp = num[i];
        num[i] = num[i + 1];
        num[i + 1] = temp;
        n += '0';
        if (num[i + 1]) i++;
    }
}


// Деление 1 на число
string OneDivBy(string num, int precision) {
    string one = "1";
    string result = ".";

    int k = 0,    //количество запятых
        index = 0;//индекс

    for (int i = 0; i < num.size(); i++) {
        if (num[i] == '.' or num[i] == ',') {
            k++; index = i;
        }
    }

    if (k > 1) return "Некорректный ввод";

    else if (num[index] == '.' or num[index] == ',') {
        //сдвиг запятой
        while (index != num.size() - 1) {
            char temp = num[index];
            num[index] = num[index + 1];
            num[index + 1] = temp;
            if (num[index + 1]) {
                index++; one += '0';
            }
            //cout << num << ' ' << one << endl;
        }

        //удаление запятой
        string n = Del(num);

        //cout << endl << n << endl;

        //добавление нулей в делимое и частное
        while (Subtract(one, n) == "0") {
            one += '0'; result += '0';
            //cout << n << ' ' << one << endl;
        }

        string o = one;
        string subtr = n;

        for (int p = 0; p < precision; p++) {
            // Целая часть текущей итерации
            int i = 0;
            while (LessThanOrEqual(subtr, one)) {
                one = Subtract(one, subtr);
                i++;
                //cout << n << ' ' << one << endl;
            }

            result += (i + '0');

            // Добавляем "0" к делимому для следующей итерации
            one += '0';
        }


        // Если точка осталась в конце, убираем её
        if (result.back() == '.') {
            result = Del(result);
        }
    }

    else if (k == 0) {
        string n = num;

        //добавление нулей в делимое и частное
        while (Subtract(one, n) == "0") {
            one += '0'; result += '0';
            //cout << n << ' ' << one << endl;
        }

        string o = one;
        string subtr = n;

        for (int p = 0; p < precision; p++) {
            // Целая часть текущей итерации
            int i = 0;
            while (LessThanOrEqual(subtr, one)) {
                one = Subtract(one, subtr);
                i++;
                //cout << n << ' ' << one << endl;
            }

            result += (i + '0');

            // Добавляем "0" к делимому для следующей итерации
            one += '0';
        }
    }
    char temp = result[0];
    result[0] = result[1];
    result[1] = temp;
    return result;
}


// Деление на 2
string DivByTwo(string num) {

    int k = 0,      //количество запятых
        index = 0;  //индекс

    for (int i = 0; i < num.size(); i++) {
        if (num[i] == '.' or num[i] == ',') {
            k++; index = i;
        }
    }

    if (k > 1) return "Некорректный ввод";

    //вещественное число
    else if (k == 1) {

        string result;

        //сдвиг запятой в конец строки
        ShiftForDBT(num, index);
        //удаление запятой из строки
        num = Del(num);

        //перенос
        int carry = 0;
        int s = num.size();
        int indexP = 0, c = 0;

        // Деление
        //цикл с s+1 итерацией для возможной дробной части
        for (int i = 0; i < s + 1; i++) {
            int curr = 0;
            //если цифра есть в исходной строке, текущий перенос
            //складывается из остатка от деления на 2 предыдущего переноса и цифры в исходной строке
            if ((num[i] - '0') > 0) {
                curr = carry * 10 + (num[i] - '0');
            }
            //иначе в текущий перенос справа добавляется 0
            else {
                curr = carry * 10;/*
                if(carry+'0'>'0') c++;
                indexP = i;*/
            }
            //добавленме цифры в строку с результатом
            result += (curr / 2) + '0';
            carry = curr % 2;

        }

        //переворот строки и добавление точки
        ReverseString(result);
        result = '.' + result;
        //сдвиг запятой на индекс, в котором она была в исходной строке
        for (int i = 0; i < result.size() - 1 - index; i++) {
            char temp = result[i];
            result[i] = result[i + 1];
            result[i + 1] = temp;
        }

        ReverseString(result);

        //удаление ведущих нулей
        if (result[0] == '0') {
            int i = 0, k = 0;
            return RemoveZeros(result, i, k);
        }
        else return result;

    }

    //целое число
    else if (k == 0) {
        string result;

        int carry = 0;
        int s = num.size();
        int indexP = 0, //индекс запятой
            c = 0;      //количество чисел после запятой

        //деление
        for (int i = 0; i < s + 1; i++) {
            int curr = 0;
            if ((num[i] - '0') > 0) {
                curr = carry * 10 + (num[i] - '0');
            }
            else {
                curr = carry * 10;
                //cout << carry << ' ' << curr << endl;
                if (carry + '0' > '0') c++;
                indexP = i;
            }

            result += (curr / 2) + '0';
            carry = curr % 2;

        }

        //добавление запятой
        ReverseString(result);
        result = '.' + result;

        for (int i = 0; i < result.size() - 1 - indexP; i++) {
            char temp = result[i];
            result[i] = result[i + 1];
            result[i + 1] = temp;
        }

        ReverseString(result);

        //удаление ведущих нулей
        if (result[0] == '0') {

            int i = 0, k = 0;
            return RemoveZeros(result, i, k);

        }
        else return result;
    }
}

void CountCommas(int& k, int& index, string num) {
    for (int i = 0; i < num.size(); i++) {
        if (num[i] == '.' or num[i] == ',') {
            k++; index = i;
        }
    }

}

// Сложение двух строковых чисел
string Sum(string a, string b) {

    //записываем в переменную a строку максимальной длины
    if (a.length() < b.length()) {
        string temp = a;
        a = b;
        b = temp;
    }
    int aLen = a.length(), bLen = b.length();

    //запятые в строке a
    int kA = 0,      //количество запятых
        indexA = 0;  //индекс

    CountCommas(kA, indexA, a);

    //запятые в строке b
    int kB = 0,      //количество запятых
        indexB = 0;  //индекс

    CountCommas(kB, indexB, b);

    int diffB = bLen - 1 - indexB; //индекс запятой в строке b с конца
    int diffA = aLen - 1 - indexA; //индекс запятой в строке a с конца

    if (kA > 1 or kB > 1) return "Некорректный ввод";
    
    //вещественное число
    else if (kA == 1 and kB == 1) {

        int iA = indexA; kA = 0;
        int iB = indexB; kB = 0;

        while (iA < iB or iA > iB) {
            if (iA > iB) {
                b = '0' + b;
                CountCommas(kB, iB, b);

                //cout << iA << ' ' << iB<<endl;
            }
            else if (iA < iB) {
                a = '0' + a;
                CountCommas(kA, iA, a);

                //cout << iA << ' ' << iB << endl;
            }
        }
        //количесвто нулей, которые нужно добавить в строку с меньшим индексом
        
        while (a.size() != b.size()) {
            if (diffA <= diffB) a += '0';
            else b += '0';
            //cout << a << endl << b << endl;
        }

        //cout << indexA << ' ' << iA << endl;

        ShiftForDBT(a, iA);
        Del(a);
        ShiftForDBT(b, iB);
        Del(b);
        kA = 1; kB = 1;
        //cout << a << endl << b << endl;
        aLen = a.size();
    }

    string result;
    int carry = 0;

    for (int i = 0; i < aLen; i++) {
        // Числа

        // для первого слагаемого берем цифры с конца строки a
        int digitA = a[a.size() - 1 - i] - '0';
        /*
        для второго слагаемого берем цифры с конца строки b,
        если индекс не выходит за пределы строки b,
        иначе присваеваем второму слагаемому 0
        */
        int digitB = (i < b.size()) ? (b[b.size() - 1 - i] - '0') : 0;

        //сумма чисел и переноса
        int sum = digitA + digitB + carry;
        //последняя цифра полученной суммы
        char t = (sum % 10) + '0';
        //добавление в резльтирующую строку этой цифры
        result = t + result;
        //первая цифра полученной суммы (перенос)
        carry = sum / 10;
    }
    //добавление последнего переноса 
    if (carry) {
        char c = carry + '0';
        result = c + result;
    }

    if (kA >= 1 and kB >= 1) {

        int index = diffA >= diffB ? diffA : diffB;
        //cout << index<<endl;

        //переворот строки и добавление точки
        ReverseString(result);
        result = '.' + result;
        //сдвиг запятой на индекс, в котором она была в исходной строке
        for (int i = 0; i < index + 1; i++) {
            char temp = result[i];
            result[i] = result[i + 1];
            result[i + 1] = temp;
        }

        ReverseString(result);
        result = Del(result);

        //удаление ведущих нулей
        if (result[0] == '0') {
            int i = 0, k = 0;
            return RemoveZeros(result, i, k);
        }
        else return result;
    }

    return result;
}

//умножение двух чисел
string Multiply(string a, string b) {

    //записываем в переменную a строку максимальной длины
    if (a.length() < b.length()) {
        string temp = a;
        a = b;
        b = temp;
    }
    int aLen = a.length(), bLen = b.length();

    //запятые в строке a
    int kA = 0,      //количество запятых
        indexA = 0;  //индекс

    CountCommas(kA, indexA, a);

    //запятые в строке b
    int kB = 0,      //количество запятых
        indexB = 0;  //индекс

    CountCommas(kB, indexB, b);
    if (kA == 0 or kB == 0) {
        if (kA == 0) {
            a += '.';
            indexA = a.size() - 1;
            kA = 1;
            aLen = a.size();
        }
        else {
            b += '.';
            indexB = b.size() - 1;
            kB = 1;
            bLen = b.size();
        }
    }
    int diffB = bLen - 1 - indexB; //индекс запятой в строке b с конца
    int diffA = aLen - 1 - indexA; //индекс запятой в строке a с конца

    if (kA > 1 or kB > 1) return "Некорректный ввод";

    //вещественное число
    else if (kA == 1 and kB == 1) {

        //cout << indexA << ' ' << iA << endl;

        ShiftForDBT(a, indexA);
        Del(a);
        ShiftForDBT(b, indexB);
        Del(b);
        kA = 1; kB = 1;
        //cout << a << endl << b << endl;
        aLen = a.size();
    }

    int len1 = a.size(), len2 = b.size();
    string result(len1 + len2, '0');

    for (int i = len1 - 2; i >= 0; i--) {
        int carry = 0;
        for (int j = len2 - 2; j >= 0; j--) {
            //сумма произведения двух текущих цифр, 
            //цифры из текущего разряда строки с произведением предыдущей цифры из первого числа, второго числа
            //и переноса
            int mul = (a[i] - '0') * (b[j] - '0') + (result[i + j + 1] - '0') + carry;
            carry = mul / 10;
            result[i + j + 1] = (mul % 10) + '0';
        }
        result[i] += carry;
    }

    if (kA >= 1 and kB >= 1) {

        int index = diffA + diffB + 1;
        //cout << index<<endl;

        //переворот строки и добавление точки
        ReverseString(result);
        result = '.' + result;
        //сдвиг запятой на индекс, в котором она была в исходной строке
        for (int i = 0; i < index + 1; i++) {
            char temp = result[i];
            result[i] = result[i + 1];
            result[i + 1] = temp;
        }

        ReverseString(result);
        result = Del(result);

        //удаление ведущих нулей
        if (result[0] == '0') {
            int i = 0, k = 0;
            return RemoveZeros(result, i, k);
        }
        else return result;
    }
}


string Sqrt(string num, int precision) {
    string n, result;

    if (num[0] == '-') {
        for (int i = 1; i < num.size(); i++) {
            n += num[i];
            
        }
        result += '-';
    }
    else {
        n = num;
    }

    string x = "1.5", b = OneDivBy(n, 10);
    string c = OneDivBy(x, 10);

    for (int i = 0; i < precision; i++) {
        x = SubtractFloat(Sum(c, x), Multiply(x, b));
    }

    cout << x;
}

void TestRemoveZeros() {
    int countTests = 1;

    string result = "0.0011";
    int i = 0, k = 0;
    if (RemoveZeros(result, i, k) == "0.0011") {
        countTests++; cout << "1)" << endl;
    }
    else cout << RemoveZeros(result, i, k) << endl << endl;

    result = "000.221";

    if (RemoveZeros(result, i, k) == "0.221") {
        countTests++; cout << "2)" << endl;
    }
    else cout << RemoveZeros(result, i, k) << endl << endl;

    result = "000221";

    if (RemoveZeros(result, i, k) == "221") {
        countTests++; cout << "3)" << endl;
    }
    else cout << RemoveZeros(result, i, k) << endl << endl;

    cout << countTests-1<<endl<<endl;

}

void TestSubtract() {
    int countTests = 1;

    string a = "12312234"; string b = "32143";

    if (Subtract(a, b) == "12280091") {
        countTests++; cout << "1)" << endl;
    }
    else cout << Subtract(a, b) << endl << endl;

    a = "2312234"; b = "32143";

    if (Subtract(a, b) == "2280091") {
        countTests++; cout << "2)" << endl;
    }
    else cout << Subtract(a, b) << endl << endl;

    a = "42312.234"; b = "32143.0";

    if (SubtractFloat(a, b) == "10169.234") {
        countTests++; cout << "3)" << endl;
    }
    else cout << SubtractFloat(a, b) << endl << endl;

    a = "123.12234"; b = "32.143";

    if (SubtractFloat(a, b) == "90.97934") {
        countTests++; cout << "4)" << endl;
    }
    else cout << SubtractFloat(a, b) << endl << endl;


    cout << countTests - 1 << endl << endl;

}

void TestLessThanOrEqual() {
    int countTests = 1;

    string a = "12312234"; string b = "32143";

    if (LessThanOrEqual(a, b) == false) {
        countTests++; cout << "1)"<<endl;
    }
    else { cout << endl<< LessThanOrEqual(a, b) << endl << endl; };

    a = "10000"; b = "32143";

    if (LessThanOrEqual(a, b) == true) {
        countTests++; cout << "2)" << endl;
    }
    else { cout << endl << LessThanOrEqual(a, b) << endl << endl; };

    a = "100000"; b = "32143";

    if (LessThanOrEqual(a, b) == false) {
        countTests++; cout << "3)" << endl;
    }
    else { cout << endl << LessThanOrEqual(a, b) << endl << endl; };

    a = "23.12234"; b = "32143";

    if (LessThanOrEqual(a, b) == true) {
        countTests++; cout << "4)" << endl;
    }
    else { cout << endl << LessThanOrEqual(a, b) << endl << endl; };

    a = "32,143"; b = "3.2143";

    if (LessThanOrEqual(b, a) == true) {
        countTests++; cout << "5)" << endl;
    }
    else { cout << endl << LessThanOrEqual(a, b) << endl << endl; };

    cout << countTests - 1 << endl << endl;

}

void TestOneDivBy() {
    int countTests = 1;

    string a = "1.2312234";

    if (OneDivBy(a, 4) == "0.8122") {
        countTests++; cout << "1)" << endl;
    }
    else cout << OneDivBy(a, 4) << endl << endl;

    a = "32143";

    if (OneDivBy(a, 10) == "0.0000311109") {
        countTests++; cout << "2)" << endl;
    }
    else cout << OneDivBy(a, 10) << endl << endl;

    a = "12312.234";

    if (OneDivBy(a, 5) == "0.00008") {
        countTests++; cout << "3)" << endl;
    }
    else cout << OneDivBy(a, 5) << endl << endl;

    a = "2";

    if (OneDivBy(a, 5) == "0.5") {
        countTests++; cout << "4)" << endl;
    }
    else cout << OneDivBy(a, 1) << endl << endl;

    cout << countTests - 1 << endl << endl;
}

void TestDivByTwo() {
    int countTests = 1;

    string a = "1.2312234";

    if (DivByTwo(a) == "0.6156117") {
        countTests++; cout << "1)" << endl;
    }
    else cout << DivByTwo(a) << endl << endl;

    a = "32143";

    if (DivByTwo(a) == "16071.5") {
        countTests++; cout << "2)" << endl;
    }
    else cout << DivByTwo(a) << endl << endl;

    a = "12312.234";

    if (DivByTwo(a) == "6156.117") {
        countTests++; cout << "3)" << endl;
    }
    else cout << DivByTwo(a) << endl << endl;

    a = "2";

    if (OneDivBy(a, 5) == "1") {
        countTests++; cout << "4)" << endl;
    }
    else cout << DivByTwo(a) << endl << endl;

    cout << countTests - 1 << endl << endl;
}

void TestSum() {
    int countTests = 1;

    string a = OneDivBy("216563", 10); string b = DivByTwo("4235");

    if (Sum(a,b) == "2117.5") {
        countTests++; cout << "1)" << endl;
    }
    else cout << Sum(a,b) << endl << endl;

    a = OneDivBy("32.143", 10);  b = DivByTwo("4,235");

    if (Sum(a,b) == "2.14861") {
        countTests++; cout << "2)" << endl;
    }
    else cout << Sum(a,b) << endl << endl;

    a = DivByTwo("4,235");  b = OneDivBy("32.143", 10);

    if (Sum(a, b) == "2.14861") {
        countTests++; cout << "3)" << endl;
    }
    else cout << Sum(a, b) << endl << endl;

    a = OneDivBy("49", 10);  b = DivByTwo("49");

    if (Sum(a, b) == "7") {
        countTests++; cout << "4)" << endl;
    }
    else cout << Sum(a, b) << endl << endl;

    cout << countTests - 1 << endl << endl;
}

void TestMultiply() {
    int countTests = 1;

    string a = DivByTwo("216563"); string b = "4.5";

    if (Multiply(b,a) == "433126") {
        countTests++; cout << "1)" << endl;
    }
    else cout << Multiply(b, a) << endl << endl;

    a = "49"; b = DivByTwo("45254");

    if (Multiply(a, b) == "433126") {
        countTests++; cout << "2)" << endl;
    }
    else cout << Multiply(b, a) << endl << endl;

    a = "1.5"; b = OneDivBy("49",10);
    string c = OneDivBy(a, 10);

    if (SubtractFloat(Sum(c,a),Multiply(a, b)) == "433126") {
        countTests++; cout << "3)" << endl;
    }
    else cout <<SubtractFloat(Sum(c, a), Multiply(a, b)) << endl << endl;

    cout << countTests - 1 << endl << endl;
}