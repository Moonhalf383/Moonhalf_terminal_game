#include "../include/items.h"
#include "../include/term.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

const std::vector<std::string> itemList = {"BlueFruit", "NoodleFly", "Rock",
                                           "Spear", "Batfly"};

std::unordered_map<std::string, Item> itemRegistry;

Item::Item(std::string itemName) : name(itemName) {}

Item::Item() {}
void Item::showInfo() {
  ItemUnit itemDisplayer = ItemUnit();
  itemDisplayer.addPrinter("Item name: " + name);
  itemDisplayer.addPrinter("Item discription: ");
  itemDisplayer.addFastPrinter(disc);
  itemDisplayer.display();
}

void itrgHelper(std::string target, int inputHunger, int inputDamage) {
  itemRegistry[target].damage = inputDamage;
  itemRegistry[target].hunger = inputHunger;
}

bool Item::isFood() { return hunger > 0; }

bool Item::isWeapon() { return damage > 0; }

void registerGlobalItem() {
  for (auto it : itemList) {
    Item temp(it);
    itemRegistry[it] = temp;
  }
  itrgHelper("BlueFruit", 1, 0);
  itrgHelper("Batfly", 1, 0);
  itrgHelper("Spear", 0, 60);
  itrgHelper("NoodleFly", 1, 0);
  itrgHelper("Rock", 0, 30);
  itemRegistry["BlueFruit"].disc =
      R"(The Blue Fruit is a common, edible item found hanging from black vines on ceilings across most regions of the Rain World. This teardrop-shaped fruit serves as a primary food source, replenishing a full pip of the food meter for most slugcats. Unlike other perishables, it can be stored in shelters and carried into the next cycle. Beyond sustenance, it has tactical uses: it can be thrown into water to lure Jetfish or used to distract Monster Kelps to safely pass by.Interestingly, this "fruit" is actually the pupa of an insect.)";
  itemRegistry["Spear"].disc =
      R"(Your lifeline and primary tool. A simple, rusty pole sharpened at one end. Throw it to pin prey or distract enemies, use it to pole-vault across gaps, or hold it close to fend off creatures. It's surprisingly versatile—just remember to pick it back up. Without it, you're just a soft slug in a hard world.)";
  itemRegistry["NoodleFly"].disc =
      R"(Look up. That’s a massive, flying knot of angry, fleshy noodles. They’re like the local, surprisingly durable air taxis—which is great, until they decide to drop you off in a pit of Red Lizards. Avoid the babies, or prepare for a very fast, very clumsy kidnapping ride.)";
  ;
  itemRegistry["Rock"].disc =
      R"(Just a rock. Not edible, not alive, and unlikely to grant you any wishes. However, it's perfect for making a loud, satisfying thunk noise, breaking glass, or mildly inconveniencing an apex predator. The ultimate low-budget throwable)";
  itemRegistry["Batfly"].disc =
      R"(Essentially, they are flying packets of bright blue protein. They're fast, foolish, and surprisingly nutritious, making them the slugcat's equivalent of a vending machine snack. Catching one is less about skill and more about having a really lucky, frantic swipe. A tiny, chaotic boost to your Karma.)";
}
