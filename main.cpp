#include <iostream>

using namespace std;

double PrintArray (double * pdArray, int size) 
{
    for (int i = 0; i<size; i++) 
    {
        
        cout << "Array[" << i << "] = " << *(pdArray + i) << endl;
    }
    return *pdArray;
}

int PrintArray (int * pdArray, int size) 
{
    for (int i = 0; i<size; i++) 
    {
        
        cout << *(pdArray + i) << " ";
    }
    cout << endl;
    return *pdArray;
}

void MagicProcedure(int * pdArray, int size) 
{
    for (int i = 0; i<size; i++) 
    {
         *(pdArray + i) ^= 1;
    }
}

void CicleArray(int * pdArray, int size, int Step) 
{
    int Begin = 1;
    for (int i = 0; i<size; i++)
    {
        *(pdArray+i) = Begin + Step * i;
    }
}

void BiasArray(int * pdArray, int size, int Bias) 
{
    if (Bias < 0 )
    {
        Bias = size + Bias;
    }
    int tmp = 0;
    for (int b = 1; b<=Bias; b++) {
        tmp = *(pdArray);
        for (int i = 0; i<size; i++) {
            *(pdArray+i) = *(pdArray+i+1);
        }
        *(pdArray+size-1) = tmp;
    }

}

bool checkBalance(int * pdArray, int size)
{
    for (int i = 1; i<size; i++)
    {
        int left = 0;
        for (int l = 0; l<i; l++)
        {
            left += *(pdArray+l);
        }
        int right = 0;
        for (int r = i; r<size; r++)
        {
            right += *(pdArray+r);
        }
        if (left == right )
        {
            return true;
        }
    }
    return false;
}
void HomeWork_1() 
{
    cout << "Home Work #1 " << endl;
    srand (static_cast <unsigned> (time(0)));
    // я знаю что rand псевдорандом, но полного рандома мне сейчас и не надо.
    const unsigned int ASIZE = 10;
    double dArray[ASIZE] = { 0 };
    //заполняем массив
    for (int i = 0; i<ASIZE; i++)
    {
        dArray[i] = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    }
    cout.precision(16);
    PrintArray (&dArray[0], ASIZE);
    cout << endl;
}

void HomeWork_2() 
{
    cout << "Home Work #2 " << endl;
    // да, да, я мог вынести заполнение массива в функцию, но честно, поленился, Копипаст наше все :)
    srand (static_cast <unsigned> (time(0)));
    const unsigned int ASIZE = 6;
    int dArray[ASIZE] = { 0 };
    for (int i = 0; i<ASIZE; i++)
    {
        dArray[i] = rand() % 2;
    }
    cout << "Orig Array:" << endl;
    PrintArray (&dArray[0], ASIZE);
    MagicProcedure(&dArray[0], ASIZE);
    cout << "Magic:" << endl;
    PrintArray (&dArray[0], ASIZE);

    cout << endl;
}

void HomeWork_3() 
{
    cout << "Home Work #3 " << endl;
    const unsigned int ASIZE = 8;
    int dArray[ASIZE] = { 0 };
    CicleArray(&dArray[0], ASIZE, 3);
    PrintArray(&dArray[0], ASIZE);
    cout << endl;
}

void HomeWork_4()
{
    cout << "Home Work #4*" << endl;
    const unsigned int ASIZE = 15;
    int dArray[ASIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    cout << "Orig Array:" << endl;
    PrintArray(&dArray[0], ASIZE);
    cout << "Bias -6:" << endl;
    BiasArray(&dArray[0], ASIZE, -6);
    PrintArray(&dArray[0], ASIZE);

    cout << endl;
}

void HomeWork_5() 
{
    cout << "Home Work #5**" << endl;
    const unsigned int ASIZE = 5;
    int oneArray[] = { 1, 1, 1, 2, 1 };
    PrintArray(&oneArray[0], ASIZE);
    cout << "Is Array in " << ((checkBalance(&oneArray[0], ASIZE)) ? "":"not ") << "balance." << endl;
    int twoArray[] = { 2, 1, 1, 2, 1 };
    PrintArray(&twoArray[0], ASIZE);
    cout << "Is Array in " << ((checkBalance(&twoArray[0], ASIZE)) ? "":"not ") << "balance." << endl;
    int threArray[] = { 10, 1, 2, 3, 4 };
    PrintArray(&threArray[0], ASIZE);
    cout << "Is Array in " << ((checkBalance(&threArray[0], ASIZE)) ? "":"not ") << "balance." << endl;
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