#ifndef SHM_ACCESS_INCLUDED
#define SHM_ACCESS_INCLUDED

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

class ShmAccess
{
public:
	ShmAccess(int shm_sz, key_t key);
	~ShmAccess();
	void *GetShmAddr();
private:
	void *m_shm_addr;
};

#endif