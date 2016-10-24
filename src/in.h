#ifndef _IN_DEF_H_
#define _IN_DEF_H_
#include <stdio.h>

class In {
public:
	virtual bool read(char* dest, size_t max_size, size_t& read) = 0;
	virtual void close() = 0;
};

class FIn {
private:
	FILE* in;

public:
	FIn(char const* file);
	~FIn();

	virtual bool read(char* dest, size_t max_size, size_t& read);
	void close();
};

#endif //_IN_DEF_H_