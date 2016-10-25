#include "reader.h"

bool Directory::NextString(std::shared_ptr<In> stream, std::string& r) {
	char buf;
	size_t read;

	do {
		if (!stream->read(&buf, 1, read) || read != 1) {
			return false;
		}
		r += buf;
	} while (buf != '\0');

	return true;
}

bool Directory::NextOff(std::shared_ptr<In> stream, size_t& r) {
	size_t buf;
	size_t read;

	if (!stream->read((char*)&buf, sizeof(size_t), read) || read != sizeof(size_t)) {
		return false;
	}

	r = buf;

	return true;
}

bool Directory::From(std::shared_ptr<In> stream, Directory& dir) {
	unsigned int MAGIC_BUFFER;
	size_t read;
	size_t c_off;

	if (!stream->read((char*) &MAGIC_BUFFER, sizeof(MAGIC_BUFFER), read)) {
		return false;
	}

	//Magic mismatch
	if (MAGIC_BUFFER != READER_MAGIC) {
		return false;
	}

	while (true) {

		if (!stream->read((char*) &MAGIC_BUFFER, sizeof(MAGIC_BUFFER), read)) {
			return false;
		}

		if (MAGIC_BUFFER == READER_LAST) {
			break;
		} else if (MAGIC_BUFFER != READER_NEXT) {
			//Magic mismatch
			return false;
		}

		std::string name;
		size_t size;

		if (!Directory::NextString(stream, name)) {
			return false;
		}

		if (!Directory::NextOff(stream, size)) {
			return false;
		}

		Item r = Item(c_off, size);

		//Push item

		c_off += size;

	}
}