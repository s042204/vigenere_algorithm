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
    return 1;
}

// Tik raidžių ir skaičių šifravimas Vigenere algoritmu
char* vigenere_encrypt_letters_numbers(const char* text, const char* key) {
    int text_length = strlen(text);
    int key_length = strlen(key);
    char* encrypted = (char*)malloc((text_length + 1) * sizeof(char));

    for (int i = 0, j = 0; i < text_length; i++) {
        char c = text[i];
        if (isalpha(c)) {
            if (isupper(c)) {
                encrypted[i] = (c + key[j % key_length] - 2 * 'A') % 26 + 'A';
            } else {
                encrypted[i] = (c + key[j % key_length] - 2 * 'a') % 26 + 'a';
            }
            j++;
        } else if (isdigit(c)) {
            encrypted[i] = (c + key[j % key_length] - 2 * '0') % 10 + '0';
            j++;
        } else {
            encrypted[i] = c; // Ne raidės ir skaičiai lieka nepakitę
        }
    }
    encrypted[text_length] = '\0';
    return encrypted;
}

// Tik raidžių ir skaičių dešifravimas Vigenere algoritmu
char* vigenere_decrypt_letters_numbers(const char* text, const char* key) {
    int text_length = strlen(text);
    int key_length = strlen(key);
    char* decrypted = (char*)malloc((text_length + 1) * sizeof(char));

    for (int i = 0, j = 0; i < text_length; i++) {
        char c = text[i];
        if (isalpha(c)) {
            if (isupper(c)) {
                decrypted[i] = (c - key[j % key_length] + 26) % 26 + 'A';
            } else {
                decrypted[i] = (c - key[j % key_length] + 26) % 26 + 'a';
            }
            j++;
        } else if (isdigit(c)) {
            decrypted[i] = (c - key[j % key_length] + 10) % 10 + '0';
            j++;
        } else {
            decrypted[i] = c; // Ne raidės ir skaičiai lieka nepakitę
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

    // Teksto šifravimas tik raidėms ir skaičiams
    char* encrypted = vigenere_encrypt_letters_numbers(text, key);
    printf("Encrypted text: %s\n", encrypted);

    // Teksto dešifravimas tik raidėms ir skaičiams
    char* decrypted = vigenere_decrypt_letters_numbers(encrypted, key);
    printf("Decrypted text: %s\n", decrypted);

    // Atlaisvinama atmintis
    free(encrypted);
    free(decrypted);

    return 0;
}