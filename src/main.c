#include <stdlib.h>
#include <stdio.h>

const int true = 1;
const int false = 0;

const char *vowels = "aeiouy";
const char *consonants = "bcdfghjklmnpqrstvwxz";
const char *specials = "!@#$%^&*-+?";

unsigned char *generate_password(int length, int capitalized, int specialized) {
    unsigned char* pwd = calloc(length + 1, sizeof(char));

    int sign = true;
    for (int i = 0; i < length; i++) {
        pwd[i] = (sign) ? consonants[0] : vowels[0];
        sign = (sign) ? false : true;
    }

    return pwd;
}

int main(int argc, char **argv) {
    unsigned char *pwd = generate_password(12, true, true);

    printf("%s\n", pwd);

    free(pwd);

    exit(EXIT_SUCCESS);
}
