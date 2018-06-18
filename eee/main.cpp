#include <iostream>
#include <typeinfo>

using namespace std;

// ====================================
class Base
{
    friend  bool operator==(const Base&, const Base&);
public:
    Base() = default;
    Base(int i) : b(i) {}
    virtual~Base() = default;
protected:
    virtual bool equal(const Base& rhs)const { return b == rhs.b;}
private:
    int  b = 0;
};
class  Derived : public Base
{
public:
    Derived(double v = 0.0) : d(v) {}
protected:
    bool  equal(const Base& rhs)const override
    {
        return  Base::equal(rhs)
                && d == dynamic_cast<const Derived&>(rhs).d;
    }
private:
    long d = 0;
};

inline bool operator==(const Base& lhs, const Base& rhs)
{
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}
// ====================================

int main()
{
    cout << "Hello world!" << endl;
    cout << "<------------------------------->" << endl;
//    Base bi(3), bj(33), bk(3);
//    Derived  di(3), dj(33), dk(33);
//    cout << boolalpha << "Bi == Bj : " << (bi == bj) << endl;
//    cout << boolalpha << "Bi == Bk : " << (bi == bk) << endl;
//    cout << boolalpha << "Di == Dj : " << (di == dj) << endl;
//    cout << boolalpha << "Dk == Dj : " << (dk == dj) << endl;
//    cout << boolalpha << "Bi == Di : " << (bi == di) << endl;
//    cout << boolalpha << "Bj == Dj : " << (bj == dj) << endl;
    cout << typeid(Base*).name();
    return 0;
}
