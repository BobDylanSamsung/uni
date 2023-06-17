#include "passports.h"

int main(int argc, char ** argv)
{
    for(int i = 1; i < argc; i++)
    {
        char password[100];

        FILE* file = fopen(argv[i], "r");
        fgets(password, 100, file);

        struct passport person;

        person = extract_information(password, person);

        person = validate(person);

        display_information(person);
        
        fclose(file);

        printf("\n\n\n");
    }
    return 0;

}