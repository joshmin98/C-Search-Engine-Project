#ifndef DATABASE_H
#define DATABASE_H

#include "WebPage.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>

class Database {
public:
  Database(const std::string &indexFilePath);
  ~Database();

  void print(const std::string &word);
  void andFunc(const std::vector<std::string> &inputs);
  void orFunc(const std::vector<std::string> &inputs);
  void incoming(const std::string &page);
  void outgoing(const std::string &page);

private:
  std::map<std::string, std::set<std::string>> searchMap;
  std::map<std::string, WebPage *> webpageMap;

  std::set<std::string> setIntersection(std::set<std::string> *first,
                                        std::set<std::string> *second);
  std::set<std::string> setUnion(std::set<std::string> *first,
                                 std::set<std::string> *second);
};
#endif
