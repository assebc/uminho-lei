#ifndef __TRACER_H__
#define __TRACER_H__

#include "../includes/utils.h"
#include <sys/wait.h>

void notifyUser(int opt, const int process_pid, time_t timestamp);


void notifyMonitor(int opt, const int process_pid, char * program_name, time_t timestamp);
void requests(const int argc, char * argv[]);
int main(const int argc, char * argv []);

#endif