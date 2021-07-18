#include <iostream>
#include <vector>

using namespace std;

//HW 1

template <typename T>
class Pair1
{
private:
    T First;
    T Second;
public:
    Pair1(T f, T s) : First(f), Second(s) { }
    T first() const
    {
        return First;
    }
    T second() const
    {
        return Second;
    }
};

void HomeWork_1()
{
    cout << "Home Work #1" << endl;
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << endl;

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << endl << endl;
}

//HW 2

template <typename T, typename C>
class Pair
{
private:
    T First;
    C Second;
public:
    Pair(T f, C s) : First(f), Second(s) { }
    T first() const
    {
        return First;
    }
    C second() const
    {
        return Second;
    }
};

void HomeWork_2()
{
    cout << "Home Work #2" << endl;
    Pair<int, double> p1(6, 7.8);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << endl;

    const Pair<double, int> p2(3.4, 5);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << endl << endl;

}

//HW 3

template <typename T>
class StringValuePair : public Pair<string, T>
{
public:
    StringValuePair(string f, T s) : Pair<string, T>(f,s) {}
};

void HomeWork_3()
{
    cout << "Home Work #3" << endl;
    StringValuePair<int> svp("Amazing", 7);
    cout << "Pair: " << svp.first() << ' ' << svp.second() << endl << endl;
}

// HW 4
class Card
{
public:
    enum Nominal
    {
        //вот тут я узнал, что у меня не те правила блекджка, поэтому переделал стоимость
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 10,
        QUEEN = 10,
        KING = 10,
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
        /*
        * могу ошибатся, но
        * так как я собираю вектор из указателей на объекты, а не создаю, то уничтожать объекты на этапе не видно смысла
        * но, с другой стороны, если колода будет вектором всех карт, из которых уже буду передавать указатели
        * то есть ли смысл хранить сброшенные карты?
        * может понадобится для истории игр
        * если я все тут не сделал криво, и данное решение валидно, я хочу оставить на свое усмотрение необходимости
        * хранения сброшенных карт
        * но, подозреваю что я наркоман и все сделал не правильно, поэтому буду ждать коментариев
        */
        Cards.clear();
    }
    int getTotal() const
    {
        // опять же узнал, что у меня не те правила, переписал код для подсчета карт в мягкой руке
        int totalB = 0;
        int totalS= 0;
        for (int i = 0; i < Cards.size();i++)
        {
            totalS += Cards[i]->getValue();
            //исключение для туза
            if ( Cards[i]->getValue() == 1 )
            {
                totalB += 11;
            }
        }   
        // а теперь смотрим какой счет выбирать
        int total = (totalB < 21) ? totalS : totalB;
        return total;
    }
};

class GenericPlayer : public Hand
{
private:
    string name;
public:
    GenericPlayer(string n) : name(n) {}
    bool IsBoosted() const
    {
        return (getTotal()>21) ? true : false;
    }
    void Bust() const
    {
        cout << "Name: " << name << ", ";
        cout << ((IsBoosted()) ? "over 21" : "less than 21");
        cout << endl;
    }
    virtual bool IsHitting()
    {
        //просто возращаю false, так как логика будет у игроков
        return false;
    }
};
void HomeWork_4()
{
    cout << "Home Work #4" << endl;
    GenericPlayer Human("Human");
    vector<Card> Deck;
    cout << "10, 10, 2" << endl;
    Deck.push_back(Card(Card::DIAMONDS, Card::TEN, true));
    Deck.push_back(Card(Card::HEARTS, Card::TEN, true));
    Deck.push_back(Card(Card::SPADES, Card::TWO, true));
    for (int i=0; i < Deck.size(); ++i)
    {
        Human.add(&Deck[i]);
    }
    Human.Bust();
    cout << "10, 10, Ace" << endl;
    Human.clear();
    Deck.clear();
    Deck.push_back(Card(Card::DIAMONDS, Card::TEN, true));
    Deck.push_back(Card(Card::HEARTS, Card::TEN, true));
    Deck.push_back(Card(Card::SPADES, Card::ACE, true));
    Human.Bust();
}

int main()
{
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    HomeWork_4();
    return 0;
}