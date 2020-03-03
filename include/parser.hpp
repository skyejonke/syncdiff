#pragma once
#include "file.hpp"
#include "conflictfile.hpp"

class parser {
    struct filePair{
      std::shared_ptr<file> source;
      std::shared_ptr<conflictFile> conf;
      std::unique_ptr<std::vector<int>> ints = std::unique_ptr<std::vector<int>> (new std::vector<int>);
    };
  public:
    //std::shared_ptr<file> getNextFile(); Probably not neccessary given you can just iterate over files/conffiles?
    parser();
    std::unique_ptr<std::vector<std::string>> getNames();
    void setSources();
    std::unique_ptr<std::vector<filePair>> compareAll();
  private:
    std::vector<std::shared_ptr<file>> files;
    std::vector<std::shared_ptr<conflictFile>> confFiles;
};
