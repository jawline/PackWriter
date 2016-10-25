#include <stdio.h>
#include <string.h>
#include "single.h"

#define CHECK_TWO() if (i+2 >= argc) { return 1; }

int main(int argc, char** argv) {

	if (argc < 3) {
		printf("Usage Example: %s pack -l name infile -l name infile -s name string outfile\n", argv[0]);
		printf("Usage Example: %s read file element\n", argv[0]);
		return 1;
	}

	printf("librepack test\n");

	if (strcmp(argv[1], "pack") == 0) {
		PackWriter p;

		for (unsigned int i = 2; i < argc - 1; i++) {
			if (strcmp(argv[i], "-l") == 0) {
				CHECK_TWO();
				p.AddStream(argv[i+1], std::shared_ptr<In>(new FIn(argv[i+2])));
				i += 2;
			} else if (strcmp(argv[i], "-s") == 0) {
				CHECK_TWO();
				p.AddStream(argv[i+1], std::shared_ptr<In>(new StringIn(argv[i+2])));
				i += 2;
			} else {
				printf("Unexpected %s\n", argv[i]);
				return 1;
			}
		}
		std::shared_ptr<Out> g_out = std::shared_ptr<Out>(new FOut(argv[argc - 1]));

		if (!SingleOut(p, g_out)) {
			printf("Error could not finalize properly\n");
		}

		g_out->close();


		printf("Out file %s\n", argv[argc - 1]);
	} else if (strcmp(argv[1], "read") == 0) {

		if (argc < 4) {
			printf("Usage read %s read file item", argv[0]);
			return 1;
		}

		char const* target = argv[2];
		char const* el = argv[3];
		std::shared_ptr<BufferedFileReader> reader = SingleInFile(target);

		if (!reader) {
			printf("Could not open reader\n");
			return 1;
		}

		auto stream = reader->GetStream(el);

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
}