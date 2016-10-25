#ifndef _PACK_DEF_H_
#define _PACK_DEF_H_
#include "In.h"
#include "Out.h"
#include <iostream>
#include <vector>
#include <memory>
#include <utility>

class PackWriter {
private: 
	std::vector<std::pair<std::string, std::shared_ptr<In>>> pairs;

public:
	void AddStream(std::string const& name, std::shared_ptr<In> const& stream);
	bool Finalize(std::shared_ptr<Out> const& data_out, std::shared_ptr<Out> const& directory_out);
};

#endif