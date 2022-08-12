/* This file represents a very basic tester to test your syscalls.
 * You can compile it with the following command:
 *
 * gcc -o test test.c
 *
 * You can modify it but do not modify the system call number!
 *
 * Use the errno variable to check the error code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <sys/syscall.h>

const static int MAX_SIZE = 256;

static inline long kls_insert(const char *key, size_t keylen, const char *val, size_t vallen)
{
    return syscall(385, key, keylen, val, vallen);
}

static inline long kls_search(const char *key, size_t keylen, char *buffer, size_t index)
{
    return syscall(386, key, keylen, buffer, index);
}

static inline long kls_delete(const char *key, size_t keylen)
{
    return syscall(387, key, keylen);
}

/*
Examples:
    - Insert:
        - ./test -o insert -k hello -v world0   (index 0)
        - ./test -o insert -k hello -v world1   (index 1)
    - Search: ./test -o search -k hello 0       (index 0)
    - Delete: ./test -o delete -k hello
*/
int main(int argc, char* const* argv)
{
    int ch;
    const char *opt = NULL, *key = NULL, *val = NULL;
    while ((ch = getopt(argc, argv, "k:v:o:i")) != -1) {
        switch (ch) {
        case 'o':
            opt = optarg;
            break;
        case 'k':
            key = optarg;
            break;
        case 'v':
            val = optarg;
            break;
        }
    }
    if (!opt) {
        fprintf(stderr, "Specify one of operations, insert, search or delete by -o\n");
        return 1;
    }
    if (strlen(opt) == strlen("insert") && !strncmp("insert", opt, strlen(opt))) {
        int err;
        if (!key) {
            fprintf(stderr, "Specify a key for insert by -k\n");
            return 1;
        }
        if (!val) {
            fprintf(stderr, "Specify a val for insert by -v\n");
            return 1;
        }
        if (kls_insert(key, strlen(key), val, strlen(val)) == 0){
            printf("Added <%s : %s>\n", key, val);
        }else if (errno == ENOSYS){
            fprintf(stderr, "Not implemented\n");
            return 1;
        }
    } else if (strlen(opt) == strlen("search") && !strncmp("search", opt, strlen(opt))) {
        char buffer[MAX_SIZE];
        if (!key) {
            fprintf(stderr, "Specify a key for insert by -k\n");
            return 1;
        }
        size_t index = atoi(argv[5]);
        if (kls_search(key, strlen(key), buffer, index) == 0){
            printf("<%s : %s> (index: %d)\n", key, buffer, index);
            return 0;
        }else if(errno == ENOENT){
            fprintf(stderr, "Key %s does not exist\n", key);
        }else if(errno == EINVAL){
            fprintf(stderr, "Invalid index for %s\n", key);
        }else if(errno == ENOSYS){
            fprintf(stderr, "Not implemented\n");
        }else{
            fprintf(stderr, "Other error: %d\n", errno);
        }
        return 1;
    } else if (strlen(opt) == strlen("delete") && !strncmp("delete", opt, strlen(opt))) {
        if (!key) {
            printf("Specify a key for insert by -k\n");
            return 1;
        }
        if (kls_delete(key, strlen(key)) == 0){
            printf("Key: %s is deleted\n", key);
        }else if (errno == ENOSYS){
            fprintf(stderr, "Not implemented\n");
            return 1;
        }
    }
    return 0;
}
