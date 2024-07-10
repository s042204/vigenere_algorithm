#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Įvesties teksto ir rakto patikrinimas
int validate_input(const char* text, const char* key) {
    if (strlen(text) == 0 || strlen(key) == 0) {
        printf("Text and key must not be empty.\n");
        return 0;
    }
    for (int i = 0; i < strlen(text); i++) {
        if (!isalpha(text[i])) {
            printf("Text must contain only letters.\n");
            return 0;
        }
    }
    for (int i = 0; i < strlen(key); i++) {
        if (!isalpha(key[i])) {
            printf("Key must contain only letters.\n");
            return 0;
        }
    }
    return 1;
}

// Teksto šifravimas Vigenere algoritmu
char* vigenere_encrypt(const char* text, const char* key) {
    int text_length = strlen(text);
    int key_length = strlen(key);
    char* encrypted = (char*)malloc((text_length + 1) * sizeof(char));

    for (int i = 0, j = 0; i < text_length; i++) {
        char c = text[i];
        if (isupper(c)) {
            encrypted[i] = (c + key[j % key_length] - 2 * 'A') % 26 + 'A';
            j++;
        } else if (islower(c)) {
            encrypted[i] = (c + key[j % key_length] - 2 * 'a') % 26 + 'a';
            j++;
        } else {
            encrypted[i] = c; // Ne raidiniai simboliai lieka nepakitę
        }
    }
    encrypted[text_length] = '\0';
    return encrypted;
}

// Teksto dešifravimas Vigenere algoritmu
char* vigenere_decrypt(const char* text, const char* key) {
    int text_length = strlen(text);
    int key_length = strlen(key);
    char* decrypted = (char*)malloc((text_length + 1) * sizeof(char));

    for (int i = 0, j = 0; i < text_length; i++) {
        char c = text[i];
        if (isupper(c)) {
            decrypted[i] = (c - key[j % key_length] + 26) % 26 + 'A';
            j++;
        } else if (islower(c)) {
            decrypted[i] = (c - key[j % key_length] + 26) % 26 + 'a';
            j++;
        } else {
            decrypted[i] = c; // Ne raidiniai simboliai lieka nepakitę
        }
    }
    decrypted[text_length] = '\0';
    return decrypted;
}

int main() {
    char text[1000];
    char key[100];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Pašalinamas naujos eilutės simbolis

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Pašalinamas naujos eilutės simbolis

    // Įvesties patikrinimas
    if (!validate_input(text, key)) {
        return 1; // Išeinama, jei patikrinimas nepavyksta
    }

    // Teksto šifravimas
    char* encrypted = vigenere_encrypt(text, key);
    printf("Encrypted text: %s\n", encrypted);

    // Teksto dešifravimas
    char* decrypted = vigenere_decrypt(encrypted, key);
    printf("Decrypted text: %s\n", decrypted);

    // Atlaisvinama atmintis
    free(encrypted);
    free(decrypted);

    return 0;
}