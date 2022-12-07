#include <fstream>
#include <string>
#include <deque>
#include <iostream>


int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    std::cerr << "Usage: " << argv[0] <<
                 " <num-consecutive-chars>" << std::endl;
    return 1;
  }
  int consecutive = std::atoi(argv[1]);
  std::fstream file("input");
  std::string line;
  std::deque<char> buff;
  unsigned int i = 1;

  std::getline(file, line);

  auto line_iter = line.begin();

  // Fill in initial buffer
  for(; i < consecutive; i++, line_iter++)
    buff.push_back(*line_iter);

  // Start going through the rest of the string buffer
  for(; line_iter != line.end(); line_iter++, i++)
  {
    buff.push_back(*line_iter);
    for(auto it1 = buff.begin(); it1 != buff.end(); it1++)
    {
      for(auto it2 = std::next(it1); it2 != buff.end(); it2++)
      {
        if(*it1 == *it2)
          goto next;
      }
    }
    std::cout << i << std::endl;
    return 0;
next:
    buff.pop_front();
  }

  return 0;
}