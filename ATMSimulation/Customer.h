#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED
#include <cstdlib>
class Customer
{
    public:
        Customer():arrival(0), processtime(0) {}
        ~Customer() = default;
        
        void set(int times) { arrival = times; processtime = std::rand()%3 + 1;}
        int  when()const {return arrival;}
        int  ptime()const {return processtime;}
    protected:
        
    private:
        int arrival;
        int processtime;
};



#endif // CUSTOMER_H_INCLUDED
