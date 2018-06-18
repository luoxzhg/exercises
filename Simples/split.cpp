#include "split.h"
#include <iostream>
#include <algorithm>
using namespace std;


void print(const string& word)
{
    size_t threshold = 2;
    if (word.size() < threshold)
        cerr << "Error: " << __FILE__ << endl
             << "       in function: " << __func__

             << " ; at line " << __LINE__ <<endl
             << "       Compiled on " << __DATE__ << " at " << __TIME__ << endl
             << "       Word read was \"" << word << "\": Length too short" << endl;
}


//const int* get_address()
//{
//    return &bufsize;
//}
inline int get_size()
{
    int temp;
    cout << "请输入一个正整数(0-1024):";
    if (cin >> temp)
        return temp;
    else
    {
        cerr << "输入错误！\n";
        return 512;
    }

}
//extern const int bufsize = get_size();

namespace
{
inline bool space(char c)
{
    return isspace(c);
}

inline bool not_space(char c)
{
    return !isspace(c);
}
}

vector<string> split(const string& str)
{
    typedef string::const_iterator iter;
    vector<string> rect;

    iter i = str.begin();
    while (i != str.end())
    {
        i = find_if(i, str.end(), not_space);

        iter j = find_if(i, str.end(), space);

        if (i != str.end())
        {
            rect.push_back(string(i,j));
        }

        i = j;
    }
    return rect;
}

