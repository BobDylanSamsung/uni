#include <stdio.h>

struct person {
    int age;
    int salary;
    float height;
};

int main() {
    struct person steven;
    steven.salary = 50000;

    printf("%d\n", steven.salary);
}