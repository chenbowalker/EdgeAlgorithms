
#include "list.hpp"

freeNode *FreeList::freelist_new() {
    freeNode *ret = freelist.front();
    freelist.pop_front();

    return ret;
}

void FreeList::freelist_free(freeNode *node) { freelist.push_back(node); }

FreeList::FreeList() {
    /**int fd;
     fd = open("/home/cb/log-structure/hello", O_RDWR);
     start = mmap(NULL, LSFS_SIZE, PROT_READ, MAP_SHARED, fd, 0);
     if (start == MAP_FAILED) {
         printf("open fail;");
     } else {
         for (int i = 0; i < LSFS_SIZE / SEGMENT_SIZE; i++) {
             node_temp = (freeNode *)malloc(sizeof(freeNode));
             node_temp->addr = ((char *)start + i * SEGMENT_SIZE);
             node_temp->size = SEGMENT_SIZE;
             freelist.push_back(node_temp);
         }
     } */
    
  //  shm_id = shmget(66, (1 << 30), 0640 | IPC_CREAT | IPC_EXCL);
    shm_id = shmget(6, LSFS_SIZE, 0640 | IPC_CREAT);
    if (shm_id == -1) {
        cout << "shmget error.";
    }
    shmptr = (void *)shmat(shm_id, NULL, 0);
    if (shmptr == (void *)(-1)) {
        cout << "shmptr error.";
    }

/**
    shm_id = shmget(66, (1 << 30), 0640 | IPC_CREAT | IPC_EXCL);
    if (shm_id == -1) {
        printf("shmget error\n");
    }
    shmptr = (void *)shmat(shm_id, NULL, 0);
    */
    uint64_t dataBaseAddress = (uint64_t)shmptr;
    memset((void *)dataBaseAddress,'\0', LSFS_SIZE);
    for (int i = 0; i < LSFS_SIZE / SEGMENT_SIZE; i++) {
        node_temp = (freeNode *)malloc(sizeof(freeNode));
        node_temp->addr = (dataBaseAddress + i * SEGMENT_SIZE);
        node_temp->size = SEGMENT_SIZE;
        freelist.push_back(node_temp);
    }
}

int FreeList::getSize() { return freelist.size(); }

FreeList::~FreeList() { 
    shmdt(shmptr);
    shmctl(shm_id, IPC_RMID, 0);
}
