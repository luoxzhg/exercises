#pragma once
#ifndef WIDGET_H
#define WIDGET_H

#include <memory>

class Widget
{
public:
    Widget();
    ~Widget()noexcept;

    // move operations
    Widget(Widget&&)noexcept;
    Widget& operator=(Widget&&)noexcept;

    // copy oeprations
    Widget(const Widget& rhs);
    Widget& operator=(const Widget& rhs);

protected:

private:
    struct  Impl;
    std::unique_ptr<Impl> pImpl;
};

#endif // WIDGET_H
