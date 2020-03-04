#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
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

  REQUIRE(testFile->getDirectory() == "/tmp/test.txt");

  SECTION("Does isSource correctly identify sources?"){
    REQUIRE(testFile->isSource(confFile));
    REQUIRE_FALSE(testFile->isSource(confFile2));
  }

  SECTION("Does setting source work?"){
    REQUIRE(confFile->setSource(testFile));
    REQUIRE_FALSE(confFile->setSource(nullptr));
  }
}

TEST_CASE("setting contents works correctly", "[contents]"){
  string str = "testtesttest";
  shared_ptr<file> testFile(new file("/tmp/syncdiff/test.txt"));
  system("mkdir /tmp/syncdiff/ > /dev/null 2>&1");
  system("echo 'testtesttest\ntesttest' > /tmp/syncdiff/test~2019.txt");
  shared_ptr<conflictFile> confFile(new conflictFile("/tmp/syncdiff/test~2019.txt"));
  confFile->setSource(testFile);
  testFile->setContents(confFile);
  auto f = testFile->getContents();
  auto c = confFile->getContents();

  for (string::size_type i = 0; i < f.size(); i++){
    REQUIRE(f.at(i) == c.at(i));
  }

  system("echo 'testtesttest\ntetttest' > /tmp/syncdiff/test~2019.txt");

  SECTION("Does comparing work?"){
    vector<int> v = vector<int>();
    v.push_back(1);
    REQUIRE(*(confFile->compare())  == v);
    v.push_back(0);
    REQUIRE_FALSE(*(confFile->compare())  == v);
  }

  SECTION("Does comparing fail when source is null?"){
    vector<int> v = vector<int>();
    shared_ptr<conflictFile> confFile3(new conflictFile("/tmp/syncdiff/test~2020.txt"));
    REQUIRE(*(confFile3->compare())  == v);
  }
}

