#pragma once
#include "file.hpp"

class parser {
  public:
    std::shared_ptr<file> getNextFile();
    parser();
  private:
    std::vector<std::unique_ptr<file>> files;
};
