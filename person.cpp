#include "person.hpp"

using namespace std;

struct Person;

ostream & operator<<(ostream & out, const Person & pers)
{
    out << pers.surname << " " << pers.name;
    if (pers.patronymic.has_value())
    {
        out << " " << pers.patronymic.value();
    }
    return out;
}

bool operator==(const Person & f1, const Person & f2)
{
    return (f1.name == f2.name && f1.surname == f2.surname && f1.patronymic == f2.patronymic);
}