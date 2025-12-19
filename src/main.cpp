#include "../include/main.h"
#include "../include/items.h"
#include "../include/term.h"

void main_backup() {
  registerGlobalOption();
  registerGlobalItem();
  registerGlobalScene();
  SlugCat menu = SlugCat(1, 1, 1, "Outskirts", "System");
  menu.act();
}

int main(int argc, char *argv[]) {
  registerGlobalOption();
  registerGlobalItem();
  registerGlobalScene();
  SlugCat menu = SlugCat(1, 1, 1, "Outskirts", "System");
  menu.act();
  return 0;
}
