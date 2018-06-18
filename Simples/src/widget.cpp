#include <string>
#include <vector>
#include "widget.h"

struct Widget::Impl {
    std::string         name;
    std::vector<double> data;
};

Widget::Widget() : pImpl(std::make_unique<Impl>())
{
    //ctor
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
Widget::Widget(const Widget& rhs) : pImpl(std::make_unique<Impl>(*rhs.pImpl))
{
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
Widget& Widget::operator=(const Widget& rhs)
{
    if (this != &rhs) {
        *pImpl = *rhs.pImpl;
    }
    return *this;
}

Widget::~Widget()noexcept = default;
Widget::Widget(Widget&&)noexcept = default;
Widget& Widget::operator=(Widget&&)noexcept = default;

