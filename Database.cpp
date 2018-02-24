#include "Database.h"
#include <fstream>

Database::Database(const std::string &indexFilePath) {
  std::ifstream index(indexFilePath);
  if (index.fail()) {
    std::cerr << "failed to read file" << std::endl;
    return;
  }

  // Create and initialize pages
  std::string page;
  while (getline(index, page)) {
    WebPage *wp = new WebPage(page);
    webpageMap.insert(std::pair<std::string, WebPage *>(page, wp));
  }

  // Handle incoming links
  std::map<std::string, WebPage *>::iterator webpageMapIter =
      webpageMap.begin();
  for (; webpageMapIter != webpageMap.end(); ++webpageMapIter) {
    std::vector<std::string> outgoingLinks =
        webpageMapIter->second->getOutgoing();
    for (unsigned int i = 0; i < outgoingLinks.size(); ++i) {
      webpageMap[outgoingLinks[i]]->addIncoming(webpageMapIter->first);
    }
  }

  // Populate our word-to-webpage map
  webpageMapIter = webpageMap.begin();
  for (; webpageMapIter != webpageMap.end(); ++webpageMapIter) {
    std::vector<std::string> words = webpageMapIter->second->getText();
    for (unsigned int i = 0; i < words.size(); ++i) {
      std::map<std::string, std::set<std::string>>::iterator searchMapIter =
          searchMap.begin();
      if (searchMap.size() == 0) {
        std::string word = words[i];
        std::set<std::string> links;
        links.insert(webpageMapIter->first);
        searchMap.insert(
            std::pair<std::string, std::set<std::string>>(word, links));
        continue;
      }
      for (; searchMapIter != searchMap.end(); ++searchMapIter) {
        if (searchMapIter->first == words[i]) {
          searchMapIter->second.insert(webpageMapIter->first);
        } else {
          std::string word = words[i];
          std::set<std::string> links;
          links.insert(webpageMapIter->first);
          searchMap.insert(
              std::pair<std::string, std::set<std::string>>(word, links));
        }
      }
    }
  }
}

// Performs an intersection of two sets. To be used to implement andFunc()
std::set<std::string> Database::setIntersection(std::set<std::string> *first,
                                                std::set<std::string> *second) {
  std::set<std::string>::iterator it = first->begin();
  std::set<std::string> output;

  for (; it != first->end(); ++it) {
    if (second->find(*it) != second->end()) {
      output.insert(*it);
    }
  }
  return output;
}

void Database::andFunc(const std::vector<std::string> &inputs) {
  if (inputs.size() < 2) {
    std::cerr << "Invalid inputs" << std::endl;
    return;
  } else {
    std::set<std::string> intersection =
        setIntersection(&searchMap[inputs[0]], &searchMap[inputs[1]]);
    for (unsigned int i = 2; i < inputs.size(); ++i) {
      intersection = setIntersection(&intersection, &searchMap[inputs[i]]);
    }
    std::set<std::string>::iterator it = intersection.begin();
    for (; it != intersection.end(); ++it) {
      std::cout << *it << std::endl;
    }
  }
}

// Performs a union of two sets. To be used to implement orFunc()
std::set<std::string> Database::setUnion(std::set<std::string> *first,
                                         std::set<std::string> *second) {
  std::set<std::string>::iterator firstIter = first->begin();
  std::set<std::string>::iterator secondIter = second->begin();
  std::set<std::string> output;

  for (; firstIter != first->end(); ++firstIter) {
    if (output.find(*firstIter) == output.end()) {
      output.insert(*firstIter);
    }
  }
  for (; secondIter != second->end(); ++secondIter) {
    if (output.find(*secondIter) == output.end()) {
      output.insert(*secondIter);
    }
  }
  return output;
}

void Database::orFunc(const std::vector<std::string> &inputs) {
  if (inputs.size() < 2) {
    std::cerr << "Invalid inputs" << std::endl;
  } else {
    std::set<std::string> unions;
    unions = setUnion(&searchMap[inputs[0]], &searchMap[inputs[1]]);
    for (unsigned int i = 2; i < inputs.size(); ++i) {
      unions = setUnion(&unions, &searchMap[inputs[i]]);
    }
    std::set<std::string>::iterator it = unions.begin();
    for (; it != unions.end(); ++it) {
      std::cout << *it << std::endl;
    }
  }
}

void Database::incoming(const std::string &page) {
  std::vector<std::string> links = webpageMap[page]->getIncoming();
  for (unsigned int i = 0; i < links.size(); ++i) {
    std::cout << links[i] << std::endl;
  }
}

void Database::outgoing(const std::string &page) {
  std::vector<std::string> links = webpageMap[page]->getOutgoing();
  for (unsigned int i = 0; i < links.size(); ++i) {
    std::cout << links[i] << std::endl;
  }
}

Database::~Database() {
  std::map<std::string, WebPage *>::iterator it = webpageMap.begin();
  for (; it != webpageMap.end(); ++it) {
    delete it->second;
  }
}
