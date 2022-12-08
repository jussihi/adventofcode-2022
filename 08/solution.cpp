#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

int main(void)
{
  std::fstream file("input");
  std::string line;

  std::vector<std::vector<std::pair<unsigned int, int>>> trees;

  // Fill the 2d vector
  while(std::getline(file, line))
  {
    std::vector<std::pair<unsigned int, int>> currline;
    for(auto& c : line)
    {
      currline.push_back(std::make_pair<unsigned int, int>(c - '0', 0));
    }
    trees.push_back(std::move(currline));
  }

  unsigned int highest_scenic = 0;

  // Get visible trees from each side
  for(int row = 0; row < trees.size(); row++)
  {
    for(int col = 0; col < trees[row].size(); col++)
    {
      unsigned int leftsc = 0, rightsc = 0, topsc = 0, bottomsc = 0;
      // Visible from left?
      for(int i = col - 1; i >= 0; i--)
      {
        leftsc++;
        if(trees[row][i].first >= trees[row][col].first)
          goto right;
      }
      trees[row][col].second++;

      // Visible from right?
right:
      for(int i = col + 1; i < trees[row].size(); i++)
      {
        rightsc++;
        if(trees[row][i].first >= trees[row][col].first)
          goto top;
      }
      trees[row][col].second++;

      // Visible from top?
top:
      for(int i = row - 1; i >= 0; i--)
      {
        topsc++;
        if(trees[i][col].first >= trees[row][col].first)
          goto bot;
      }
      trees[row][col].second++;

      // Visible from bottom?
bot:
      for(int i = row + 1; i < trees.size(); i++)
      {
        bottomsc++;
        if(trees[i][col].first >= trees[row][col].first)
          goto end;
      }
      trees[row][col].second++;
end:
      unsigned int scenic_score = leftsc * rightsc * topsc * bottomsc;
      if(scenic_score > highest_scenic)
        highest_scenic = scenic_score;
    }
  }

  // Mark edge trees always visible from all sides
  for(int i = 0; i < trees[0].size(); i++)
  {
    trees[0][i].second++;
    trees[trees.size() - 1][i].second++;
  }
  for(int i = 0; i < trees.size(); i++)
  {
    trees[i][0].second++;
    trees[i][trees[0].size() - 1].second++;
  }

  // Accumulate trees that are visible
  unsigned int total = 0;
  for(auto& row : trees)
    for(auto& col : row)
      if(col.second > 0)
        total++;
  
  // answer part1
  std::cout << total << std::endl;

  // answer part2
  std::cout << highest_scenic << std::endl;
  return 0;
}