#include <iostream>

using namespace std;

//HM 1

const float pi = 3.14;

class Figure
{
public:
    virtual float area() const = 0;
};

class Parallelogram: public Figure
{
protected:
    float side_a;
    float side_b;
public:
    Parallelogram(float a, float b) : side_a(a), side_b(b) { }
};

class Circle: public Figure
{
private:
    float radius;
public:
    Circle(float r) : radius(r) { }
    float area() const override 
    {
        return pi * radius * radius;
    }
};

class Square: public Parallelogram
{
public:
    Square(float a) : Parallelogram(a,a) { }
    float area() const override
    {
        return side_a * side_a;
    }
};

class Rectangle: public Parallelogram
{
public:
    Rectangle(float a, float b) : Parallelogram(a,b) { }
    float area() const override
    {
        return side_b * side_a;
    }
};

class Rhombus: public Parallelogram
{
private:
    float D1;
    float D2;
public:
    Rhombus(float d1, float d2) : D1(d1), D2(d2), Parallelogram(0.0,0.0) { }
    float area() const override
    {
        return (D1 * D2)/2;
    }
};

void HomeWork_1()
{
    cout << "Home Work #1" << endl;
    Circle C(2.0);
    Rectangle R(5.0, 4.0);
    Square S(8.0);
    Rhombus F(10.0, 9.0);
    cout << "Area of Circle: " << C.area() << endl;
    cout << "Area of Rectangle: " << R.area() << endl;
    cout << "Area of Square: " << S.area() << endl;
    cout << "Area of Rhombus: " << F.area() << endl;
}

// HW 2
class Car
{
protected:
    string company;
    string model;
public:
    Car(string c, string m) : company(c), model(m)
    {
        cout << "Car: " << company << "-" << model << " created" << endl;
    }
};

class PassengerCar: virtual public Car
{
public:
    PassengerCar(string c, string m) : Car(c, m)
    {
        cout << "Car: " << company << "-" << model << " is Passenger" << endl;
    }
};

class Bus: virtual public Car
{
public:
    Bus(string c, string m) : Car(c,m)
    {
        cout << "Car: " << company << "-" << model << " is Bus" << endl;
    }
};

class Minivan: public PassengerCar, public Bus
{
public:
    Minivan(string c, string m) : PassengerCar(c, m), Bus(c,m), Car(c, m)
    {
        cout << "Car: " << company << "-" << model << " is Minivan" << endl;
    }
};

void HomeWork_2()
{
    cout << endl << "Home Work #2" << endl;
    Bus pasik("pas", "3306");
    PassengerCar vasik("LADA", "2106");
    Minivan rafik("RAF", "2204");
}

//HW 3

class Fraction
{
private:
    int numerator;
    int denominator;
public:
    Fraction(int num, int den) : numerator(num), denominator(den)
    {
        int tnum = abs(numerator);
        int tden = abs(denominator);
        int temp;
        if (tden == 0)
        {
            cout << "Denominator is not 0!" << endl;
            throw exception();
        }
        if (tnum == 0)
        {
            numerator = 0;
            denominator = 1;
        }
        while (tnum != 0)
        {
            if (tnum < tden)
            {
                temp = tnum;
                tnum = tden;
                tden = temp;
            }
            tnum = tnum - tden;
        }
        int global = tden;
        numerator = numerator/global;
        denominator = denominator/global;
    }
    void getFraction() const
    {
        cout << numerator << "/" << denominator;
    }
    friend Fraction operator+(Fraction &f1, Fraction &f2);
    friend Fraction operator-(Fraction &f1, Fraction &f2);
    friend Fraction operator*(Fraction &f1, Fraction &f2);
    friend Fraction operator/(Fraction &f1, Fraction &f2);
    friend Fraction operator-(Fraction &f1);
    friend bool operator==(Fraction &f1, Fraction &f2);
    friend bool operator!=(Fraction &f1, Fraction &f2);
    friend bool operator<(Fraction &f1, Fraction &f2);
    friend bool operator>(Fraction &f1, Fraction &f2);
    friend bool operator<=(Fraction &f1, Fraction &f2);
    friend bool operator>=(Fraction &f1, Fraction &f2);
};

void Print(Fraction &d1, Fraction &d2, Fraction &d3, string c)
{
    d1.getFraction();
    cout << " " << c << " ";
    d2.getFraction();
    cout << " = ";
    d3.getFraction();
    cout << endl;
}

void Print(Fraction &d1, Fraction &d2, string c, bool t)
{
    d1.getFraction();
    cout << " " << c << " ";
    d2.getFraction();
    cout << " = " << ((t) ? "True" : "False") << endl;
}

void Print(Fraction &d1, Fraction &d3)
{
    cout << "Minus ";
    d1.getFraction();
    cout << " = ";
    d3.getFraction();
    cout << endl;
}

Fraction operator+(Fraction &f1, Fraction &f2)
{
    return Fraction((f1.numerator*f2.denominator+f2.numerator*f1.denominator), (f1.denominator*f2.denominator));
}

Fraction operator-(Fraction &f1, Fraction &f2)
{
    return Fraction((f1.numerator*f2.denominator-f2.numerator*f1.denominator), (f1.denominator*f2.denominator));
}

Fraction operator*(Fraction &f1, Fraction &f2)
{
    return Fraction((f1.numerator*f2.numerator),(f1.denominator*f2.denominator));
}

Fraction operator/(Fraction &f1, Fraction &f2)
{
    return Fraction((f1.numerator*f2.denominator),(f1.denominator*f2.numerator));
}

Fraction operator-(Fraction &f1)
{
    return Fraction(-f1.numerator, f1.denominator);
}

bool operator==(Fraction &f1, Fraction &f2)
{
        return (f1.denominator == f2.denominator && f1.numerator == f2.numerator);

}

bool operator!=(Fraction &f1, Fraction &f2)
{
    return (f1.denominator != f2.denominator || f1.numerator != f2.numerator);
}

bool operator<(Fraction &f1, Fraction &f2)
{
    return (static_cast<float>(f1.numerator)/f1.denominator < static_cast<float>(f2.numerator)/f2.denominator);
}

bool operator>(Fraction &f1, Fraction &f2)
{
    return (static_cast<float>(f1.numerator)/f1.denominator > static_cast<float>(f2.numerator)/f2.denominator);;
}

bool operator<=(Fraction &f1, Fraction &f2)
{
    return !(f1 > f2);
}

bool operator>=(Fraction &f1, Fraction &f2)
{
    return !(f1 < f2);
}

void HomeWork_3()
{
    cout << endl << "Home Work #3" << endl;
    Fraction d1(1,2);
    Fraction d2(1,4);
    Fraction d3 = d1 + d2;
    Print(d1, d2, d3, "+");
    d3 = d1 - d2;
    Print(d1, d2, d3, "-");
    d3 = d1 * d2;
    Print(d1, d2, d3, "*");
    d3 = d1 / d2;
    Print(d1, d2, d3, ":");
    d3 = - d1;
    Print(d1, d3);
    Print(d1, d2, "==", (d1 == d2));
    Print(d1, d2, "!=", (d1 != d2));
    Print(d1, d2, "<", (d1 < d2));
    Print(d1, d2, ">", (d1 > d2));
    Print(d1, d2, ">=", (d1 >= d2));
    Print(d1, d2, "<=", (d1 <= d2));
}


//HW 4

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
    ACE = 1
};

class Card
{
private:
    Nominal value;
    Suit suit;
    bool shirt;
public:
    Card(Suit s, Nominal v, bool t) : suit(s), value(v), shirt(t) { }
    void Flip()
    {
        shirt = !shirt;
        cout << "Fliping" << endl;
    }
    int GetValue()
    {
        return static_cast<int>(value);
    }

};

void HomeWork_4()
{
    cout << endl << "Home Work #3" << endl;
    Card korolpik(SPADES, KING, true);
    korolpik.Flip();
    cout << "Is weight: " << korolpik.GetValue() << endl;

}

int main()
{
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    HomeWork_4();
    return 0;
}