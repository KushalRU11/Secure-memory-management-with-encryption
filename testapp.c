#include "uapi_mm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <unistd.h>

#define MAX_NAME_LENGTH 32

// Define structures for employee, student, book, car, and 50 additional structures
typedef struct student_ {
    char name[MAX_NAME_LENGTH];
    char usn[40];
    uint32_t age;
    char department[50];
} student_t;

// Function to handle errors
void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

// Function to encrypt data
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

// Function to print block usage
void print_block_usage() {
    printf("\nBlock Usage:\n");
    mm_print_block_usage();
}

int main(int argc, char **argv) {
    // Initialize the memory manager
    mm_init();
    // Register the emp_t structure with the memory manager
    MM_REG_STRUCT(student_t);

    char key[] = "01234567890123456789012345678901"; // 256-bit key
    char iv[] = "0123456789012345"; // 128-bit IV

    if (argc != 2) {
        printf("Usage: %s [encrypt|decrypt]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "encrypt") == 0) {
        // Print the size of the emp_t structure
        printf("Size of student_t: %zu\n", sizeof(student_t));

        // Allocate memory for the emp_t structure
        student_t *emp_mem = XCALLOC(1, student_t);

        // Take input for the emp_t structure
        printf("Enter name: ");
        scanf("%s", emp_mem->name);
        printf("Enter usn: ");
        scanf("%s", emp_mem->usn);
        printf("Enter age: ");
        scanf("%u", &emp_mem->age);
        printf("Enter department: ");
        scanf("%s", emp_mem->department);

        // Buffer for encrypted text
        unsigned char ciphertext[MAX_NAME_LENGTH + 40 + sizeof(uint32_t) * 2 + 50 + EVP_MAX_BLOCK_LENGTH];

        // Encrypt the input
        int ciphertext_len = encrypt((unsigned char *)emp_mem, sizeof(student_t), (unsigned char *)key, (unsigned char *)iv, ciphertext);

        // Write encrypted data to file
        FILE *file = fopen("encrypted_data.txt", "wb");
        fwrite(ciphertext, 1, ciphertext_len, file);
        fclose(file);

        // Print memory usage
        printf("\nMemory Usage after allocation:\n");
        mm_print_memory_usage(0);

        // Print block usage after allocation
        print_block_usage();

        // Free the allocated memory
        XFREE(emp_mem);
    } else if (strcmp(argv[1], "decrypt") == 0) {
        // Read encrypted data from file
        FILE *file = fopen("encrypted_data.txt", "rb");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        fseek(file, 0, SEEK_END);
        long filesize = ftell(file);
        fseek(file, 0, SEEK_SET);

        unsigned char *ciphertext = malloc(filesize);
        if (ciphertext == NULL) {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }

        fread(ciphertext, 1, filesize, file);
        fclose(file);

        // Buffer for decrypted text
        unsigned char decryptedtext[sizeof(student_t)];

        // Decrypt the data
        EVP_CIPHER_CTX *ctx;
        int len;
        if (!(ctx = EVP_CIPHER_CTX_new()))
            handleErrors();

        if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
            handleErrors();

        if (1 != EVP_DecryptUpdate(ctx, decryptedtext, &len, ciphertext, filesize))
            handleErrors();

        int decryptedtext_len = len;

        if (1 != EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len))
            handleErrors();

        decryptedtext_len += len;

        EVP_CIPHER_CTX_free(ctx);

        // Check if the user is root
        if (geteuid() == 0) {
            // If root, display decrypted data
            printf("Decrypted Data:\n");
            student_t *emp_data = (student_t *)decryptedtext;
            printf("Name: %s\n", emp_data->name);
            printf("USN: %s\n", emp_data->usn);
            printf("Age: %u\n", emp_data->age);
            printf("Department: %s\n", emp_data->department);
        } else {
            // If not root, display encrypted data
            printf("Encrypted Data:\n");
            for (int i = 0; i < decryptedtext_len; i++) {
                printf("%02X", decryptedtext[i]);
            }
            printf("\n");
        }

        free(ciphertext);
    } else {
        printf("Invalid option. Use 'encrypt' or 'decrypt'.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}