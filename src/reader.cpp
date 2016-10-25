#include "reader.h"

bool Directory::NextString(std::shared_ptr<In> stream, std::string& r) {
	char buf;
	size_t read;

	do {

		if (!stream->read(&buf, 1, read) || read != 1) {
			return false;
		}

		//Dont add the null terminator
		if (buf) {
			r += buf;
		}

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

bool Directory::Get(std::string const& name, Item& item) const {
	for (unsigned int i = 0; i < items.size(); i++) {
		printf("Check %s\n", items[i].first.c_str());
		if (items[i].first == name) {
			item = items[i].second;
			return true;
		}
	}

	return false;
}

bool Directory::From(std::shared_ptr<In> stream, Directory& dir) {
	unsigned int MAGIC_BUFFER;
	size_t read;
	size_t c_off = 0;

	if (!stream->read((char*) &MAGIC_BUFFER, sizeof(MAGIC_BUFFER), read) || read != sizeof(MAGIC_BUFFER)) {
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

		dir.items.push_back(std::pair<std::string, Item>(name, Item(c_off, size)));

		c_off += size;
	}

	return true;
}

BufferedFileReader::BufferedFileReader(std::string const& file, Directory dir) {
	_dataFile = file;
	_dir = dir;
}

std::shared_ptr<In> BufferedFileReader::GetStream(std::string const& file) {

	Item found;

	if (!_dir.Get(file, found)) {
		return nullptr;
	} else {
		return std::shared_ptr<In>(new FIn(_dataFile, found.start, found.size));
	}
}