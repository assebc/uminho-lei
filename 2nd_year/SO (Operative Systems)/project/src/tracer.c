#include "../includes/tracer.h"

void notifyUser(int opt, const int process_pid, time_t timestamp){
	char * pid_str = int_to_str(process_pid);
	char * timestamp_str = time_t_to_str(timestamp);
	char * buffer;
	size_t size;
	
	switch(opt){
		case START: // running pid
			size = sizeof(char)*(12+strlen(pid_str))+1;
			buffer = malloc(size);
			strcpy(buffer,"Running PID ");
			strcat(buffer, pid_str);
			strcat(buffer, "\n");
			_printf(buffer, size);
			break;

		case END: // end program
			size = sizeof(char)*(9+strlen(timestamp_str))+1;
			buffer = malloc(size);
			strcpy(buffer, "Ended in ");
			strcat(buffer, timestamp_str);
			strcat(buffer, "\n");
			_printf(buffer,size);
			break;

		default:
			_printf("Option is invalid, try again!\n", 31);

	}
}

void notifyMonitor(int opt, const int process_pid, char * program_name, time_t timestamp){
	char result[100];
	char time_str[20];
	time_t now = time(NULL);
	timestamp++;
	strftime(time_str, 20, "%d-%m-%Y %H:%M:%S", localtime(&now)); 
    sprintf(result, "%d,%d,%s,%s\n",opt, process_pid, program_name, time_str);
	int fd = open("tracer_to_monitor",O_WRONLY);
	write(fd,result,sizeof(result));
	close(fd);
}

void execute_program(char ** program_cmd) {
	execvp(program_cmd[0],program_cmd);

}

void requests(const int argc, char * argv []){
	if (strcmp(argv[1], "execute") == 0){
		if (strcmp(argv[2], "-u") == 0){ // one program
			int process_pid = getpid();
			char ** program_cmd = getProgram(argc, argv, 3);

			char*lista[100];

			char *copia = strdup(program_cmd[0]);

    		transformString(copia,lista);

			char * program_name = lista[0]; 

			time_t start = time(NULL), end;
			notifyMonitor(START, process_pid, program_name,start);
			notifyUser(START,process_pid, 0); 

			pid_t pid = fork();


			if (pid == 0) {
				// Processo filho
				execute_program(lista);
				perror("Erro ao executar o programa");
				_exit(1);
			} else if (pid > 0) {
				int status;
				waitpid(pid, &status, 0);
			}

			end = time(NULL);
			notifyMonitor(1, process_pid, program_name, end);
			notifyUser(END,process_pid, end-start);

		} else if (strcmp(argv[2], "-p") == 0){ // (extra) FIXME: programs' pipeline
			int process_pid = getpid();
			char **program_cmd = getProgram(argc, argv, 3);

    		char*lista[100];

			char *copia = strdup(program_cmd[0]);

    		transformString(copia,lista);
    
    		char * program_name = transformList(lista, _size(program_cmd[0]));
			time_t start = time(NULL), end;
			notifyMonitor(START,process_pid,program_name,start);
			notifyUser(START,process_pid, 0);

			pid_t pid = fork();


			if (pid == 0) {
				execute_program(lista);
				perror("Erro ao executar o programa");
				_exit(1);
			} else if (pid > 0) {
				int status;
				waitpid(pid, &status, 0);
			}

			end = time(NULL);

			notifyMonitor(END, process_pid, program_name, end);
			notifyUser(END,process_pid, end-start);
		}
    
	} else if (strcmp(argv[1], "status") == 0){  
		int process_pid = getpid();
		notifyMonitor(2, process_pid," ",get_timeofday());

		int monitor_to_tracer = open("monitor_to_tracer", O_RDONLY);
		if (monitor_to_tracer == -1) {
			perror("Failed to open monitor_to_tracer pipe");
			exit(1);
		}

		char buffer[1024];
    	ssize_t bytes_read;

		while((bytes_read = read(monitor_to_tracer, buffer, sizeof(buffer))) > 0) {
			//buffer[bytes_read] = '\0';
			_printf(buffer,bytes_read);
		}

		close(monitor_to_tracer);


	} else if (strcmp(argv[1], "stats-time") == 0){ 
	// (extra) TODO: status program to count time of ended commands 

	} else if (strcmp(argv[1], "stats-command") == 0){ 
	// (extra) TODO: number of times programs been executed

	} else if (strcmp(argv[1], "stats-uniq") == 0) { 
	// (extra) TODO: list of unique programs executed 

	}

	//close fifos
}

int main(const int argc, char * argv []){

	if(argc < 2){
		fprintf(stderr, "ERROR: Invalid number of arguments!\n");
		return 1;
	} 

	requests(argc, argv);
	return 0;
}