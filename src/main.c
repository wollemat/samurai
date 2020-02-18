#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int true = 1;
const int false = 0;

const char *vowels = "aeiouy";
const char *consonants = "bcdfghjklmnpqrstvwxz";
const char *numbers = "0123456789";
const char *specials = "!@#$%^&*-+?";

unsigned char *generate_password(int length, int capitalized, int specialized, int numbered, time_t seed) {
    unsigned char *pwd = calloc(length + 1, sizeof(char));
    int sign = true;
    srand(time(&seed));

    for (int i = 0; i < length; i++) {
        pwd[i] = (sign) ? consonants[rand() % strlen(consonants)] : vowels[rand() % strlen(vowels)];
        sign = (sign) ? false : true;
    }

    if (capitalized) pwd[0] = toupper(pwd[0]);

    if (numbered) {
        pwd[length - 1] = numbers[rand() % strlen(numbers)];
        pwd[length - 2] = numbers[rand() % strlen(numbers)];

        if (specialized) pwd[length - 3] = specials[rand() % strlen(specials)];
    } else if (specialized) pwd[length - 1] = specials[rand() % strlen(specials)];

    return pwd;
}

int main(int argc, char **argv) {
    unsigned char *pwd = generate_password(10, true, true, true, time(0));

    printf("%s\n", pwd);

    free(pwd);

    exit(EXIT_SUCCESS);
}
