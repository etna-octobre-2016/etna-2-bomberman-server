#ifndef SOFTWAR_THREAD_H
#define SOFTWAR_THREAD_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1

#include <pthread.h>

///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////

void* thread_handle_bomb(void* data);
void thread_display_map();
void killThread(pthread_t* threads);


#endif
