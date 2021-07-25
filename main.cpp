#include <iostream>
#include <memory> 
#include <utility>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Date
{
private:
    int year;
    int month;
    int day;
public:
    Date(int y, int m, int d) : year(y), month(m), day(d) { }
    int getYear() const
    {
        return year;
    }
    int getMonth() const
    {
        return month;
    }
    int getDay() const
    {
        return day;
    }
    friend ostream& operator<<(ostream &out, const Date &date);
    //friend Date maxDate(Date d1, Date d2);
};

ostream& operator<<(ostream &out, const Date &date)
{
    out << "Year: " <<  date.year << ", Month: " << date.month << ", Day: " << date.day;
    return out;
}

Date maxDate(Date * d1, Date * d2)
{
    if (d2->getYear() > d1->getYear())
    {
        return *d2;
    }
    if (d1->getYear() > d2->getYear())
    {
        return *d1;
    }
    if (d2->getMonth() > d1->getMonth())
    {
        return *d2;
    }
    if (d1->getMonth() > d2->getMonth())
    {
        return *d1;
    }
    if (d2->getDay() > d1->getDay())
    {
        return *d2;
    }

    return *d1;
}

void swapDate(unique_ptr<Date> & d1, unique_ptr<Date> & d2)
{
    d1.swap(d2);
}

void HomeWork_1()
{
    cout << "Home Work #1" << endl << endl;
    //make_unique в std 14, сделал под 11
    unique_ptr<Date> today(new Date(2021,7,24));
    unique_ptr<Date> date ;
    cout << "Year: " << today->getYear() << endl;
    cout << "Month: " << today->getMonth() << endl;
    cout << "Day: " << today->getDay() << endl;
    cout << * today << endl;
    date = move(today);
    cout << "Today is " << ((today == nullptr) ? "" : "not ") << "null" << endl;
    cout << "Date is " << ((date == nullptr) ? "" : "not ") << "null" << endl << endl;
}

void HomeWork_2()
{
    cout << "Home Work #2" << endl << endl;
    unique_ptr<Date> date1(new Date(2021, 10, 24));
    unique_ptr<Date> date2(new Date(1983, 9, 12));
    cout << maxDate(date1.get(), date2.get()) << endl << endl;
    swapDate(date1, date2);
    cout << * date1 << endl;
    cout << * date2 << endl << endl;
}

class Card
{
public:
    enum Nominal
    {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13
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
    friend ostream& operator<< (ostream &out, const Card &card);
private:
    Nominal value;
    Suit suit;
    bool isShirtDown;
};

Card::Card(Suit s, Nominal v, bool iss) : suit(s), value(v), isShirtDown(iss) { }

int Card::getValue() const
{
    if (isShirtDown) {
        if (value > 10)
        {
            return 10;
        }
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

ostream& operator<< (ostream &out, const Card &card)
{
    string s = "";
    if (card.isShirtDown)
    {
        switch (card.suit)
        {
        case Card::HEARTS:
            s += "♡";
            break;
        case Card::SPADES:
            s += "♠";
            break;
        case Card::DIAMONDS:
            s += "♢";
            break;
        case Card::CLUBS:
            s += "♣";
            break;
        default:
            s += " ";
            break;
        }
        switch (card.value)
        {
        case Card::ACE:
            s += "A";
            break;
        case Card::JACK:
            s += "J";
            break;
        case Card::QUEEN:
            s += "Q";
            break;
        case Card::KING:
            s += "K";
            break;
        case Card::TEN:
            s += "10";
            break;
        default:
            s += to_string(card.value);
            break;
        }
    }
    else
    {
        s += "XX";
    }
    out << s;
    return out;
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
        //таки да, по задумки авторов методички это тут
        for (int i = 0; i < Cards.size(); i++)
        {

            delete Cards[i];
        }
        Cards.clear();
    }
    int getTotal() const
    {
        int totalB = 0;
        int totalS= 0;
        for (int i = 0; i < Cards.size();i++)
        {
            totalS += Cards[i]->getValue();
            totalB += Cards[i]->getValue();
            if ( Cards[i]->getValue() == 1 )
            {
                totalB += 10;
            }
        }   
        
        int total = (totalB > 21) ? totalS : totalB;
        return total;
    }
    ~Hand()
    {
        clear();
    }
};

class GenericPlayer : public Hand
{
protected:
    string name;
public:
    GenericPlayer(string n) : name(n) {}
    bool IsBoosted() const
    {
        return (getTotal()>21);
    }
    void Bust() const
    {
        cout << "Points ";
        cout << ((IsBoosted()) ? "over 21" : "less than 21");
        cout << endl;
    }
    virtual bool IsHitting() const
    {
        return false;
    }
    friend ostream& operator<< (ostream &out, const GenericPlayer &player);
};

ostream& operator<< (ostream &out, const GenericPlayer &player)
{
    out << "Name: " << player.name << "\n";
    out << "Points: " << player.getTotal() << "\n";
    out << ((player.Cards.size()>0) ? "C" : "No c") << "ards in hand"  << ((player.Cards.size()>0) ? ":" : ".") << "\n";
    for (int i = 0; i < player.Cards.size(); i++)
    {
        out << *player.Cards[i] << " ";
    }
    out << "\n";
    return out;
}

class Player: public GenericPlayer
{
private:

public:
    Player(string n): GenericPlayer(n) {}
    bool IsHitting() const override
    {
        cout << "Player: " << name;
        string s;
        int tryIn = 0;
        cout << " yours points: " << getTotal() << "." << endl;
        cout << "You need new card? Enter ";
        while (true)
        {
            cout << "Y or N: ";
            cin >> s;
            if (s == "Y" || s == "y")
            {
                cout << "Ok, here's card" << endl;
                return true;
            }
            if (s == "N" || s == "n")
            {
                cout << "No so no" << endl;
                return false;
            }
            if (tryIn > 1)
            {
                cout << "Ok, i think is not" << endl;
                return false;
            }
            cout << "I do not understand. Please enter only ";
            tryIn++;
        }
        
    }

    void Win() const
    {
        cout << "Player " << name << ", you game is win!" << endl; 
    }

    void Lose() const
    {
        cout << "Player " << name << " you game is lose!" << endl; 
    }

    void Push() const
    {
        cout << "Player " << name << " you game is push" << endl; 
    }
};

class House: public GenericPlayer
{
private:

public:
    House(): GenericPlayer("Dealer") { }
    bool IsHitting() const override
    {
        return (getTotal() <= 17);
    }
    void FlipFirstCard()
    {
        if (Cards.size()>0)
        {
            Cards[0]->flip();
        }
    }
};

class Deck : public Hand
{
private:
public:
    void Populate()
    {
        for (int s = 0; s <= 3; s++)
        {
            for (int n = 1; n <= 13; n++)
            {
                Card * D = new Card(static_cast<Card::Suit>(s), static_cast<Card::Nominal>(n), true);
                add(D);
            }
        }
    }
    
    void Shuffle()
    {
        random_device rng;
        mt19937 urng (rng());
        //random_shuffle is deprecated in 14
        shuffle(Cards.begin(), Cards.end(), urng);
    }

    Deck()
    {   
        Populate();
        //Shuffle();
        //странно вытаскивать перемешивание в конструктор Game
    }

    void Deal(Hand & aHand)
    {
        if (Cards.size()>0)
        {
            aHand.add(Cards.back());
            Cards.pop_back();
        }
        else
        {
            //вот тут пока беда с пониманием правил
            //поэтому пока добавляю 52 карты и все мешаю
            cout << "Deck is over, add new Deck" << endl;
            Populate();
            Shuffle();
        }
    }

    void AddltionalCards (GenericPlayer& aGenericPlayer)
    {
        while (!(aGenericPlayer.IsBoosted()) && aGenericPlayer.IsHitting())
        {
            Deal(aGenericPlayer);
            if (aGenericPlayer.IsBoosted())
            {
                aGenericPlayer.Bust();
            }
        }
    }
};

class Game
{
private:
    Deck gDeck;
    House gHouse;
    vector<Player> gPlayers;
public:
    Game(const vector<string>& names)
    {
        vector<string>::const_iterator pName;
        for (pName = names.begin(); pName != names.end(); pName++)
        {
            gPlayers.push_back(Player(*pName));
        }
        gDeck.Populate();
        gDeck.Shuffle();

    }
    void Play()
    {
        for (int k = 0; k < 2; k++)
        {
            for (int i = 0; i < gPlayers.size(); i++)
            {
                gDeck.Deal(gPlayers[i]);
            }
            gDeck.Deal(gHouse);
        }
        gHouse.FlipFirstCard();
        //всех показать
        cout << gHouse << endl;
        for (int i = 0; i < gPlayers.size(); i++)
        {
            cout << gPlayers[i] << endl;
        }
        for (int i = 0; i < gPlayers.size(); i++)
        {
            gDeck.AddltionalCards(gPlayers[i]);
        }
        gHouse.FlipFirstCard();
        gDeck.AddltionalCards(gHouse);
        //всех показать
        cout << gHouse << endl;
        for (int i = 0; i < gPlayers.size(); i++)
        {
            cout << gPlayers[i] << endl;
        }
        if (gHouse.IsBoosted())
        {
            for (int i = 0; i < gPlayers.size(); i++)
            {
                if (!gPlayers[i].IsBoosted())
                {
                    gPlayers[i].Win();
                }
                else
                {
                    gPlayers[i].Lose();
                }
            }
        }
        else
        {
            for (int i = 0; i < gPlayers.size(); i++)
            {
                if (!gPlayers[i].IsBoosted())
                {
                    if (gPlayers[i].getTotal() > gHouse.getTotal())
                    {
                        gPlayers[i].Win();
                    }
                    else if (gPlayers[i].getTotal() < gHouse.getTotal())
                    {
                        gPlayers[i].Lose();
                    }
                    else
                    {
                        gPlayers[i].Push();
                    }
                }
                else
                {
                    gPlayers[i].Lose();
                }
            }
        }
        for (int i = 0; i < gPlayers.size(); i++)
        {
            gPlayers[i].clear();
        }
        gHouse.clear();
    }   
};


void HomeWork_3()
{
    cout << "Home Work #3" << endl << endl;
    Deck D;
    D.Shuffle();
    //Player P("Klef");
    House P;
    cout << "In deck " << D.getTotal() << " point, in hand " << P.getTotal() << endl;
    D.AddltionalCards(P);
    cout << "In deck " << D.getTotal() << " point, in hand " << P.getTotal() << endl << endl;
}

void HomeWork_4()
{
    cout << "Home Work #4" << endl << endl;
    
    vector<string> Names;
    Names.push_back("Mihail");
    Names.push_back("Petr");
    Game G(Names);
    G.Play();
    cout << endl;
}

void HomeWork_5()
{
    cout << "Home Work #5" << endl << endl;
    cout << "it is main for game blackjack" << endl;
    vector<string> Names;
    int totalPlayer = 0;
    int tryIn = 0;
    bool isArr = true;
    int maxPlayer = 6;
    string inName = "";
    do
    {
        cout << "Enter name of player #" << ++totalPlayer << ": ";
        cin >> inName;
        cout << "You enter name: " << inName << "." << endl;
        Names.push_back(inName);
        if (totalPlayer < maxPlayer)
        {
            cout << "Add new player? ";
            string s;
            while (true)
            {
                cout << "Y or N: ";
                cin >> s;
                if (s == "Y" || s == "y")
                {
                    cout << "Add new player." << endl;
                    break;
                }
                if (s == "N" || s == "n")
                {
                    cout << "No so no" << endl;
                    isArr = false;
                    break;
                }
                if (tryIn > 1)
                {
                    cout << "Ok, i think is not" << endl;
                    isArr = false;
                    break;
                }
                cout << "I do not understand. Please enter only ";
                tryIn++;
            }
        }
        else
        {
            isArr = false;
            cout << "You enter max players." << endl;
        }
    } while (isArr);
    
    Game G(Names);
    while (true)
    {
        G.Play();
        string s = "";
        //а это нужно выносить в функцию и быть счастиливым. пока костылем )
        cout << "Play Again? ";
        cout << "Y or N: ";
        cin >> s;
        if (s == "N" || s == "n")
        {
            cout << "Thanx" << endl;
            break;
        }
        if (s == "Y" || s == "y")
        {
            cout << "Going!" << endl;
        }
        else
        {
            cout << "I do not understand. We believe that it is not" << endl;
            break;
        }
    }
    cout << endl;
}

int main()
{
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    HomeWork_4();
    HomeWork_5();
    return 0;
}
