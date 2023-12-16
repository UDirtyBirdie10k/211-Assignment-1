#include <stdio.h>
#include <ctype.h>

void rot13(char* input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            char base = isupper(input[i]) ? 'A' : 'a';
            input[i] = ((input[i] - base + 13) % 26) + base;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    
    char* input = argv[1];
    rot13(input);
    printf("%s\n", input);
    return 0;
}