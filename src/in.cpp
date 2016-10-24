#include "in.h"

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

	return read != max_size ? ferror(in) : true;
}

void FIn::close() {
	if (in) {
		fclose(in);
		in = nullptr;
	}
}