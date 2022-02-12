#ifndef HASHTABLE_1_H
#define HASHTABLE_1_H

typedef struct ht_entry ht_entry;
typedef struct ht ht;

int hash(char *key);
ht* ht_create(int size);
void* ht_get(ht *ht, char *key, void*(*create_type)(void),void(*copy_data)(void*, void*));
void ht_del(ht *ht, char *key);
ht_entry* ht_pair(char *key, void *d);
void ht_insert(ht *ht, char *key, void *d);
int ht_count(ht *ht);
void ht_destroy(ht *ht, void(*delete_data)(void *));
void ht_init(ht *ht, char *file, void*(*create_type)(void), void(*set_type)(void*, char*), char*(*get_key)(void*));
void ht_print_table(ht *ht);
#endif
