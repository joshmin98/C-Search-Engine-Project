#include "Database.h"
#include "WebPage.h"
int main(int argc, char *argv[])
{
  if (argc < 2) {
    std::cerr << "Invalid argument" << std::endl;
    return -1;
  }
  WebPage w = WebPage("data/page1.txt");
  std::cout << w.getName() << std::endl;
  std::cout << w.getRaw() << std::endl;
  std::vector<std::string> links = w.getOutgoing();
  for (unsigned int i = 0; i < links.size(); ++i) {
    std::cout << links[i] << std::endl;
  }

  return 0;
}
