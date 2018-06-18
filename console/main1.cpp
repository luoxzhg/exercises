#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>

using namespace std;

//template <typename T> T const&
//    myMax(T const&x, T const&y)
//    {
//        return greater<T>()(x, y) ? x : y;
//    }
//
//template int const& myMax(int const& x, int const& y);

void  eatspaces(char *str);
double  expr(const char *, int &offset);
double  term(const char *, int &offset);
double  prime(const char *, int &offset);
char  *getexpr(char * , size_t bufsize);
inline double  calculate(char *str)
{
    int  pos = 0;       // 记录位置
    return expr(str, pos);
}

int main(/*int argc, char *argv[]*/)
{
    const int MAXSIZE = 256;
    char str[MAXSIZE];
    getexpr(str, MAXSIZE);
    double result = calculate(str);
    cout << "\t = "  << result << endl;
    return 0;
}

char  *getexpr(char *str, size_t  bufsize)
{
    cout << "输入表达式(换行结束)：" << endl;
    if (!cin.getline(str, MAXSIZE))
        return nullptr;
    eatspaces(str);
    cout << "\n表达式为: \n" << str << endl;
    return  str;
}

void  eatspaces(char *str)
{
    char *p = str;           // p用于前导
    while ((*str = *p++))
    {
        if (!isspace(*str))
        {
            ++str;
        }
    }
}

double  expr(const char *str, int &offset)
{

    double  result = term(str, offset);

    while (true)
    {
        switch (*(str + offset))
        {
        case '\0':
            return result;
        case '+':
            result += term(str, ++offset);
            break;
        case '-':
            result -= term(str, ++offset);
            break;
        case')':
            ++offset;
            return result;
            break;
        default:
            cerr.width(offset + 1);
            cerr << "^" << "\a\nERROR: something wrong!\n";
            exit(EXIT_FAILURE);
        }
    }
}

double  term(const char *str, int &offset)
{
    double  result = prime(str, offset);
    while (true)
    {
        switch (*(str + offset))
        {
        case '*':
            result *= prime(str, ++offset);
            break;
        case '/':
            result /= prime(str, ++offset);
            break;
        default:
            return result;
        }
    }
}

double  prime(const char *str, int &offset)
{
    double  result;
    char  *str_end;
    char  ch = *(str + offset);
    if (!isdigit(ch))
    {
        if (ch == '(')
        {
            result = expr(str, ++offset);
            return result;
        }
        return 0;   // 错误
//        cerr.width(offset+1);
//        cerr << "^" << "something is wrong\n";
//        exit(EXIT_FAILURE);
    }
    result = strtod(str + offset, &str_end);
    offset = str_end - str;
    return result;
}
