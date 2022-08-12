#include <linux/kernel.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>


#define KLS_SIZE 1024
#define MAX_WORD_SIZE 512

typedef struct KLS_ITEM{
	char *key;
	char *val;
} ITEM;

// DEFINE THE KLS
ITEM *KLS[KLS_SIZE];

// FIND INDEX
long find_index(){
	int _index;
	for(_index=0; _index<KLS_SIZE; _index++){
		if(KLS[_index] == NULL){
			return _index;
			break;
		}
	}
	return -ENOMEM;
}

// INSERT SYST CALL
asmlinkage long sys_kls_insert(const char *key, size_t keylen, const char *val, size_t vallen){
	if (keylen > MAX_WORD_SIZE || vallen > MAX_WORD_SIZE){
		printk(KERN_ERR "ERROR : %s\n", strerror(EINVAL));
		return -EINVAL;
	}
	else{
		long _idx = find_index();
		if (_idx < 0 ){
			printk(KERN_ERR "ERROR : %s\n", strerror(_idx));
			return _idx;
		}
		else{
			ITEM *item;
			strcpy(item->key, key);
			strcpy(item->val, val);
			KLS[_idx] = item;
			printk(KERN_INFO "New item added!");
		}
	}
	return 0;
	
}

// SEARCH SYST CALL
asmlinkage long sys_kls_search(const char *key, size_t keylen, char *val, size_t index){
	if (keylen > MAX_WORD_SIZE ){
		printk(KERN_ERR "ERROR : %s\n", strerror(EINVAL));
		return -EINVAL;
	}
	else{
		int _pos = 0;
		int _idx;
		for (_idx=0; _idx<KLS_SIZE; _idx++){
			if (KLS[_idx]->key == key){
				if (_pos == index){
					strcpy(val, KLS[_idx]->val);
					return 0;
				}
				else _pos ++;
			}
		}
	}
	printk(KERN_ERR "ERROR : %s\n", strerror(ENOENT));
	return -ENOENT;
}

// DELETE SYST CALL
asmlinkage long sys_kls_delete(const char *key, size_t keylen){
	if (keylen > MAX_WORD_SIZE ){
		printk(KERN_ERR "ERROR : %s\n", strerror(EINVAL));
		return -EINVAL;
	}
	else{
		int _idx;
		for(_idx=0; _idx<KLS_SIZE; _idx++){
			if(KLS[_idx]->key == key){
				KLS[_idx] = NULL;
			}
		}
	}
	return 0;
}
