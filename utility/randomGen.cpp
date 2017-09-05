#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

// First create an instance of an engine.

random_device rnd_device;
// Specify the engine and distribution.
mt19937 mersenne_engine(rnd_device());
uniform_int_distribution<int> dist(1, 52);

auto gen = std::bind(dist, mersenne_engine);
