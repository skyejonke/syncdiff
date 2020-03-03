#pragma once
#include "file.hpp"

class conflictFile : public file {
  public:
    conflictFile(std::string dirIn);
    std::unique_ptr<std::vector<int>> compare();
    bool setSource(std::shared_ptr<file> fileIn);
    bool isConflict = true;
    std::shared_ptr<file> getSource();
  private:
    std::shared_ptr<file> source;
};
