#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Item {
public:
  Item(std::string);
  Item();
  void showInfo();
  std::string name = "";
  std::string disc = "";
  int hunger = 0;
  int damage = 0;
  bool isFood();
  bool isWeapon();
};

extern const std::vector<std::string> itemList;

extern std::unordered_map<std::string, Item> itemRegistry;

void registerGlobalItem();
