#include "extracter.h"

struct passport extract_information(char* password, struct passport person)
{   
    char* delim = "<";
    person.country_code = strtok(password + 2, delim);
    person.firstname = strtok(NULL, delim);
    person.lastname = strtok(NULL, delim);
    person.age = (unsigned int)atoi(strtok(NULL, delim));
    person.passport_code = strtok(NULL, delim);
    person.checksum = atoi(strtok(NULL, delim));
    return person;
}