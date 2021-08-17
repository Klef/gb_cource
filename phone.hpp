#pragma once
#include <iostream>
#include <optional>

struct PhoneNumber
{
    int country;
    int city;
    std::string number;
    std::optional<int> add = std::nullopt;
};
std::ostream & operator<<(std::ostream & out, const PhoneNumber & phone);