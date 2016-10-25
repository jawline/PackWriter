#ifndef _READER_DEF_H_
#define _READER_DEF_H_
#include "shared.h"
#include "in.h"
#include <memory>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>

class Item {
public:

	Item() {}
	
	Item(size_t start, size_t size) {
		this->start = start;
		this->size = size;
	}

	size_t start;
	size_t size;
};

class Directory {
private:
	static bool NextString(std::shared_ptr<In> stream, std::string& r);
	static bool NextOff(std::shared_ptr<In> stream, size_t& r);

public:
	std::vector<std::pair<std::string, Item>> items;

	bool Get(std::string const& name, Item& i) const;

	static bool From(std::shared_ptr<In> stream, Directory& result);
};

class BufferedFileReader {
private:
	Directory _dir;
	std::string _dataFile;

public:
	BufferedFileReader(std::string const& file, Directory dir);
	std::shared_ptr<In> GetStream(std::string const& file);
};

#endif //_READER_DEF_H_