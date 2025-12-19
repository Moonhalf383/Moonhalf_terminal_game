#include "../include/basic.h"
#include "../include/items.h"
#include "../include/main.h"
#include "../include/term.h"
#include <cctype>
#include <iostream>
#include <string>
#include <term.h>
#include <vector>

SlugCat::SlugCat(int inputHealth, int inputHunger, int inputKarma,
                 std::string region, std::string inputType)
    : health(inputHealth), hunger(inputHunger), karma(inputKarma),
      currentRegion(region) {
  for (auto it : itemList) {
    backpack[it] = inputType == "System" ? 1 : 0;
  }
  type = inputType;
  distance = 100;
  time = 100;
};

void SlugCat::move() {
  time = 100;
  health = 100;
  distance = 100;
  currentRegion.move();
}

bool SlugCat::isDead() {
  if (health <= 0)
    return true;
  return false;
}

void SlugCat::damage(int damageValue) {
  health -= damageValue;
  if (health < 0)
    health = 0;
}

void SlugCat::gainKarma() {
  if (karma < 5)
    karma += 1;
}

bool SlugCat::sleep() {
  asleep = true;
  return true;
}

bool SlugCat::isExhausted() { return exhausted; }

void SlugCat::setExhausted(bool state) { exhausted = state; }

std::string SlugCat::checkHealth() {
  if (isDead())
    return "die_of_injury";
  if (time <= 0 && distance > 0)
    return "die_of_rain";
  if (asleep && hunger < 4 && !exhausted)
    return "hungry_reached";
  if (asleep &&
      ((hunger >= 4 && !exhausted) || (hunger == maximumHunger && exhausted)))
    return "full_reached";
  return "normal";
}

void SlugCat::showInfo() {
  ItemUnit info = ItemUnit();
  info.addPrinter("Karma: " + std::to_string(karma));
  info.addPrinter("Health: " + std::to_string(health));
  info.addPrinter("Hunger: " + std::to_string(hunger));
  info.addPrinter("Time left: " + std::to_string(time));
  info.addPrinter("Distance left: " + std::to_string(distance));
  info.addContent("Current items", "Highlight");
  for (auto it : itemList) {
    if (backpack[it] != 0)
      info.addFastPrinter("    " + it + " : " + std::to_string(backpack[it]));
  }
  info.display();
}

void SlugCat::generateScene() {
  // int index = randint(0, sceneList.size() - 1);
  // currentScene = sceneRegistry[sceneList[index]];
  if (type == "System")
    currentScene = sceneRegistry["Main Menu"];
  if (type == "Player") {
    if (distance <= 0) {
      currentScene = sceneRegistry["hibernation"];
      return;
    }
    int hostile = randint(1, 100);
    std::string target;
    if (hostile <= currentRegion.getHostileWeight()) {
      target = "hostile";
    } else {
      int move = randint(1, 100);
      if (move <= currentRegion.getMoveWeight()) {
        target = "setback";
      } else
        target = "peace";
    }
    while (true) {
      int index = randint(0, sceneList.size());
      if (sceneRegistry[sceneList[index]].type == target) {
        currentScene = sceneRegistry[sceneList[index]];
        break;
      }
    }
    return;
  }
}

void SlugCat::act() {
  generateScene();
  asleep = false;
  SceneUnit unit = SceneUnit();
  unit.addPrinter("Event: " + currentScene.name);
  unit.addFastPrinter(currentScene.disc);
  unit.addContent(" ", "Normal");
  std::vector<std::string> selectList = {};
  for (auto it : currentScene.options) {
    unit.addOption(optionRegistry[it]);
    selectList.push_back(optionRegistry[it].index);
  }
  unit.addPrinter("Enter your action.");
  int currentDamage = 0;
  while (true) {
    // debug(checkHealth());
    //  debug(health);
    if (checkHealth() == "die_of_injury")
      break;
    unit.display();
    std::string selection = getResponse(selectList);
    if (selection == "ci") {
      checkInfo();
      continue;
    }
    if (selection == "cr") {
      checkRegion("Player");
      continue;
    }
    if (selection == "rg") {
      regionGuide();
    }
    if (selection == "i") {
      itemGuide();
    }
    if (selection == "S") {
      StartGame("Outskirts");
    }
    if (selection == "c") {
      currentDamage += fight(currentScene.danger - currentDamage);
      time -= randint(5, 10);
    }
    if (selection == "r") {
      escape(currentDamage);
      time -= randint(10, 20);
      break;
    }
    if (selection == "g") {
      time -= randint(10, 20);
      break;
    }
    if (selection == "t") {
      take();
      time -= randint(10, 20);
      break;
    }
    if (selection == "n") {
      distance = randint(30, 60);
      time -= randint(10, 20);
      sleep();
      break;
    }
    if (selection == "e") {
      time -= randint(1, 3);
      eat();
      continue;
    }
  }
  int consequence = randint(1, 100);
  if (consequence <= currentScene.danger) {
    SceneUnit hurtUnit = SceneUnit();
    health -= randint(5, 25);
    hurtUnit.addPrinter("Event: You hurt yourself!");
    hurtUnit.addFastPrinter(
        "Status: Injured. You're dinged up, shaky, and seriously reconsidering "
        "your career as a prey animal. Need shelter, or at least a hug.");
    hurtUnit.display();
  }
  distance -= randint(10, 30);
}
