#include "shm-access.h"

ShmAccess::ShmAccess(int shm_sz, key_t key)
{
	m_shm_addr = NULL;
	
	int shmid = 0;

    // Create the segment.
    if ((shmid = shmget(key, shm_sz, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
		return;
    }

    // Now we attach the segment to our data space.
    if ((m_shm_addr = shmat(shmid, NULL, 0)) == (void *) -1) {
        perror("shmat");
    }
}

ShmAccess::~ShmAccess()
{

}

void* ShmAccess::GetShmAddr()
{
	return m_shm_addr;
}

