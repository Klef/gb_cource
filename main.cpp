#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

const int NumOfFile = 2;
string NameOfFile[NumOfFile];

void GenerateArrayPowers(long long * p_Array, int size)
{
    for (int i = 0;i<size;i++)
    {
        *(p_Array+i) = pow(2,i);
    }
}

void PrintArray(long long * p_Array, int size)
{
    for (int i = 0;i<size;i++)
    {
        cout << *(p_Array+i) << " ";
    }
    cout << endl;
}

void HomeWork_1() 
{
    cout << "Home Work #1 " << endl;
    int InSize = 0;
    do
    {
        cout << "Input size of dynamic array: ";
        cin >> InSize;
        if ( InSize == 0 )
        {
            cout << "not so no" << endl;
            break;
        }
        else if ( InSize < 0 )
        {
            cout << "Size of array must be positive!" << endl;
        }
    } while (InSize < 0);
    
    long long * pt_array = nullptr;
    pt_array = new long long [InSize];
    GenerateArrayPowers(&pt_array[0], InSize);
    cout << "here is your array:" << endl;
    PrintArray(&pt_array[0], InSize);
    delete [] pt_array;
    pt_array = nullptr;
    cout << endl;
}

void GenerateArrayRand(int * pt_array, int size)
{
    //rand()
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            *(pt_array+size*x+y) = rand();
        }
    }
}

void PrintArray(int * pt_array, int size)
{   
    cout << "here is your array:" << endl;
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            cout << *(pt_array+size*x+y) << " ";
        }
        cout << endl;
    }
}

void HomeWork_2()
{
    cout << "Home Work #2 " << endl;
    const int SizeMatrix = 4;
    int ** pt_array = new int * [SizeMatrix];
    for (int i = 0; i < SizeMatrix; i++)
    {
        pt_array[i] = new int [SizeMatrix];
    }
    GenerateArrayRand(&pt_array[0][0], SizeMatrix);
    PrintArray(&pt_array[0][0], SizeMatrix);
    for (int i = 0; i < SizeMatrix; i++)
    {
        delete [] pt_array[i];
    }
    delete [] pt_array;
    cout << endl;
}

void EnterName(string * name, int number)
{
    bool check;
    do
    {
        check = true;
        for (int i = 0; i < number; i++) {
            cout << "Enter name new file # " << (i +1) << ": ";
            cin >> *(name+i);
            for (int j =0; j < number; j++)
            {
                if (i != j) 
                {
                    if (*(name+i) == *(name+j))
                    {
                        check = false;
                        cout << "Name file # " << (i + 1) << " must not be equal name file # " << (j + 1) << "!" << endl;
                    }
                }
            }
        }
    } while (!check);
}

void WriteFile(string * name)
{
    ofstream file;
    file.open("./" + *name);
    if (file.is_open())
    {
        file << "File name: " << *name << endl;
        int NumStrong = 50 + rand() %50;
        for (int i = 0; i < NumStrong; i++)
        {
            file << (rand() % 9);
        }
        file << endl << "End" << endl;
        cout << "Writing file name: " << *name << endl;
        file.close();
    }
    else
    {
        cout << "Don't read/write file " << *name << endl;
    }
}

void HomeWork_3()
{
    cout << "Home Work #3 " << endl;
    EnterName(&NameOfFile[0], NumOfFile);
    for (int i = 0; i < NumOfFile; i++ )
    {
        WriteFile(&NameOfFile[i]);
    }
    cout << endl;
}

void SplitFile(string * Name3, string * NameFirst, int Num)
{
    ofstream NewFile;
    NewFile.open("./" + *Name3);
    if (NewFile.is_open())
    {
        for (int i = 0; i < Num; i++)
        {
            ifstream ReadFile;
            string Line;
            ReadFile.open("./" + *(NameFirst+i));
            if (ReadFile.is_open())
            {
                while (getline(ReadFile,Line))
                {
                    NewFile << Line << endl;
                }
                cout << "Read file name: " << *(NameFirst+i) << endl;
                ReadFile.close();
            }
            else
            {
                cout << "Don't read/write file " << *(NameFirst+i) << endl;
            }
        }
        cout << "Writing file name: " << *Name3 << endl;
        NewFile.close();
    }
    else
    {
        cout << "Don't read/write file " << *Name3 << endl;
    }

}

void HomeWork_4()
{
    cout << "Home Work #4 * " << endl;
    string TriFiles = "";
    bool Check;
    do
    {
        Check = true;
        cout << "Enter name new file: ";
        cin >> TriFiles;
        for (int i = 0; i < NumOfFile; i++)
        {
            if (TriFiles == NameOfFile[i])
            {
                Check = false;
                cout << "Name of new file must not be equal name file # " << (i + 1) << "!" << endl;
            }
        }
    } while (!Check);
    SplitFile(&TriFiles, &NameOfFile[0], NumOfFile);
    
    cout << endl;
}

void HomeWork_5()
{
    cout << "Home Work #5 * " << endl;
    string Grep;
    string NameFile;
    ifstream File;
    bool Succes = false;
    cout << "Enter what you need to find: ";
    cin >> Grep;
    cout << endl;
    cout << "Enter where to find: ";
    cin >> NameFile;
    File.open("./" + NameFile);
    if (File.is_open())
    {
        string s;
        for (File >> s; !File.eof(); File >> s) 
        {
            if (Grep == s)
            {
                cout << "Bingo! " << Grep << " find in " << NameFile << endl;
                Succes = true;
                break;
            }
        }
        if (!Succes)
        {
            cout << "Oops... " << Grep << " not find in " << NameFile << endl;
        }
        File.close();
    }
    else
    {
        cout << "Don't read/write file " << NameFile << endl;
    }
}

int main()
{
    srand (static_cast <unsigned> (time(0)));
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    HomeWork_4();
    HomeWork_5();
    
}