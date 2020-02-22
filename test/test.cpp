#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "file.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
TEST_CASE("files work as intended", "[file]"){

  file *testFile = new file("/tmp/test.txt");
  conflictFile *confFile = new conflictFile("/tmp/test~2019-11-12.txt");
  SECTION("Files can be created"){
    REQUIRE(testFile->name == "test");
  }
  SECTION("isName works correctly"){
    REQUIRE(testFile->isName(*confFile));
  }
  delete testFile;
  delete confFile;
}
