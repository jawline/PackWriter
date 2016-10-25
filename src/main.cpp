#include <stdio.h>
#include "single.h"

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

	if (!SingleOut(p, g_out)) {
		printf("Error could not finalize properly\n");
	}

	g_out->close();

	std::shared_ptr<BufferedFileReader> reader = SingleInFile("./test.pack");

	if (!reader) {
		printf("Could not open reader\n");
		return 1;
	}

	auto stream = reader->GetStream("t3");

	if (stream != nullptr) {
		char buf;
		size_t read;

		std::string str;

		while (stream->read(&buf, 1, read) && read == 1) {
			str += buf;
		}

		printf("%s\n", str.c_str());

		stream->close();
	} else {
		printf("Could not get a t1 stream\n");
	}
}