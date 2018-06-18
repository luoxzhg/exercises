#ifndef SALESITEM_H
#define SALESITEM_H

#include <iosfwd>
#include <string>

class SalesItem {
   friend  std::istream &operator>>(std::istream &, SalesItem &);
   friend  std::ostream &operator<<(std::ostream &, const SalesItem &);
   friend  SalesItem operator+(const SalesItem &, const SalesItem &);
public:
   /** Default constructor */
   SalesItem();
   /** Default destructor */
   ~SalesItem();
   /** Copy constructor
    *  \param other Object to copy from
    */
   SalesItem(const SalesItem &other);
   /** Assignment operator
    *  \param other Object to assign from
    *  \return A reference to this
    */
   SalesItem &operator=(const SalesItem &other);

   SalesItem &operator+=(const SalesItem &other);

   /** Access m_count
    * \return The current value of m_count
    */
   unsigned int Getcount()const { return m_count; }
   /** Set m_count
    * \param val New value to set
    */
   void Setcount(unsigned int val) { m_count = val; }
   /** Access m_price
    * \return The current value of m_price
    */
   float Getsale()const { return m_sale; }
   /** Set m_price
    * \param val New value to set
    */
   void Setsale(float val) { m_sale = val; }

   const std::string &isbn()const { return m_isbn; }

protected:
private:
   unsigned int m_count; //!< Member variable "m_count"
   float m_sale; //!< Member variable "m_sale"
   std::string m_isbn; //!< Member variable "m_isbn"
};

#endif // SALESITEM_H
