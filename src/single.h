#ifndef _SINGLE_REPACK_DEF_H_
#define _SINGLE_REPACK_DEF_H_
#include "writer.h"
#include "reader.h"

bool SingleOut(PackWriter& pack, std::shared_ptr<Out> outf);
std::shared_ptr<BufferedFileReader> SingleInFile(std::string const& filename);

#endif //_SINGLE_REPACK_DEF_H_