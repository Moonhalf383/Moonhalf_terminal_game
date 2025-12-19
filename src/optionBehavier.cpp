#include "../include/basic.h"
#include "../include/items.h"
#include "../include/main.h"
#include "../include/term.h"
#include <cctype>
#include <iostream>
#include <string>
#include <term.h>
#include <utility>
#include <vector>

std::string getResponse(std::vector<std::string> &options) {
  std::cout << ">>> ";
  std::string input;
  std::cin >> input;
  bool state = false;
  while (true) {
    for (auto it : options) {
      if (it == input) {
        state = true;
      }
    }
    if (state)
      break;
    std::cout << "Invalid input!" << std::endl;
    std::cout << ">>> ";
    std::cin >> input;
  }
  if (isdigit(input[0]))
    return std::string(1, input[0]);
  // debug(std::string(1,'0'));
  return input;
}

void SlugCat::clearBackpack() {
  for (auto it : itemList) {
    backpack[it] = 0;
  }
}

void SlugCat::checkInfo() {
  showInfo();
  SceneUnit unit = SceneUnit();
  int i = 0;
  std::vector<std::string> itemToCheck = {};
  std::vector<std::string> toCheckIndeices = {};
  for (auto it : itemList) {
    if (backpack[it] > 0) {
      unit.addOption("Check " + it, "Printer", std::to_string(i));
      itemToCheck.push_back(it);
      toCheckIndeices.push_back(std::to_string(i));
      i++;
    }
  }
  if (itemToCheck.empty()) {
    return;
  }
  unit.addOption("Back", "Printer", "b");
  toCheckIndeices.push_back("b");
  unit.addPrinter("Enter your action.");
  unit.display();
  std::string selection = getResponse(toCheckIndeices);
  if (selection == "b")
    return;
  itemRegistry[itemToCheck[std::stoi(selection)]].showInfo();
  checkInfo();
}

void SlugCat::checkRegion(std::string mode) {
  currentRegion.showInfo(mode);
  return;
}

void SlugCat::regionGuide() {
  if (type != "System")
    return;
  SceneUnit regionUnit = SceneUnit();
  regionUnit.addPrinter("Regions:");
  regionUnit.addFastPrinter(
      R"(Distinct zones within the iterator's superstructure, each with unique terrain, hazards, and ecosystems. Survival requires learning their layouts, resources, and the threats that call them home. Progress is measured by the gates you unlock between them.)");
  regionUnit.addContent(" ", "Normal");
  std::vector<std::string> toCheckIndeices = {};
  int index = 0;
  for (auto it : regionList) {
    regionUnit.addOption(it, "Printer", std::to_string(index));
    toCheckIndeices.push_back(std::to_string(index));
    index++;
  }
  regionUnit.addOption("Back", "Printer", "b");
  toCheckIndeices.push_back("b");
  regionUnit.addPrinter("Enter your action.");
  regionUnit.display();
  std::string selection = getResponse(toCheckIndeices);
  if (selection == "b")
    return;
  currentRegion = regionList[std::stoi(selection)];
  checkRegion("System");
  regionGuide();
}

int SlugCat::fight(int threat) {
  bool haveWeapon = false;
  std::vector<std::string> weapons = {};
  std::vector<std::string> toCheckIndeices = {};
  for (auto it : itemList) {
    if (backpack[it] > 0 && itemRegistry[it].isWeapon()) {
      haveWeapon = true;
      weapons.push_back(it);
    }
  }
  SceneUnit fightUnit = SceneUnit();
  if (!haveWeapon) {
    fightUnit.addPrinter("You have NO weapon!");
    fightUnit.display();
    return 0;
  }
  fightUnit.addPrinter("Fortunately, you have weapon!");
  fightUnit.addContent("", "Normal");
  int index = 0;
  for (auto it : weapons) {
    fightUnit.addOption(it, "Printer", std::to_string(index));
    toCheckIndeices.push_back(std::to_string(index));
    index++;
  }
  fightUnit.addPrinter("Enter your choice.");
  fightUnit.display();
  std::string selection = getResponse(toCheckIndeices);
  int damage = itemRegistry[weapons[std::stoi(selection)]].damage;
  backpack[weapons[std::stoi(selection)]]--;
  int chance = threat - damage;
  if (chance < 0)
    chance = 0;
  int consequence = randint(1, 100);
  if (consequence > threat) {
    SceneUnit winUnit = SceneUnit();
    winUnit.addPrinter("Event: You hit it!");
    winUnit.addFastPrinter(
        R"(Solid hit. Whatever you threw made a deeply satisfying thunk against its scales. It's stunned, angry, and probably wants revenge. Run now.)");
    winUnit.display();
    return damage;
  } else {
    SceneUnit failUnit = SceneUnit();
    failUnit.addPrinter("Event: You failed.");
    failUnit.addFastPrinter(
        R"(Sloppy toss. You hit nothing but air, and now you’ve revealed your position and expended your only throwable item. The creature's smile just got wider)");
    failUnit.display();
    health = 0;
    return 0;
  }
}

void SlugCat::escape(int currentDamage) {
  int consequence = randint(1, 100);
  // debug(consequence);
  if (consequence > currentScene.danger - currentDamage) {
    SceneUnit winUnit = SceneUnit();
    winUnit.addPrinter("Event: Successful escape.");
    winUnit.addFastPrinter(
        R"(A dive, a desperate scramble, and a platform collapse that accidentally saved your life. That wasn't skill; that was pure, dumb, survival luck. Check your pants.)");
    winUnit.display();
    return;
  }
  health = 0;
  SceneUnit failUnit = SceneUnit();
  failUnit.addPrinter("Event: You failed.");
  failUnit.addFastPrinter(
      R"(The chase is over. You are now merely a statistic, a protein snack that briefly interrupted the ecosystem's nap. Try again, little morsel.)");
  failUnit.display();
  return;
}

void SlugCat::gainHunger(int value) {
  hunger += value;
  if (hunger > maximumHunger)
    hunger = maximumHunger;
}

void SlugCat::eat() {
  bool haveFood = false;
  std::vector<std::string> foods = {};
  std::vector<std::string> toCheckIndeices = {};
  for (auto it : itemList) {
    if (backpack[it] > 0 && itemRegistry[it].isFood()) {
      haveFood = true;
      foods.push_back(it);
    }
  }
  SceneUnit foodUnit = SceneUnit();
  if (!haveFood) {
    foodUnit.addPrinter("You have NO food!");
    foodUnit.display();
    return;
  }
  foodUnit.addPrinter("You have food!");
  foodUnit.addContent("", "Normal");
  int index = 0;
  for (auto it : foods) {
    foodUnit.addOption(it, "Printer", std::to_string(index));
    toCheckIndeices.push_back(std::to_string(index));
    index++;
  }
  foodUnit.addPrinter("Enter your choice.");
  foodUnit.display();
  std::string selection = getResponse(toCheckIndeices);
  backpack[foods[std::stoi(selection)]]--;
  gainHunger(itemRegistry[foods[std::stoi(selection)]].hunger);
}

void SlugCat::itemGuide() {
  if (type != "System")
    return;
  SceneUnit unit = SceneUnit();
  unit.addPrinter("Items:");
  unit.addFastPrinter(
      R"(Objects found, carried, and used for survival. Your ability to identify and utilize them defines your path through the ruins.)");
  unit.addContent(" ", "Normal");
  int i = 0;
  std::vector<std::string> itemToCheck = {};
  std::vector<std::string> toCheckIndeices = {};
  for (auto it : itemList) {
    if (backpack[it] > 0) {
      unit.addOption("Check " + it, "Printer", std::to_string(i));
      itemToCheck.push_back(it);
      toCheckIndeices.push_back(std::to_string(i));
      i++;
    }
  }
  unit.addOption("Back", "Printer", "b");
  toCheckIndeices.push_back("b");
  unit.addPrinter("Enter your action.");
  unit.display();
  std::string selection = getResponse(toCheckIndeices);
  if (selection == "b")
    return;
  itemRegistry[itemToCheck[std::stoi(selection)]].showInfo();
  itemGuide();
}

void SlugCat::take() {
  SceneUnit takeUnit = SceneUnit();
  if (currentScene.name == "batfly") {
    backpack["Batfly"] += randint(1, 3);
    takeUnit.addPrinter("Event: You caught some batflies.");
    takeUnit.addFastPrinter(
        R"(Score! The Batfly, in its infinite foolishness, mistook your outstretched paw for a nice place to land. A momentary energy boost has been secured.)");
    takeUnit.display();
  } else if (currentScene.name == "rock") {
    backpack["Rock"] += 1;
    takeUnit.addPrinter("Event: You picked a rock.");
    takeUnit.addFastPrinter(
        R"(Inventory updated. New item: Stone. Description: Not a spear. Highly disappointing, but useful for throwing anyway)");
    takeUnit.display();
  } else if (currentScene.name == "bluefruit") {
    backpack["BlueFruit"] += randint(1, 3);
    takeUnit.addPrinter("Event: You picked some bluefruits.");
    takeUnit.addFastPrinter(
        R"(Found a Blue Fruit. It's the universe's way of apologizing for everything else. Slightly more nutritious than the Batfly, and won't fly away. Consume immediately)");
    takeUnit.display();
  } else if (currentScene.name == "spear") {
    backpack["Spear"] += 1;
    takeUnit.addPrinter("Event: You took a spear.");
    takeUnit.addFastPrinter(
        R"(You've acquired a Spear. It's sharp, pointy, and exponentially increases your chance of not being immediately eaten. Suddenly, you are slightly less pathetic.)");
    takeUnit.display();
  }
}

void SlugCat::StartGame(std::string region) {
  SlugCat player = SlugCat(100, 1, 1, region, "Player");
  player.setExhausted(false);
  int currentProgress = player.currentRegion.getProgress();
  int recordedHunger = player.hunger;
  while (true) {
    player.act();
    if (player.checkHealth() == "normal") {
      continue;
    } else if (player.checkHealth() == "hungry_reached") {
      player.setExhausted(true);
      SceneUnit sleepUnit = SceneUnit();
      sleepUnit.addPrinter("Event: You have a bad sleep.");
      sleepUnit.addContent("", "Normal");
      sleepUnit.addPrinter(
          R"(You are still hungry. The shelter door closes, forcing your body into a shallow, uneasy hibernation. The system registers a failed cycle. You will awaken in the same shelter, your Karma weakened. The path forward has not advanced.)");
      sleepUnit.addContent("", "Normal");
      if (player.currentRegion.getProgress() >
          player.currentRegion.getShelterNum())
        sleepUnit.addPrinter(
            R"(You reached the karma gate, but it's blocked. The ancient mechanism acknowledges your existence but denies passage. It seems your life hasn't been miserable enough yet. Back to the grind.)");
      sleepUnit.display();
      player.checkInfo();
      player.move();
      player.hunger -= 4;
      if (player.hunger < 0)
        player.hunger = 0;
      player.health -= 30;
      continue;
    } else if (player.checkHealth() == "full_reached") {
      currentProgress = player.currentRegion.getProgress();
      recordedHunger = player.hunger;
      player.move();
      player.gainKarma();
      player.setExhausted(false);
      player.hunger -= 4;
      if (player.hunger < 0)
        player.hunger = 0;
      if (player.currentRegion.getProgress() >
          player.currentRegion.getShelterNum()) {
        if (karma >= randint(1, 5)) {
          SceneUnit passUnit = SceneUnit();
          passUnit.addPrinter("Event: You passed the region " + region + "!");
          std::string nextRegion =
              regionList[randint(0, regionList.size() - 1)];
          passUnit.addContent("", "Normal");
          passUnit.addFastPrinter(
              R"(The gate groans, acknowledges your improbable survival streak, and reluctantly opens. You are briefly worthy. Welcome to a whole new area of spectacular ways to die. Proceed.)");
          passUnit.addContent("", "Normal");
          passUnit.addPrinter("The next region is ...");
          sleepFor(1);
          passUnit.addContent("", "Normal");
          passUnit.addContent(nextRegion, "SlowPrinter");
          passUnit.addContent("", "Normal");
          passUnit.display();
          StartGame(nextRegion);
          return;
        }
        SceneUnit blockUnit = SceneUnit();
        blockUnit.addPrinter("Event: Karma not yet satisfied.");
        blockUnit.addFastPrinter(
            R"(The Karma Gate looms. It judges your worth, finds you lacking, and sighs dismissively. You are not spiritually ready for the next room. Go do some good deeds (i.e., survive more).)");
        blockUnit.display();
      }
      SceneUnit sleepUnit = SceneUnit();
      sleepUnit.addPrinter("You have a nice sleep!");
      sleepUnit.addContent("", "Normal");
      sleepUnit.addPrinter(
          R"(Your hunger is fully sated. As you enter the shelter and the door seals, your body enters deep hibernation. The system registers your successful survival. Your Karma remains intact, and the path forward is strengthened.)");
      sleepUnit.display();
      player.move();
      player.checkInfo();
      continue;
    } else if (player.checkHealth() == "die_of_rain") {
      SceneUnit dieRainUnit = SceneUnit();
      dieRainUnit.addPrinter("Cause of Death: RAIN.");
      dieRainUnit.addFastPrinter(
          R"(You were caught in the open when the full force of the Rain descended. Its colossal, pressurized droplets are not water—they are liquid concrete, a devastating deluge that pulverizes structures and flesh alike. No creature, not even the hardiest predator, can withstand its cleansing fury.)");
      dieRainUnit.addContent("", "Normal");
      dieRainUnit.addFastPrinter(
          R"(Your consciousness fades in the roar, only to painfully stitch itself back together within the safety of your last visited Shelter. The ordeal has scarred your spirit, reducing your Karma level by one. The world is now slightly more hostile, and the path forward, more demanding.)");
      dieRainUnit.display();
      player.health = 100;
      player.time = 100;
      player.distance = 100;
      player.hunger = recordedHunger;
      player.clearBackpack();
      player.checkInfo();
      continue;
    } else if (player.checkHealth() == "die_of_injury") {
      SceneUnit dieInjuryUnit = SceneUnit();
      dieInjuryUnit.addPrinter("Cause of Death: DANGER.");
      dieInjuryUnit.addFastPrinter(
          R"(Your journey was cut short by the unforgiving laws of this world—be it the jaws and claws of a Creature, or a fatal miscalculation in traversal that led to a long Fall. In this ecosystem, you are both a predator and prey, and the terrain itself is a constant hazard.)");
      dieInjuryUnit.addContent("", "Normal");
      dieInjuryUnit.addFastPrinter(
          R"(Your consciousness bleeds back into the familiar, sterile darkness of your last visited Shelter. The revival process is taxing, and your spiritual resonance—your Karma—has been reduced by one as a result. The gates ahead now seem a little more demanding.)");
      dieInjuryUnit.display();
      player.distance = 100;
      player.health = 100;
      player.time = 100;
      player.hunger = recordedHunger;
      player.clearBackpack();
      player.checkInfo();
      continue;
    }
  }
}
