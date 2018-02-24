#include "WebPage.h"
#include <fstream>
#include <stack>
#include <ctype.h>

WebPage::WebPage(const std::string& page) {
  name = page;
  std::ifstream infile(page);
  while (infile.good()) {
    std::string line;
    getline(infile, line);
    rawText += line;
  }
  infile.close();

  for (unsigned int i = 0; i < rawText.size(); ++i) {
    if (isalpha(rawText[i]) || isdigit(rawText[i])) {
      std::string word;
      while (isalpha(rawText[i]) || isdigit(rawText[i])) {
        word += rawText[i];
        ++i;
      }
      text.push_back(word);
    }
    else if (rawText[i] == '(') {
      ++i;
      std::string link;
      while (rawText[i] != ')') {
        link += rawText[i];
        ++i;
      }
      outgoingLinks.push_back(link);
    }
    else if (rawText[i] == '[') {
      ++i;
      std::string word;
      while (rawText[i] != ']') {
        word += rawText[i];
        ++i;
      }
      text.push_back(word);
    }
  }
}

WebPage::~WebPage() {};
