#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *version = "V1.0.4";

const char* flag_version_short = "-v";
const char* flag_help_short = "-h";
const char* flag_seed_short = "-s";
const char* flag_pump_short = "-p";
const char* flag_bulk_short = "-b";
const char* flag_length_short = "-l";
const char* flag_numbers_short = "-n";
const char* flag_capitalised_short = "-c";
const char* flag_specialised_short = "-@";

const char* flag_version_long = "--version";
const char* flag_help_long = "--help";
const char* flag_seed_long = "--seed";
const char* flag_pump_long = "--pump";
const char* flag_bulk_long = "--bulk";
const char* flag_length_long = "--length";
const char* flag_numbers_long = "--numbers";
const char* flag_capitalised_long = "--capitalised";
const char* flag_specialised_long = "--specialised";

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

        printf("%s, %s\n\tPrint the program's version.\n\n", flag_version_short, flag_version_long);
        printf("%s, %s\n\tPrint this help message.\n\n", flag_help_short, flag_help_long);

        printf("%s, %s\n\tSet the seed used for random number generation. Defaults to the amount of clock ticks since program start.\n\n", flag_seed_short, flag_seed_long);
        printf("%s, %s\n\tSet how many times the random number generator is iterated over before generating each password. Defaults to %d\n\n", flag_pump_short, flag_pump_long, pump);
        printf("%s, %s\n\tSet how many passwords are generated. Defaults to %d.\n\n", flag_bulk_short, flag_bulk_long, bulk);

        printf("%s, %s\n\tSet the character length of each password. Defaults to %d.\n\n", flag_length_short, flag_length_long, length);
        printf("%s, %s\n\tSet the digit length of the numbered suffix, can be zero. Defaults to %d\n\n", flag_numbers_short, flag_numbers_long, suffix);

        printf("%s, %s\n\tCapitalise passwords.\n\n", flag_capitalised_short, flag_capitalised_long);
        printf("%s, %s\n\tUse special characters in the passwords.\n", flag_specialised_short, flag_specialised_long);
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
