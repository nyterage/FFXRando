#include "BytesHelper.hpp"

std::vector<char> bytes_mapper_t::fileToBytes( const std::string& filepath ) {
  std::ifstream file( filepath, std::ios::binary );
  if (!file)
  {
    std::cerr << "Failed to open file: " << filepath << std::endl;
    std::cout << "Please be sure your extracted ffx_ps2 folder is in the input folder" << std::endl;
    return {};
  }

  std::vector<char> buffer( std::istreambuf_iterator<char>( file ), {} );
  return buffer;
}

std::vector<chunk_t> bytes_mapper_t::bytesToChunks( const std::vector<char>& bytes, uint16_t assumedChunkCount, size_t chunkOffset ) {
  if (bytes.empty())
  {
    return {};
  }

  uint16_t chunkCount = assumedChunkCount;
  std::vector<size_t> offsets( chunkCount + 1, 0 );

  for (int i = 0; i <= chunkCount; i++)
  {
    size_t offset = read4Bytes( bytes, i * 4 + chunkOffset );
    if (offset == 0xFFFFFFFF)
      chunkCount = i - 1;
    else
      offsets.at( i ) = offset;
  }

  std::vector<chunk_t> chunks;

  for (size_t i = 0; i < chunkCount; i++)
  {
    size_t offset = offsets.at( i );
    if (offset == 0)
      chunks.emplace_back();
    else
    {
      size_t to = -1;
      for (size_t j = i + 1; j <= chunkCount; j++)
      {
        if (offsets[ j ] >= offset)
        {
          to = offsets[ j ];
          break;
        }
      }
      if (to == -1)
        to = bytes.size();
      chunks.emplace_back( bytes, offset, to, static_cast< int >( i ) );
    }
  }

  return chunks;
}

// This is very redundant, but for consistency sake its here. 
char bytes_mapper_t::read1Byte( const std::vector<char>& bytes, size_t offset ) {
  if (bytes.empty() || offset >= static_cast< int >( bytes.size() ))
    return 0;

  return bytes[ offset ];
}

uint16_t bytes_mapper_t::read2Bytes( const std::vector<char>& bytes, size_t offset ) {
  if (bytes.size() < offset + 2)
    return 0;

  return static_cast< uint8_t >( bytes[ offset ] ) |
    ( static_cast< uint8_t >( bytes[ offset + 1 ] ) << 8 );
}

uint32_t bytes_mapper_t::read4Bytes( const std::vector<char>& bytes, size_t offset ) {
  if (offset + 3 >= bytes.size())
    return 0;

  return static_cast< uint8_t >( bytes[ offset ] ) |
    ( static_cast< uint8_t >( bytes[ offset + 1 ] ) << 8 ) |
    ( static_cast< uint8_t >( bytes[ offset + 2 ] ) << 16 ) |
    ( static_cast< uint8_t >( bytes[ offset + 3 ] ) << 24 );
}

// same as read1Byte
void bytes_mapper_t::write1Byte( std::vector<char>& bytes, size_t offset, int value ) {
  if (offset >= bytes.size())
    return;

  bytes[ offset ] = static_cast< char >( value & 0xFF );
}

void bytes_mapper_t::write2Bytes( std::vector<char>& bytes, size_t offset, int value ) {
  if (offset + 1 >= bytes.size())
    return;

  bytes[ offset ] = static_cast< char >( value & 0xFF );
  bytes[ offset + 1 ] = static_cast< char >( ( value >> 8 ) & 0xFF );
}

void bytes_mapper_t::write4Bytes( std::vector<char>& bytes, size_t offset, int value ) {
  if (offset + 3 >= bytes.size())
    return;

  bytes[ offset ] = static_cast< char >( value & 0xFF );
  bytes[ offset + 1 ] = static_cast< char >( ( value >> 8 ) & 0xFF );
  bytes[ offset + 2 ] = static_cast< char >( ( value >> 16 ) & 0xFF );
  bytes[ offset + 3 ] = static_cast< char >( ( value >> 24 ) & 0xFF );
}

void bytes_mapper_t::writeDataToBytes( std::vector<char>& bytes, const std::vector<char>& data, size_t offset ) {
  if (offset < 0 || offset + static_cast< int >( data.size() ) > static_cast< int >( bytes.size() ))
  {
    return;
  }
  for (int i = 0; i < static_cast< int >( data.size() ); i++)
  {
    bytes[ offset + i ] = data[ i ];
  }
}

void bytes_mapper_t::writeBytesToNewFile( const std::vector<char>& bytes, const std::string& filepath ) {
  std::ofstream file( filepath, std::ios::binary );
  if (!file)
  {
    return;
  }
  for (char byte : bytes)
  {
    file.put( byte );
  }
}

void bytes_mapper_t::test() const {
  if (bytes.empty())
  {
    printf( "Empty bytes\n" );
  }
}