#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int TRUE = 1;
const int FALSE = 0;

const char *vowels = "aeiouy";
const char *consonants = "bcdfghjklmnpqrstvwxz";
const char *numbers = "0123456789";
const char *specials = "!@#$%^&*-+?";

unsigned char *generate_password(int length, int capitalized, int specialized, int numbered, int seed) {
    unsigned char *pwd = calloc(length + 1, sizeof(char));
    int sign = TRUE;
    srand(seed);

    for (int i = 0; i < length; i++) {
        pwd[i] = (sign) ? consonants[rand() % strlen(consonants)] : vowels[rand() % strlen(vowels)];
        sign = (sign) ? FALSE : TRUE;
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
    int length = 10;
    int capitalized = FALSE;
    int specialized = FALSE;
    int numbered = FALSE;
    int num = 1;

    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        printf("Samurai: Human Readable Password Generator\n\n");
        printf("Usage: samurai [-h] [-x <int>] [-l <int>] [-c] [-s] [-n]\n\n");
        printf("-h:\t\t Print this help page.\n");
        printf("-x <int>:\t Set the amount of generated passwords.\n");
        printf("-l <int>:\t Set the length of the generated password.\n");
        printf("-c:\t\t Enable capitalization of the password.\n");
        printf("-s:\t\t Add a special character to the password.\n");
        printf("-h:\t\t Add numbers to the password.\n");
        exit(EXIT_SUCCESS);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) capitalized = TRUE;
        else if (strcmp(argv[i], "-s") == 0) specialized = TRUE;
        else if (strcmp(argv[i], "-n") == 0) numbered = TRUE;
        else if (strcmp(argv[i], "-l") == 0) {
            i++;
            if (sscanf(argv[i], "%d", &length) == 0) {
                printf("\"%s\" is not an integer value.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-x") == 0) {
            i++;
            if (sscanf(argv[i], "%d", &num) == 0) {
                printf("\"%s\" is not an integer value.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else {
            printf("\"%s\" is not a valid flag. Run `samurai -h` for usage information.\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num; i++) {
        unsigned char *pwd = generate_password(length, capitalized, specialized, numbered, clock());
        printf("%s\n", pwd);
        free(pwd);
    }

    exit(EXIT_SUCCESS);
}
