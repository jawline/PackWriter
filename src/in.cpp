#include "in.h"

StringIn::StringIn(std::string const& ldata) {
	data = ldata;
	pos = 0;
}

bool StringIn::read(char* dest, size_t max_size, size_t& read) {

	read = 0;

	while (max_size > 0 && pos < data.size()) {
		*dest = data.at(pos);
		dest++;
		pos++;
		max_size -= 1;
		read += 1;
	}

	return true;
}

void StringIn::close() {
	pos = data.size();
}

FIn::FIn(std::string const& file) {
	in = fopen(file.c_str(), "rb");
	max_read_limit = false;
}

FIn::FIn(std::string const& file, size_t start) {
	in = fopen(file.c_str(), "rb");
	fseek(in, start, SEEK_SET);
}

FIn::FIn(std::string const& file, size_t start, size_t max_read) {
	in = fopen(file.c_str(), "rb");
	fseek(in, start, SEEK_SET);
	max_read_limit = true;
	this->max_read = max_read;
}

FIn::~FIn() {
	close();
}

bool FIn::read(char* dest, size_t max_size, size_t& read) {
	
	if (!in) {
		return false;
	}

	if (max_read_limit && max_size > max_read) {
		max_size = max_read;
	}

	read = fread(dest, sizeof(char), max_size, in);

	max_read -= read;

	return read != max_size ? feof(in) : true;
}

void FIn::close() {
	if (in) {
		fclose(in);
		in = nullptr;
	}
}