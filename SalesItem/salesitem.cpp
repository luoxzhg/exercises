#include "salesitem.h"

#include <cassert>
#include <iomanip>
using namespace std;

SalesItem::SalesItem() :
{
   //ctor
}

SalesItem::~SalesItem()
{
   //dtor
}

SalesItem::SalesItem(const SalesItem &other)
{
   //copy ctor
}

SalesItem &SalesItem::operator=(const SalesItem &rhs)
{
   if (this == &rhs) return *this; // handle self assignment
   //assignment operator
   return *this;
}

SalesItem &SalesItem::operator+=(const SalesItem &rhs)
{
   assert(m_isbn == rhs.isbn());
   m_count += rhs.m_count;
   m_sale += rhs.m_sale;
}

istream &operator>>(istream &is, SalesItem &sale)
{
   float unit_price;
   is >> sale.m_isbn >> sale.m_count >> unit_price;
   sale.m_sale = sale.m_count * unit_price;
}

ostream &operator<<(ostream &os, const SalesItem &sale)
{
   ios_base::fmtflags  oldfmt = os.flags();
   os << sale.m_isbn << sale.m_count
      << fixed << setprecision(2)
      << sale.m_sale << sale.m_sale / sale.m_count << endl;
   os.flags(oldfmt);
}

SalesItem operator+(const SalesItem &lhs, const SalesItem &rhs)
{
   SalesItem temp = lhs;
   temp += rhs;
   return temp;
}
