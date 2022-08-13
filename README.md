# Adding-System-Calls
In this work, i will implement a Key-List-Storage (KLS) functionality in the Linux kernel. The kernel-space KLS offers three system calls for insert, search, and delete operations.
\n
long kls_insert(const char *key, size_t keylen, const char *val, size_t vallen);\n
long kls_search(const char *key, size_t keylen, char *buffer, size_t index);\n
long kls_delete(const char *key, size_t keylen);\n

The system call number assignment is as follows:\n
• kls insert: 385\n
• kls search: 386\n
• kls delete: 387\n

