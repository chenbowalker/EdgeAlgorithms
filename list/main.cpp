
#include "list.hpp"

uint64_t metaSize = 0;
char *data = (char *)malloc(4095);

void init() {
    memset(data, 'a', 4095);
    cout << "init ok\n";
}

FreeList *fl = new FreeList();
bool write(char *buffer, uint64_t size, uint64_t offset) {

    uint32_t log_tail = 0;
    char buf[4095];
    // FreeList *fl = new FreeList();
    freeNode *node = fl->freelist_new();
    if (((0xFFFFFFFFFFFFFFFF - offset) < size) || (size == 0)) {
        return false;
    } else {
        int extent = (size + offset - 1) / SEGMENT_SIZE;
        int size_align = ALIGN(size, BLOCK_SIZE);
        if (metaSize == 0 ||
            ((offset + size - 1) / BLOCK_SIZE > (metaSize - 1) / BLOCK_SIZE)) {
            for (int i = 0; i <= extent; i++) {
                if ((log_tail + size_align / BLOCK_SIZE) <= BLOCK_COUNT) {
                    memcpy((char *)(node->addr + log_tail * BLOCK_SIZE), buffer,
                           size);
                    memcpy(buf, (char *)node->addr + log_tail * BLOCK_SIZE,
                           4095);
                    log_tail += size_align / BLOCK_SIZE;
                }
            }
            cout << "log_tail:" << log_tail << endl;
            // memcpy(buf, (char *)node->addr + log_tail * BLOCK_SIZE, 40);
            // memcpy(buf, data, 40);
            printf("%s\n", buf);
        }
        return true;
    }
    // delete fl;
}
int main() {


    FreeList *fl = new FreeList();
    cout << "init..";
    init();
    write(fl,data, 4097, 0);
    write(fl, data, TESTFILESIZE, 0);
    delete fl;
    return 0;
    /**    Debug::debugItem("main..");
        FreeList *fl = new FreeList();
        cout << fl->getSize(); */
    /**
    cout << "init..";
    init();
    write(data, 4095, 0);
    // FreeList *fl = new FreeList();
    // cout <<fl->getSize();
    // delete fl;
    delete fl; */
}
