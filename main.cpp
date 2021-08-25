#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "timer.hpp"

using namespace std;

template <typename T>
void Swap(T * a, T * b)
{
    //I like to move it, move it 
    T temp = move(* a);
    * a = move (* b);
    * b = move(temp);
}

void HomeWork_1()
{
    cout << "Home Work #1" << endl;
    int a = 100;
    int b = 200;
    cout << "a = " << a << ", b = " << b << endl;
    Swap(& a, & b);
    cout << "Swaping" << endl;
    cout << "a = " << a << ", b = " << b << endl << endl;
}

void PrintVector(vector<int *> & pA)
{
    for (size_t i = 0; i < pA.size(); ++i)
    {
        cout << * pA[i] << " ";
    }
    cout << endl;
}

bool compareSortPoint(int * a, int * b)
{
    return (* a < * b);
}

void SortPointers(vector<int *> & pA)
{
    sort(pA.begin(), pA.end(), compareSortPoint);
}

void HomeWork_2()
{
    cout << "Home Work #2" << endl;
    //использную простой int без сложных объектов
    vector <int *> Vec;
    //заполенение на 10 случайных элементов
    const size_t t = 10;
    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> distribution(1, 100);
    for (size_t i = 0; i < t; ++i)
    {
        int * a = new int(distribution(generator));
        Vec.push_back(a);
    }
    cout << "Unsort vector: " << endl;
    PrintVector(Vec);
    SortPointers(Vec);
    cout << "Sort vector: " << endl;
    PrintVector(Vec);

    //и не забываем освободить память
    for (size_t i = 0; i < Vec.size(); ++i)
    {
        delete Vec[i];
    }
    cout << endl;
}

void HomeWork_3()
{
    cout << "Home Work #3" << endl;
    ifstream file("hhgttg.txt");
    if (file)
    {
        size_t countVowel = 0;
        string vowel = "aeiouyAEIOUY";
        char S;

        //count_if и find
        Timer t("count_if and find");
        countVowel = count_if(istream_iterator<char>(file), istream_iterator<char>(), [vowel] (const char S)
        {
            return (vowel.find(S) != string::npos);
        });
        t.print();
        cout << "Vowel: " << countVowel << endl << endl;

        //count_if и цикл for
        countVowel = 0;
        file.clear();
        file.seekg(0);
        t.start("count_if and for");
        countVowel = count_if(istream_iterator<char>(file), istream_iterator<char>(), [vowel] (const char S)
        {
            for (size_t i = 0; i < vowel.size(); ++i)
            {
                if (S == vowel[i])
                {
                    return true;
                }
            }
            return false;
        });
        t.print();
        cout << "Vowel: " << countVowel << endl << endl;

        //цикл for и find
        countVowel = 0;
        file.clear();
        file.seekg(0);
        t.start("     for and find");
        for (file >> S; !file.eof(); file >> S)  
        {
            if (vowel.find(S) != string::npos)
            {
                countVowel++;
            }
        }
        t.print();
        cout << "Vowel: " << countVowel << endl << endl;

        // 2 цикла for
        countVowel = 0;
        file.clear();
        file.seekg(0);
        t.start("     for and for");
        for (file >> S; !file.eof(); file >> S)
        {
            for (size_t i = 0; i < vowel.size(); ++i)
            {
                if (S == vowel[i])
                {
                    countVowel++;
                }
            }
        }
        t.print();
        cout << "Vowel: " << countVowel << endl << endl;
    }
    file.close();
}

int main()
{
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    return 0;
}