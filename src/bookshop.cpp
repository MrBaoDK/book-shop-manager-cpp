#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "bookshop.h"

using namespace std;

// internal data file name
string DATA_FILE_NAME = "bookshop.csv";
// internal data header names
string DATA_HEADERS = "id,title,author,quantity,price,sold";

BookShop::BookShop(): head(nullptr), tail(nullptr), count(0) {}

int BookShop::getNextId(int default_id){
   if (head == nullptr){
      // tra ve mac dinh neu chua co
      return default_id;
   }

   // khoi tao id ban dau
   int maxId = head->id;
   Book * current = head->next;

   while (current != nullptr) {
      if (current->id > maxId) {
         maxId = current->id;
      }
      current = current->next;
   }

   return maxId + 1;
}

void BookShop::insertBook(Book* new_book){

   if (head == nullptr){
      head = tail = new_book;
   } else {
      tail->next = new_book;
      new_book->prev = tail;
      tail = new_book;
   }
   
   count++;
}

Book* BookShop::getBook(int book_id){
   
   if (head == nullptr){
      throw Exception("Khong co quyen sach nao.");
   }
   Book * current = head;
   while (current != nullptr){
      if (current->id == book_id){
         return current;
      }
      current = current->next;
   }
   throw Exception("Khong tim thay sach voi id=" + to_string(book_id) + "!" );
}

void BookShop::deleteBook(int book_id){
   Book * book = getBook(book_id);

   if (book==head){
      head = book->next;
      if (head != nullptr){
         head->prev = nullptr;
      }
   } else {
      book->prev->next = book->next;
   }
   if (book==tail){
      tail = book->prev;
      if (tail != nullptr){
         tail->next = nullptr;
      }
   } else {
      book->next->prev = book->prev;
   }

   delete book;
   count--;
}

void BookShop::removeBook(){
   int bookId = getIntInput("Nhap ma sach can xoa: ");
   deleteBook(bookId);
   cout << "[o] Da xoa sach voi id=" + to_string(bookId) << endl;
}


void BookShop::addBook() {
   string title = getStringInput("Nhap ten sach: ");
   string author = getStringInput("Nhap ten tac gia: ");
   float priceInVnd = getFloatInput("Nhap gia ban (VND): ");
   int qty = getIntInput("Nhap so luong: ");
   Book *newBook = new Book(getNextId(101), title, author, qty, priceInVnd);
   insertBook(newBook);
   cout << "[o] Da them sach " + title << endl;
}

void BookShop::showAllBooks() const {
   if (head == nullptr){
      throw Exception( "Khong co quyen sach nao.");
   }

   cout << "[=] Danh sach nhung Sach trong cua hang" << endl;
   cout << left << setw(10) << "Ma sach"
      << left << setw(50) << "Ten sach" 
      << left << setw(20) << "Tac gia" 
      << left << setw(10) << "Gia ban"
      << right << setw(9) << "So luong" << endl;

   cout << setfill('-') << setw(99) << "" << setfill(' ') << endl;
   
   Book* current = head;
   while (current != nullptr){
      cout << left << setw(10) << current->id
         << left << setw(50) << current->title
         << left << setw(20) << current->author
         << right << setw(10) << fixed << setprecision(2) << current->price
         << right << setw(8) << current->quantity << endl;
      current = current->next;
   }
   cout << setfill('-') << setw(99) << "" << setfill(' ') << endl << endl;
}



void BookShop::saveData(){
   string content = DATA_HEADERS + "\n";
   Book* current = head;
   while (current != nullptr) {
      content += to_string(current->id) + ","
               + current->title + ","
               + current->author + ","
               + to_string(current->quantity) + ","
               + to_string(current->price) + ","
               + to_string(current->sold ? 1 : 0) + "\n";
      current = current->next;
   }

   writeFile(DATA_FILE_NAME, content);
   cout << "[o] Luu du lieu thanh cong!" << endl;
}

void BookShop::loadData(){
   string data = readFileStream(DATA_FILE_NAME);
   istringstream ss(data);
   string line;
   int currentCount = count;
   int lineCount = -1;
   while(getline(ss, line)){
      lineCount++;
      istringstream lineStream(line);
      string token;
      vector<string> fields;

      while(getline(lineStream, token, ',')){
         fields.push_back(token);
      }

      if(fields.size()<6) continue;
      if (lineCount == 0) {
         continue;
      }

      Book* book = new Book(stoi(fields[0])
                           , fields[1]
                           , fields[2]
                           , stoi(fields[3])
                           , stof(fields[4])
                           , fields[5] == "1");
      insertBook(book);
   }

   cout << "Da nhap vao " + to_string(count-currentCount) + " quyen sach!";
}

Book* BookShop::searchBookByField(string search_term, string field_name){
   if (head==nullptr){
      throw Exception("Khong co Sach de tim");
   }

   field_name = toLowerString(field_name);
   cout << "Dang tim kiem sach theo truong \"" + field_name + "\"..." << endl;
   if (field_name == "id" || field_name == "ma sach"){
      return getBook(stoi(search_term));
   }
   Book * current = head;
   while (current!= nullptr){
      bool isCatch = false;
      if (field_name == "ten sach") {
         isCatch = current->title == search_term;
      } else if (field_name == "tac gia") {
         isCatch = current->author == search_term;
      } else if (field_name == "gia ban") {
         isCatch = current->price == stof(search_term);
      } else if (field_name == "so luong") {
         isCatch = current->quantity > stoi(search_term);
      } else {
         throw Exception("Ten cot khong hop le");
      }
      if(isCatch){
         return current;
      }
   }
   throw Exception("Khong tim thay quyen sach voi tu khoa nay!");
}

void BookShop::searchBook(){
   string fieldName = getStringInput("Nhap ten cot de tim kiem (ma sach/ten sach/tac gia): ");
   string searchTerm = getStringInput("Nhap tu khoa tim kiem theo cot \"" + fieldName + "\": ");
   Book* book = searchBookByField(searchTerm, fieldName);
   book->show();
}

void BookShop::sortBooksByField(string field_name){
   if (head==nullptr || head->next == nullptr){
      throw Exception("Khong co Sach hoac co 1 Sach. Khong can sap xep");
   }
   field_name = toLowerString(field_name);
   bool swapped;
   do {
      swapped = false;
      Book * current = head;
      while (current->next != nullptr){
         bool needSwap = false;
         Book * nextBook = current->next;
         if (field_name == "ma sach"){
            needSwap = current->id > nextBook->id;
         } else if (field_name == "ten sach") {
            needSwap = current->title > nextBook->title;
         } else if (field_name == "tac gia") {
            needSwap = current->author > nextBook->author;
         } else if (field_name == "gia ban") {
            needSwap = current->price > nextBook->price;
         } else if (field_name == "so luong") {
            needSwap = current->quantity > nextBook->quantity;
         } else {
            throw Exception("Ten cot khong hop le");
         }
         if (needSwap){
            swap(current->id, nextBook->id);
            swap(current->title, nextBook->title);
            swap(current->author, nextBook->author);
            swap(current->price, nextBook->price);
            swap(current->quantity, nextBook->quantity);
            swap(current->sold, nextBook->sold);
            swapped = true;
         }
         current = current->next;
      }
   } while (swapped);
}

void BookShop::sortAllBooks(){
   string fieldName = getStringInput("Nhap ten cot de sap xep (ma sach/ten sach/tac gia/so luong/gia ban): ");
   sortBooksByField(fieldName);
   showAllBooks();
}

BookShop::~BookShop(){
   Book* current = head;
   while (current != nullptr){
      Book* temp = current;
      current = current->next;
      delete temp;
   }
}