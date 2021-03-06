#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "file.hpp"
#include "conflictfile.hpp"
#include "parser.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
TEST_CASE("files work as intended", "[file]"){

  shared_ptr<file> testFile(new file("/tmp/test.txt"));
  shared_ptr<conflictFile> confFile(new conflictFile("/tmp/test~2019-11-12.txt"));
  SECTION("Files can be created"){
    REQUIRE(testFile->getName() == "test");
  }
  SECTION("isName works correctly"){
    REQUIRE(testFile->isName(confFile));
  }
}

TEST_CASE("conflict files work as intended", "[conflictFile]"){
  shared_ptr<file> testFile(new file("/tmp/test.txt"));
  shared_ptr<conflictFile> confFile(new conflictFile("/tmp/test~2019-11-12.txt"));
  shared_ptr<conflictFile> confFile2(new conflictFile("/tmp/tent~2019-11-12.txt"));

  SECTION("Does isSource correctly identify sources?"){
    REQUIRE(testFile->isSource(confFile));
    REQUIRE_FALSE(testFile->isSource(confFile2));
  }

  SECTION("Does setting source work?"){
    REQUIRE(confFile->setSource(testFile));
  }
}
