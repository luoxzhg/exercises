// include文件
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <functional>
#include <limits.h>
#include <iomanip>
#include <bitset>
#include <random>
#include <cmath>
#include <stdexcept>
#include <stdint-gcc.h>
#include <signal.h>
#include <thread>
//====================================================
using namespace std;
//====================================================
#include "mystdafx.h"
//extern int C;
//int A = C;



char *mystrncpy(char *dest, const char *src, size_t cnt)
{
    char *tempPtr = dest;
    while (cnt && (*dest++ = *src++))
        --cnt;

    if (0 == cnt)
        *dest = '\0';

    return tempPtr;
}

// 改进筛法判断是否是质数
bool  is_prime(int num)
{
    for (int i = 2; i <= sqrt(num); ++i)
        if (num % i == 0)
            return false;
    return true;
}

void  output_factor(int num, ostream &os)
{
    vector<int>  factorSet;
    if (num % 2 == 0)
    {
        factorSet.push_back(2);
        while (num % 2 == 0)
            num /= 2;
    }

    int  factor = 3;
    while (num != 1)
    {
        if (is_prime(factor) && (num % factor == 0))
        {
            num /= factor;
            if (!binary_search(factorSet.begin(), factorSet.end(), factor))
                factorSet.push_back(factor);
        }
        else
            factor += 2;
    }

    ostream_iterator<int>  outPutIter(os, " ");
    copy(factorSet.begin(), factorSet.end(), outPutIter);
}

//-------------------------------------------------------------
/// implementation
void  word_transform(ifstream &input, ifstream &map_file)
{
    //ofstream out("out.txt", ios::out);
    map<string, string> word_map;
    buildMap(word_map, map_file);
    string text;

    while (getline(input, text))
    {
        istringstream ss(text);
        string word;

        while (ss >> word)
        {
            auto it = word_map.find(word);

            if (it != word_map.end())
            {
                cout << it->second << " ";
            }
            else
            {
                cout << word << " ";
            }
        }

        cout << endl;
    }
}
//----------------------------------------------------------------
void  buildMap(map<string, string> &word_map, ifstream &map_file)
{
    string text;

    while (getline(map_file, text))
    {
        string key, value;
        istringstream ss(text);
        ss >> key;
        eatspace(ss);
        getline(ss, value);
        word_map[key] = value;
        // cout << key << ": " << value << endl;
    }
}

void  eatspace(istream &is)
{
    while (isspace(is.get()))
    {
        continue;
    }

    is.unget();
}


vector<int> *getVector(void)
{
    return new vector<int>;
}

void getValue(vector<int> &v, istream &is)
{
    int tem;
    cout << "请输入一列整数:\n";

    while (is >> tem)
    {
        v.push_back(tem);
    }
}


void printVector(vector<int> &v, ostream &os)
{

    for (const auto i : v)
    {
        os << i << " ";
    }
}

template <typename T>
void Swap(T &n1, T &n2)
{
    T temp = n1;
    n1 = n2;
    n2 = temp;
}
