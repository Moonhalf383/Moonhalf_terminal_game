#include "../include/basic.h"
#include <chrono>
#include <random>
#include <thread>

std::random_device rd;
std::mt19937 gen(rd());

std::uniform_real_distribution<> distf(0.0, 1.0);

void sleepFor(double seconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds((int)(seconds * 1000)));
}

double randf() { return distf(gen); }

int randint(int inf, int sup) {
  std::uniform_int_distribution<> distint(inf, sup);
  return distint(gen);
}
