#include <exception>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

#define RESET 	"\033[0m"

#define BRIGHT 	"\033[1m"

#define RED 	"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW 	"\033[33m"
#define BLUE 	"\033[34m"
#define MAGENTA "\033[35m"
#define CYAN	"\033[36m"

namespace fs = std::filesystem;

void output_lists(fs::path& path) {
	std::vector<fs::directory_entry> entries;

	for (const auto& entry : fs::directory_iterator(path)) {
		
		entries.push_back(entry);
	}

	std::sort(
		entries.begin(),
		entries.end(),
		[](const auto& a, const auto& b){
			return (
				a.path().filename().string()
				<
				b.path().filename().string()
			);
		}
	);

	for (const auto& entry : entries) {
		char sign = ' ';

		if (entry.is_directory()) {
			std::cout << BRIGHT << BLUE;
			sign = '/';
		}

		else if (entry.is_fifo()) {
			std::cout << YELLOW;
			sign = '|';
		}

		else if (entry.is_symlink()) {
			std::cout << BRIGHT << CYAN;
			sign = '@';
		}

		else if (entry.is_regular_file()) {
			if (entry.is_socket()) {
				std::cout << BRIGHT << MAGENTA;
			}

			else if (entry.is_block_file() || entry.is_character_file()) {
				std::cout << BRIGHT << YELLOW;
			}

			else if (entry.is_other()) {
				std::cout << RED;
			}

			sign = '\0';

			if ((entry.status().permissions() & (
				fs::perms::owner_exec |
				fs::perms::group_exec |
				fs::perms::others_exec
				)) != fs::perms::none
			) {
				std::cout << BRIGHT << GREEN;
				sign = '*';
			}
		}

		std::cout 
			<< entry.path()
					.filename()
					.string();

		std::cout << RESET;
		std::cout << sign << "  ";
	}
	std::cout << std::endl;
}

int main(int argc, char **argv) {
	int status = 0;

	try {
		std::vector<fs::path> list;
		
		for (int i=(argc > 1); i < argc; i++) {
			std::string_view temp = (
				i
				?
				argv[i]
				:
				"."
			);

			if (!fs::exists(temp)) {
				std::cerr 
					<< argv[0]
					<< ": cannot access '" 
					<< argv[i]
					<< "': No such file or directory"
					<< std::endl;
				
				status = 2;
			}
	
			else {
				list.push_back(temp);
			}
		}
	
		for (auto& ls : list) {
			if (argc > 2) {
				std::cout << std::endl;
				std::cout << ls.c_str() << ":\n";
			}
			output_lists(ls);
		}
	} 

	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	catch (...) {
		std::cerr << 0[argv] << ": error" << std::endl;
	}

	return status;
}