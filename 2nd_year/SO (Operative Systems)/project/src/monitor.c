#include "../includes/monitor.h"


void print_hash_table(GHashTable* hash_table) {
	int fd = open("monitor_to_tracer",O_WRONLY);
	guint size_aux = g_hash_table_size(hash_table);
	guint *size_pointer_aux = &size_aux;
	gpointer *array_aux = g_new(gpointer, size_aux);
	array_aux = g_hash_table_get_keys_as_array(hash_table,size_pointer_aux); 
	char * res = malloc(sizeof(char)*1024);
	int i = 0;
	while (i<(int)size_aux) {
		char* data = strdup((char*)g_hash_table_lookup(hash_table,array_aux[i]));

		strcpy(res, array_aux[i]);

		strcat(res, " | ");

		strtok(data,",");
		strtok(NULL,",");
		char *program = strtok(NULL,",");
		strcat(res, program); 

		strcat(res," | ");

		char *date = strtok(NULL,",");

    	struct tm tm_time = {0};

    	my_strptime(date, "%d-%m-%Y %H:%M:%S", &tm_time);

		time_t data_atual = time(NULL);
    	time_t data_convertida = mktime(&tm_time);

    	double diferenca = difftime(data_convertida, data_atual);

		char str_time[20];

    	sprintf(str_time, "%.2f", diferenca);

		strcat(res,str_time);
		strcat(res,"\n");
		write(fd,res,strlen(res));
		i++;

	}

	close(fd);


}

int main(const int argc, char * argv []){
	HASH_UTILS *ht = newHash_Table();
	mkfifo("tracer_to_monitor",0777);
	mkfifo("monitor_to_tracer",0777);

	
	char buffer[1024];
    ssize_t bytes_read;

	if(argc < 2){
		fprintf(stderr, "ERROR: Invalid number of arguments!\n");
		return 1;
	}

	int tracer = open("tracer_to_monitor", O_RDONLY);
	if (tracer == -1) {
		perror("Failed to open tracer_to_monitor pipe");
		exit(1);
	}

	open("tracer_to_monitor",O_WRONLY); // Pomos isto de forma a evitar um while (1) e uma espera ativa


	if(!exists_dir(argv[1])){
		char result_dir[100];
		sprintf(result_dir,"../%s",argv[1]);
		make_dir(result_dir);
	} 


	while((bytes_read = read(tracer, buffer, sizeof(buffer))) > 0) {
		char result[100];
		char* string_copy = strdup(buffer);
		char* str_final = strdup(buffer);

		char *startPtr, *endPtr;

		startPtr = strchr(str_final, ',');
		startPtr++; 
		endPtr = strchr(startPtr, '\0');
		if (endPtr == NULL) {
        	printf("Erro: String de entrada inválida\n");
        	return 1;
    	}


		strtok(str_final,",");


		char* token = strtok(string_copy, ",");
		int opt = atoi(token);
		char* id = strtok(NULL, ","); 

		if (opt == 0) {
			sprintf(result,"../%s/%s",argv[1],"log.txt");
			write_file_append(result,startPtr);
			insert_PIDS(ht,id,buffer);
		}
		if (opt==1){
			sprintf(result,"../%s/%s.txt",argv[1],id);

			char * aux = strdup(startPtr);
			strtok(aux,",");
			strtok(NULL, ",");

			char *date = strtok(NULL,",");

    		struct tm tm_time = {0};

    		my_strptime(date, "%d-%m-%Y %H:%M:%S", &tm_time);

    		time_t data_convertida = mktime(&tm_time);

			char * info = g_hash_table_lookup(getHashTable(ht),id);

			strtok(info,",");
			char * program = strtok(NULL,",");
			strtok(NULL,",");

			char *date2 = strtok(NULL,",");

			struct tm tm_time2 = {0};

    		my_strptime(date2, "%d-%m-%Y %H:%M:%S", &tm_time2);

    		time_t data_convertida2 = mktime(&tm_time2);

			double diferenca = difftime(data_convertida, data_convertida2);

			char str_time[20];

    		sprintf(str_time, "%.2f", diferenca);

			char res[100];

			sprintf(res, "%s,%s,%s s\n",id,program,str_time);

			write_file_append(result,res);
			delete_PID(ht,id);
		}
		if (opt==2) {
			print_hash_table(getHashTable(ht));			
		}
		free(string_copy);
	}

	close(tracer);

	return 0;
}
