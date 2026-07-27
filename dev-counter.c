#include <ctype.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char** argv) {

	if (argc < 2) {
		fprintf(stderr, "error: invalid arguments\n");
		return 1;
	} 

	FILE* target_file = NULL;
	if ((target_file = fopen(argv[1], "r")) == NULL) {
		perror("error");
		return 1;
	}

	int char_count  = 0;
	int newl_count  = 0;
	int non_space   = 0;
	int line_count  = 0;
	int letters[26] = {};

	int buffer = fgetc(target_file);

	if (buffer != EOF) {

		while ( 1 ) {
			char_count++;

			if (buffer >= 'a' && buffer <= 'z') {

				letters[buffer - 'a']++;
			}

			if (buffer == '\n') newl_count++, line_count++;
			if (buffer == ' ') non_space++;

			if ((buffer = fgetc(target_file)) == EOF) {
				line_count++;
				break;
			}
		}
	}

	printf("name: '%s'\n\n", argv[1]);

	printf("char: %d\n", char_count);
	printf("newl: %d\n", newl_count);
	printf("spac: %d\n", non_space);
	printf("line: %d\n\n", line_count);

	for (int i=0; i < 26; i++) {

		if (letters[i])
			printf("%c: %d\n", 'a' + i, letters[i]);
	}

	fclose(target_file);
}