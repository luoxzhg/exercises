#include <iostream>
#include "mystring.h"

using namespace std;

int main(void)
{
    String str("This is a String object");
    String str2("abcde");

    str += str2;
    cout << str << endl;
}

