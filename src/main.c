#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *version = "2.0.0"; // Current version number of Samurai.

const char *flag_version = "--version"; // Flag used for version command.
const char *flag_help = "--help"; // Flag used for help command.
const char *flag_copy = "--copy";
const char *flag_length = "--length";
const char *flag_numbered = "--numbered";
const char *flag_capitalised = "--capitalised";
const char *flag_specialised = "--specialised";

const int TRUE = 1;
const int FALSE = 0;

const char *vowels = "aeiou";
const char *consonants = "bcdfghjklmnpqrstvwxyz";
const char *numbers = "0123456789";
const char *specials = "!@#$%^&*-+?";

int length = 12;
int suffix = 0;
int capitalised = 0;
int specialised = 0;

int copied = 0;

char *generate_password() {
    char *pwd = calloc(length + 1, sizeof(char));
    int sign = TRUE;

    for (int i = 0; i < length; i++) {
        if (sign) pwd[i] = (char) consonants[arc4random_uniform(strlen(consonants))];
        else pwd[i] = (char) vowels[arc4random_uniform(strlen(vowels))];

        sign = (sign) ? FALSE : TRUE; // Flip sign.
    }

    for (int i = 0; i < suffix; i++) {
        pwd[length - 1 - i] = (char) numbers[arc4random_uniform(strlen(numbers))];
    }

    if (capitalised) pwd[0] = (char) toupper(pwd[0]);
    if (specialised) pwd[length - 1 - suffix] = specials[arc4random_uniform(strlen(specials))];

    return pwd;
}

void print_version() {
    printf("This is version %s\n", version);
    exit(EXIT_SUCCESS);
}

void print_help() {
    printf("Samurai: The Human Readable Password Generator\n\n");
    printf("%s:\n\tPrint the program's version.\n\n", flag_version);
    printf("%s:\n\tPrint this help message.\n\n", flag_help);
    printf("%s:\n\tCopy password to clipboard instead of printing.\n\n", flag_copy);
    printf("%s <int>:\n\tSet the character length of password. Defaults to %d.\n\n", flag_length, length);
    printf("%s <int>:\n\tSet the digit length of the number suffix. Defaults to %d.\n\n", flag_numbered, suffix);
    printf("%s:\n\tCapitalise the password. \n\n", flag_capitalised);
    printf("%s:\n\tEnd password with special character.\n\n", flag_specialised);
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
    printf("\"%s\" is not a valid flag. Run `samurai %s` for usage information.\n", flag, flag_help);
    exit(EXIT_FAILURE);
}

int read_integer(int *param, const char *arg) {
    char *ptr;
    *param = (int) strtol(arg, &ptr, 10);
    return ptr == arg;
}

void read_params(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], flag_capitalised) == 0) {
            capitalised = TRUE;
        } else if (strcmp(argv[i], flag_specialised) == 0) {
            specialised = TRUE;
        } else if (strcmp(argv[i], flag_copy) == 0) {
            copied = TRUE;
        } else if (strcmp(argv[i], flag_length) == 0) {
            if (argc <= i + 1) print_missing_param(argv[i]);
            i++;
            if (read_integer(&length, argv[i])) print_invalid_integer(argv[i]);
        } else if (strcmp(argv[i], flag_numbered) == 0) {
            if (argc <= i + 1) print_missing_param(argv[i]);
            i++;
            if (read_integer(&suffix, argv[i])) print_invalid_integer(argv[i]);
        } else print_invalid_flag(argv[i]);
    }
}

void execute() {
    arc4random();

    char *pwd = generate_password();

    if (copied) {
        char cmd[128];
        strcpy(cmd, "echo ");
        strcat(cmd, pwd);
        strcat(cmd, " | pbcopy");
        system(cmd);
        printf("Password has been copied to the clipboard.\n");
        exit(EXIT_SUCCESS);
    }

    printf("%s\n", pwd);
    free(pwd);
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], flag_version) == 0) print_version();
    if (argc > 1 && strcmp(argv[1], flag_help) == 0) print_help();

    read_params(argc, argv);
    execute();

    exit(EXIT_SUCCESS);
}
