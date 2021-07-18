#include <iostream>
#include <cassert>
#include <vector>

using namespace std;


//HW 1
#ifndef ARRAYINT_H
#define ARRAYINT_H

//код класса взят из методички, добавлены функции pop_back, pop_front, sort, print
class ArrayInt
{
private:
    int m_length;
    int *m_data;
public:
    ArrayInt(): m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length):
    m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
    }

    int getLength() { return m_length; }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

        void resize(int newLength)
    {

        if (newLength == m_length)
            return;

        if (newLength <= 0)
        {
            erase();
            return;
        }

        int *data = new int[newLength];

        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;
            for (int index=0; index < elementsToCopy ; ++index)
                data[index] = m_data[index];
        }
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

     void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);
        int *data = new int[m_length+1];
        for (int before=0; before < index; ++before)
            data[before] = m_data[before];
        data [index] = value;
        for (int after=index; after < m_length; ++after)
            data[after+1] = m_data[after];
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) {
        insertBefore(value, m_length);
    }

    void pop_back()
    {
        int *data = new int[m_length-1];
        for (int i = 0; i < (m_length-1); ++i)
        {
            data[i] = m_data[i];
        }
        delete m_data;
        m_data = data;
        --m_length;
    }

    void pop_front()
    {
        int *data = new int[m_length-1];
        for (int i = 1; i < m_length; ++i)
        {
            data[i-1] = m_data[i];
        }
        delete m_data;
        m_data = data;
        --m_length;
    }

    void sort()
    {
        for (int i = 0; i < m_length-1; i++)
        {
            for (int j = 0; j < m_length - i - 1; j++)
            {
                if (m_data[j] > m_data[j+1])
                {
                    int temp = m_data[j];
                    m_data[j] = m_data[j+1];
                    m_data[j+1] = temp;
                }
            }
        }
    }

    void print()
    {
        for (int i = 0; i < m_length; i++)
        {
            cout << " " <<m_data[i];
        }
        cout << " ";
    }
};

#endif

void HomeWork_1()
{
    cout << "Home Work #1" << endl;
    ArrayInt array(3);
    array[0] = 12;
    array[1] = 3;
    array[2] = 5;
    array.resize(5);
    array[3] = 24;
    array[4] = 2;
    array.push_back(10);
    array.push_back(11);
    array.insertBefore(7, 2);
    array.pop_back();
    array.pop_front();
    array.sort();
    cout << "Size of array: " << array.getLength() << endl;
    cout << "Listing array:" << endl << "{";
    array.print();
    cout << "}" << endl << endl;
}

//HW 2

void HomeWork_2()
{
    cout << "Home Work #2" << endl;
    vector<int> array = { 10, 8, 6, 4, 2, 1, 10, 4, 1, 9 };
    vector<int> array_temp;
    array_temp.push_back(array[0]);
    for (int i = 1; i < array.size(); i++) 
    {
        if (find(array_temp.begin(), array_temp.end(), array[i])== array_temp.end())
        {
           array_temp.push_back(array[i]);
        }
    }
    cout << endl;
    cout << "In array:" << endl << "{ ";
    for (int i = 0; i < array.size(); i++) 
    {
        cout << array[i] << " ";
    }
    cout << "}" << endl << "Unique: " << array_temp.size() << endl << endl;
}

//HW 3

class Card
{
public:
    enum Nominal
    {
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 2,
        QUEEN = 3,
        KING = 4,
        ACE = 1
    };
    enum Suit
    {
        SPADES,
        HEARTS,
        DIAMONDS,
        CLUBS
    };
    Card(Suit s, Nominal v, bool iss);
    int getValue() const;
    void flip();
private:
    Nominal value;
    Suit suit;
    bool isShirtDown;
};

Card::Card(Suit s, Nominal v, bool iss) : suit(s), value(v), isShirtDown(iss) { }

int Card::getValue() const
{
    if (isShirtDown) {
        return static_cast<int>(value);
    }
    else
    {
        return 0;
    }
}

void Card::flip()
{
    isShirtDown=!(isShirtDown);
}

class Hand
{
protected:
    vector<Card*> Cards;
public:
    Hand() {}
    void add(Card* pCard)
    {
        Cards.push_back(pCard);
    }
    void clear()
    {
        Cards.clear();
    }
    int getTotal() const
    {
        int total = 0;
        for (int i = 0; i < Cards.size();i++)
        {
            total += Cards[i]->getValue();
        }    
        return total;
    }
};

void HomeWork_3()
{
    cout << "Home Work #3" << endl;
    Card T1(Card::SPADES, Card::QUEEN, false);
    Card T2(Card::HEARTS, Card::TEN, true);
    Card T3(Card::DIAMONDS, Card::EIGHT, true);
    Card T4(Card::CLUBS, Card::JACK, true);
    Hand H;
    H.add(&T1);
    H.add(&T2);
    cout << "All weight: " << H.getTotal() << endl;
    H.clear();
    cout << "After clear: " << H.getTotal() << endl;

}

int main()
{
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    return 0;
}