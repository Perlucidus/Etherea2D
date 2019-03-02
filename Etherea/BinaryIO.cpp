#include "BinaryIO.hpp"

BinaryWriter::BinaryWriter(ostream & stream) : stream(stream) {}

BinaryReader::BinaryReader(istream & stream) : stream(stream) {}
