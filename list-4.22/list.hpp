#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include <list>
#include <iostream>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "debug.hpp"

#define LSFS_SIZE (1 << 30)
#define SEGMENT_SIZE (1 << 22)
#define BLOCK_SIZE (1 << 12)
#define BLOCK_COUNT (SEGMENT_SIZE / BLOCK_SIZE)

#define ALIGN(num, align) (((num) + ((align) - 1)) & ~((align) - 1))
using namespace std;

typedef struct freeNode {
    uint64_t addr;
    uint64_t size;
} freeNode;

class FreeList {
  private:
    //FreeList *fl;
    freeNode *node_temp;
    std::list<freeNode *> freelist;
   // bool is_inited = false;
   // void *start;
    int shm_id;
    void *shmptr;

  public:
    freeNode *freelist_new();
    void freelist_free(freeNode *node);
    int getSize();

    FreeList();
    ~FreeList();
};


#endif // end _LIST_H
