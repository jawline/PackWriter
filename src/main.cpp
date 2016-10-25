#include <stdio.h>
#include "writer.h"
#include "reader.h"

int main(int argc, char** argv) {
	printf("librepack test\n");

	std::shared_ptr<In> t_str = std::shared_ptr<In>(new StringIn("Hello World"));
	std::shared_ptr<In> t_str2 = std::shared_ptr<In>(new StringIn("Other Data"));
	std::shared_ptr<In> t_str3 = std::shared_ptr<In>(new StringIn("Third and craziest string"));

	PackWriter p;
	p.AddStream("t1", t_str);
	p.AddStream("t2", t_str2);
	p.AddStream("t3", t_str3);

	std::shared_ptr<Out> g_out = std::shared_ptr<Out>(new FOut("./test.pack"));
	std::shared_ptr<Out> g_out_dir = std::shared_ptr<Out>(new FOut("./test.pack.dir"));

	if (!p.Finalize(g_out, g_out_dir)) {
		printf("Error could not finalize properly\n");
	}

	g_out->close();
	g_out_dir->close();

	std::shared_ptr<In> g_in_dir = std::shared_ptr<In>(new FIn("./test.pack.dir"));

	Directory dir;

	if (!Directory::From(g_in_dir, dir)) {
		printf("Error, could not read directory\n");
	}

	Item t_str_off;

	if (!dir.Get("t1", t_str_off)) {
		printf("Could not find t1\n");
	}

	printf("t1 data %zu %zu\n", t_str_off.start, t_str_off.size);
}