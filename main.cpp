#include <iostream>
#include "mylib.hpp"
#include <fstream>

#define CHECKVALUE(Value,MaxValue) (( Value >= 0 && Value <= MaxValue) ? "True" : "False" )
#define SIZE_ARRAY 4
#define SwapINT(a, b) a += b; b -= a; b = -b; a -= b;
#define OutTo(txt, value) << txt << value << endl

using namespace std;

void HomeWork_1()
{
    cout << "Home Work #1 *" << endl;
    const int SIZE = 10;
    float SmallArray[SIZE] = { 0 };
    MyLibArray::InitArray(&SmallArray[0], SIZE);
    MyLibArray::PrintArray(&SmallArray[0], SIZE);
    MyLibArray::CheckArray(&SmallArray[0], SIZE);
    cout << endl;
}

void HomeWork_2()
{
    cout << "Home Work #1 " << endl;
    const int MAXVALUE = 100;
    int InputValue;
    cout << "Enter value: ";
    cin >> InputValue;
    cout << "Value " << InputValue << " in diapazone (0-" << MAXVALUE << "): " << CHECKVALUE(InputValue, MAXVALUE) << endl;
    cout << endl;
}

void HomeWork_3()
{
    cout << "Home Work #1 " << endl;
    int ArrayForSort[SIZE_ARRAY] = { 0 };
    cout << "Iniate array from " << SIZE_ARRAY << " ellements" << endl;
    for ( int i = 0; i<SIZE_ARRAY; i++)
    {
        cout << "Enter element #" << (i+1) << ": ";
        cin >> ArrayForSort[i];
    }
    cout << "Thank you." << endl << endl << "Sorting array: " << endl;
    for (int i = 0; i < SIZE_ARRAY - 1; i++)
    {
        for (int j = 0; j < SIZE_ARRAY - i - 1; j++)
        {
            if (ArrayForSort[j] > ArrayForSort[j + 1])
            {
                SwapINT(ArrayForSort[j], ArrayForSort[j + 1]);
            }
        }
    }
    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        cout << "Element #" << (i+1) << ": " << ArrayForSort[i] << endl;
    }
    cout << endl;
}

void HomeWork_4()
{
    cout << "Home Work #4 *" << endl;
    #pragma pack(push, 1)
    struct stEmploy
    {
        int Id;
        string Name;
        string LastName;
        long Phone;
        int Cab;
    };
    #pragma pack(pop)
    
    stEmploy ZD;
    ZD.Id = 1;
    ZD.Name = "Dmitry";
    ZD.LastName = "Zheludkov";
    ZD.Phone = 79261122333;
    ZD.Cab = 609;
    cout << "Employee:" << endl;
    cout OutTo("ID #: ", ZD.Id);
    cout OutTo("Name: ", ZD.LastName + " " + ZD.Name);
    cout OutTo("Сabinet: ", ZD.Cab);
    cout OutTo("Phone: ", ZD.Phone);
    cout << endl;
    cout OutTo("Size: ", sizeof(ZD));
    ofstream File;
    File.open("./file.txt");
    if (File.is_open()) 
    {
        File << "Employee:" << endl;
        File OutTo("ID #: ", ZD.Id);
        File OutTo("Name: ", ZD.LastName + " " + ZD.Name);
        File OutTo("Сabinet: ", ZD.Cab);
        File OutTo("Phone: ", ZD.Phone);
    }
    else
    {
        cout << "Failed open file!" << endl; 
    }
    File.close();
    cout << endl;
}
int main()
{
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    HomeWork_4();
}
