#include "book.hpp"

using namespace std;

optional<string> getSubFromLine (string & in, size_t numer, char sep = 59)
{
    size_t n = 0;
    size_t first = 0;
    while (true)
    {
        size_t lenght = in.find(sep, first) - first;
        if ( in.length() < lenght)
        {
            break;
        }
        string value = in.substr(first, lenght);
        if (n == numer)
        {
            if ( lenght < 2 )
            {
                return nullopt;
            }
            return value;
        }
        first += lenght + 1;
        ++n;
    }
    return nullopt;
}


PhoneBook::PhoneBook(ifstream & in)
{
    if (in.is_open())
    {
        string line;
        
        while (getline(in, line))
        {
            // при отсуствии имени или фамилии
            // а так же кривого номера не создает запись
            Person P;
            if (getSubFromLine(line, 0).has_value())
            {
                P.surname = getSubFromLine(line, 0).value();
                if (getSubFromLine(line, 1).has_value())
                {
                    P.name = getSubFromLine(line, 1).value();
                    P.patronymic = getSubFromLine(line, 2);
                    string phoneWhile;
                    if (getSubFromLine(line, 3).has_value())
                    {
                        string phoneGray = getSubFromLine(line, 3).value();
                        for (size_t j = 0; j <= phoneGray.length(); ++j)
                        {
                            if (isdigit(phoneGray[j]))
                            {
                                phoneWhile += phoneGray[j];
                            }
                        }
                        if (phoneWhile.length() == 11)
                        {
                            PhoneNumber N;
                            N.city = stoi(phoneWhile.substr(1,3));
                            N.country = stoi(phoneWhile.substr(0,1));
                            N.number = phoneWhile.substr(4,7);
                            if (getSubFromLine(line, 4).has_value())
                            { 
                                N.add = stoi(getSubFromLine(line, 4).value());
                            }
                            record.push_back(make_pair(P, N));
                        }
                    }
                }
            }  
        }
    }
}

ostream & operator<<(ostream & out, const PhoneBook & book)
{
    for (size_t i = 0; i < book.record.size(); ++i)
    {
        out << book.record[i].first << " " << book.record[i].second << endl;
    }
    return out;
}

bool ComparePerson(pair<Person, PhoneNumber> a, pair<Person, PhoneNumber> b)
{
    string N1 = (a.first.patronymic.has_value()) ? a.first.surname + a.first.name + a.first.patronymic.value() : a.first.surname + a.first.name;
    string N2 = (b.first.patronymic.has_value()) ? b.first.surname + b.first.name + b.first.patronymic.value() : b.first.surname + b.first.name;
    return N1 < N2;
}

void PhoneBook::SortByName()
{
    sort(record.begin(), record.end(), ComparePerson);
}

bool ComparePhone(pair<Person, PhoneNumber> a, pair<Person, PhoneNumber> b)
{
    string N1 = (a.second.add.has_value()) ? to_string(a.second.country) + to_string(a.second.city) + a.second.number + to_string(a.second.add.value()) : "" + to_string(a.second.country) + to_string(a.second.city) + a.second.number;
    string N2 = (b.second.add.has_value()) ? to_string(b.second.country) + to_string(b.second.city) + b.second.number + to_string(b.second.add.value()) : "" + to_string(b.second.country) + to_string(b.second.city) + b.second.number;
    return N1 < N2;
}

void PhoneBook::SortByPhone()
{
    sort(record.begin(), record.end(), ComparePhone);
}


tuple<string, PhoneNumber> PhoneBook::GetPhoneNumber(const string & surname) const
{
    string outText;
    PhoneNumber outPhone;
    size_t isFind = false;
    for_each(record.begin(), record.end(), [& surname, & isFind, & outText, & outPhone](const auto & rec)
    {

        if (rec.first.surname == surname)
        {
            cout << rec.first.surname << " " << rec.first.name << endl;
            if (!isFind)
            {
                isFind = true;
                outPhone = rec.second;
            }
            else
            {
                outText = "found more than 1";
            }
        }

    });
    if (!isFind)
    {
        outText = "not found";
    }
    tuple<string, PhoneNumber> res = make_tuple(outText, outPhone);
    return res;
}

void PhoneBook::ChangePhoneNumber(const Person & fio, const PhoneNumber & number)
{
    
    vector<pair<Person, PhoneNumber>>::iterator finding = find_if(record.begin(), record.end(), [& fio](const auto & rec)
    {
        return (rec.first == fio);
    });
    if (!(finding == record.end()))
    {
        finding->second = number;
    }
    
}