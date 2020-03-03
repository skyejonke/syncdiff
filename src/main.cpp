#include "file.hpp"
#include "conflictfile.hpp"
#include "parser.hpp"

using namespace std;
int main() {
  unique_ptr<parser> par (new parser());
  unique_ptr<vector<string>> names = par->getNames();
  auto pairs =  par->compareAll();
  for (auto it = pairs.begin(); it != pairs.cend(); ++it){
    cout << ((it->source != nullptr) ? it->source->getName() : "NONE") << " | " << it->conf->getName() << endl;
  }
  // for (auto it = names->begin(); it != names->end(); ++it){
  //  cout << *it << endl;
  //}
  //par->setSources();
  //par->compareAll();
  /* file test = file("test.txt"); */
  /* vector<string> t = test.getContents(); */

  /* shared_ptr<file> ptr (new file("test.txt")); */

  /* shared_ptr<conflictFile> cTest( */
  /*     new conflictFile("test2.txt",ptr)); */

  /* auto ints = cTest->compare(); */

  /* if (ints->size() != 0){ */
  /*   bool done = false; */

  /*   cout << "Keep? (l/r, 1/2)" << endl; */
  /*   string in; */
  /*   cin >> in; */

  /*   while (!done){ */
  /*     if (in == "l" || in == "1"){ */
  /*       done = true; */
  /*     } */
  /*     else if (in == "r" || in == "2"){ */
  /*       done = true; */
  /*       test.setContents(cTest); */
  /*     } */
  /*     else { */
  /*       cout << "Please input again." << endl; */
  /*       cin >> in; */
  /*     } */
  /*   } */
  /* } */


  return 0;
}
