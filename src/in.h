#ifndef _IN_DEF_H_
#define _IN_DEF_H_
#include <iostream>
#include <stdio.h>

class In {
public:
	virtual bool read(char* dest, size_t max_size, size_t& read) = 0;
	virtual void close() = 0;
};

class StringIn: public In {
private:
	std::string data;
	size_t pos;

public:
	StringIn(std::string const& data);

	virtual bool read(char* dest, size_t max_size, size_t& read);
	virtual void close();
};

class FIn: public In {
private:
	FILE* in;

public:
	FIn(char const* file);
	~FIn();

	virtual bool read(char* dest, size_t max_size, size_t& read);
	void close();
};

#endif //_IN_DEF_H_