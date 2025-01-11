#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s (data file name, e.g. data.txt) (max size)\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    char* endPtr;
    size_t bufferSize = strtol(argv[2], &endPtr, 10);
    if (*endPtr != '\0' || argv[2][0] == '-') {
        printf("Invalid max size: %s, expected unsigned int\n", argv[2]);
        return 1;
    }
    char** buffer = malloc(bufferSize * sizeof(char*));
    if (buffer == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = malloc(bufferSize * sizeof(char));

        if (buffer[i] == NULL) {
            printf("Memory allocation failed");
            return 1;
        }
    }

    size_t lineIndex = 0;
    size_t charIndex = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ') {
            continue;
        }

        if (lineIndex >= bufferSize) {
            printf("Height is too small\n");
            return 1;
        } else if (charIndex >= bufferSize + 1) {
            printf("Width is too small\n");
            return 1;
        }

        if (ch == '\n') {
            buffer[lineIndex++][charIndex] = '\0';
            charIndex = 0;
            continue;
        }

        buffer[lineIndex][charIndex++] = (char)ch;
    }

    // warshall algorithm here
    for (int k = 0; k < bufferSize; k++) {
        for (int i = 0; i < bufferSize; i++) {
            for (int j = 0; j < bufferSize; j++) {
                if (buffer[i][k] == '1' && buffer[k][j] == '1') {
                    buffer[i][j] = '1';
                }
            }
        }
    }

    for (int i = 0; i < lineIndex; i++) {
        for (int j = 0; j < bufferSize; j++) {
            printf("%c ", buffer[i][j]);
            if (buffer[i][j] == '\n') {
                break;
            }
        }
        printf("\n");
    }

    fclose(file);
}
