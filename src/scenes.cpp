#include "../include/main.h"
#include <string>
#include <vector>

const std::vector<std::string> sceneList = {
    "normal",      "bluefruit", "rock",   "climb",     "batfly",
    "hibernation", "rain",      "lizard", "Main Menu", "spear"};

std::unordered_map<std::string, Scene> sceneRegistry;

/*
const std::vector<std::string> optionList = {
    "goAhead", "combat", "escape", "eat", "take", "checkInfo", "checkRegion"};
*/

void registerGlobalScene() {
  for (auto it : sceneList) {
    Scene temp;
    temp.name = it;
    sceneRegistry[it] = temp;
  }
  sceneRegistry["Main Menu"].danger = 0;
  sceneRegistry["Main Menu"].type = "system";
  sceneRegistry["Main Menu"].disc =
      R"(Welcome to Rain World. Everything here is hungry, and you look like a marshmallow. Good luck.)";
  sceneRegistry["Main Menu"].options = {"start", "savings", "items", "regions"};

  sceneRegistry["normal"].danger = 5;
  sceneRegistry["normal"].type = "peace";
  sceneRegistry["normal"].disc =
      R"(Totally uneventful. Walked my usual route, pipes hummed the same old tune, and even the rain decided to be boring today—just a light drizzle. Reached the shelter on time, no surprises, no drama. Door closed. Another cycle, successfully... underwhelming. Guess even this place needs a day off.)";
  sceneRegistry["normal"].options = {"goAhead", "eat", "checkInfo",
                                     "checkRegion"};

  sceneRegistry["bluefruit"].danger = 10;
  sceneRegistry["bluefruit"].type = "peace";
  sceneRegistry["bluefruit"].disc =
      R"(Look at that—a **blue fruit** just hanging there, all plump and untouched, like it's waiting just for me. Talk about good service. One quick grab, and it's mine. Easy. Today's menu is looking up.)";
  sceneRegistry["bluefruit"].options = {"goAhead", "take", "eat", "checkInfo",
                                        "checkRegion"};

  sceneRegistry["rock"].danger = 5;
  sceneRegistry["rock"].type = "peace";
  sceneRegistry["rock"].disc =
      R"(Perfect! There it is, just lying on the ground. Not hiding, not doing anything useful—just being a rock. Guess it got tired of rolling. Pocket secured. My collection of very important pebbles grows by one.)";
  sceneRegistry["rock"].options = {"goAhead", "take", "eat", "checkInfo",
                                   "checkRegion"};
  sceneRegistry["spear"].danger = 5;
  sceneRegistry["spear"].type = "peace";
  sceneRegistry["spear"].disc =
      R"(Jackpot. It’s long, it’s sharp, and it’s the only thing standing between you and a lizard's digestive tract. A true masterpiece of primitive engineering. You feel 200% more courageous already—which is still not very much, but it’s a start. Handle with care, or don't.)";
  sceneRegistry["spear"].options = {"goAhead", "take", "eat", "checkInfo",
                                    "checkRegion"};

  sceneRegistry["climb"].danger = 30;
  sceneRegistry["climb"].type = "setback";
  sceneRegistry["climb"].disc =
      R"(Time to get vertical. These rusty maintenance pipes look sketchy but they're solid—mostly. One slip and you'll get a not-so-great view of the ground. Up we go. The view from the top better be worth it.)";
  sceneRegistry["climb"].options = {"goAhead", "eat", "checkInfo",
                                    "checkRegion"};

  sceneRegistry["batfly"].danger = 15;
  sceneRegistry["batfly"].type = "peace";
  sceneRegistry["batfly"].disc =
      R"(Bzzzt. A swarm of batflies doing their chaotic dance. Annoying, but also lunch. Just gotta time a good swipe... Gotcha! Crunchy. Not exactly gourmet, but it'll do.)";
  sceneRegistry["batfly"].options = {"goAhead", "take", "eat", "checkInfo",
                                     "checkRegion"};

  sceneRegistry["hibernation"].danger = 0;
  sceneRegistry["hibernation"].type = "system";
  sceneRegistry["hibernation"].disc =
      R"(The shelter door seals with a satisfying thud. The roar of the rain turns into a muffled rumble. Time to power down and let the world flood. Another cycle in the bag. See you on the other side, hopefully.)";
  sceneRegistry["hibernation"].options = {"nextCycle", "eat", "checkInfo",
                                          "checkRegion"};

  sceneRegistry["rain"].danger = 10;
  sceneRegistry["rain"].type = "setback";
  sceneRegistry["rain"].disc =
      R"(The sky just opened up. This isn't drizzle—this is a wall of water that wants to pound you into paste. RUN. Every second counts now. That shelter door looks very, very far away.)";
  sceneRegistry["rain"].options = {"goAhead", "eat", "checkInfo",
                                   "checkRegion"};

  sceneRegistry["lizard"].danger = 50;
  sceneRegistry["lizard"].type = "hostile";
  sceneRegistry["lizard"].disc =
      R"(Oh great. A green lizard, and it's looking right at you. Not the curious kind of look—the “you'd make a decent snack” kind. It's between you and where you need to go. Time for a sudden change of plans.)";
  sceneRegistry["lizard"].options = {"combat", "escape", "eat", "checkInfo",
                                     "checkRegion"};
}
