#include <memory>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <locale>
#include <iostream>
#include <limits>

struct File
{
  File(std::string w_name, unsigned int w_size)
  {
    name = w_name; size = w_size;
  }

  unsigned int size;
  std::string name;
};

struct Directory
{
  std::set<std::shared_ptr<Directory>> dirs;
  std::set<std::shared_ptr<File>> files;
  std::weak_ptr<Directory> parent;
  std::string name;
};

/*
 * PART 1, part of PART 2 also ...
 */
unsigned int dir_size_100k_callback(unsigned int in_size)
{
  static unsigned int total = 0;

  if(in_size < 100000)
    total += in_size;
  
  return total;
}

unsigned int traverse_dir_size(std::shared_ptr<Directory> start_dir)
{
  unsigned int total_dir_size = 0;
  for(auto& dir : start_dir->dirs)
  {
    total_dir_size += traverse_dir_size(dir);
  }
  for(auto& file : start_dir->files)
  {
    total_dir_size += file->size;
  }
  dir_size_100k_callback(total_dir_size);
  return total_dir_size;
}

/*
 * PART 2
 */
unsigned int min_dir_finder_callback(std::shared_ptr<Directory> curr_dir,
                                     unsigned int curr_dir_size,
                                     unsigned int min_size)
{
  static unsigned int best_size = std::numeric_limits<unsigned int>::max();

  if(curr_dir_size >= min_size && curr_dir_size < best_size)
    best_size = curr_dir_size;

  return best_size;
}

unsigned int traverse_dir_size2(std::shared_ptr<Directory> start_dir,
                                unsigned int min_size)
{
  unsigned int total_dir_size = 0;
  for(auto& dir : start_dir->dirs)
  {
    total_dir_size += traverse_dir_size2(dir, min_size);
  }
  for(auto& file : start_dir->files)
  {
    total_dir_size += file->size;
  }
  min_dir_finder_callback(start_dir, total_dir_size, min_size);
  return total_dir_size;
}



int main(void)
{
  std::fstream file("input");
  std::string line;

  // We create root dir manually, set it as "curr"
  std::getline(file, line);
  std::shared_ptr<Directory> root = std::make_shared<Directory>();
  root->name = "/";

  std::shared_ptr<Directory> curr = root;

  // Fill directory structure
  while(std::getline(file, line))
  {
    std::string s1, s2, s3;

    std::istringstream iss(line);
    iss >> s1 >> s2 >> s3;

    if(s1 == "$" && s2 == "cd")
    {
      if(s3 == "..")
      {
        curr = curr->parent.lock();
      }
      else
      {
        std::shared_ptr<Directory> new_dir = std::make_shared<Directory>();
        new_dir->name = s3;
        new_dir->parent = curr;
        curr->dirs.insert(new_dir);
        curr = new_dir;
      }
    }
    else if(s1.length() && std::isdigit(s1[0]))
    {
      std::shared_ptr<File> new_file = std::make_shared<File>(s2, std::stoi(s1));
      curr->files.insert(new_file);
    }
  }

  // Traverse files
  unsigned int root_size = traverse_dir_size(root);

  // Part 1 answer
  std::cout << dir_size_100k_callback(0) << std::endl;

  traverse_dir_size2(root, 30000000 - (70000000 - root_size));

  // Part 2 answer
  std::cout << min_dir_finder_cb(root, 70000000, 1) << std::endl;

  return 0;
}