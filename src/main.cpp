#include <stdio.h>
#include "pack.h"

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

	if (!p.Finalize(g_out, g_out)) {
		printf("Error could not finalize properly\n");
	}
}