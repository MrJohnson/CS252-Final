#include <stdio.h>
#include <stdlib.h>
#include <synch.h>

struct List {
  int val;
  int next;
};

struct List * head = NULL;

// More variables
pthread_mutex_t mutexLock;
sema_t fullSem;
sema_t emptySem;

main()
{

 pthread_mutex_init(&mutexLock, NULL);
 sema_init(&fullSem, 20, USYNC_THREAD, NULL);
 sema_init(&emptySem, 0, USYNC_THREAD, NULL);


}

void insert( int val )
{

  sema_wait(&fullSem);
  List tmp = new List;
  tmp->val = val;
  pthread_mutex_lock(&mutexLock);
  tmp->next = head;
  head = tmp;
  ptherad_mutex_unlock(&mutexLock);
  sema_post(&emptySem);

}

Struct List * removeFirst()
{

  sema_wait(&emptySem);
  pthread_mutex_lock()
  List tmp = head;
  head = tmp->next;
  sema_post(&fullSem);
  ptherad_mutex_unlock(&mutexLock);

  return tmp;

}