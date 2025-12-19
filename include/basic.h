#pragma once

#include <iostream>
#include <string>
#include <vector>
void sleepFor(double);

double randf();

int randint(int inf, int sup);

template <typename T> void debug(T x) {
  std::cout << "DEBUG: " << x << std::endl;
}

std::string getResponse(std::vector<std::string> &);
