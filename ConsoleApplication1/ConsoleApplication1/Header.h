#pragma once
#include <iostream>
#include <string>
using namespace std;

string Del(string num);
void ShiftForDBT(string& num, int i);
void CountCommas(int& k, int& index, string num);

void ReverseString(string& str);

string RemoveZeros(string& result, int i, int k);
void TestRemoveZeros();

string Subtract(string a, string b);
void TestSubtract();

bool LessThanOrEqual(string a, string b);
void TestLessThanOrEqual();

string OneDivBy(string num, int precision);
void TestOneDivBy();

string DivByTwo(string num);
void TestDivByTwo();

string Sum(string a, string b);
void TestSum();

string Multiply(string num1, string num2);
void TestMultiply();

string Sqrt(string x, int precision);
string SqrtNewton(string x, string precision);
void TestSqrt();

string DivByTen(const string& num);
void TestDivByTen();