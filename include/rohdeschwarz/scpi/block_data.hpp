/**
 * \file block_data.hpp
 * \brief `rohdeschwarz::scpi::BlockData` definition
 */


#ifndef ROHDESCHWARZ_SCPI_BLOCK_DATA_HPP
#define ROHDESCHWARZ_SCPI_BLOCK_DATA_HPP


// std lib
#include <cstddef>
#include <vector>


namespace rohdeschwarz::scpi
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
   * This constructor supports move semantics.
   *
   * \param[in] data Initial data to populate Block Data with
   */
  BlockData(std::vector<unsigned char> data);


  // header

  /**
   * \brief Checks the header for errors
   *
   * Incomplete headers are judged based on the
   *
   * \returns `true` if block data header is valid or has the potential to be valid; `false` otherwise
   */
  bool isHeaderError() const;


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
   * \brief Copies data to block
   */
  void push_back(std::vector<unsigned char>::const_iterator begin, std::size_t size);


  // payload data

  /**
   * \brief Gets payload size, in bytes, from a complete header
   *
   * Requires `isHeader()` to be `true`.
   *
   * \returns payload size, in bytes, if header is valid and complete; `0` otherwise
   */
  std::size_t size() const;


  /**
   * \brief Gets a pointer to the payload data
   *
   * Requires `isHeader()` to be `true`.
   *
   * \returns pointer to payload data
   */
  unsigned char* data();


private:

  // header members
  bool         _isHeader;
  std::size_t _headerSize_B;
  std::size_t _payloadSize_B;
  std::size_t _blockSize_B;


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
  std::size_t parseNumberOfSizeDigits() const;


  /**
   * \brief Parses the payload size from the Block Data header
   *
   * Requires `isHeader()` to be `true`
   */
  std::size_t parsePayloadSize_B() const;


  /**
   * \brief Gets size of complete Block Data, in bytes
   *
   * Requires `isHeader()` to be `true`
   */
  std::size_t parseBlockSize_B()   const;


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
  std::size_t bytesRemaining() const;


};  // BlockData


}       // rohdeschwarz::scpi
#endif  // ROHDESCHWARZ_SCPI_BLOCK_DATA_HPP
