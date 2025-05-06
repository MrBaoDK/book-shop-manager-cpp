#pragma once
#include <string>
#include <exception>

typedef struct {
   int day;
   int month;
   int year;
} Date;


typedef struct Exception: public std::exception {
   std::string message;
   Exception(const std::string& msg): message(msg) {};
   const char* what() const noexcept override {
      return message.c_str();
   }
} Exception ;

/* Nhan so nguyen nhap tu ban phim 
   @param prompt: Cau lenh cho user
*/ 
int getIntInput(std::string prompt);
/* Nhan so thuc nhap tu ban phim
   @param prompt: Cau lenh cho user
*/
float getFloatInput(std::string prompt);
/* Nhan chuoi nhap tu ban phim
   @param prompt: Cau lenh cho user
*/
std::string getStringInput(std::string prompt);
/*  Doi chuoi sang chu thuong
   @param origin_string: chuoi goc
*/
std::string toLowerString(std::string origin_string);
/* save file
   @param file_name: ten file
   @param content: noi dung file
*/
void writeFile(std::string file_name, std::string content);
/* doc file
   @param file_name: ten file
*/
std::string readFileStream(std::string file_name);
