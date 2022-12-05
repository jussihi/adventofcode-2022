#include <map>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <locale>

int main(void)
{
  std::fstream file("input");
  std::string line;

  std::map<int, std::deque<char>> stackContainerP1;
  std::map<int, std::deque<char>> stackContainerP2;

  while(std::getline(file, line))
  {
    // Skip one more line, break out of this loop
    if(line.length()>1 && line[1] == '1')
    {
      std::getline(file, line);
      break;
    }
    for(auto [i, j] = std::tuple{1, 1}; j < line.length(); i++, j+=4)
    {
      if(std::isalpha(line[j]))
      {
        stackContainerP1[i].push_front(line[j]);
        stackContainerP2[i].push_front(line[j]);
      }
    }
  }

  // Move crates
  while(std::getline(file, line))
  {
    int move, from, to;
    std::string placeholder;
    std::istringstream iss(line);
    iss >> placeholder >> move >> placeholder >> from >> placeholder >> to;
    // Part 1
    for(int i = 0; i < move; i++)
    {
      stackContainerP1[to].push_back(stackContainerP1[from].back());
      stackContainerP1[from].pop_back();
    }
    // Part 2
    stackContainerP2[to].insert(stackContainerP2[to].end(),
                              stackContainerP2[from].end() - move,
                              stackContainerP2[from].end());
    stackContainerP2[from].erase(stackContainerP2[from].end() - move,
                               stackContainerP2[from].end());
  }

  // Solution to P1
  for(auto& cont : stackContainerP1)
  {
    std::cout << cont.second.back();
  }
  std::cout << std::endl;

  // Solution to P2
  for(auto& cont : stackContainerP2)
  {
    std::cout << cont.second.back();
  }
  std::cout << std::endl;

  return 0;
}