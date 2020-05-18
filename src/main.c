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

unsigned char *generate_password(int length, int capitalized, int specialized, int number_amount, int seed) {
    unsigned char *pwd = calloc(length + 1, sizeof(char));
    int sign = TRUE;
    srand(seed);

    for (int i = 0; i < length; i++) {
        pwd[i] = (sign) ? consonants[rand() % strlen(consonants)] : vowels[rand() % strlen(vowels)];
        sign = (sign) ? FALSE : TRUE;
    }

    for (int i = 0; i < number_amount; i++) {
        pwd[length - 1 - i] = numbers[rand() % strlen(numbers)];
    }

    if (capitalized) pwd[0] = toupper(pwd[0]);
    if (specialized) pwd[length - 1 - number_amount] = specials[rand() % strlen(specials)];

    return pwd;
}

int main(int argc, char **argv) {
    int length = 12;
    int capitalized = FALSE;
    int specialized = FALSE;
    int number_amount = 0;
    int password_amount = 1;

    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        printf("Samurai: Human Readable Password Generator\n\n");
        printf("Usage: samurai [-h] [-x <int>] [-l <int>] [-c] [-s] [-n]\n\n");
        printf("-h:\t\t Print this help page.\n");
        printf("-x <int>:\t Set the amount of generated passwords. Defaults to 1.\n");
        printf("-l <int>:\t Set the length of the generated passwords. Defaults to 12.\n");
        printf("-n <int>:\t Set the amount of numbers in the generated passwords. Defaults to 0.\n");
        printf("-c:\t\t Enable capitalization of the generated passwords.\n");
        printf("-s:\t\t Add a special character to the generated passwords.\n");
        exit(EXIT_SUCCESS);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) capitalized = TRUE;
        else if (strcmp(argv[i], "-s") == 0) specialized = TRUE;
        else if (strcmp(argv[i], "-n") == 0) {
            i++;
            if (sscanf(argv[i], "%d", &number_amount) == 0) {
                printf("\"%s\" is not an integer value.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-l") == 0) {
            i++;
            if (sscanf(argv[i], "%d", &length) == 0) {
                printf("\"%s\" is not an integer value.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-x") == 0) {
            i++;
            if (sscanf(argv[i], "%d", &password_amount) == 0) {
                printf("\"%s\" is not an integer value.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else {
            printf("\"%s\" is not a valid flag. Run `samurai -h` for usage information.\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < password_amount; i++) {
        unsigned char *pwd = generate_password(length, capitalized, specialized, number_amount, clock());
        printf("%s\n", pwd);
        free(pwd);
    }

    exit(EXIT_SUCCESS);
}
