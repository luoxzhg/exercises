#ifndef SPLIT_H_INCLUDED
#define SPLIT_H_INCLUDED
#include <vector>
#include <string>
#include <iostream>
// function prototype
std::vector<std::string> split(const std::string& str);
const int* get_address();
bool str_subrange(const std::string &str1, const std::string &str2);
void print(const std::string& word);
void hello();
inline void hello()
{
    std::cout << "Hello";
}


//const auto bufsize = 1024;
#endif // SPLIT_H_INCLUDED
