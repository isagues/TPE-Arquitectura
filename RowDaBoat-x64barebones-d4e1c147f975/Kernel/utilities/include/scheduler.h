#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

uint64_t scheduler(uint64_t rsp);

//Starts with default (neutral) priority. Retorna el PID del proceso. Ante un error devuelve 0 (no existe PID 0).
uint16_t initializeProccess(int (*function)(int , char **), char* name, uint8_t fg, int argc, char ** argv);

void loader2(int argc, char *argv[], int (*function)(int , char **));

void kill(uint16_t pid);

void exit();

uint16_t getPID();

void dumpScheduler();

void initScheduler();

void changeProccessPriority(uint16_t pid, uint8_t prority);

#endif