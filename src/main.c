#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *version = "V1.0.4";

const int TRUE = 1;
const int FALSE = 0;

const char *vowels = "aeiouy";
const char *consonants = "bcdfghjklmnpqrstvwxz";
const char *numbers = "0123456789";
const char *specials = "!@#$%^&*-+?";

unsigned char *generate_password(int length, int capitalized, int specialized, int number_amount) {
    unsigned char *pwd = calloc(length + 1, sizeof(char));
    int sign = TRUE;

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
    int suffix = 2;
    int bulk = 10;
    int pump = 65536;
    int seed = clock();

    if (argc > 1 && strcmp(argv[1], "-v") == 0) {
        printf("This is version %s\n", version);
        exit(EXIT_SUCCESS);
    }

    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        printf("Samurai: The Human Readable Password Generator\n\n");

        printf("Usage: samurai -v | -h | [[-s <int>] [-p <int>] [-b <int>] [-l <int>] [-n <int>] -c -s]\n\n");

        printf("-v, --version\n\tPrint the program's version.\n\n");
        printf("-h, --help\n\tPrint this help message.\n\n");

        printf("-s, --seed\n\tSet the seed used for random number generation. Defaults to the amount of clock ticks since program start.\n\n");
        printf("-p, --pump\n\tSet how many times the random number generator is iterated over before generating each password. Defaults to %d\n\n", pump);
        printf("-b, --bulk\n\tSet how many passwords are generated. Defaults to %d.\n\n", bulk);

        printf("-l, --length\n\tSet the character length of each password. Defaults to %d.\n\n", length);
        printf("-n, --numbers\n\tSet the digit length of the numbered suffix, can be zero. Defaults to %d\n\n", suffix);

        printf("-c, --capitalised\n\tCapitalise passwords.\n\n");
        printf("-@, --specialised\n\tUse special characters in the passwords.\n");
        exit(EXIT_SUCCESS);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) capitalized = TRUE;
        else if (strcmp(argv[i], "-s") == 0) specialized = TRUE;
        else if (strcmp(argv[i], "-n") == 0) {
            i++;
            if (sscanf(argv[i], "%d", &suffix) == 0) {
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
            if (sscanf(argv[i], "%d", &bulk) == 0) {
                printf("\"%s\" is not an integer value.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-i") == 0) {
            i++;
            if (sscanf(argv[i], "%d", &pump) == 0) {
                printf("\"%s\" is not an integer value.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "--seed") == 0) {
            i++;
            if (sscanf(argv[i], "%d", &seed) == 0) {
                printf("\"%s\" is not an integer value.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        } else {
            printf("\"%s\" is not a valid flag. Run `samurai -h` for usage information.\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    srand(seed);

    for (int i = 0; i < bulk; i++) {
        for (int j = 0; j < pump; j++) {
            rand();
        }

        unsigned char *pwd = generate_password(length, capitalized, specialized, suffix);
        printf("%s\n", pwd);
        free(pwd);
    }

    exit(EXIT_SUCCESS);
}
