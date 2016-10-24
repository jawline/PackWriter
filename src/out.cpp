#include "out.h"

FOut::FOut(char const* file) {
	out = fopen(file, "wb");
}

FOut::~FOut() {
	close();
}

bool FOut::write(char const* data, size_t size) {
	
	if (!out) {
		return false;
	}

	return fwrite(data, sizeof(char), size, out) == size;
}

void FOut::close() {
	if (out) {
		fclose(out);
		out = nullptr;
	}
}