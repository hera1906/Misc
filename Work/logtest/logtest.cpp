#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <systemd/sd-journal.h>
#include <bk_common/logger.hpp>

using namespace std;
using namespace bk_common;

volatile bool who;

void *ThreadFunc(void *threadid) 
{
   long tid;
   int count = 0;
   tid = (long)threadid;
   sd_journal_print(LOG_NOTICE, "Hello World! Thread ID %ld", tid);
   for (;;)
   { 
       if (who)
       {
           //sd_journal_print(LOG_NOTICE, "Thread %d", count++);
           Log() << "Thread " << count++;
           who = false;
       }
   }
   pthread_exit(NULL);
}

int main () 
{
    pthread_t thread;
    int rc;
    int count = 0;
    who = false;   
    rc = pthread_create(&thread, NULL, ThreadFunc, (void *)0);
      
    if (rc) 
    {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
    }
    for (;;)
    { 
        if (!who)
        {
            //sd_journal_print(LOG_NOTICE, "Main   %d", count++);
            Log() << "Main   " << count++;
            who = true;
        }
    }
   pthread_exit(NULL);
}
