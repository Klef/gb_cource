#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <curl/curl.h>

using namespace std;

//HW1
void HomeWork_1()
{
    cout << "Home Work #1" << endl;
    int i;
    while (true)
    {
        string s;
        cout << "Enter int: ";
        cin >> s;
        bool isInt = true;
        for (int n = 0; n < s.size(); n++)
        {
            if (!isdigit(s[n]))
            {
                isInt = false;
                break;
            }
        }
        if (isInt)
        {
            i = stoi(s);
            break;
        }
        cout << "You enter NOT int!" << endl;
    }
    cout << "You enter: " << i << endl << endl;
}

//HW2
//кажется задание было не в этом, но я взял манипулятор endl из стандартной библетоеки, и добавил второй перевод строки
template <class _CharT, class _Traits>
inline _LIBCPP_INLINE_VISIBILITY
basic_ostream<_CharT, _Traits>&
endll(basic_ostream<_CharT, _Traits>& __os)
{
    __os.put(__os.widen('\n'));
    __os.put(__os.widen('\n'));
    __os.flush();
    return __os;
}
void HomeWork_2()
{
    cout << "Home Work #2" << endl;
    cout << "A" << endll << "B" << endll;

}

//HM 3, 4 and 5;
// пора наверное наработки по блэкджеку выносить в свою библеотеку
class Card
{
public:
    enum Nominal
    {
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
        KING = 13,
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
        Cards.clear();
    }
    int getTotal() const
    {
        int totalB = 0;
        int totalS= 0;
        for (int i = 0; i < Cards.size();i++)
        {
            totalS += Cards[i]->getValue();
            if ( Cards[i]->getValue() == 1 )
            {
                totalB += 11;
            }
        }   
        int total = (totalB < 21) ? totalS : totalB;
        return total;
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
        return false;
    }
    friend ostream& operator<< (ostream &out, const GenericPlayer &player);
};

ostream& operator<< (ostream &out, const GenericPlayer &player)
{
    out << "Name: " << player.name << "\n";
    out << "Points: " << player.getTotal() << "\n";
    out << "Cards in hand: " << "\n";
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
    virtual bool IsHitting() const
    {
        string s;
        int tryIn = 0;
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
        cout << "Player " << name << "you game is lose!" << endl; 
    }

    void Push() const
    {
        cout << "Player " << name << "you game is push" << endl; 
    }
};

class House: public GenericPlayer
{
private:

public:
    House(): GenericPlayer("Dealer") { }
    virtual bool IsHitting() const
    {
        return ((getTotal() <= 16) ? true : false);
    }
    void FlipFirstCard()
    {
        if (Cards.size()>0)
        {
            Cards[0]->flip();
        }
    }
};

void HomeWork_3()
{
    cout << "Home Work #3" << endll;
    Player G("Test user");
    G.IsHitting();
    G.Win();
    G.Push();
    G.Lose();
    cout << endl;
}

void HomeWork_4()
{
    cout << "Home Work #4" << endll;
    House D;
    vector<Card> Deck;
    //даем диллеру две десятки (одну в темную)
    Deck.push_back(Card(Card::DIAMONDS, Card::TEN, false));
    Deck.push_back(Card(Card::HEARTS, Card::TEN, true));
    for (int i=0; i < Deck.size(); ++i)
    {
        D.add(&Deck[i]);
    }
    cout << boolalpha ;
    cout << "Total point: " << D.getTotal() << endl;
    cout << "Needs card: " << D.IsHitting() << endll;
    cout << "Open all card:" << endl;
    D.FlipFirstCard();
    cout << "Total point: " << D.getTotal() << endl;
    cout << "Needs card: " << D.IsHitting() << endl;
    

}

void HomeWork_5()
{
    cout << "Home Work #5" << endll;
    vector<Card> Deck;
    Player H("Bill");
    Deck.push_back(Card(Card::DIAMONDS, Card::TEN, true));
    Deck.push_back(Card(Card::HEARTS, Card::KING, true));
    Deck.push_back(Card(Card::DIAMONDS, Card::ACE, false));
    for (int i=0; i < Deck.size(); ++i)
    {
        H.add(&Deck[i]);
    }
    cout << H;
}

// задача со звездочкой

static size_t write_data(char *data, size_t size, size_t nmemb, std::ofstream* pBuf){
    size_t result = 0;
    if(pBuf != NULL){
        pBuf->write(data, size*nmemb);
        result = size * nmemb;
    }
    return result;
}
string FindCurs(string & p, string f)
{
    //очень не люблю парсить html :)
    string t = ">" + f;
    string stockString = "inline-stocks__value_inner'>";
    string endPos = "</span>";
    int n1 = p.find(stockString, p.find(t));
    int n2 = p.find(endPos, n1);

    string out = p.substr(n1 + stockString.size(), n2 - n1 - stockString.size());
    return f + " = " + out;
}

void HomeWork_6()
{
    cout << "Home Work #6*" << endll;
    CURL *curl;
    CURLcode result;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://yandex.ru/");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        ofstream CurlToFile;
        CurlToFile.open("yandex.html", ios::binary);
        if (CurlToFile.is_open())
            {
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &CurlToFile);
                curl_easy_perform(curl);
                if(result != CURLE_OK)
                {
                    cerr << "WARNING: Not download" << endl;
                    exit(1);
                }
            }
            else
            {
                cerr << "WARNING: Not writing" << endl;
                exit(1);
            }
            CurlToFile.close();
            curl_easy_cleanup(curl);

            ifstream YA;
            YA.open("yandex.html");
            if (YA.is_open())
            {
                string page = "";
                char T;
                //дергаю по символу, так как переводы не нужны
                //и про буфер думать не надо
                while (YA.get(T))
                {
                    page += T;
                }
                cout << FindCurs(page, "USD") << endl;
                cout << FindCurs(page, "EUR") << endl << endl;
                
            }
            else
            {
                cerr << "WARNING: Not reading" << endl;
                exit(1);
            }

        }
        else
        {
            cerr << "WARNING: Not libcurl" << endl;
            exit(1);
        }

}

int main()
{
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    HomeWork_4();
    HomeWork_5();
    HomeWork_6();
    return 0;
}