#include <fstream>
#include <iostream>
#include <string>


int main(void)
{
  std::fstream file("input");
  std::string line;

  unsigned int total = 0;

  while(std::getline(file, line))
  {
    int table[256] = {0};
    std::string firstHalf = line.substr(0, line.length()/2);
    std::string otherHalf = line.substr(line.length()/2);
    for(char const& a : firstHalf)
    {
      table[a]++;
    }
    for(char const& a : otherHalf)
    {
      if(table[a])
      {
        if(a >= 'a')
        {
          total += a - 'a' + 1;
        }
        else
        {
          total += a - 'A' + 27;
        }
        break;
      }
    }
  }

  std::cout << "total p1: " << total << std::endl;

  std::fstream file2("input");
  std::string line1;
  std::string line2;
  std::string line3;

  total = 0;

  while(std::getline(file2, line1))
  {
    std::getline(file2, line2);
    std::getline(file2, line3);

    int table[256] = {0};
  
    for(char const& a : line1)
    {
      if(!table[a])
        table[a]++;
    }
    for(char const& a : line2)
    {
      if(table[a] == 1)
        table[a]++;
    }
    for(char const& a : line3)
    {
      if(table[a] == 2)
      {
        if(a >= 'a')
          total += a - 'a' + 1;
        else
          total += a - 'A' + 27;
        break;
      }
    }
  }

  std::cout << "total p2: " << total << std::endl;

  return 0;
}