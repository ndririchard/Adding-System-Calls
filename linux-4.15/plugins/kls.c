#include <linux/kernel.h>
#include <linux/module.h>
#include <stddef.h>

/*
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
*/

#define KLS_SIZE 1024
#define MAX_WORD_SIZE 256

struct KLS_ITEM{
	char key[MAX_WORD_SIZE];
	char val[MAX_WORD_SIZE];
};

struct KLS_ITEM NULL_KLS_ITEM = {.key = "NULL_WORD", .val = "NULL_WORD"}; 

#define NULL_KLS_ITEM_t &NULL_KLS_ITEM

// DEFINE THE KLS
struct KLS_ITEM *KLS[KLS_SIZE];

// FIND INDEX
asmlinkage long find_index(void){
	int _index;
	for(_index=0; _index<KLS_SIZE; _index++){
		if(KLS[_index] == NULL || strcmp(KLS[_index]->key, "NULL_WORD") == 0){
			return _index;
			break;
		}
	}
	return -ENOMEM;
}


// INSERT SYST CALL
asmlinkage long sys_kls_insert(const char *key, size_t keylen, const char *val, size_t vallen){
	if (keylen > MAX_WORD_SIZE || vallen > MAX_WORD_SIZE){
		printk(KERN_ERR "ERROR : Invalid argument\n");
		return -EINVAL;
	}
	else{
		long _idx = find_index();
		if (_idx < 0 ){
			printk(KERN_ERR "ERROR : Out of memory\n");
			return _idx;
		}
		else{
			struct KLS_ITEM item;
			strcpy(item.key, key); 
			strcpy(item.val, val);
			KLS[_idx] = &item;
			printk(KERN_ERR "New item added!\n");
		}
	}
	return 0;
	
}

// SEARCH SYST CALL
asmlinkage long sys_kls_search(const char *key, size_t keylen, char *val, size_t index){
	int found = 0;
	if (keylen > MAX_WORD_SIZE ){
		printk(KERN_ERR "ERROR : Invalid argument\n");
		return -EINVAL;
	}
	else{
		int _pos = 0;
		int _idx;
		for (_idx=0; _idx<KLS_SIZE; _idx++){
			if (strcmp(KLS[_idx]->key, key) == 0){
				if (_pos == index){
					strcpy(val, KLS[_idx]->val);
					found = 1;
					break;
				}
				else _pos ++;
			}
		}
	}
	if (found == 1){
		printk(KERN_ERR "ERROR : No such file or directory\n");
		return -ENOENT;
	}
	return 0;
}

// DELETE SYST CALL
asmlinkage long sys_kls_delete(const char *key, size_t keylen){
	if (keylen > MAX_WORD_SIZE ){
		printk(KERN_ERR "ERROR : Invalid argument\n");
		return -EINVAL;
	}
	else{
		int _idx;
		for(_idx=0; _idx<KLS_SIZE; _idx++){
			if (KLS[_idx] != NULL){
				if (strcmp(KLS[_idx]->key, key) == 0)
					KLS[_idx] = NULL_KLS_ITEM_t;
			}
		}
	}
	return 0;
}
