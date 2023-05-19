#include "../includes/utils.h"

typedef struct hash_utils{
    GHashTable* hash_table;
} HASH_UTILS;

GHashTable *getHashTable (HASH_UTILS *ht) {
    return ht->hash_table;
}

HASH_UTILS *newHash_Table () {
    HASH_UTILS *hu;
    hu = malloc(sizeof(HASH_UTILS));
    hu->hash_table = g_hash_table_new(g_str_hash,g_str_equal);
    return hu;
}

void insert_PIDS(HASH_UTILS *ht, char* key, char* value) {
    gpointer existing_value = g_hash_table_lookup(ht->hash_table, key);
    if (existing_value != NULL) {
        // Atualiza o valor existente
        g_hash_table_replace(ht->hash_table, g_strdup(key), g_strdup(value));
    } else {
        // Insere um novo par chave-valor
        g_hash_table_insert(ht->hash_table, g_strdup(key), g_strdup(value));
    }
}


void delete_PID (HASH_UTILS *ht, char *key) {
    g_hash_table_remove(ht->hash_table,key);
}


int _readc(int fd, char * c){
    return read(fd, c, 1);
}

size_t _readln(int fd, char * buffer, size_t size){
    
    size_t i = 0;

    while(i < size && _readc(fd, &buffer[i]) > 0){
        i++;
        if(((char*) buffer)[i-1] == '\n'){
            return i;
        }
    }

    return i;
}

void _printf(char * buffer, size_t size){
	write(STDOUT_FILENO,buffer,size);
}

void _printf_string(char ** buffer, size_t size){
	for (int i = 0; i < (int)size; i++) {
	    _printf(strcat(buffer[i], " "), sizeof(buffer[i]));
	}
	_printf("\n", 1);
}


char * int_to_str(int num){
  int temp = num;
  int digits = 0;
  
  // Count the number of digits in the integer
  while (temp != 0) {
	  digits++;
	  temp /= 10;
  }
  
  // Allocate memory for the string and null terminator
  char* str = (char*)malloc((digits) * sizeof(char));
  
  // Convert each digit to ASCII and store in the string
  for (int i = digits - 1; i >= 0; i--) {
      str[i] = (char)((num % 10) + '0');
      num /= 10;
  }
  
  return str;
}

char * time_t_to_str(time_t timestamp){

    long long ms = timestamp * 1000;
    char * buffer = malloc(sizeof(char)*20); 
    sprintf(buffer, "%lld", ms);
    strcat(buffer, " ms\n");
    return buffer;
}

char ** _tail(char** arr, int len) {
    if (len <= 1) return NULL;
    
    char **new_arr = (char **)malloc((len-1) * sizeof(char *));
    
    // Copy all the elements except the first one into the new array
    for (int i = 1; i < len; i++) {
        new_arr[i-1] = strdup(arr[i]);
    }

    return new_arr;
}

void make_dir(const char * dirname){
	// permissions to read / write / execute to everyone
	size_t status = mkdir(dirname, 0777); 
	if(status == 0) _printf("SUCCESS: directory created successfully!\n", 42);
	else _printf("ERROR: failed while creating directory!\n", 41);
}

int exists_dir(const char * dirname){
	struct stat st;
    if (stat(dirname, &st) == 0 && S_ISDIR(st.st_mode)) return 1;
    return 0;
}

void make_file(const char * filename){
	// permissions to read / write / execute to everyone
    int fd = open(filename, O_CREAT | O_WRONLY, 0777);

	if(fd == -1) _printf("ERROR: failed while creating file!\n", 36);
	else _printf("SUCCESS: file created successfully!\n", 37);
}

void write_file(const char * filename, char * buffer){
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC , 0777);

	if (fd != -1) {
        size_t len = strlen(buffer);
        ssize_t bytes_written = write(fd, buffer, len);
        if (bytes_written == -1) _printf("ERROR: failed to write in file!\n", 33);
        else if ((size_t)bytes_written != len) _printf("ERROR: Write was not finished!\n", 32);
        else _printf("SUCCESS: Successfully wrote to file.\n", 38);
        close(fd);
    } else {
        _printf("ERROR: failed to open file for writing.\n", 41);
    } 
}

void write_file_append(const char * filename, char * buffer){
	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);

	if (fd != -1) {
        size_t len = strlen(buffer);
        ssize_t bytes_written = write(fd, buffer, len);
        if (bytes_written == -1) _printf("ERROR: failed to write in file!\n", 33);
        else if ((size_t)bytes_written != len) _printf("ERROR: Write was not finished!\n", 32);
        else _printf("SUCCESS: Successfully wrote to file.\n", 38);
        close(fd);
    } else {
        _printf("ERROR: failed to open file for writing.\n", 41);
    } 
}

void write_file_string(const char * filename, char ** buffer, size_t num_lines){
	ssize_t fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd != -1) {
        ssize_t bytes_written = 0;
        for (size_t i = 0; i < num_lines; i++) {
            size_t len = strlen(buffer[i]);
            bytes_written = write(fd, buffer[i], len);
            if (bytes_written == -1) {
                _printf("ERROR: failed to write in file!\n", 33);
                break;
            } else if ((size_t)bytes_written != len) {
                _printf("ERROR: Write was not finished!\n", 32);
                break;
            }
        }
        if (bytes_written != -1) _printf("SUCCESS: Successfully wrote to file.\n", 38);
        close(fd);
    } else {
        _printf("ERROR: failed to open file for writing.\n", 41);
    }
}

int exists_file(const char * filename){
	struct stat st;
    if (stat(filename, &st) == 0) return 1;
    return 0;
}

time_t get_timeofday(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000;
}

char ** getProgram(const int argc, char *argv[], int start) {
    char ** res = malloc(sizeof(char *) * (argc - start));

    for (int i = start; i < argc; i++) {
        res[i - start] = malloc(strlen(argv[i]) + 1);
        strcpy(res[i - start], argv[i]);
    }

    res[argc - start] = NULL;

    return res;
}


char* join_strings(char** strings, int num_strings) {
    // Calcula o tamanho total da string resultante
    int total_size = 0;
    for (int i = 0; i < num_strings; i++) {
        total_size += strlen(strings[i]);
    }
    total_size += num_strings - 1; // Adiciona o espaço em branco entre cada elemento

    // Aloca memória para a string resultante
    char* result = malloc(total_size + 1);
    result[0] = '\0';

    // Concatena cada elemento na string resultante
    for (int i = 0; i < num_strings; i++) {
        strcat(result, strings[i]);
        if (i != num_strings - 1) {
            strcat(result, " ");
        }
    }

    return result;
}

void print_status(const int process_pid, const char* name, time_t timestamp) {

	char * buffer_pid = int_to_str(process_pid);
	char * buffer_time = time_t_to_str(timestamp);
	size_t size = sizeof(char)*(sizeof(buffer_pid)*sizeof(buffer_time)*sizeof(name)+3); // 2 whitespaces + \n
	char * buffer = malloc(size); 

	strcpy(buffer, buffer_pid);
	strcat(buffer, " ");
	strcat(buffer, name);
	strcat(buffer, " ");
	strcat(buffer, buffer_time);
	strcat(buffer, "\n");
	_printf(buffer, size);
}

char* transformList(char** list, int size) {
    if(!list) return "";
    char* result = malloc(sizeof(char) * 1024);
    strcpy(result, "");
    int isFirstCommand = 1;
    int isCommand = 1;


    for (int i = 0; i < size-1; i++) {
        if (strcmp(list[i], "|") == 0) {
            strcat(result, "|");
            isCommand=1;
        } else {
            if (!isFirstCommand) {
            strcat(result, " ");
            }
            if (isCommand) {
              strcat(result, list[i]);
              isCommand=0;

            }
            isFirstCommand = 0;
        }
    }

    return result;
}

void transformString(char* str, char **lista) {
    char *token;
    
    // Extrair a primeira palavra antes do primeiro "|" e adicionar à nova string
    token = strtok(str, " ");
    lista[0] = token;
    
    for (int i=1;token!=NULL;i++) {
      token = strtok(NULL, " ");
      lista[i] = token;
    }
    
    
}

int _size(char *str) {
  
    char *token;
    int i;
    
    // Extrair a primeira palavra antes do primeiro "|" e adicionar à nova string
    token = strtok(str, " ");
    
    for (i=1;token!=NULL;i++) {
      token = strtok(NULL, " ");
    }
    
    return i;
  
  }


char *my_strptime(const char *s, const char *format, struct tm *tm_time) {
    char *p = (char *)s;
    int value;
    int year = 0, mon = 0, mday = 0, hour = 0, min = 0, sec = 0;

    while (*format && *p) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'Y':
                    if (sscanf(p, "%4d", &value) != 1) return NULL;
                    year = value;
                    p += 4;
                    break;
                case 'm':
                    if (sscanf(p, "%2d", &value) != 1) return NULL;
                    mon = value - 1; // month is zero-based in struct tm
                    p += 2;
                    break;
                case 'd':
                    if (sscanf(p, "%2d", &value) != 1) return NULL;
                    mday = value;
                    p += 2;
                    break;
                case 'H':
                    if (sscanf(p, "%2d", &value) != 1) return NULL;
                    hour = value;
                    p += 2;
                    break;
                case 'M':
                    if (sscanf(p, "%2d", &value) != 1) return NULL;
                    min = value;
                    p += 2;
                    break;
                case 'S':
                    if (sscanf(p, "%2d", &value) != 1) return NULL;
                    sec = value;
                    p += 2;
                    break;
                default:
                    // unrecognized format specifier
                    return NULL;
            }
            format++;
        } else {
            if (*format != *p) return NULL;
            p++;
            format++;
        }
    }

    tm_time->tm_year = year - 1900; // year is offset by 1900 in struct tm
    tm_time->tm_mon = mon;
    tm_time->tm_mday = mday;
    tm_time->tm_hour = hour;
    tm_time->tm_min = min;
    tm_time->tm_sec = sec;

    return p;
}