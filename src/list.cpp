#include <cstring>
#include <iostream>
#include <filesystem>

#define RESET 	"\033[0m"

#define BRIGHT 	"\033[1m"

#define RED 	"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW 	"\033[33m"
#define BLUE 	"\033[34m"
#define MAGENTA "\033[35m"
#define CYAN	"\033[36m"

namespace fs = std::filesystem;

bool is_image(const std::string& name) {
	const char* img_ext[] = {
		".png", ".jpeg", ".gif",
		".jpg", ".webp", ".avif",
		".svg", ".eps",
	};

	for (auto& e : img_ext)
		if (name == e)
			return true;

	return false;
}

int main(int argc, char **argv) {
	fs::path current = ".";

	for (const auto& entry : fs::directory_iterator(current)) {
		auto item = entry.path().filename();

		if (entry.is_directory()) {
			std::cout << BRIGHT << BLUE;
			item.concat(RESET "/");
		}

		else if (entry.is_symlink()) {
			std::cout << BRIGHT << CYAN;
			item.concat(RESET "@");
		}

		else if (entry.is_fifo()) {
			std::cout << YELLOW;
			item.concat(RESET "|");
		}

		else if (entry.is_socket()) {
			std::cout << BRIGHT << YELLOW;
			item.concat(RESET);
		}

		else if (entry.is_regular_file()) {
			if (is_image(item.extension().c_str())) {
				std::cout << RED;
				item.concat(RESET "^");
			}

			else if (false) {

			}
		}

		std::cout << item.c_str() << "  ";
	}
	std::cout << std::endl;

	return 0;
}