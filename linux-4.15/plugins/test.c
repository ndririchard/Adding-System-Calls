#include "kls_test.c"
#include <stdio.h>



int main(){
	const char *key = "Mac";
	const char *val = "Mojave";
	size_t keylen = strlen(key);
	size_t vallen = strlen(val);
	
	char buffer[MAX_WORD_SIZE];
	
	printf("test 1 : find_index() --> %ld\n", find_index());
	
	printf("test 2 : insert() --> %ld\n", sys_kls_insert(key, keylen, val, vallen));
	
	printf("test 1 : find_index() --> %ld\n", find_index());
	
	printf("test 3 : search() --> %ld\n", sys_kls_search(key, keylen, buffer, 0));
	
	printf(" buffer --> %s\n", buffer);
	
	printf("test 4 : delete() --> %ld\n", sys_kls_delete(key, keylen));
	
	printf("test 1 : find_index() --> %ld\n", find_index());
	
	
}
