#include <iostream>

using namespace std;

//HW 1
enum sex_type
{
    MALE,
    FEMALE
};

class Person
{
protected:
    string name;
    int age;
    sex_type sex;
    int weight; 
public:
    Person(string n, int a, sex_type s, int w) : name(n), age(a), sex(s), weight(w) { }
    string getName() const
    {
        return name;
    }
    int getAge() const
    {
        return age;
    }
    sex_type getSex() const
    {
        return sex;
    }
    int getWeight() const
    {
        return weight;
    }
    void setName(string n)
    {
        name = n;
    }
    void setAge (int a)
    {
        age = a;
    }
    void setWeight(int w)
    {
        weight = w;
    }

};

class Student : public Person
{
private:
    int cource;
public:
    static int count;   
    Student(string n, int a, sex_type s, int w, int c) : Person(n, a, s, w), cource(c)
    {
        count++;
    }
    int getCource() const
    {
        return cource;
    }
    void setCource(int c)
    {
        cource = c;
    }
    void addCource()
    {
        cource++;
    }
};

int Student::count = 0;

void PrintStudent(Student S)
{
    cout << "Name: " << S.getName() << " ,Age: " << S.getAge() << " ,Sex: " << ((S.getSex() == MALE) ? "Male": "Female") << " ,Weight: " << S.getWeight() << " ,Coyrce: " << S.getCource() << endl;
}

void HomeWork_1()
{
    cout << "Home Work #1" << endl;
    Student S1("Petr", 18, MALE, 76, 1);
    Student S2("Nina", 22, FEMALE, 54, 5);
    Student S3("Micha", 20, MALE, 105, 3);
    S2.addCource();
    S3.setWeight(102);
    S1.setAge(21);
    PrintStudent(S1);
    PrintStudent(S2);
    PrintStudent(S3);
    cout << "All students: "<< Student::count << endl;
}

// HW 2

class Fruit
{
protected:
    string name;
    string color;
public:
    Fruit (string n, string c) : name(n), color(c) { }
    string getName() const
    {
        return name;
    }
    string getColor() const
    {
        return color;
    }
};

class Apple : public Fruit
{
public:
    Apple(string a) : Fruit("Apple", a) { }
};

class Banana : public Fruit
{
public:
    Banana() : Fruit("Banana", "yellow") { }
};

class GrannySmith : public Fruit
{
public:
    GrannySmith() : Fruit("Granny Smith apple", "green") { }
};

void HomeWork_2()
{
    cout << "Home Work #2" << endl;
    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

}

//HW 3

#define size_deck 36

enum Suit
{
    SPADES,
    HEARTS,
    DIAMONDS,
    CLUBS
};

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
    ACE = 11
};

class Card
{
private:
    Nominal value;
    Suit suit;
public:
    Card() { }
    Nominal getNominal() const
    {
        return value;
    }
    string getNominalName() const
    {
        switch (value)
        {
        case SIX:
            return "6";
            break;
        case SEVEN:
            return "7";
            break;
        case EIGHT:
            return "8";
            break;
        case NINE:
            return "9";
            break;
        case TEN:
            return "10";
            break;
        case JACK:
            return "Jack";
            break;
        case QUEEN:
            return "Queen";
            break;
        case KING:
            return "King";
            break;
        case ACE:
            return "Ace";
            break;
        default:
        return "";
            break;
        }
    }
    Suit getSuit() const
    {
        return suit;
    }
    string getSuitName() const
    {
        switch (suit)
        {
        case SPADES:
            return "Spades";
            break;
        case HEARTS:
            return "Hearts";
            break;
        case DIAMONDS:
            return "Diamonds";
            break;
        case CLUBS:
            return "Clubs";
            break;
        default:
            return "";
            break;
        }
    }
    int getWeight() const
    {
        return static_cast<int>(value);
    }
    void setNominal(int i)
    {
        value = static_cast<Nominal>(i);
    }
    void setSuit(int i)
    {
        suit = static_cast<Suit>(i);
    }
};

class Deck
{
private:
    Card card[size_deck];
    bool in_deck[size_deck]; //in deck or game
public:
    Deck()
    {
        int pos = 0;
        for (int i = 2; i < 12; i++)
        {
            for (int s = 0; s < 4; s++)
            {
                if (i != 5)
                {
                    card[pos].setSuit(s);
                    card[pos].setNominal(i);
                    in_deck[pos] = true;
                    pos++;
                }
            }
        }
    }
    Suit getSuit(int i) const
    {
        return card[i].getSuit();
    }
    Nominal getNominal(int i) const
    {
        return card[i].getNominal();
    }
    string getSuitName(int i) const
    {
        return card[i].getSuitName();
    }
    string getNominalName(int i) const
    {
        return card[i].getNominalName();
    }
    bool getStatusCard(int i) const
    {
        return in_deck[i];
    }
    void handOver(int i)
    {
        in_deck[i] = false;
    }

};

class Player
{
private:
    string name;
    bool isAI;
    Card hand[size_deck/2];
    int card_in_hand = 0;
    int cash;
public:
    Player()
    {

    }
    string getName() const
    {
        return name;
    }
    bool getIsAi() const
    {
        return isAI;
    }
    string getSuitName(int i) const
    {
        return hand[i].getSuitName();
    }
    string getNominalName(int i) const
    {
        return hand[i].getNominalName();
    }
    Suit getSuit(int i) const
    {
        return hand[i].getSuit();
    }
    Nominal getNominal(int i) const
    {
        return hand[i].getNominal();
    }
    void AddPlayers(string n, bool ai, int c)
    {
        name = n;
        isAI = ai;
        cash = c;
    }
    void AddCard(Suit s, Nominal n)
    {
        hand[card_in_hand].setSuit(s);
        hand[card_in_hand].setNominal(n);
        card_in_hand++;
    }
    int getSum() const
    {
        int sum = 0;
        for (int i = 0; i<card_in_hand; i++)
        {
            sum += hand[i].getWeight();
        }
        return sum;
    }
    void getCardInHands()
    {
        int sum = 0;
        for (int i = 0; i<card_in_hand; i++)
        {
            cout << (i+1) << ". " << hand[i].getSuitName() << " " << hand[i].getNominalName() << endl;
        }
    }

};
class Game
{
private:
    Player P[2];
    Deck D;
    int bank;
    int shag = 0;
public:
    Game(string n) 
    {
        P[0].AddPlayers(n, false, 100);
        P[1].AddPlayers("Casino", true, 1000);
    }
    string getAI() const
    {
        return P[1].getName();
    }
    string getHuman() const
    {
        return P[0].getName();
    }
    void tour() 
    {
        int R = rand() % size_deck;
        P[0].AddCard(D.getSuit(R), D.getNominal(R));
        R = rand() % size_deck;
        P[1].AddCard(D.getSuit(R), D.getNominal(R));
        shag++;
        cout << "Tour: " << shag << endl;
        cout << "player 1: " << P[0].getName() << endl;
        P[0].getCardInHands();
        cout << "Weight: " << P[0].getSum() << endl;
        cout << "player 2: " << P[1].getName() << endl;
        P[1].getCardInHands();
        cout << "Weight: " << P[1].getSum() << endl << endl;
    }
};

void HomeWork_3()
{
    cout << "Home Work #2" << endl;
    Game G("Dmitry");
    G.tour();
    G.tour();
    G.tour();


}

int main()
{
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    return 0;
}