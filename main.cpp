#include <iostream>
#include <random>

using namespace std;

template <typename T>
T division(T & a, T & b)
{
    if (b == 0)
    {
        throw runtime_error("Divide by zero");
    }
    return a / b;
}

void HomeWork_1()
{
    cout << "Home Work #1" << endl;
    int a = 10;
    int b = 2;
    try
    {
        cout << a << "/" << b << "=" << division(a, b) << endl; 
        b = 0;
        cout << a << "/" << b << "=" << division(a, b) << endl;
    }
    catch(const runtime_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << endl;
}

class Ex
{
private:
    float x;
public:
    Ex(float x) : x(x) { }
    friend ostream& operator<<(ostream &out, const Ex &ex); 
};

ostream& operator<<(ostream &out, const Ex &ex)
{
    out << ex.x;
    return out;
}

class Bar
{
private:
    float y;
public:
    Bar()
    {
        y = 0;
    }
    void set(float & a)
    {
        if (y + a > 100)
        {
            throw Ex (a * y);
        }
        else
        {
            y = a;
        }
    }
};

void HomeWork_2()
{
    cout << "Home Work #2" << endl;
    float n;
    Bar foo;
    try
    {
        while (true)
        {
            cout << "Enter float: ";
            cin >> n;
            if (n == 0)
            {
                throw Ex(n);
            }
            foo.set(n);
        }
    }
    catch(const Ex & e)
    {
        cerr << "Exeption: " << e << endl;
    }
    cout << "For next homework push ENTER";
    char ok;
    cin.get(ok);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
}


class IllegalCommand
{
protected:
    string txtError;
    string command;
public:
    IllegalCommand(string com) : command(com) { }
    const char * getError()
    {
        txtError = "Command " + command + " illegal!" + "\n";
        txtError += "Variable: UP, DOWN, LEFT, RIGHT, HELP, QUIT\n\n\n";
        return txtError.c_str();
    }
};

class OffTheField : public IllegalCommand
{
private:
    int field;
    int x;
    int y;
public:
    OffTheField(int f, int xm, int ym, string com) : field(f), x(xm), y(ym), IllegalCommand(com) { }
    const char * getError()
    {
        txtError = "Out of the field\n";
        txtError += "Field: " + to_string(field) + "x" + to_string(field) + "\n";
        txtError += "Posicion: " + to_string(x) + "x" + to_string(y) + "\n";
        txtError += "Direction: " + command + "\n";
        return txtError.c_str();
    }
};

char lower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

class Robot
{
private:
    int x;
    int y;
    int field;
    bool inGame;
public:
    Robot(int max) : field(max)
    {
        //случайное размещение робота
        inGame = true;
        random_device random_device;
        mt19937 generator(random_device());
        uniform_int_distribution<> distribution(1, field);
        x = distribution(generator);
        y = distribution(generator);
    }
    bool getStatus() const
    {
        //статус завершения игры
        return inGame;
    }
    void command(string & s)
    {
        transform(s.begin(), s.end(), s.begin(), lower);
        //switch кажется не умеет в string, поэтому старые добрые if
        //только мне это кажется индусским
        if (s == "up")
        {
            if (y == 1)
                throw OffTheField(field, x, y, s);
            y--;
            cout << "Robot moving up\n";
        }
        else if (s == "down")
        {
            if (y == field - 1)
                throw OffTheField(field, x, y, s);
            y++;
            cout << "Robot moving down\n";
        }
        else if (s == "left")
        {
            if (x == 1)
                throw OffTheField(field, x, y, s);
            x--;
            cout << "Robot moving left\n";
        }
        else if (s == "right")
        {
            if (x == field - 1)
                throw OffTheField(field, x, y, s);
            y--;
            cout << "Robot moving right\n";
            //да, нужно на функцию выбрасывать
        }
        else if (s == "quit")
        {
            cout << "Thanx for all\n";
            inGame = false;
        }
        else if (s == "help")
        {
            cout << "Variable command: UP, DOWN, LEFT, RIGHT, HELP, QUIT\n";
        }
        else
        {
            throw IllegalCommand(s);
        }
        cout << "\n\n\n\n";
    }
    friend ostream& operator<<(ostream &out, const Robot &rob); 
};

ostream& operator<<(ostream &out, const Robot &rob)
{
    //в тз не было, но почему бы и нет визуализации
    out << "┌";
    for (int i = 1; i <= rob.field; i++)
    {
        out << "─";
    }
    out << "┐\n";
    for (int y = 1; y <= rob.field; y++)
    {
        for (int x = 0; x <= rob.field + 1; x++)
        {
            if (x == 0 || x == rob.field + 1)
            {
                out << "│";
            }
            else if (y == rob.y && x == rob.x)
            {
                out << "X";
            }
            else
            {
                out << " ";
            }
        }
        out << "\n";
    }
    out << "└";
    for (int i = 1; i <= rob.field; i++)
    {
        out << "─";
    }
    out << "┘\n";
    return out;
}

void HomeWork_3()
{
    cout << "\x1B[2J\x1B[H";
    cout << "Home Work #3\n\n\n\n" << endl;
    Robot Game(10);
    while (Game.getStatus())
    {
        cout << Game << endl;
        cout << "Enter action: ";
        string s;
        cin >> s;
        cout << "\x1B[2J\x1B[H";
        try
        {
            Game.command(s);
        }
        catch(OffTheField & e)
        {
            cerr << e.getError() << endl;
        }
        catch(IllegalCommand & e)
        {
            cerr << e.getError() << endl;
        }
    }
    cout << Game << endl;
    
}
int main()
{
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    return 0;
}