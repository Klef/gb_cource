#pragma once
#include <iostream>
#include <optional>

using namespace std;

struct Person
{
    std::string surname;
    std::string name;
    std::optional<std::string> patronymic = std::nullopt;
};
std::ostream & operator<<(std::ostream & out, const Person & pers);
bool operator==(const Person & f1, const Person & f2);