
#include <iostream>

#include "bookshop.h"

using namespace std;

Book::Book(int id, string title, string author, int qty, float price_in_vnd, bool sold)
: id(id), title(title), author(author), quantity(qty), price(price_in_vnd), sold(sold), next(nullptr), prev(nullptr) {}

void Book::show(){
   
   cout << "\n[=] Thong tin sach :\n";
   cout << "-----------------------------\n";
   cout << "  Ma sach: " << id << "\n"
      << "  Tieu de: " << title << "\n"
      << "  Tac gia: " << author << "\n"
      << "  So luong: " << quantity << "\n"
      << "  Gia ban: " << price << "\n";
   cout << "-----------------------------\n";
}