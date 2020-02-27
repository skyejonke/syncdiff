#pragma once
#include "file.hpp"

class conflictFile : public file {
  public:
    conflictFile(std::string dirIn);
    std::shared_ptr<std::vector<int>> compare();
    bool setSource(std::shared_ptr<file> fileIn);
  private:
    std::shared_ptr<file> source;
};
