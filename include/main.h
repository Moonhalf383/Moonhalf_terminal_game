#pragma once

#include "items.h"
#include "term.h"
#include <string>
#include <unordered_map>
#include <vector>

struct Scene {
  std::vector<std::string> options;
  std::string type;
  std::string disc;
  int danger;
  std::string name;
};

extern const std::vector<std::string> sceneList;

extern std::unordered_map<std::string, Scene> sceneRegistry;

void registerGlobalScene();

class Region {
public:
  Region(std::string);
  void showInfo(std::string);
  int getMoveWeight();
  int getHostileWeight();
  int getProgress();
  int getShelterNum();
  void move();

private:
  std::string name;
  int hostileWeight;
  int moveWeight;
  int numOfShelter;
  int progress;
  std::string disc;
};

extern const std::vector<std::string> regionList;

class Main {
public:
};

class SlugCat {
public:
  SlugCat(int /*health*/, int /*hunger*/, int /*karma*/, std::string /*region*/,
          std::string /*type*/);
  void damage(int);
  bool isDead();
  bool isSafe();
  void eat();
  void gainHunger(int);
  void move();
  void take();
  std::string checkHealth();
  void showInfo();
  void generateScene();
  void act();
  std::unordered_map<std::string, int> backpack;
  void checkInfo();
  void checkRegion(std::string);
  void regionGuide();
  void itemGuide();
  std::string getType();
  void StartGame(std::string);
  void gainKarma();
  bool sleep();
  bool isExhausted();
  void setExhausted(bool);
  int fight(int);
  void escape(int);
  void clearBackpack();

private:
  bool exhausted;
  std::string type;
  Region currentRegion;
  int health;
  Scene currentScene;
  int hunger;
  int maximumHunger = 7;
  int karma;
  int distance;
  int time;
  std::string nextScene = "Null";
  bool asleep;
};
