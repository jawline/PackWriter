#include "single.h"

bool SingleOut(PackWriter& pack, std::shared_ptr<Out> outf) {
	return pack.Finalize(outf, outf);
}

std::shared_ptr<BufferedFileReader> SingleInFile(std::string const& filename) {

	//Code to find the header in a single serialized file
	FILE* t_reader = fopen(filename.c_str(), "rb");

	if (!t_reader) {
		//Failed to open file
		return nullptr;
	}

	if (fseek(t_reader, -sizeof(size_t), SEEK_END)) {
		//Failed to fseek
		return nullptr;
	}

	size_t h_size;

	if (fread(&h_size, sizeof(size_t), 1, t_reader) != 1) {
		//Failed to read
		return nullptr;
	}

	long int h_start = -sizeof(size_t) - h_size;

	if (fseek(t_reader, h_start, SEEK_END)) {
		//Failed to fseek to header
		return nullptr;
	}

	size_t start_h = ftell(t_reader);

	//Now we know start_h is start of header (Or bogus value that bad magic will pickup)
	Directory resulting_dir;

	//If dir files to parse, return nullptr
	if (!Directory::From(std::shared_ptr<In>(new FIn(filename, start_h)), resulting_dir)) {
		return nullptr;
	}

	return std::shared_ptr<BufferedFileReader>(new BufferedFileReader(filename, resulting_dir));
}