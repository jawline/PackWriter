#include "writer.h"
#include "shared.h"

void PackWriter::AddStream(std::string const& name, std::shared_ptr<In> const& stream) {
	pairs.push_back(std::pair<std::string, std::shared_ptr<In>>(name, stream));
}

bool PackWriter::Finalize(std::shared_ptr<Out> const& data_out, std::shared_ptr<Out> const& directory_out) {
	std::vector<std::pair<std::string, size_t>> directory;

	char buf[512];

	for (unsigned int i = 0; i < pairs.size(); i++) {
		size_t size = 0;
		size_t read;

		do {
			if (!pairs[i].second->read(buf, 512, read)) {
				return false;
			}

			if (!data_out->write(buf, read)) {
				return false;
			}

			size += read;
		} while (read > 0);

		directory.push_back(std::pair<std::string, size_t>(pairs[i].first, size));
	}


	//Write the directory
	//TODO: Split
	size_t dir_size = 0;

	if (!directory_out->write((char*)&READER_MAGIC, sizeof(READER_MAGIC))) {
		return false;
	}

	dir_size += sizeof(READER_MAGIC);
	
	for (unsigned int i = 0; i < directory.size(); i++) {
		
		if (!directory_out->write((char*)&READER_NEXT, sizeof(READER_NEXT))) {
			return false;
		}

		dir_size += sizeof(READER_NEXT);

		//+1 for null terminator
		if (!directory_out->write(directory[i].first.c_str(), directory[i].first.size() + 1)) {
			return false;
		}

		dir_size += directory[i].first.size() + 1;

		if (!directory_out->write((char*) &directory[i].second, sizeof(size_t))) {
			return false;
		}

		dir_size += sizeof(size_t);
	}

	if (!directory_out->write((char*)&READER_LAST, sizeof(READER_LAST))) {
		return false;
	}

	dir_size += READER_LAST;


	if (!directory_out->write((char*)&dir_size, sizeof(size_t))) {
		return false;
	}

	return true;
}