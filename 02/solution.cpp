#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

std::map<char, std::map<char, unsigned int>> strategyGuideP1 =
    { { 'A', { {'X', 4}, {'Y', 8}, {'Z', 3} } },
      { 'B', { {'X', 1}, {'Y', 5}, {'Z', 9} } },
      { 'C', { {'X', 7}, {'Y', 2}, {'Z', 6} } }
    };

std::map<char, std::map<char, unsigned int>> strategyGuideP2 =
    { { 'A', { {'X', 3}, {'Y', 4}, {'Z', 8} } },
      { 'B', { {'X', 1}, {'Y', 5}, {'Z', 9} } },
      { 'C', { {'X', 2}, {'Y', 6}, {'Z', 7} } }
    };

int main(void)
{
  std::fstream file("input");
  std::string line;

  unsigned int totalP1 = 0, totalP2 = 0;

  while(std::getline(file, line))
  {
    char me, opp;
    std::istringstream iss(line);
    iss >> opp >> me;
    totalP1 += strategyGuideP1[opp][me];
    totalP2 += strategyGuideP2[opp][me];
  }
  // Part 1
  std::cout << "total points: " << totalP1 << std::endl;

  // Part 2
  std::cout << "total points: " << totalP2 << std::endl;
}