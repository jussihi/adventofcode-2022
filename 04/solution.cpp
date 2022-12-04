#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::vector<int> split_ints(const std::string& text, const std::string& delims)
{
  std::vector<int> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while((end = text.find_first_of(delims, start)) != std::string::npos)
  {
    tokens.push_back(std::atoi(text.substr(start, end - start).c_str()));
    start = text.find_first_not_of(delims, end);
  }
  if(start != std::string::npos)
    tokens.push_back(std::atoi(text.substr(start).c_str()));

  return tokens;
}

int main(void)
{
  std::fstream file("input");
  std::string line;

  unsigned int totalP1 = 0, totalP2 = 0;

  while(std::getline(file, line))
  {
    std::vector<int> nums = split_ints(line, "-,");
    // For p1, the shorter part is always inside indexes 2,3
    if(nums[3] - nums[2] > nums[1] - nums[0])
    {
      std::swap(nums[3], nums[1]);
      std::swap(nums[2], nums[0]);
    }
    if(nums[3] <= nums[1] && nums[2] >= nums[0])
      totalP1++;
    if((nums[2] <= nums[1] && nums[3] >= nums[1]) || (nums[0] <= nums[3] && nums[1] >= nums[3]))
      totalP2++;
  }

  std::cout << "total p1: " << totalP1 << std::endl;
  std::cout << "total p2: " << totalP2 << std::endl;
}