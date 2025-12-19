#pragma once

#include "items.h"
#include <string>
#include <unordered_map>
#include <vector>

class Message {
public:
  Message(std::string, std::string);
  virtual void display();

private:
  std::string content;
  std::string effect;
  std::vector<int> args;
};

class Option {
public:
  Option();
  Option(std::string, std::string, std::string);
  void display();
  std::string index;
  Message content;
  std::string command;
};

extern std::vector<std::string> optionList;

extern std::unordered_map<std::string, Option> optionRegistry;

void registerGlobalOption();

class Command {};

class Unit {
public:
  std::vector<Message> textContents;
  std::vector<Option> textOptions;
  Unit();
  void addContent(std::string, std::string);
  void addContent(Message);
  void addPrinter(std::string);
  void addFastPrinter(std::string);
  void addOption(std::string, std::string, std::string);
  void addOption(Option);
  virtual void display();
  void play();
};

class SceneUnit : public Unit {
public:
  void display() override;
};

class ItemUnit : public Unit {
public:
  void display() override;
};
