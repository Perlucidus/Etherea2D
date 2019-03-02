#pragma once

#include <iostream>

using std::istream;
using std::ostream;

class BinaryReader {
public:
	BinaryReader() = delete;
	BinaryReader(istream&);
	virtual ~BinaryReader() = default;

	template<typename Type>
	Type read();
private:
	istream & stream;
};

class BinaryWriter {
public:
	BinaryWriter() = delete;
	BinaryWriter(ostream&);
	virtual ~BinaryWriter() = default;

	template<typename Type>
	void write(Type const&);
private:
	ostream & stream;
};

template<typename Type>
inline void BinaryWriter::write(Type const & value)
{
	static_assert("Type is not supported for the write operation");
	throw;
}

template<typename Type>
inline Type BinaryReader::read()
{
	static_assert("Type is not supported for the read operation");
	throw;
}
