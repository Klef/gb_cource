#include <iostream>


namespace MyLibArray
{
    using namespace std;
    void InitArray(float * ptArray, int SIZE)
    {
        for (int i = 0; i < SIZE; i++) {
            if (i % 2 == 0)
            {
                *(ptArray + i) = 10.0;
            }
            else
            {
                *(ptArray + i) = -10.0;
            }
        }
    }
    void PrintArray(float * ptArray, int SIZE)
    {
        for (int i = 0; i < SIZE; i++)
        {
            cout << *(ptArray + i) << endl;
        }
    }
    void CheckArray(float * ptArray, int SIZE)
    {
        int Positive = 0;
        int Negative = 0;
        for (int i = 0; i < SIZE; i++)
        {
            if (*(ptArray + i) > 0) 
            {
                Positive++;
            }
            else if (*(ptArray +i) < 0) 
            {
                Negative++;
            }
        }
        cout << "Positive count: " << Positive << endl;
        cout << "Negative count: " << Negative << endl;
    }

}