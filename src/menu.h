#pragma once
#include <vector>
#include <functional>
#include "common.h"

typedef struct MenuItem{
   int optionNumber;
   std::string description;
   std::function<void()> action;
   MenuItem(int option_number, std::string description, std::function<void()> act);
} MenuItem;

typedef struct {
   std::string name;
   std::vector<MenuItem> items;
   void display();
   void run();
   void addItem(MenuItem new_item);
   MenuItem getItem(int option_number);
   void changeName(std::string new_name);
} Menu;
