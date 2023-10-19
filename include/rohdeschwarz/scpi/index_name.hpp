/**
 * \file index_name.cpp
 * \brief rohdeschwarz::scpi::IndexName definition
 */


#ifndef ROHDESCHWARZ_SCPI_INDEX_NAME_HPP
#define ROHDESCHWARZ_SCPI_INDEX_NAME_HPP


// std lib
#include <string>
#include <vector>


namespace rohdeschwarz::scpi
{


/**
 * \brief Data type for handling named and indexed quantities.
 *
 * The ZNX will often return a list of objects in the format:
 *
 * `<index1>,<name1>,<index2>,<name2>,...`
 *
 * This struct is designed to handle this type of data
 */
struct IndexName
{


  unsigned int index;
  std::string  name;


  // parse

  /**
   * \brief Parses index-name pairs from text
   *
   * \param[in] csvList CSV list of index-name pairs in a C style string
   */
  static std::vector<IndexName> parse(const char* csvList);


  /**
   * \brief Parses index-name pairs from text
   *
   * \param[in] csvList CSV list of index-name pairs in a C++ style string
   */
  static std::vector<IndexName> parse(const std::string& csvList);


  /**
   * \brief Returns index list from IndexName list
   */
  static std::vector<unsigned int> indexesFrom(const std::vector<IndexName>& list);


  /**
   * \brief Returns names list from IndexName list
   */
  static std::vector<std::string> namesFrom(const std::vector<IndexName>& list);

};  // IndexName


}      // rohdeschwarz::scpi
#endif // ROHDESCHWARZ_SCPI_INDEX_NAME_HPP
