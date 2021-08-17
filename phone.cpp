#include "phone.hpp"

using namespace std;

struct PhoneNumber;

ostream & operator<<(ostream & out, const PhoneNumber & phone)
{
    out << "phone +" << phone.country << "(" << phone.city << ")" << phone.number;
    if (phone.add.has_value())
    {
        out << " additional " << phone.add.value();
    }
    return out;
}