#include "salesitem.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    SalesItem  val;
    if (cin >> val)
    {
        int cnt = 1;
        SalesItem temp;
        while (cin >> temp)
        {
            if (val.isbn() == temp.isbn())
                ++cnt;
            else
            {
                cout << val.isbn() << "has" << cnt << "transactions." << endl;
                val = temp;
                cnt = 1;
            }
        } // while
        cout << val.isbn() << "has" << cnt << "transactions." << endl;
    }
    else
        cerr << "No Data?!" << endl;
    return 0;
}
