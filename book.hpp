#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "phone.hpp"
#include "person.hpp"


class PhoneBook
{
private:
    std::vector<pair<Person, PhoneNumber>> record;
public:
    PhoneBook(ifstream & in);
    friend std::ostream & operator<<(std::ostream & out, const PhoneBook & book);
    void SortByName();
    void SortByPhone();
    tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string & surname) const;
    void ChangePhoneNumber(const Person & fio, const PhoneNumber & number);
};