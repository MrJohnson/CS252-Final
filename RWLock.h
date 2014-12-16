class RWLock{
	int _nreaders;
	sema_t _semAccess;
	mutex_t _mutex;
	
	public:
		RWLock();
		void readLock();
		void writeLock();
		void readUnlock();
		void writeUnlock();
}