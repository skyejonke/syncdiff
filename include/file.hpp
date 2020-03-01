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
    bool isSource(std::shared_ptr<file> fileIn);
    bool isName(std::shared_ptr<file> fileIn);
    std::string getName();
    std::string getDirectory();
  private:
    std::string directory;
    std::string name;
    std::string ext;
};

