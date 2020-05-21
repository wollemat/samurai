#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *version = "V1.1.0";

const char *flag_version_short = "-v";
const char *flag_help_short = "-h";
const char *flag_seed_short = "-s";
const char *flag_pump_short = "-p";
const char *flag_bulk_short = "-b";
const char *flag_copy_short = "-C";
const char *flag_length_short = "-l";
const char *flag_numbers_short = "-n";
const char *flag_capitalised_short = "-c";
const char *flag_specialised_short = "-S";

const char *flag_version_long = "--version";
const char *flag_help_long = "--help";
const char *flag_seed_long = "--seed";
const char *flag_pump_long = "--pump";
const char *flag_bulk_long = "--bulk";
const char *flag_copy_long = "--copy";
const char *flag_length_long = "--length";
const char *flag_numbers_long = "--numbers";
const char *flag_capitalised_long = "--capitalised";
const char *flag_specialised_long = "--specialised";

const int TRUE = 1;
const int FALSE = 0;

const char *vowels = "aeiou";
const char *consonants = "bcdfghjklmnpqrstvwxyz";
const char *numbers = "0123456789";
const char *specials = "!@#$%^&*-+?";

int length = 12;
int capitalized = 0;
int specialized = 0;
int suffix = 2;
int bulk = 10;
int pump = 65536;
int seed = 0;
int copied = 0;

unsigned char *generate_password() {
    unsigned char *pwd = calloc(length + 1, sizeof(char));
    int sign = TRUE;

    for (int i = 0; i < length; i++) {
        pwd[i] = (sign) ? consonants[rand() % strlen(consonants)] : vowels[rand() % strlen(vowels)];
        sign = (sign) ? FALSE : TRUE;
    }

    for (int i = 0; i < suffix; i++) {
        pwd[length - 1 - i] = numbers[rand() % strlen(numbers)];
    }

    if (capitalized) pwd[0] = toupper(pwd[0]);
    if (specialized) pwd[length - 1 - suffix] = specials[rand() % strlen(specials)];

    return pwd;
}

int check_flag(char *arg, const char *flag_short, const char *flag_long) {
    return strcmp(arg, flag_short) == 0 || strcmp(arg, flag_long) == 0;
}

void print_version() {
    printf("This is version %s\n", version);
    exit(EXIT_SUCCESS);
}

void print_help() {
    printf("Samurai: The Human Readable Password Generator\n\n");
    printf("Usage: samurai %s | %s | [[%s <int>] [%s <int>] [%s <int> | %s ] [%s <int>] [%s <int>] %s %s]\n\n",
           flag_version_short, flag_help_short, flag_seed_short, flag_pump_short, flag_bulk_short, flag_copy_short,
           flag_length_short, flag_numbers_short, flag_capitalised_short, flag_specialised_short);
    printf("%s, %s\n\tPrint the program's version.\n\n", flag_version_short, flag_version_long);
    printf("%s, %s\n\tPrint this help message.\n\n", flag_help_short, flag_help_long);
    printf("%s, %s\n\tSet the seed used for random number generation. Defaults to the amount of clock ticks since program start.\n\n",
           flag_seed_short, flag_seed_long);
    printf("%s, %s\n\tSet how many times the random number generator is iterated over before generating each password. Defaults to %d\n\n",
           flag_pump_short, flag_pump_long, pump);
    printf("%s, %s\n\tSet how many passwords are generated. Defaults to %d.\n\n", flag_bulk_short, flag_bulk_long,
           bulk);
    printf("%s, %s\n\tOverrides --bulk and instead will generate a single password. This password is copied to the clipboard however instead of printed to the terminal.\n\n",
           flag_copy_short, flag_copy_long);
    printf("%s, %s\n\tSet the character length of each password. Defaults to %d.\n\n", flag_length_short,
           flag_length_long, length);
    printf("%s, %s\n\tSet the digit length of the numbered suffix, can be zero. Defaults to %d\n\n",
           flag_numbers_short, flag_numbers_long, suffix);
    printf("%s, %s\n\tCapitalise passwords.\n\n", flag_capitalised_short, flag_capitalised_long);
    printf("%s, %s\n\tUse special characters in the passwords.\n", flag_specialised_short, flag_specialised_long);
    exit(EXIT_SUCCESS);
}

void print_missing_param(char *flag) {
    printf("The flag \"%s\" expects a parameter.\n", flag);
    exit(EXIT_FAILURE);
}

void print_invalid_integer(char *str) {
    printf("\"%s\" is not an integer value.\n", str);
    exit(EXIT_FAILURE);
}

void print_invalid_flag(char *flag) {
    printf("\"%s\" is not a valid flag. Run `samurai %s` or `samurai %s` for usage information.\n", flag,
           flag_help_short, flag_help_long);
    exit(EXIT_FAILURE);
}

void read_params(int argc, char **argv) {
    seed = clock();

    for (int i = 1; i < argc; i++) {
        if (check_flag(argv[i], flag_capitalised_short, flag_capitalised_long)) {
            capitalized = TRUE;
            continue;
        } else if (check_flag(argv[i], flag_specialised_short, flag_specialised_long)) {
            specialized = TRUE;
            continue;
        } else if (check_flag(argv[i], flag_copy_short, flag_copy_long)) {
            copied = TRUE;
            continue;
        } else if (check_flag(argv[i], flag_numbers_short, flag_numbers_long)) {
            if (argc <= i + 1) print_missing_param(argv[i]);
            i++;
            if (sscanf(argv[i], "%d", &suffix) == 0) print_invalid_integer(argv[i]);
        } else if (check_flag(argv[i], flag_length_short, flag_length_long)) {
            if (argc <= i + 1) print_missing_param(argv[i]);
            i++;
            if (sscanf(argv[i], "%d", &length) == 0) print_invalid_integer(argv[i]);
        } else if (check_flag(argv[i], flag_bulk_short, flag_bulk_long)) {
            if (argc <= i + 1) print_missing_param(argv[i]);
            i++;
            if (sscanf(argv[i], "%d", &bulk) == 0) print_invalid_integer(argv[i]);
        } else if (check_flag(argv[i], flag_pump_short, flag_pump_long)) {
            if (argc <= i + 1) print_missing_param(argv[i]);
            i++;
            if (sscanf(argv[i], "%d", &pump) == 0) print_invalid_integer(argv[i]);
        } else if (check_flag(argv[i], flag_seed_short, flag_seed_long)) {
            if (argc <= i + 1) print_missing_param(argv[i]);
            i++;
            if (sscanf(argv[i], "%d", &seed) == 0) print_invalid_integer(argv[i]);
        } else print_invalid_flag(argv[i]);
    }
}

void execute() {
    srand(seed);

    for (int i = 0; i < bulk; i++) {
        for (int j = 0; j < pump; j++) rand();

        unsigned char *pwd = generate_password();

        if (copied) {
            char cmd[128];
            strcpy(cmd, "echo ");
            strcat(cmd, pwd);
            strcat(cmd, " | pbcopy");
            system(cmd);
            exit(EXIT_SUCCESS);
        }

        printf("%s\n", pwd);
        free(pwd);
    }
}

int main(int argc, char **argv) {
    if (argc > 1 && check_flag(argv[1], flag_version_short, flag_version_long)) print_version();
    if (argc > 1 && check_flag(argv[1], flag_help_short, flag_help_long)) print_help();

    read_params(argc, argv);

    execute();

    exit(EXIT_SUCCESS);
}
