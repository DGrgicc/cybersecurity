#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

void generiraj_izvjestaj() {
	printf("Generiram sigurnosni izvještaj...\n");
	FILE* file = fopen("security_log.txt", "r");
	if (!file) {
		printf("Nije moguće otvoriti datoteku za čitanje.\n");
		return;
	}

	char line[256];
	while (fgets(line, sizeof(line), file)) {
		printf("%s", line);
	}

	fclose(file);
}

void log_event(const char* event) {
	FILE* file = fopen("security_log.txt", "a"); //10.
	if (!file) {
		printf("Nije moguće otvoriti datoteku za logiranje.\n");
		return;
	}

	time_t now = time(NULL);
	fprintf(file, "[%s] %s\n", ctime(&now), event);
	fclose(file);
}