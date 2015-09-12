#ifndef SOFTWAR_THREAD_H
#define SOFTWAR_THREAD_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////

void* thread_acceptance(void* data_array);
void* thread_handle_cycle();
void killThread(pthread_t* threads);


#endif
