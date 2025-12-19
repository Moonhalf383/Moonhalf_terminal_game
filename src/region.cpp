#include "../include/basic.h"
#include "../include/main.h"
#include "../include/term.h"
#include <string>
#include <vector>

const std::vector<std::string> regionList = {
    "Outskirts",      "Industrial Complex", "Drainage System", "Chimney Canopy",
    "Garbage Wastes", "Shaded Citadel",     "Five Pebbles"};

Region::Region(std::string regionName) {
  name = regionName;
  progress = 0;
  if (regionName == "Outskirts") {
    hostileWeight = 15;
    moveWeight = 10;
    numOfShelter = randint(3, 5);
    disc =
        R"(The nursery of this wet hell. It’s full of rusty pipes to climb and Green Lizards that act tough but are too fat to climb after you. Basically a playground, assuming playgrounds have apex predators and bottomless pits. Great for practicing your 'running away' skills before the real pain begins. Don't miss the jump.)";
  } else if (regionName == "Industrial Complex") {
    hostileWeight = 30;
    moveWeight = 25;
    numOfShelter = randint(2, 4);
    disc =
        R"(Rust, dust, and trust issues. The architecture is 90% vertical drops and 10% unstable platforms. The lizards here have learned how to climb, which is incredibly rude. Also, the Scavengers have spears and a fluctuating economy based on shiny rocks. Pay the toll or get porcupined. Watch the sky; the shadows have teeth.)";
  } else if (regionName == "Drainage System") {
    hostileWeight = 20;
    moveWeight = 60;
    numOfShelter = randint(2, 3);
    disc =
        R"(If you love holding your breath until you pass out, this is the spot. It’s dark, damp, and infested with leeches that just want a hug—a permanently binding, drowning hug. Swimming mechanics are your new worst enemy here. Pro tip: If you hear a wet sucking sound, you're already dead.)";
  } else if (regionName == "Chimney Canopy") {
    hostileWeight = 50;
    moveWeight = 50;
    numOfShelter = randint(2, 4);
    disc =
        R"(The floor is lava? No, the floor is a two-mile drop. You are essentially a snack on a stick for the King Vultures circling above. The view is breathtaking, mostly because the Vulture masks scare the breath out of you. Parkour skills are mandatory; fear of heights is fatal. Good luck finding a shelter before the rain hits.)";
  } else if (regionName == "Garbage Wastes") {
    hostileWeight = 40;
    moveWeight = 30;
    numOfShelter = randint(3, 5);
    disc =
        R"(A literal dumpster fire, minus the fire, plus acid. It’s where civilization threw its leftovers, including the explosive kind. The Scavengers run this joint like a mafia. Don't touch the green water unless you want to dissolve. On the bright side, there are plenty of spears. On the downside, they are usually being thrown at you.)";
  } else if (regionName == "Shaded Citadel") {
    hostileWeight = 60;
    moveWeight = 40;
    numOfShelter = randint(1, 3);
    disc =
        R"(Bring a flashlight or become spider food. It’s pitch black, ancient, and everything here has too many legs. You will step on a Lantern Mouse by accident and feel bad about it, right before a Wolf Spider lunges at your face from the shadows. The darkness doesn't just hide things; it bites back.)";
  } else if (regionName == "Five Pebbles") {
    hostileWeight = 80;
    moveWeight = 90;
    numOfShelter = randint(1, 2);
    disc =
        R"(Zero gravity meets zero mercy. You are crawling inside the brain of a depressed god. There is no floor, no up, no down, just blue electric cancer (The Rot) trying to eat you. On the bright side, you can fly. On the downside, the walls are alive and they hate you. Try not to annoy the supercomputer.)";
  }
}

int Region::getHostileWeight() { return hostileWeight; }

int Region::getMoveWeight() { return moveWeight; }

int Region::getProgress() { return progress; }

int Region::getShelterNum() { return numOfShelter; }

void Region::showInfo(std::string mode) {
  ItemUnit info = ItemUnit();
  info.addPrinter("Region name: " + name);
  info.addPrinter("Region Discription: ");
  info.addFastPrinter(disc);
  if (mode == "Player") {
    info.addPrinter("Current process: " + std::to_string(progress));
    std::string visualProcess = progress == 0 ? "[*]" : "[#]";
    for (int i = 1; i <= numOfShelter; i++) {
      if (i == progress)
        visualProcess += "-----[*]";
      else
        visualProcess += "-----[@]";
    }
    visualProcess += progress > numOfShelter ? "-----[*]" : "-----[#]";
    info.addPrinter(visualProcess);
  }
  info.addContent("Creature Density: " + std::to_string(hostileWeight),
                  "Printer");
  info.addContent("Room complexity: " + std::to_string(moveWeight), "Printer");
  info.display();
}

void Region::move() { progress++; }
