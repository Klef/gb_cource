#include <iostream>

using namespace std;
enum TicTacToe {
    FIELD_NULL,
    FIELD_X,
    FIELD_O
};

void HomeWork_3();

void PrintField(TicTacToe* fiel) {
    //указатели крутая штука
    for (short x=0;x<3;x++) {
        cout << "|";
        for (short y=0;y<3;y++) {
            switch (*(fiel+3*x+y))
            {
            case FIELD_X:
                cout<<"X";
                break;
            case FIELD_O:
                cout<<"O";
                break;
            default:
                cout<<" ";
                break;
            }
            cout << "|";
        }
        cout << endl;
    }
}

void ClearField(TicTacToe* fiel) {
    //  я не смог победить инициализацию пустыми значениями массив в структуре
    // так что в лучших традиция индуского кода делаю это через функцию
    for (short x=0;x<3;x++) {
        for (short y=0;y<3;y++) {
            *(fiel+3*x+y) = FIELD_NULL;
        }
    }
}

void PrintIsHuman (bool* H) {
    if (*H == true) {
        cout << "Human ";
        }
    else {
        cout << "Computer ";
    }
}

void HomeWork_1() {
    //short int, int, long long, char, bool, float, double
    
    cout << "Home Work #1 " << endl;
    short int VarShIn = 32767;
    int VarIn = 2147483647;
    long long VarLoLo = 9223372036854775807;
    char VarCh = 'A';
    bool VarBu = true;
    float VarFl = 7.1234567;
    double VarDu = 15.12345678901234;
    // да, можно выкинуть в функцию, но операции со строками пока оставлю в покое
    cout << "short int: " << VarShIn << endl;
    cout << "int: " << VarIn << endl;
    cout << "long long: " << VarLoLo << endl;
    cout << "char: " << VarCh << endl;
    cout << "bool: " << VarBu << endl;
    cout.precision(10);
    cout << "float: " << VarFl << endl;
    cout.precision(16);
    cout << "double: " << VarDu << endl;
    cout << endl;
}

void HomeWork_2() {
    cout << "Home Work #2 " << endl;
    //определение enum вынес на уровень выше, ибо хочу его юзать в двух функциях
    TicTacToe VarL = FIELD_NULL;
    cout << "Null Field: " << VarL << endl;
    VarL = FIELD_O;
    cout << "Zero Field: " << VarL << endl;
    VarL = FIELD_X;
    cout << "Cross Field: " << VarL << endl;
    cout << endl;
}

void HomeWork_3() {
    cout << "Home Work #3" << endl;  
    TicTacToe aField[3][3] = {
        { FIELD_NULL, FIELD_NULL, FIELD_X },
        { FIELD_O, FIELD_O, FIELD_X },
        { FIELD_X, FIELD_O, FIELD_X }
    };
    PrintField(&aField[0][0]);
    cout << endl;
}

void HomeWork_4() {
    cout << "Home Work #4 *" << endl;  
    struct gamers
    {
        string Name;
        bool isHuman;
        TicTacToe Figure;

    };
    
    struct Game
    {
        bool isActive;
        unsigned int Winner;
        unsigned int WhoseTour;
        unsigned int FirstTour;
        unsigned int CountTour;
        gamers Player[2];
        TicTacToe Field[3][3]; 
    };
    const int CountGame = 2;
    Game game[CountGame];
    game[0].isActive = false;
    game[0].Winner = 0;
    game[0].FirstTour = 0;
    game[0].WhoseTour = 0;
    game[0].CountTour = 5;
    game[0].Player[0].Name = "Dmitry";
    game[0].Player[0].isHuman = true;
    game[0].Player[0].Figure = FIELD_X;
    game[0].Player[1].Name = "Roberto";
    game[0].Player[1].isHuman = false;
    game[0].Player[1].Figure = FIELD_O;
    ClearField(&game[0].Field[0][0]);
    game[0].Field[0][0] = FIELD_X;
    game[0].Field[0][1] = FIELD_O;
    game[0].Field[0][2] = FIELD_O;
    game[0].Field[1][1] = FIELD_X;
    game[0].Field[2][2] = FIELD_X;
    game[1].isActive = true;
    game[1].Winner = 0;
    game[1].FirstTour = 1;
    game[1].WhoseTour = 1;
    game[1].CountTour = 3;
    game[1].Player[0].Name = "Petr";
    game[1].Player[0].isHuman = true;
    game[1].Player[0].Figure = FIELD_X;
    game[1].Player[1].Name = "Victor";
    game[1].Player[1].isHuman = true;
    game[1].Player[1].Figure = FIELD_O;
    ClearField(&game[1].Field[0][0]);
    game[1].Field[2][0] = FIELD_O;
    game[1].Field[0][0] = FIELD_X;
    game[1].Field[2][2] = FIELD_O;

    for (int i =0; i<CountGame;i++) {
        cout << "Game #" << (i+1) << endl;
        cout << "Players: ";
        cout << game[i].Player[0].Name << " as ";
        PrintIsHuman(&game[i].Player[0].isHuman);
        cout << "VS ";
        cout << game[i].Player[1].Name << " as ";
        PrintIsHuman(&game[i].Player[1].isHuman);
        cout << endl;
        cout << "Game ";
        if (game[i].isActive == true) {
            cout << "is active." << endl;
            cout << "Tour #" << game[i].CountTour << " play " << game[i].Player[game[i].WhoseTour].Name<< endl;
            
        }
        else 
        {
            cout << "is over." << endl << "Winner:  " << game[i].Player[game[i].Winner].Name;
            cout << " in " << game[i].CountTour << " tours" << endl;
        }
        cout << endl;
        PrintField(&game[i].Field[0][0]);
        cout << endl;
    }
    
    cout << endl;
}

void HomeWork_5() {
    cout << "Home Work #5 **" << endl;  
    //вот, если честно, в голове никак не ложится практическое применение union
    union dynamic
    {
        int vInt;
        float vFloat;
        char vChar;
    };
    
    struct HW
    {
        dynamic vUnion;
        unsigned int isInt:1;
        unsigned int isFloat:1;
        unsigned int isChar:1;
    };
    const int count = 3;
    HW A[count];
    A[0].isChar = 1;
    A[0].isFloat = 0;
    A[0].isInt = 0;
    A[0].vUnion.vChar = 'C';
    A[1].isChar = 0;
    A[1].isFloat = 1;
    A[1].isInt = 0;
    A[1].vUnion.vFloat = 1.115;
    A[2].isChar = 0;
    A[2].isFloat = 0;
    A[2].isInt = 1;
    A[2].vUnion.vInt = 300;
    cout.precision(7);
    for (int i=0;i<count;i++) {
        cout << "# " << i << endl;
        if (A[i].isChar == 1) {
            cout << "Is Char: " << A[i].vUnion.vChar << endl;
        }
        if (A[i].isInt == 1) {
            cout << "Is Int: " << A[i].vUnion.vInt << endl;
        }
        if (A[i].isFloat == 1) {
            cout << "Is Float: " << A[i].vUnion.vFloat << endl;
        }
        cout << "Int: " << A[i].vUnion.vInt << endl;
        cout << "Float: " << A[i].vUnion.vFloat << endl;
        cout << "Char: " << A[i].vUnion.vChar << endl;
    }
    cout << endl;
}
int main() {

    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    HomeWork_4();
    HomeWork_5();
    return 0;
}