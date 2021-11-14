#include "define.h"

typedef struct{
	char * idU;
	char ** idR;
} Data_2;

typedef struct{
	char * idR;
	int commit_R;
} Data_R;

Data_2 * hash_table[TABLE_SIZE];
Data_R * hash_tableR[TABLE_SIZE];
unsigned int hash(char * idU);
unsigned int hashR(char * idR);
void init_hash_table();
void init_hash_tableR();
void print_table();
void print_tableR();
bool hash_table_insert(Data_2 * p);
bool hash_table_insertR(Data_R * p);
bool hash_table_member_insert(Data_2 * p, char * idR, char * repo_id);
bool hash_table_member_insertR(Data_R * p, char * commit_R);
bool hash_insert(char * p);
bool hash_insertR(char * p);
Data_2 *hash_table_lookup (char * idU);
Data_R *hash_table_lookupR (char * idR);
int hash_table_member_lookupR(char * idR);
Data_2 *hash_table_delete (char * idU);
Data_R *hash_table_deleteR (char * idR);




