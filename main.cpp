#include <iostream>
#include <cmath>
#include <cstdint>

using namespace std;

const int SizeStack = 10;

class Power
{
private:
    int Var1 = 10;
    int Var2 = 2;
public:
    Power() { }
    void set(int a, int b)
    {
        Var1 = a;
        Var2 = b;
    }
    int calculate()
    {
        return pow (Var1, Var2);
    }
};

class RGBA
{
private:
    uint8_t m_red = 0;
    uint8_t m_green = 0;
    uint8_t m_blue = 255;
    uint8_t m_alpha = 255;
public:
    RGBA()
    {
        cout << "Input RED: " << endl;
        cin >> m_red;
        cout << "Input GREEN: " << endl;
        cin >> m_green;
        cout << "Input BLUE: " << endl;
        cin >> m_blue;
        cout << "Input ALPHA: " << endl;
        cin >> m_alpha;
    }
    void print()
    {
        cout << "RED = " << m_red << endl; 
        cout << "GREEN = " << m_green << endl; 
        cout << "BLUE = " << m_blue << endl; 
        cout << "ALPHA = " << m_alpha << endl; 
    }
};


class Stack
{
private:
    int Value[SizeStack];
    int Pos = 0;
public:
    Stack()
    {
        reset();
    }
    void reset()
    {
        Pos = 0;
        for (int i = 0; i<SizeStack; i++)
        {
            Value[i] = 0;
        }
    }
    bool push(int a)
    {
        if (Pos<SizeStack) 
        {
            Value[Pos] = a;
            Pos++;
            return true;
        }
        else 
        {
            return false;
        }
        
    }
    int pop()
    {
        if (Pos>0)
        {
            Pos--;
            int R = Value[Pos];
            Value[Pos] = 0;
            return R;
        }
        else
        {
            cout << "WARNING: Stack is emty" << endl;
            return 0;
        }
    }
    void print()
    {
        cout << "{ ";
        for (int i = 0; i < Pos; i++)
        {
            cout << Value[i] << " ";
        }
        cout << "}" << endl;
    }
};

void HomeWork_1()
{
    cout << "HomeWork #1" << endl;
    Power P;
    P.set(15,3);
    cout << P.calculate() << endl;
}

void HomeWork_2()
{
    cout << "HomeWork #2" << endl;
    RGBA color;
    color.print();

}

void HomeWork_3()
{
    cout << "HomeWork #3" << endl;
    Stack stack;
    stack.reset();
    stack.print();
    
    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();
    
    stack.pop();
    stack.print();
    
    stack.pop();
    stack.pop();
    stack.print(); 
}
int main() {
  //HomeWork_1();
  //HomeWork_2();
  HomeWork_3();

  return 0;
}
