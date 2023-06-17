/** 
 * Binary passport creator
 *
 * (c) Simon, 2019
 *
 */

#include <stdio.h>
#include <stdint.h>

typedef struct {
    char document_type;
    char last_name[32];
    char first_name[32];
    unsigned birth_year;
    unsigned birth_month;
    unsigned birth_day;
    char country_code[3];
    char passport_code;
    unsigned long checksum;
} passport_t;

int print_passport(passport_t p) {
    return printf( 
            "Document Type:  %c\n"
            "Name:           %s, %s \n"
            "Birth date:     %02u/%02u/%04u \n"
            "Country code:   %c%c%c \n"
            "Passport code:  %c \n"
            "Checksum:       %lu \n", 
            p.document_type, p.last_name, p.first_name, 
            p.birth_day, p.birth_month, p.birth_year,
            p.country_code[0], p.country_code[1], p.country_code[2],
            p.passport_code, p.checksum
        );
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <passport_binary_file>\n", argv[0]);
        return 1;
    }

    FILE* passport_file = fopen(argv[1], "rb");
    if (passport_file <= 0) {
        fprintf(stderr, "Error: Passport binary file %s could not be opened or doesn't exist\n", argv[1]);
        return 1;
    }

    passport_t passport;

    if (fread(&passport, sizeof(passport_t), 1, passport_file) != 1) {
        fprintf(stderr, "Error: Could not read passport binary file %s. Corrupted format?\n", argv[1]);
        return 1;
    }
    fclose(passport_file);

    print_passport(passport);

    return 0;
}


