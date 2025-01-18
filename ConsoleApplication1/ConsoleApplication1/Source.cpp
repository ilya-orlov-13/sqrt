#include "Header.h"

// ������� ��� ���������� ������
void ReverseString(string& str) {
    int n = str.size();
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}


//�������� ������� �����
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

// ��������� ��������� �����
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

    //���� ����� ���, ��������� � ����� ������
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
        //��������� ����� ������
        while (i < pA and i < pB) {
            if (a[i] < b[i]) return true; //a<b
            if (a[i] > b[i]) return false; //a>b
            i++;
        }
    }

    if ((a.size() - 1 - i) > (b.size() - 1 - i)) return true; //a<b
    else if ((a.size() - 1 - i) < (b.size() - 1 - i)) return false; //a>b
    else {
        //��������� ������� ������
        i = pA + 1;
        while (i < a.size() and i < b.size()) {
            if (a[i] < b[i]) return true; //a<b
            if (a[i] > b[i]) return false; //a>b
            i++;
        }
    }
    return true;

}

// ������� ��� ��������� ���� ��������� �����
string Subtract(string a, string b) {
    if (LessThanOrEqual(b, a)) {
        string result(a.size(), '0');
        int carry = 0;

        for (int i = 0; i < a.size(); i++) {
            //�����
            int digitA = a[a.size() - 1 - i] - '0';
            int digitB = (i < b.size()) ? (b[b.size() - 1 - i] - '0') : 0;
            //��������� �� ������� ����� ������� ����� ������� ����� ������� � ��������
            int diff = digitA - digitB - carry;
            //�������
            if (diff < 0) {
                diff += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            //���������� ����� � ���������
            result[result.size() - 1 - i] = diff + '0';
        }

        //�������� ������� �����
        if (result[0] == '0') {
            int i = 0, k = 0;
            return RemoveZeros(result, i, k);
        }

        else return result;

        cout << result << endl << endl;
    }

    return "0";
}


//�������� �������
string Del(string num) {
    string n(num.size() - 1, '0');
    for (int i = 0; i < num.size() - 1; i++) {
        n[i] = num[i];
    }
    return n;
}

//����� ������� ��� ���������� ����� � ������ � �����������
//��� ������� ������� �� 2
void ShiftForDBT(string& num, int i) {
    while (i != num.size() - 1) {
        char temp = num[i];
        num[i] = num[i + 1];
        num[i + 1] = temp;
        if (num[i + 1]) i++;
    }
}

//����� ������� � ����������� ����� � ������ � �����������
void Shift(string& num, string& n, int& i) {
    while (i != num.size() - 1) {
        char temp = num[i];
        num[i] = num[i + 1];
        num[i + 1] = temp;
        n += '0';
        if (num[i + 1]) i++;
    }
}


// ������� 1 �� �����
string OneDivBy(string num, int precision) {
    string one = "1";
    string result = ".";

    int k = 0,    //���������� �������
        index = 0;//������

    for (int i = 0; i < num.size(); i++) {
        if (num[i] == '.' or num[i] == ',') {
            k++; index = i;
        }
    }

    if (k > 1) return "������������ ����";

    else if (num[index] == '.' or num[index] == ',') {
        //����� �������
        while (index != num.size() - 1) {
            char temp = num[index];
            num[index] = num[index + 1];
            num[index + 1] = temp;
            if (num[index + 1]) {
                index++; one += '0';
            }
            //cout << num << ' ' << one << endl;
        }

        //�������� �������
        string n = Del(num);

        //cout << endl << n << endl;

        //���������� ����� � ������� � �������
        while (Subtract(one, n) == "0") {
            one += '0'; result += '0';
            //cout << n << ' ' << one << endl;
        }

        string o = one;
        string subtr = n;

        for (int p = 0; p < precision; p++) {
            // ����� ����� ������� ��������
            int i = 0;
            while (LessThanOrEqual(subtr, one)) {
                one = Subtract(one, subtr);
                i++;
                //cout << n << ' ' << one << endl;
            }

            result += (i + '0');

            // ��������� "0" � �������� ��� ��������� ��������
            one += '0';
        }


        // ���� ����� �������� � �����, ������� �
        if (result.back() == '.') {
            result = Del(result);
        }
    }

    else if (k == 0) {
        string n = num;

        //���������� ����� � ������� � �������
        while (Subtract(one, n) == "0") {
            one += '0'; result += '0';
            //cout << n << ' ' << one << endl;
        }

        string o = one;
        string subtr = n;

        for (int p = 0; p < precision; p++) {
            // ����� ����� ������� ��������
            int i = 0;
            while (LessThanOrEqual(subtr, one)) {
                one = Subtract(one, subtr);
                i++;
                //cout << n << ' ' << one << endl;
            }

            result += (i + '0');

            // ��������� "0" � �������� ��� ��������� ��������
            one += '0';
        }
    }
    char temp = result[0];
    result[0] = result[1];
    result[1] = temp;
    return result;
}


// ������� �� 2
string DivByTwo(string num) {

    int k = 0,      //���������� �������
        index = 0;  //������

    for (int i = 0; i < num.size(); i++) {
        if (num[i] == '.' or num[i] == ',') {
            k++; index = i;
        }
    }

    if (k > 1) return "������������ ����";

    //������������ �����
    else if (k == 1) {

        string result;

        //����� ������� � ����� ������
        ShiftForDBT(num, index);
        //�������� ������� �� ������
        num = Del(num);

        //�������
        int carry = 0;
        int s = num.size();
        int indexP = 0, c = 0;

        // �������
        //���� � s+1 ��������� ��� ��������� ������� �����
        for (int i = 0; i < s + 1; i++) {
            int curr = 0;
            //���� ����� ���� � �������� ������, ������� �������
            //������������ �� ������� �� ������� �� 2 ����������� �������� � ����� � �������� ������
            if ((num[i] - '0') > 0) {
                curr = carry * 10 + (num[i] - '0');
            }
            //����� � ������� ������� ������ ����������� 0
            else {
                curr = carry * 10;/*
                if(carry+'0'>'0') c++;
                indexP = i;*/
            }
            //���������� ����� � ������ � �����������
            result += (curr / 2) + '0';
            carry = curr % 2;

        }

        //��������� ������ � ���������� �����
        ReverseString(result);
        result = '.' + result;
        //����� ������� �� ������, � ������� ��� ���� � �������� ������
        for (int i = 0; i < result.size() - 1 - index; i++) {
            char temp = result[i];
            result[i] = result[i + 1];
            result[i + 1] = temp;
        }

        ReverseString(result);

        //�������� ������� �����
        if (result[0] == '0') {
            int i = 0, k = 0;
            return RemoveZeros(result, i, k);
        }
        else return result;

    }

    //����� �����
    else if (k == 0) {
        string result;

        int carry = 0;
        int s = num.size();
        int indexP = 0, //������ �������
            c = 0;      //���������� ����� ����� �������

        //�������
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

        //���������� �������
        ReverseString(result);
        result = '.' + result;

        for (int i = 0; i < result.size() - 1 - indexP; i++) {
            char temp = result[i];
            result[i] = result[i + 1];
            result[i + 1] = temp;
        }

        ReverseString(result);

        //�������� ������� �����
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


// �������� ���� ��������� �����
string Sum(string a, string b) {

    //���������� � ���������� a ������ ������������ �����
    if (a.length() < b.length()) {
        string temp = a;
        a = b;
        b = temp;
    }
    int aLen = a.length(), bLen = b.length();

    //������� � ������ a
    int kA = 0,      //���������� �������
        indexA = 0;  //������

    CountCommas(kA, indexA, a);

    //������� � ������ b
    int kB = 0,      //���������� �������
        indexB = 0;  //������

    CountCommas(kB, indexB, b);

    int diffB = bLen - 1 - indexB; //������ ������� � ������ b � �����
    int diffA = aLen - 1 - indexA; //������ ������� � ������ a � �����

    if (kA > 1 or kB > 1) return "������������ ����";

    //������������ �����
    else if (kA == 1 and kB == 1) {

        //���������� �����, ������� ����� �������� � ������ � ������� ��������
        if (diffA <= diffB) {
            int diff = diffB - diffA;
            for (int i = 0; i < diff; i++) {
                a += '0';
            }
        }
        else {
            int diff = diffA - diffB;
            for (int i = 0; i < diff; i++) {
                b += '0';
            }
        }

        ShiftForDBT(a, indexA);
        Del(a);
        ShiftForDBT(b, indexB);
        Del(b);


    }

    string result;
    int carry = 0;

    for (int i = 0; i < aLen; i++) {
        // �����

        // ��� ������� ���������� ����� ����� � ����� ������ a
        int digitA = a[a.size() - 1 - i] - '0';
        /*
        ��� ������� ���������� ����� ����� � ����� ������ b,
        ���� ������ �� ������� �� ������� ������ b,
        ����� ����������� ������� ���������� 0
        */
        int digitB = (i < b.size()) ? (b[b.size() - 1 - i] - '0') : 0;

        //����� ����� � ��������
        int sum = digitA + digitB + carry;
        //��������� ����� ���������� �����
        char t = (sum % 10) + '0';
        //���������� � ������������� ������ ���� �����
        result = t + result;
        //������ ����� ���������� ����� (�������)
        carry = sum / 10;
    }
    //���������� ���������� �������� 
    if (carry) {
        char c = carry + '0';
        result = c + result;
    }

    if (kA == 1 and kB == 1) {

        int index = diffA >= diffB ? diffA : diffB;

        //��������� ������ � ���������� �����
        ReverseString(result);
        result = '.' + result;
        //����� ������� �� ������, � ������� ��� ���� � �������� ������
        for (int i = 0; i < index + 1; i++) {
            char temp = result[i];
            result[i] = result[i + 1];
            result[i + 1] = temp;
        }

        ReverseString(result);
        result = Del(result);

        //�������� ������� �����
        if (result[0] == '0') {
            int i = 0, k = 0;
            return RemoveZeros(result, i, k);
        }
        else return result;
    }

    return result;
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

    a = "12312234"; b = "32143";

    if (Subtract(b, a) == "0") {
        countTests++; cout << "3)" << endl;
    }
    else cout << Subtract(a, b) << endl << endl;


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

    a = "32,143"; b = "32143";

    if (LessThanOrEqual(b, a) == false) {
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

    a = OneDivBy("32.143", 10); string b = DivByTwo("4,235");

    if (Sum(a,b) == "2.14861") {
        countTests++; cout << "2)" << endl;
    }
    else cout << Sum(a,b) << endl << endl;

    cout << countTests - 1 << endl << endl;
}