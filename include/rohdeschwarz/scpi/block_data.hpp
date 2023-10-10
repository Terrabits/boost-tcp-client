/**
 * \file block_data.hpp
 * \brief `BlockData` definition
 */


#ifndef RS_VISA_BLOCK_DATA_HPP
#define RS_VISA_BLOCK_DATA_HPP


// std lib
#include <vector>


namespace RsVisa
{


/**
 * \brief Object-oriented Block Data storage and manipulation
 */
class BlockData
{

public:

  // life cycle

  /**
   * \brief Default Constructor
   */
  BlockData();


  /**
   * \brief Constructor
   *
   * \param[in] data Initial data to populate Block Data with
   */
  BlockData(const std::vector<unsigned char> &data);  // copy


  /**
   * \brief Constructor
   *
   * This constructor supports move semantics.
   *
   * \param[in] data Initial data to populate Block Data with
   */
  BlockData(std::vector<unsigned char>&& data);       // move


  // header

  /**
   * \brief Checks if Block Data header is at least partially valid
   *
   * Incomplete Block Data headers are checked for the potential to be correct
   * with more data.
   *
   * \returns `true` if block data header is valid or has the potential to be valid; `false` otherwise
   */
  bool isPartialHeader() const;


  /**
   * \brief Checks for a valid and complete Block Data header
   */
  bool isHeader()   const;


  /**
   * \brief Checks for complete Block Data header and payload
   */
  bool isComplete() const;


  // push back

  /**
   * \brief Appends data to Block Data
   */
  void push_back(const std::vector<unsigned char>& data);


  /**
   * \brief Appends data to Block Data
   *
   * This method supports move semantics.
   */
  void push_back(std::vector<unsigned char>&& data);


  // payload data

  /**
   * \brief Gets payload size, in bytes, from a complete header
   *
   * Requires `isHeader()` to be `true`.
   *
   * \returns payload size, in bytes, if header is valid and complete; `0` otherwise
   */
  unsigned int payloadSize_B() const;


  /**
   * \brief Gets a pointer to the payload data
   *
   * Requires `isHeader()` to be `true`.
   *
   * \returns pointer to payload data
   */
  unsigned char* payload();


private:

  // header members
  bool         _isHeader;
  unsigned int _headerSize_B;
  unsigned int _payloadSize_B;
  unsigned int _blockSize_B;


  // data
  std::vector<unsigned char> _data;


  // helpers


  // header

  /**
   * \brief Parses the number of characters used to represent the payload size
   * from the Block Data header
   *
   * Requires access to the second byte of the Block Data header
   */
  unsigned int parseNumberOfSizeDigits() const;


  /**
   * \brief Parses the payload size from the Block Data header
   *
   * Requires `isHeader()` to be `true`
   */
  unsigned int parsePayloadSize_B() const;


  /**
   * \brief Gets size of complete Block Data, in bytes
   *
   * Requires `isHeader()` to be `true`
   */
  unsigned int parseBlockSize_B()   const;


  /**
   * \brief Parses the Block Data header
   *
   * Requires `isHeader()` to be `true`
   */
  void processHeader();


  // payload

  /**
   * \brief Calculates the number of bytes missing from Block Data
   *
   * Requires `isHeader()` to be `true`
   */
  unsigned int bytesRemaining() const;


}; // class BlockData


}       // RsVisa
#endif  // RS_VISA_BLOCK_DATA_HPP
