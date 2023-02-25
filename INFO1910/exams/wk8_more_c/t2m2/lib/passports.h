#ifndef PASSPORT_H
#define PASSPORT_H

#include <stdio.h>
#include <string.h>

#include "extracter.h"
#include "printer.h"
#include "validator.h"


struct passport 
{
    char* firstname;
    char* lastname;
    char* country_code;
    char* passport_code;
    unsigned int age;
    int checksum;
    int is_valid;
    int foundsum; 
};



#endif