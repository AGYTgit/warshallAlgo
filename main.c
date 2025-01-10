#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: %s (data file name, e.g. data.txt) (max width) (max height)\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    char* endPtr;
    size_t bufferSizeWidth = strtol(argv[2], &endPtr, 10);
    if (*endPtr != '\0' || argv[2][0] == '-') {
        printf("Invalid max width: %s, expected unsigned int\n", argv[2]);
        return 1;
    }
    size_t bufferSizeHeight = strtol(argv[3], &endPtr, 10);
    if (*endPtr != '\0' || argv[3][0] == '-') {
        printf("Invalid max height: %s, expected unsigned int\n", argv[3]);
        return 1;
    }
    char** buffer = malloc(bufferSizeHeight * sizeof(char*));
    if (buffer == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    for (int i = 0; i < bufferSizeHeight; i++) {
        buffer[i] = malloc(bufferSizeWidth * sizeof(char));

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

        if (lineIndex >= bufferSizeHeight) {
            printf("Height is too small\n");
            return 1;
        } else if (charIndex >= bufferSizeWidth + 1) {
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

    for (int i = 0; i < lineIndex; i++) {
        for (int j = 0; j < bufferSizeWidth; j++) {
            printf("%c", buffer[i][j]);
            if (buffer[i][j] == '\n') {
                break;
            }
        }
        printf("\n");
    }

    // warshall algorithm here

    for (int i = 0; i < lineIndex; i++) {
        for (int j = 0; j < bufferSizeWidth; j++) {
            printf("%c", buffer[i][j]);
            if (buffer[i][j] == '\n') {
                break;
            }
        }
        printf("\n");
    }

    fclose(file);
}
