#pragma once

#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <map>
#include <functional>

struct chunk_t
{
  std::vector<char> data{ 0, 0 };
  size_t initial_offset = 0;
  int index = 0;

  chunk_t() = default; // Empty chunk constructor

  chunk_t( const std::vector<char>& bytes, size_t from, size_t to, int index ) : index( index ) 
  {
    if (from < to && from >= 0 && to <= bytes.size())
    {
      initial_offset = from;
      data.assign( bytes.begin() + from, bytes.begin() + to );
    }
  }
};

struct bytes_mapper_t
{
  std::vector<char> bytes;

  bytes_mapper_t( const std::vector<char>& bytes ) : bytes( bytes )
  {
    if (bytes.empty())
    {
      throw std::runtime_error( "Empty bytes" );
    }
  }

  static std::vector<char> fileToBytes( const std::string& filepath );

  static std::vector<chunk_t> bytesToChunks( const std::vector<char>& bytes, uint16_t assumedChunkCount, size_t chunkOffset );

  static char read1Byte( const std::vector<char>& bytes, size_t offset );

  static uint16_t read2Bytes( const std::vector<char>& bytes, size_t offset );

  static uint32_t read4Bytes( const std::vector<char>& bytes, size_t offset );

  static void write1Byte( std::vector<char>& bytes, size_t offset, int value );

  static void write2Bytes( std::vector<char>& bytes, size_t offset, int value );

  static void write4Bytes( std::vector<char>& bytes, size_t offset, int value );

  static void writeDataToBytes( std::vector<char>& bytes, const std::vector<char>& data, size_t offset );

  static void writeBytesToNewFile( const std::vector<char>& bytes, const std::string& filepath );

  virtual void test() const;
};
