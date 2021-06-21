#include <iostream>

using namespace std;

void HomeWork_1() {
    cout << "Home Work #1 " << endl;
    int Num1;
    int Num2;
    cout << "Input number #1: ";
    cin >> Num1;
    cout << "Input number #2: ";
    cin >> Num2;
    if ( (Num1 + Num2) >= 10 && (Num1 + Num2) <= 20) {
        cout << "True";
    }
    else {
        cout << "False";
    }
    cout << endl << endl;
}

void HomeWork_2() {
    cout << "Home Work #2 " << endl;
    const int C1 = 10;
    const int C2 = 0;
    if ( ((C1 == 10) && (C2 == 10)) || ((C1 + C2) == 10)) {
        cout << "True";
    }
    else {
        cout << "False";
    }
    cout << endl << endl;
}

void HomeWork_3() {
    cout << "Home Work #3 " << endl;
    const int Begin = 1;
    const int Final = 50;
    const int Сhet = 0; //1 для четных, 0 для нечетных
    int TBegin = Begin;
    if (Begin%2 == Сhet) {
        TBegin = Begin+1;
    }
    for (int i = TBegin; i<=Final; i=i+2) {
        cout << i << " ";
    }
    cout << endl << endl;
}

void HomeWork_4() {
    cout << "Home Work #4 *" << endl;
    int Number = - 5;
    bool isPrime = true;

    for (int i = 2; i<=(sqrt(Number)); i++) {
        if (Number%i == 0) {
            isPrime = false;
        }
    }
    cout << "Number " << Number << ((isPrime)? " " : " not ") << "a prime." << endl << endl;
}

void HomeWork_5() {
    cout << "Home Work #5 *" << endl;
    int Year;
    bool isLeap = false;
    do {
        cout << "Input a year (1-3000): ";
        cin >> Year;
    } while (!(Year >= 1 && Year <= 3000));
    if ( Year%4 == 0 && (!(Year%100 == 0) || Year%400 == 0) ) {
        isLeap = true;
    }
    cout << "Year " << Year << " is" << ((isLeap) ? " " : " not ") << "leap year." << endl;
}

int main() {

    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    HomeWork_4();
    HomeWork_5();

    return 0;
}