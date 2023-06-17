#include "printer.h"

void display_information(struct passport person)
{
    printf("Name: %s %s\n", person.firstname, person.lastname);
    printf("Age: %d\n", person.age);
    printf("Passport code: %s\n", person.passport_code);
    printf("Country Code: %s\n", person.country_code);
    printf("Checksum: %d\n", person.checksum);
    printf("Computed checksum: %d\n", person.foundsum);
        
    if (person.is_valid > 0)
    {
        printf("Valid - YES\n");
    }

    else
    {
        printf("Valid - NO\n");
    }

    return;
}