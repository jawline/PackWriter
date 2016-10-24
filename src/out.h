#ifndef OUT_DEF_H_
#define OUT_DEF_H_
#include <stdio.h>

class Out {
public:
	virtual bool write(char const* data, size_t amount) = 0;
	virtual void close() = 0;
};

class FOut: public Out {
private:
	FILE* out;

public:
	FOut(char const* path);
	virtual ~FOut();
	bool write(char const* data, size_t size);
	void close();
};

#endif //OUT_DEF_H_