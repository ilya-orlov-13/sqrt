#pragma once
#include <iostream>
#include <string>
using namespace std;

void CountCommas(int& k, int& index, string num);

void ReverseString(string& str);

string RemoveZeros(string& result, int& i, int& k);
void TestRemoveZeros();

string Subtract(string a, string b);
void TestSubtract();

bool LessThanOrEqual(string a, string b);
void TestLessThanOrEqual();

string OneDivBy(string num, int precision);
void TestOneDibBy();