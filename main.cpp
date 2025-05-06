#include <iostream>

#include "src/menu.h"
#include "src/bookshop.h"

using namespace std;
// dung cho helloworld

int main(){
   BookShop bookShop = BookShop();
   Menu mainMenu = {"MENU QUAN LY NHA SACH"
      , { MenuItem(1, "Danh sach Sach trong cua hang", [&]() { bookShop.showAllBooks(); })
         ,MenuItem(2, "Them sach", [&]() { bookShop.addBook(); })
         ,MenuItem(3, "Tim kiem sach", [&]() { bookShop.searchBook(); })
         ,MenuItem(4, "Sap xep sach", [&]() { bookShop.sortAllBooks(); })
         ,MenuItem(5, "Loai bo sach", [&]() { bookShop.removeBook(); })
         ,MenuItem(6, "Ghi du lieu cua hang vao file", [&]() { bookShop.saveData(); }) 
         ,MenuItem(7, "Nhap du lieu cua hang tu file", [&]() { bookShop.loadData(); }) } };

   mainMenu.run();
   
   return 0;

}