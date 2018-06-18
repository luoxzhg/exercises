#include <iostream>
#include <ctime>
#include "Queue.h"

using namespace std;

bool  newcustomer(double x)   // x 是每小时的平均用户数
{
    return rand() * x < RAND_MAX;
}

int main()
{
    cout << "Hello world!" << endl;
    srand(time(0));

    cout << "Case Study: Bank of Heather Automatic Teller\n"
         "Enter maximum size of queue: ";
    int  qs;
    cin >> qs;
    Queue line(qs);

    cout << "Enter the number of simulation hours: ";
    int hours;
    cin >> hours;

    // simulation will run 1 cycle per minute
    long cyclelimit = 60 * hours;

    cout << "Enter the average number of customers per hour: ";
    double perhour;
    cin >> perhour;

    double min_per_cust = 60.0 / perhour;

    Queue::Item temp;
    long turnaways = 0;          // turned away by full queue
    long customers = 0;          // joined the queue
    long served = 0;             // served during the simulation
    long sum_line = 0;           // cumulative line length
    int  wait_time = 0;          // time until autoteller is free
    long  line_wait = 0;         // cumulative time in line

    // running the simulation
    for (int cycle = 0; cycle < cyclelimit; ++cycle)
    {
        if (newcustomer(min_per_cust))  // not have newcomer
        {
            if (line.isfull())
            {
                ++turnaways;
            }
            else
            {
                ++customers;
                temp.set(cycle);    // cycle is the time of arrival
                line.enqueue(temp);
            }
        }

        if (wait_time > 0)
        {
            --wait_time;
        }
        else if (!line.isempty())
        {
            line.dequeue(temp);     // attend next customer
            wait_time = temp.ptime();
            line_wait += cycle - temp.when();
            ++served;
        }
        
        sum_line += line.size();
    }
    
    // reporting results
    if (customers > 0)
    {
        cout << "customers accepted: " << customers << endl;
        cout << "  customers served: " << served << endl;
        cout << "         turnaways: " << turnaways << endl;
        
        
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout << "average queue size: " 
            << double(sum_line) / cyclelimit << endl;
        cout << " average wait time: " 
            << double(line_wait) / served << "minutes\n";
    }
    else
        cout << "No customers!\n";
    cout << "Done!\n";
    return 0;
}
