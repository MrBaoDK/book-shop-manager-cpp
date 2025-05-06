#include <iostream>
#include <limits>
#include <fstream>
#include <sstream> 

#include "common.h"


using namespace std;

int getIntInput( string prompt){
   int value;
   while(true){
      cout << prompt;
      cin >> value;
      if (cin.fail()) {
         cin.clear(); // reset error flag
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         throw Exception("Muc ban nhap khong phai so nguyen.");
      } else {
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         return value;
      }}
}


float getFloatInput( string prompt){
   float value;
   while(true){
      cout << prompt;
      cin >> value;
      if (cin.fail()) {
         cin.clear(); // reset error flag
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         throw Exception("Muc ban nhap vuot muc cho phep.");
      } else {
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         return value;
      }}
}

string getStringInput( string prompt){
   string value;
   cout << prompt;
   getline(cin, value);
   if (value.empty()) {
      throw Exception("Chuoi nhap vao khong duoc rong.");
   }
   return value;
}

string toLowerString(string origin_string){
   string convertedString = "";
   for (int i=0; i<origin_string.length(); i++){
      convertedString += tolower(origin_string[i]);
   }
   return convertedString;
}

void writeFile(string file_name, string content){
   ofstream file(file_name);
   if(!file){
      throw Exception("Khong tao file duoc!");
   }
   file << content;
   file.close();
}

string readFileStream(string file_name){
   ifstream file(file_name);
   if(!file){
      throw Exception("Khong mo file duoc!");
   }

   stringstream buffer;
   buffer << file.rdbuf();
   file.close();
   return buffer.str();
}