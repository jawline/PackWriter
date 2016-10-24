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

FIn::FIn(char const* file) {
	in = fopen(file, "rb");
}

FIn::~FIn() {
	close();
}

bool FIn::read(char* dest, size_t max_size, size_t& read) {
	
	if (!in) {
		return false;
	}

	read = fread(dest, sizeof(char), max_size, in);

	return read != max_size ? feof(in) : true;
}

void FIn::close() {
	if (in) {
		fclose(in);
		in = nullptr;
	}
}