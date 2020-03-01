#pragma once
#include "file.hpp"
#include "conflictfile.hpp"

class parser {
  public:
    //std::shared_ptr<file> getNextFile(); Probably not neccessary given you can just iterate over files/conffiles?
    parser();
    std::unique_ptr<std::vector<std::string>> getNames();
    void setSources();
    void compareAll();
  private:
    std::vector<std::shared_ptr<file>> files;
    std::vector<std::shared_ptr<conflictFile>> confFiles;
};
