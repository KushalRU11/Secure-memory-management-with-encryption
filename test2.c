#include "uapi_mm.h"
#include <stdio.h>

// Define structures for employee and student
typedef struct emp_ {
    char name[32];
    uint32_t emp_id;
} emp_t;

typedef struct student_ {
    char name[32];
    uint32_t rollno;
    uint32_t marks_phys;
    uint32_t marks_chem;
    uint32_t marks_maths;
    struct student_ *next;
} student_t;

int main(int argc, char **argv) {
    int wait;

    // Initialize the memory manager
    mm_init();

    // Register structures with the memory manager
    MM_REG_STRUCT(emp_t);
    MM_REG_STRUCT(student_t);

    // Print registered page families
    printf("Registered Page Families:\n");
    mm_print_registered_page_families();

    // Allocate memory for employees and students
    emp_t *emp1 = XCALLOC(1, emp_t);
    emp_t *emp2 = XCALLOC(1, emp_t);
    emp_t *emp3 = XCALLOC(1, emp_t);
    student_t *stud1 = XCALLOC(1, student_t);
    student_t *stud2 = XCALLOC(1, student_t);

    // Print memory and block usage for scenario 1
    printf("\nSCENARIO 1: Memory and Block Usage After Allocation:\n");
    mm_print_memory_usage(0);
    mm_print_block_usage();

    // Wait for user input to continue
    printf("\nPress any key to continue to Scenario 2...\n");
    scanf("%d", &wait);

    // Free allocated memory for some objects
    XFREE(emp1);
    XFREE(emp3);
    XFREE(stud2);

    // Print memory and block usage for scenario 2
    printf("\nSCENARIO 2: Memory and Block Usage After Freeing Some Objects:\n");
    mm_print_memory_usage(0);
    mm_print_block_usage();

    // Wait for user input to continue
    printf("\nPress any key to continue to Scenario 3...\n");
    scanf("%d", &wait);

    // Free allocated memory for remaining objects
    XFREE(emp2);
    XFREE(stud1);

    // Print memory and block usage for scenario 3
    printf("\nSCENARIO 3: Memory and Block Usage After Freeing Remaining Objects:\n");
    mm_print_memory_usage(0);
    mm_print_block_usage();



    return 0;
}