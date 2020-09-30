#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *version = "2.0.0"; // Current version number of Samurai.

const char *flag_version = "--version"; // Flag used for version command.
const char *flag_help = "--help"; // Flag used for help command.
const char *flag_copy = "--copy"; // Flag used for copy-to-clipboard function.
const char *flag_length = "--length"; // Flag used for setting password length.
const char *flag_numbered = "--numbered"; // Flag used for setting numbered suffix length.
const char *flag_capitalised = "--capitalised"; // Flag used to capitalise password.
const char *flag_specialised = "--specialised"; // Flag used to add special character suffix to password.

const int TRUE = 1; // True constant.
const int FALSE = 0; // False constant.

const char *pool_vowel = "aeiou"; // Pool of vowel characters.
const char *pool_consonant = "bcdfgklmnpqrstvz"; // Pool of consonants characters.
const char *pool_numeric = "0123456789"; // Pool of numeric digits.
const char *pool_special = "@#$"; // Pool of special characters.

int length = 12; // Default password length is 12.
int suffix = 0; // Default numbered suffix length is zero.
int capitalised = 0; // By default the password is not capitalised.
int specialised = 0; // By default the password does not end with special character.
int copied = 0; // By default password is not copied to the clipboard.

/**
 * Generate a password using the global settings.
 *
 * @return The generated password.
 */
char *generate_password() {
    char *pwd = calloc(length + 1, sizeof(char)); // Allocate some memory for the password.
    int sign = TRUE; // Set sign to true, meaning that the first character will be a consonant.

    for (int i = 0; i < length; i++) { // Run loop password length times.
        if (sign) pwd[i] = (char) pool_consonant[arc4random_uniform(strlen(pool_consonant))]; // Generate consonant.
        else pwd[i] = (char) pool_vowel[arc4random_uniform(strlen(pool_vowel))]; // Generate vowel.

        sign = (sign) ? FALSE : TRUE; // Flip sign. True is consonant, False is vowel.
    }

    for (int i = 0; i < suffix; i++) { // Run loop numbered suffix length times.
        pwd[length - 1 - i] = (char) pool_numeric[arc4random_uniform(strlen(pool_numeric))]; // Generate numeric digit.
    }

    // If capitalised then set capitalise first character.
    if (capitalised) pwd[0] = (char) toupper(pwd[0]);

    // If specialised then set last character to special character.
    if (specialised) pwd[length - 1 - suffix] = pool_special[arc4random_uniform(strlen(pool_special))];

    return pwd; // Return the generated password.
}

/**
 * Print the current version.
 * Exits program successfully.
 */
void print_version() {
    printf("This is version %s\n", version);
    exit(EXIT_SUCCESS); // Exit program successfully.
}

/**
 * Print help manual message.
 * Exits program successfully.
 */
void print_help() {
    printf("Samurai: The Human Readable Password Generator\n\n");
    printf("%s:\n\tPrint the program's version.\n\n", flag_version);
    printf("%s:\n\tPrint this help message.\n\n", flag_help);
    printf("%s:\n\tCopy password to clipboard instead of printing.\n\n", flag_copy);
    printf("%s <int>:\n\tSet the character length of password. Defaults to %d.\n\n", flag_length, length);
    printf("%s <int>:\n\tSet the digit length of the number suffix. Defaults to %d.\n\n", flag_numbered, suffix);
    printf("%s:\n\tCapitalise the password. \n\n", flag_capitalised);
    printf("%s:\n\tEnd password with special character.\n\n", flag_specialised);
    exit(EXIT_SUCCESS); // Exit program successfully.
}

/**
 * Print the error message when a flag argument is missing.
 * Exits program unsuccessfully.
 *
 * @param flag The flag that expected the missing argument.
 */
void print_missing_param(char *flag) {
    printf("The flag \"%s\" expects a parameter.\n", flag);
    exit(EXIT_FAILURE); // Exit program unsuccessfully.
}

/**
 * Print error message when an integer was expected but was not found.
 * Exits program unsuccessfully.
 *
 * @param arg The argument string that was expected to be an integer.
 */
void print_invalid_integer(char *arg) {
    printf("\"%s\" is not an integer value.\n", arg);
    exit(EXIT_FAILURE); // Exit program unsuccessfully.
}

/**
 * Print error message when command flag was not recognised.
 * Exits program unsuccessfully.
 *
 * @param flag The flag that was not recognised.
 */
void print_invalid_flag(char *flag) {
    printf("\"%s\" is not a valid flag. Run `samurai %s` for usage information.\n", flag, flag_help);
    exit(EXIT_FAILURE); // Exit program unsuccessfully.
}

/**
 * Read integer from argument string.
 *
 * @param ret The pointer to the integer where te value is stored.
 * @param arg The argument string to be parsed.
 * @return Returns TRUE (1) when function fails, returns FALSE (0) when function succeeds.
 */
int read_integer(int *ret, const char *arg) {
    char *ptr; // Pointer to next character after parsing
    *ret = (int) strtol(arg, &ptr, 10); // Parse long and cast as int.
    return ptr == arg; // If equal then no integer could be parsed and therefore the function failed.
}

/**
 * Read the program's arguments and set the global settings with them.
 *
 * @param argc The number of program;s arguments.
 * @param argv The program's arguments.
 */
void read_params(int argc, char **argv) {
    for (int i = 1; i < argc; i++) { // Loop all arguments.
        if (strcmp(argv[i], flag_capitalised) == 0) { // If capitalise flag is used then:
            capitalised = TRUE; // Set capitalise setting to True.
        } else if (strcmp(argv[i], flag_specialised) == 0) { // If specialise flag is used then:
            specialised = TRUE; // Set specialise setting to True.
        } else if (strcmp(argv[i], flag_copy) == 0) { // If copy flag is used then:
            copied = TRUE; // Set copy setting to True.
        } else if (strcmp(argv[i], flag_length) == 0) { // If length flag is used then:
            if (argc <= i + 1) print_missing_param(argv[i]); // Check for enough arguments.
            i++; // Increase index to search for argument.
            if (read_integer(&length, argv[i])) print_invalid_integer(argv[i]); // Parse integer.
        } else if (strcmp(argv[i], flag_numbered) == 0) { // If numbered flag is used then:
            if (argc <= i + 1) print_missing_param(argv[i]); // Check for enough arguments.
            i++; // Increase index to search for argument.
            if (read_integer(&suffix, argv[i])) print_invalid_integer(argv[i]); // Parse integer.
        } else print_invalid_flag(argv[i]); // Flag is not recognised and program fails.
    }
}

/**
 * Execute the program based on the global settings.
 */
void execute() {
    arc4random(); // Initialise arc4random random number generator.

    char *pwd = generate_password(); // Generate password

    if (copied) { // If the passwords needs to be copied to the clipboard
        char cmd[128]; // Allocate some memory for command.
        strcpy(cmd, "echo ");
        strcat(cmd, pwd);
        strcat(cmd, " | pbcopy");
        system(cmd);
        printf("Password has been copied to the clipboard.\n");
        exit(EXIT_SUCCESS); // Exit program successfully.
    } else {
        printf("%s\n", pwd); // Print password to terminal.
        free(pwd); // Free password memory.
        exit(EXIT_SUCCESS); // Exit program successfully.
    }
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], flag_version) == 0) print_version(); // Print version number.
    if (argc > 1 && strcmp(argv[1], flag_help) == 0) print_help(); // Print help message.

    read_params(argc, argv); // Set global settings using program's arguments.
    execute(); // Generate password using the global settings.

    exit(EXIT_SUCCESS); // Exit program successfully.
}
