#include "validator.h"

struct passport validate(struct passport person)
{
    int total = 0;
    char* strings[4] = {person.country_code, person.firstname, person.lastname, person.passport_code};

    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < strlen(strings[i]); j++)
        {
            total += (int)strings[i][j];
        }
    }

    total -= person.age - 7;

    person.foundsum = total % 100;

    if (person.foundsum == person.checksum)
    {
        person.is_valid = 1;
    }

    else
    {
        person.is_valid = 0;
    }

    return person;
}