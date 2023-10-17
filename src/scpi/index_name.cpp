/**
 * \file index_name.cpp
 * \brief rohdeschwarz::scpi::IndexName implementation
 */


#include "rohdeschwarz/scpi/index_name.hpp"
#include "rohdeschwarz/helpers.hpp"
using namespace rohdeschwarz::scpi;
using namespace rohdeschwarz;


// std lib
#include <cstddef>


std::vector<IndexName> IndexName::parse(const char* csvList)
{
  const std::string csv_list_str(csvList);
  return IndexName::parse(csv_list_str);
}


std::vector<IndexName> IndexName::parse(const std::string& csvList)
{
  // split csv list
  std::vector<std::string> parts = split(csvList);

  // create vector of IndexNames
  std::vector<IndexName> indexNames;
  indexNames.reserve(parts.size() / 2);
  for (int i = 0; i + 1 < parts.size(); i += 2)
  {
    // create IndexName
    IndexName index_name;
    index_name.index = std::stoi(parts[i]);
    index_name.name  = parts[i + 1];

    // insert
    indexNames.push_back(index_name);
  }
  return indexNames;
}


std::vector<unsigned int> IndexName::indexesFrom(const std::vector<IndexName>& list)
{
  // create vector; set capacity
  std::vector<unsigned int> indexes;
  indexes.reserve(list.size());

  // populate vector
  for (int i = 0; i < list.size(); i++)
  {
    indexes.emplace_back(list[i].index);
  }
  return indexes;
}


std::vector<std::string> IndexName::namesFrom(const std::vector<IndexName>& list)
{
  // create vector; set capacity
  std::vector<std::string> names;
  names.reserve(list.size());

  // populate vector
  for (int i = 0; i < list.size(); i++)
  {
    names.emplace_back(list[i].name);
  }
  return names;
}
