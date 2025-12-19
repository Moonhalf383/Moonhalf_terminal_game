#include "../include/term.h"
#include <iostream>
#include <string>

Unit::Unit() {
  textContents = {};
  textOptions = {};
}

void Unit::addContent(std::string content, std::string effect) {
  Message inputMessage(content, effect);
  textContents.push_back(inputMessage);
}

void Unit::addPrinter(std::string content) {
  Message inputMessage(content, "Printer");
  textContents.push_back(inputMessage);
}
void Unit::addFastPrinter(std::string content) {
  Message inputMessage(content, "FastPrinter");
  textContents.push_back(inputMessage);
}

void Unit::addOption(std::string content, std::string effect,
                     std::string index) {
  Option inputOption = Option(content, effect, index);
  textOptions.push_back(inputOption);
}

void Unit::addOption(Option inputOption) { textOptions.push_back(inputOption); }

void Unit::addContent(Message inputMessage) {
  textContents.push_back(inputMessage);
}

void Unit::display() {
  for (auto message : textContents) {
    message.display();
  }
  for (auto option : textOptions) {
    option.display();
  }
}

void SceneUnit::display() {
  Message seperator("------------------------------------", "Highlight");
  seperator.display();
  for (auto it : textContents) {
    it.display();
  }
  std::cout << std::endl;
  for (auto it : textOptions) {
    it.display();
  }
  seperator.display();
}

void ItemUnit::display() {
  Message seperator("------------------------------------", "Confused");
  seperator.display();
  for (auto it : textContents) {
    it.display();
  }
  std::cout << std::endl;
  for (auto it : textOptions) {
    it.display();
  }
  seperator.display();
}
