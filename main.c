#include <stdio.h>
#include <string.h>

int main() {
    char text[1000];
    char key[100];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove the newline character

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove the newline character

    // Print the inputs to verify
    printf("Text: %s\n", text);
    printf("Key: %s\n", key);

    return 0;
}