#pragma once
#include "file.hpp"

class conflictFile : public file {
  public:
    conflictFile(std::string dirIn, std::shared_ptr<file> sourceIn);
    std::shared_ptr<std::vector<int>> compare();
  private:
    std::shared_ptr<file> source;
};
