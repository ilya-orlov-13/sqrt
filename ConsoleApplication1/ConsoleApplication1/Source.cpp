#include "Header.h"
using namespace std;

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
string RemoveZeros(string& result, int i, int k) {

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

    string r;
    int P = 0, index = 0;
    CountCommas(P, index, res);

    if (P == 1) {
        ReverseString(res);
        k = 0; i = 0;
        
        while (res[i] == '0') {
            k++; i++;
        }

        string r(res.length() - k, '0');
        for (int j = i; j < res.length(); j++) {
            r[j - k] = res[j];
        }

        ReverseString(r);
        return r;
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

// ������� ��� ��������� ���� ������������ �����
string SubtractFloat(string a, string b) {
    if (LessThanOrEqual(b, a)) {

        int aLen = a.length(), bLen = b.length();

        //������� � ������ a
        int kA = 0,      //���������� �������
            indexA = 0;  //������

        CountCommas(kA, indexA, a);

        //������� � ������ b
        int kB = 0,      //���������� �������
            indexB = 0;  //������

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

        int diffB = bLen - 1 - indexB; //������ ������� � ������ b � �����
        int diffA = aLen - 1 - indexA; //������ ������� � ������ a � �����

        if (kA > 1 or kB > 1) return "������������ ����";

        //������������ �����
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
            //���������� �����, ������� ����� �������� � ������ � ������� ��������

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


        if (kA >= 1 and kB >= 1) {

            int index = diffA >= diffB ? diffA : diffB;
            //cout << index<<endl;

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

    }


    return "0";
}

// ������� ��� ��������� ���� ����� �����, ��� ������� �������
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
    //����� �������
    char temp = result[0];
    result[0] = result[1];
    result[1] = temp;


    //�������� ������� �����
    if (result[0] == '0') {
        int i = 0, k = 0;
        return RemoveZeros(result, i, k);
    }
    else return result;
}

// ������� �� 2
string DivByTwo(string num) {

    string result;
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

    }

    //�������� ������� �����
    if (result[0] == '0') {

        int i = 0, k = 0;
        return RemoveZeros(result, i, k);

    }
    else return result;
}

void CountCommas(int& k, int& index, string num) {
    for (int i = 0; i < num.size(); i++) {
        if (num[i] == '.' or num[i] == ',') {
            k++; index = i;
        }
    }

}

// �������� ���� �����
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

    int diffB = bLen - 1 - indexB; //������ ������� � ������ b � �����
    int diffA = aLen - 1 - indexA; //������ ������� � ������ a � �����

    if (kA > 1 or kB > 1) return "������������ ����";
    
    //������������ �����
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
        //���������� �����, ������� ����� �������� � ������ � ������� ��������
        
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

    if (kA >= 1 and kB >= 1) {

        int index = diffA >= diffB ? diffA : diffB;
        //cout << index<<endl;

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

// ��������� ���� �����
string Multiply(string a, string b) {

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

    if (kA == 0 or kB == 0 or (kA==0 and kB==0)) {
        if (kA == 0) {
            a += '.';
            indexA = a.size() - 1;
            kA = 1;
            aLen = a.size();
        }
        else if(kB==0) {
            b += '.';
            indexB = b.size() - 1;
            kB = 1;
            bLen = b.size();
        }
        else if (kA == 0 and kB==0) {
            a += '.';
            indexA = a.size() - 1;
            kA = 1;
            aLen = a.size();

            b += '.';
            indexB = b.size() - 1;
            kB = 1;
            bLen = b.size();
        }
    }

    int diffB = bLen - 1 - indexB; //������ ������� � ������ b � �����
    int diffA = aLen - 1 - indexA; //������ ������� � ������ a � �����

    if (kA > 1 or kB > 1) return "������������ ����";

    //������������ �����
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
            //����� ������������ ���� ������� ����, 
            //����� �� �������� ������� ������ � ������������� ���������� ����� �� ������� �����, ������� �����
            //� ��������
            int mul = (a[i] - '0') * (b[j] - '0') + (result[i + j + 1] - '0') + carry;
            carry = mul / 10;
            result[i + j + 1] = (mul % 10) + '0';
        }
        result[i] += carry;
    }

    if (kA >= 1 and kB >= 1) {

        int index = diffA + diffB + 1;
        //cout << index<<endl;

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
}

//string Sqrt(string num, string precision) {
//    string n, result;
//
//    if (num[0] == '-') {
//        for (int i = 1; i < num.size(); i++) {
//            n += num[i];
//            
//        }
//        result += '-';
//    }
//    else {
//        n = num;
//    }
//    //cout << DivByTwo(n)<<endl;
//    string p = n;
//    string b = OneDivBy(n, 10);
//    string x;
//    string c = OneDivBy(p, 10);
//
//    //for (int i = 0; i < 1200; i++) {
//    //    //x = Subtract(x, Multiply(Subtract(Multiply(x, x), n), OneDivBy(Multiply("2", x), 10)));
//    //    x = SubtractFloat(Sum(c, x), Multiply(x, b));
//    //}
//
//
//    /*while (SubtractFloat(Sum(c, x), Multiply(x, b)) < Sum(precision, x)) {
//
//        x = SubtractFloat(Sum(c, x), Multiply(x, b)); cout << x << endl;
//    }*/
//    //cout << Sum(OneDivBy("7", 16), "7")<<endl<< Multiply("7", OneDivBy("49", 16)) << endl;
//    //cout << SubtractFloat(Sum(OneDivBy("7", 10), "7"),Multiply("7", OneDivBy("49", 10))) << endl;
//    while (LessThanOrEqual(c,Multiply(p,b)) == true) {
//        /*cout << c << " + " << p << " - " << Multiply(p, b)<<endl;
//        cout << Sum(c, p) << endl;*/
//        p = DivByTwo(p);
//        x = SubtractFloat(Sum(c, p), Multiply(p, b));
//        
//        /*cout << "�������: " << p << endl;
//        cout << "�����������: " << x << endl;
//        cout << "�������: " << SubtractFloat(c, Multiply(p, b)) << endl;*/
//    }
//    p = DivByTwo(p);
//    x = SubtractFloat(Sum(c, p), Multiply(p, b));
//    
//
//    //while (LessThanOrEqual(c, Multiply(p,b)) == false) {
//
//    //    p = Sum(p, "1");
//    //    x = SubtractFloat(Sum(c, p), Multiply(p, b));
//
//    //}
//
//    return x;
//}

string DivByTen(const string& num) {
    // �������� �� 0
    if (num == "0") {
        return "0";
    }

    // ����������� ����� �����
    bool isNegative = (num[0] == '-');
    string absNum = isNegative ? num.substr(1) : num;

    // ��������� �� ����� � ������� �����
    string integerPart, fractionalPart;
    size_t dotPos = absNum.find('.');
    if (dotPos != string::npos) {
        integerPart = absNum.substr(0, dotPos);
        fractionalPart = absNum.substr(dotPos + 1);
    }
    else {
        integerPart = absNum;
        fractionalPart = "";
    }

    // ��������� ���� � ������� ����� ��� ����������� �������
    fractionalPart += '0';

    // ������������ ����� �����
    string result;
    int carry = 0;
    for (char digit : integerPart) {
        int current = carry * 10 + (digit - '0');
        result += (current / 10) + '0';
        carry = current % 10;
    }

    // ������� ������� ���� �� ����� �����
    result.erase(0, result.find_first_not_of('0'));
    if (result.empty()) {
        result = "0";
    }

    // ��������� ����� ��� ������� �����
    result += '.';

    // ������������ ������� �����
    for (char digit : fractionalPart) {
        int current = carry * 10 + (digit - '0');
        result += (current / 10) + '0';
        carry = current % 10;
    }

    // ������� ������ ���� � ����� ������� �����
    while (result.back() == '0' && result[result.size() - 2] != '.') {
        result.pop_back();
    }

    // ���� ������� ����� ������� ������ �� �����, ������� ��
    if (result.back() == '.') {
        result.pop_back();
    }

    // ��������� ���� ��� �������������� �����
    if (isNegative) {
        result = '-' + result;
    }

    return result;
}

string Sqrt(string num, int precision) {
    string n, result="0";
    
    if (num[0] == '-') {
        for (int i = 1; i < num.size(); i++) {
            n += num[i];
            
        }
        result += '-';
    }
    else {
        n = num;
    }

    if (n == "0" or n == "1") return num; // Base cases

    string low = "0";
    string high = n;
    string mid, square;

    //�������� ����� ��� ����� �����
    while (LessThanOrEqual(low, high)) {
        mid = DivByTwo(Sum(low, high)); // mid = (low + high) / 2
        square = Multiply(mid, mid); // square = mid * mid

        if (square == n) {
            result = mid;
            break;
        }
        else if (LessThanOrEqual(square, n)) {
            result = mid; 
            low = Sum(mid, "1");
        }
        else {
            high = SubtractFloat(mid, "1");
        }
    }

    // ���������� ������� �����
    string fraction = "0.";
    for (int i = 0; i < precision; i++) {
        fraction += "0";
    }

    for (int i = 0; i < precision; i++) {
        string tempResult = Sum(result, fraction);
        square = Multiply(tempResult, tempResult); // square = tempResult * tempResult
        //cout << square<<endl;
        if (LessThanOrEqual(square, n)) {
            result = tempResult; 
        }
        else {
            fraction = DivByTen(fraction); // Reduce the fraction precision
        }
    }

    return result;
}
//
//string Sqrt(string x, string epsilon) {
//        // ���� x ����� 0 ��� 1, ��������� ����� ������ x
//    if (x == "0" || x == "1") {
//        return x;
//    }
//
//    string left = "0";
//    string right = x; // ���� x < 1, ���� ������ � ��������� [0, 1]
//    string mid;
//
//    while (LessThanOrEqual(SubtractFloat(right, left), epsilon) == false) {
//        mid = Sum(left, DivByTwo(SubtractFloat(right, left)));
//        if (LessThanOrEqual(Multiply(mid, mid), x) == false) {
//            right = mid;
//        }
//        else {
//            left = mid;
//        }
//    }
//
//    return left; // ����������� �������� ����������� �����
//}

string SqrtNewton(string x, string precision) {
   
    if (x == "0" or x == "1") {
        return x; // ������ �� 0 ��� 1 ����� ������ �����
    }

    string y = x; // ��������� �����������
    string prevY;

    do {
        prevY = y;
        
        y = DivByTwo(Sum(y,Multiply(x,OneDivBy(y,10)))); // ������� ������ �������
    } while (LessThanOrEqual(y,prevY) ? LessThanOrEqual(precision,SubtractFloat(prevY, y)) : LessThanOrEqual(precision, SubtractFloat(y, prevY)));

    return y;
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

    result = "221.00";

    if (RemoveZeros(result, i, k) == "221.") {
        countTests++; cout << "3)" << endl;
    }
    else cout << RemoveZeros(result, i, k) << endl << endl;

    result = "0221.300";

    if (RemoveZeros(result, i, k) == "221.3") {
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

    a = "0.49999999987"; b = "0.04081632653";

    if (LessThanOrEqual(a, b) == false) {
        countTests++; cout << "2)" << endl;
    }
    else { cout << endl << LessThanOrEqual(a, b) << endl << endl; };

    a = "0.0816327"; b = "0.25";

    if (LessThanOrEqual(a, b) == true) {
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

    a = "7.";  b = "0";

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

    a = "7"; b = "0.14285714282";

    if (Multiply(a, b) == "433126") {
        countTests++; cout << "2)" << endl;
    }
    else cout << Multiply(b, a) << endl << endl;

    cout << countTests - 1 << endl << endl;
}

void TestSqrt() {
    int countTests = 1;

    string a = "2"; int e = 10;

    if (Sqrt(a,e) == "1.41421") {
        countTests++; cout << "1)" << endl;
    }
    else cout << Sqrt(a,e) << endl << endl;

    a = "4";

    if (Sqrt(a,e) == "2") {
        countTests++; cout << "2)" << endl;
    }
    else cout << Sqrt(a,e) << endl << endl;

    a = "49";

    if (Sqrt(a,e) == "7") {
        countTests++; cout << "3)" << endl;
    }
    else cout << Sqrt(a,e) << endl << endl;


    a = "548.8";

    if (Sqrt(a,e) == "74.08104") {
        countTests++; cout << "4)" << endl;
    }
    else cout << Sqrt(a,e) << endl << endl;

    a = "55453465465767546547767078945653075489231974";

    if (Sqrt(a,e) == "7446708364490148780823.58813") {
        countTests++; cout << "5)" << endl;
    }
    else cout << Sqrt(a,e) << endl << endl;

    cout << countTests - 1 << endl << endl;
}

void TestDivByTen() {
    int countTests = 1;

    string a = "2";

    //if (Sqrt(a, "0.001") == "1.41421") {
    //    countTests++; cout << "1)" << endl;
    //}
    //else cout << Sqrt(a, "0.001") << endl << endl;

    //a = "4";

    //if (Sqrt(a, "0") == "2") {
    //    countTests++; cout << "2)" << endl;
    //}
    //else cout << Sqrt(a, "0.001") << endl << endl;

    a = "49";

    if (DivByTen(a) == "4") {
        countTests++; cout << "3)" << endl;
    }
    else cout << DivByTen(a) << endl << endl;


    a = "-5488";

    if (DivByTen(a) == "-548") {
        countTests++; cout << "4)" << endl;
    }
    else cout << DivByTen(a) << endl << endl;

    a = "55453465465767546547767078945653075489231974";

    if (DivByTen(a) == "5545346546576754654776707894565307548923197") {
        countTests++; cout << "5)" << endl;
    }
    else cout << DivByTen(a) << endl << endl;

    cout << countTests - 1 << endl << endl;
}