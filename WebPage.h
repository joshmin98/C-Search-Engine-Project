#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <string>
#include <vector>

class WebPage {
public:
  WebPage(const std::string &page /*Database* db*/);
  ~WebPage();

  void addIncoming(const std::string &link) { incomingLinks.push_back(link); }
  void addOutgoing(const std::string &link) { outgoingLinks.push_back(link); }
  void addText(const std::string &word) { text.push_back(word); }

  const std::vector<std::string> getOutgoing() { return outgoingLinks; }
  const std::vector<std::string> getIncoming() { return incomingLinks; }
  const std::vector<std::string> getText() { return text; }
  const std::string getRaw() { return rawText; }
  const std::string getName() { return name; }

private:
  std::vector<std::string> incomingLinks;
  std::vector<std::string> outgoingLinks;
  std::vector<std::string> text;
  std::string name;
  std::string rawText;
};
#endif
