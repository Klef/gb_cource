#include <iostream>

using namespace std;

void HomeWork_14() {
    cout << "Home Work #4 **" << endl; 
    
    extern int a;
    extern int b;
    extern int c;
    extern int d;

    float result = a * (b + (float(c) / d));

    cout <<"a*(b+(c/d)="<< result << endl << endl;
}

void HomeWork_2() {
    cout << "Home Work #2" << endl;
    const int c = 21;
    int a = 15;
    int r = (a <= c) ? c - a :  (a - c) * 2;
    cout << "a = " << a << " result: " << r << endl;
    a = 40;
    r = (a <= c) ? c - a :  (a - c) * 2;
    cout << "a = " << a << " result: " << r << endl << endl;
}

void HomeWork_3() {
    cout << "Home Work #3 *" << endl;
    int array[3][3][3] = {
        {{1,2,3},{4,5,6},{7,8,9}},
        {{10,11,12},{13,14,15},{16,17,18}},
        {{19,20,21},{22,23,24},{25,26,27}}
    };
    int *pArr = &array[1][1][1];
    cout << "Midle in kube: " << *pArr << endl << endl;

}

int main() {
    cout << "Home work #1 in #4" << endl << endl;
    HomeWork_2();
    HomeWork_3();
    HomeWork_14();

    return 0;
}