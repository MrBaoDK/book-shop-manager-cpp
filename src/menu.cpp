#include <iostream>

#include "menu.h"

using namespace std;

void Menu::changeName(string new_name){
   name = new_name;
}

void Menu::display(){
   cout << "\n---    " << name << "    ---" << endl;
   cout << "===================================" << endl;
   for (const auto& item: items){
      cout << item.optionNumber << ". " << item.description << endl;
   }
   cout << "0. Thoat" << endl;
   cout << "===================================" << endl;
}

int getChoice(){
   int choice = getIntInput("Hay nhap lua chon cua ban: ");
   return choice;
}

void Menu::addItem(MenuItem new_item){
   items.emplace_back(new_item);
}

MenuItem Menu::getItem(int option_number){
   for (const auto& item: items){
      if (item.optionNumber == option_number) {
         return item;
      }
   }
   throw Exception("Khong tim thay muc nay!");
}

void Menu::run(){
   int choice;
   cout << "=== HE THONG QUAN LY CUA HANG SACH ===" << endl;
   do
   {
      // printMenu(menu);
      display();
      choice = getChoice();
      try {
         MenuItem chosenItem = getItem(choice);
         cout << "[-] Muc da chon : " << choice << ". " << chosenItem.description << " !" << endl;
         chosenItem.action();
      } catch (const Exception& exp) {
         cout << "[!] " << exp.what() << endl;
         cout << "[!] Lua chon khong hop le. Hay nhap lai." << endl;
      }
   } while (choice != 0);
   
}

MenuItem::MenuItem(int option_number, string description, function<void()> act):
   optionNumber(option_number), description(description), action(act) {};