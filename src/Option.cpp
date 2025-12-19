#include "../include/term.h"
#include <string>

#include <iostream>
#include <vector>

void Option::display() {
  std::cout << "[" << index << "]";
  content.display();
}

Option::Option() : content("None", "Normal"), index("N") {}

Option::Option(std::string messageContent, std::string messageEffect,
               std::string inputIndex)
    : content(messageContent, messageEffect), index(inputIndex) {}

std::unordered_map<std::string, Option> optionRegistry;

std::vector<std::string> optionList;

void oprgHelper(std::string target, std::string inputIndex,
                std::string inputContent) {
  optionRegistry[target].index = inputIndex;
  optionRegistry[target].content = Message(inputContent, "Printer");
  optionRegistry[target].command = target;
  optionList.push_back(target);
}

void registerGlobalOption() {
  optionList = {};
  oprgHelper("goAhead", "g", "Go ahead!");
  oprgHelper("combat", "c", "Fight!!!");
  oprgHelper("escape", "r", "Try to ESCAPE!!");
  oprgHelper("eat", "e", "I eat.");
  oprgHelper("checkInfo", "ci", "Check my condition.");
  oprgHelper("checkRegion", "cr", "Check current region.");
  oprgHelper("start", "S", "START YOUR JOURNEY!");
  oprgHelper("savings", "ss", "Checkout your savings.");
  oprgHelper("items", "i", "Items guide");
  oprgHelper("regions", "rg", "Regions guide");
  oprgHelper("take", "t", "Take some.");
  oprgHelper("nextCycle", "n", "Next Cycle.");
}
