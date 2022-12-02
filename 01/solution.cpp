#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

int main(void)
{
  std::vector<int> elves_cals;

  std::fstream file("input");
  std::string line;
  unsigned int total = 0;

  while(std::getline(file, line))
  {
    if(line.size() == 0)
    {
      elves_cals.push_back(total);
      total = 0;
    }
    else
    {
      total += std::stoi(line);
    }
  }

  // Part 1
  std::cout << "max cals per elf: "
            << *std::max_element(elves_cals.begin(), elves_cals.end())
            << std::endl;

  // Part 2
  std::partial_sort(elves_cals.begin(), elves_cals.begin() + 3,
                    elves_cals.end(), std::greater{});

  std::cout << "max 3 elves cals: "
            << std::accumulate(elves_cals.begin(), elves_cals.begin() + 3, 0)
            << std::endl;
}