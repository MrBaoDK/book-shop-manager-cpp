#pragma once

#include "common.h"
// #include "client.h"

// tao cau truc node cho Sach
typedef struct Book {
   int id;
   std::string title;
   std::string author;
   int quantity;
   float price;
   bool sold;
   Book* next;
   Book* prev;
   // Khoi tao bien cho Sach
   Book(int id, std::string title, std::string author, int qty, float price_in_vnd, bool sold=false);
   void show();
} Book;

typedef struct BookShop {
   Book* head;
   Book* tail;
   int count;
   // Tao bien cho cua hang
   BookShop();
   // Giai phong bo nho cho bien luu du lieu cua hang
   ~BookShop();
   /* Lay ma sach tiep theo: tim ma sach lon nhat roi +1
      @param default_id: ma sach mac dinh neu cua hang chua co sach
   */
   int getNextId(int default_id);
   /* Them sach vao cua hang
      @param new_book: object sach
   */
   void insertBook(Book* new_book);
   // In ra tat ca sach trong cua hang
   void showAllBooks() const;
   //Nhap sach thu cong vao cua hang
   void addBook();
   /* Tim node Sach
      @param book_id: ma sach can tim
   */
   Book* getBook(int book_id);
   /* Xoa sach ra khoi cua hang
      @param book_id: ma sach can xoa
   */
   void deleteBook(int book_id);
   // Nhap id để xóa sách
   void removeBook();
   /* Sap xep cac Sach bang 1 ten truong
      @param field_name: ten truong can sap xep
   */
  void sortBooksByField(std::string field_name="id");
  // Nhap ten truong de sort
  void sortAllBooks();
   /*Tim Sach bang ten truong
      @param field_name: ten truong can tim
   */
  Book* searchBookByField(std::string search_term, std::string field_name="id");
  // Nhap ten truong de tim
  void searchBook();
  // Luu du lieu vao file
  void saveData();
  // Tu dong nhap du lieu tu file
  void loadData();
} BookShop;
