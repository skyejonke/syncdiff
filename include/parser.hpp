#pragma once
#include "file.hpp"
#include "conflictfile.hpp"
//#include "conflictfile.hpp"

class parser {
  public:
    std::shared_ptr<file> getNextFile();
    parser();
  private:
    std::vector<std::shared_ptr<file>> files;
    std::vector<std::shared_ptr<conflictFile>> confFiles;
};
