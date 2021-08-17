#include <iostream>
#include "book.hpp"


using namespace std;

void HomeWork_1()
{
    cout << "Home Work #1" << endl;
    Person P1, P2;
    P1.name = "Джон";
    P1.surname = "Смит";
    P2.name = "Иван";
    P2.surname = "Иванов";
    P2.patronymic = "Иванович";
    cout << P1 << endl << P2 << endl << endl;
}

void HomeWork_2()
{
    cout << "Home Work #2" << endl;
    PhoneNumber N1, N2;
    N1.city = 372;
    N1.country = 1;
    N1.number = "11-22-333";
    N2.city = 495;
    N2.country = 7;
    N2.number = "85-23-245";
    cout << N1 << endl << N2 << endl << endl;
}

void HomeWork_3()
{
    cout << "Home Work #3" << endl;
    ifstream file("PhoneBook.txt");
    PhoneBook book(file);
    cout << "-----PrintAllPhone------" << endl;
   	cout << book;
 
   	cout << "------SortByPhone-------" << endl;
   	book.SortByPhone();
   	cout << book;
 
   	cout << "------SortByName--------" << endl;
   	book.SortByName();
   	cout << book;
 
   	cout << "-----GetPhoneNumber-----" << endl;
   	// лямбда функция, которая принимает фамилию и выводит номер телефона этого    	человека, либо строку с ошибкой
   	auto print_phone_number = [&book](const string& surname) { 
   	   	cout << surname << "\t"; 
   	   	auto answer = book.GetPhoneNumber(surname); 
   	   	if (get<0>(answer).empty()) 
   	   	   	cout << get<1>(answer); 
   	   	else 
   	   	   	cout << get<0>(answer); 
   	   	   	cout << endl; 
    };

   	// вызовы лямбды
   	print_phone_number("Герасимов");
   	print_phone_number("Голованов");
    print_phone_number("Иванов");
 
   	cout << "----ChangePhoneNumber----" << endl;
   	book.ChangePhoneNumber(Person{ "Никитин", "Богдан", "Анатольевич" }, PhoneNumber{7, 123, "15344458", nullopt});
   	book.ChangePhoneNumber(Person{ "Свиридов", "Иван", "Витальевич" }, PhoneNumber{ 16, 465, "9155448", 13 });
   	cout << book;

    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    HomeWork_1();
    HomeWork_2();
    HomeWork_3();
    return 0;
}