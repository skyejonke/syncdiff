#pragma once
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>

class file {
  public:
    file(std::string dirIn);
    std::vector<std::string> getContents();
    bool setContents(std::shared_ptr<file> fileIn);
    bool isSource(std::string pathIn);
  private:
    std::string directory;
    std::string name;
};

#include "conflictfile.hpp"
#include "parser.hpp"
