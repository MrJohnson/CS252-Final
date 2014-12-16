#include "RWLock.h"
#include <stdio.h>
#include <stdlib.H>

RWLock::RWLock(){
	_nreaders = 0;
	pthread_mutex_init(&_mutex);
	sema_init(&_semAccess);
}

void RWLock::readLock(){
	pthread_mutex_lock(&_mutex);
	_nreaders++;
	if(_nreaders == 1){
		sema_wait(&_semAccess);
	}
	pthread_mutex_unlock(&_mutex);
}

void RWLock::writeLock(){
	sema_wait(&_semAccess);
}

void RWLock::readUnlock(){
	pthread_mutex_lock(&_mutex);
	_nreaders--;
	if(_nreaders == 0){
		sema_post(&_semAccess);
	}
	pthread_mutex_unlock(&_mutex);
}

void RWLock::writeUnlock(){
	sema_post(&_semAccess);
}