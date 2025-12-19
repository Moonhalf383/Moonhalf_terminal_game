#include "../include/basic.h"
#include "../include/term.h"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

Message::Message(std::string strContent, std::string strEffect) {
  content = strContent;
  effect = strEffect;
}

void printer(std::string &content, int width = 50, double pace = 0.05) {
  int counter = 0;
  for (auto it : content) {
    counter++;
    if (it == ' ' && counter > width)
      counter = 0;
    std::cout << it << std::flush;
    if (counter == 0)
      std::cout << std::endl;
    sleepFor(pace);
  }
  std::cout << std::endl;
}

void Message::display() {
  if (effect == "Normal") {
    std::cout << content << std::endl;
  } else if (effect == "Highlight") {
    std::cout << "***" << content << "***" << std::endl;
  } else if (effect == "Printer") {
    printer(content);
  } else if (effect == "Confused") {
    std::cout << "???" << content << "???" << std::endl;
  } else if (effect == "FastPrinter") {
    printer(content, 50, 0.02);
  } else if (effect == "SlowPrinter") {
    printer(content, 50, 0.1);
  }
}
