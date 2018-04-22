
#include "list.hpp"
#include "debug.hpp"

#define MAX_FILE_SEGMENT_COUNT 20
#define TESTFILESIZE (1 << 22)+2

#define hashLocalNode 0;

typedef uint64_t NodeHash;

typedef struct {
    NodeHash hashNode;
    uint64_t indexSegment;
    uint32_t indexBlockStart;
    uint32_t countBlock;
} FileMetaTuple;

typedef struct {
    time_t timeLastModified;
    uint64_t size;  // file size to write;
    uint32_t count; // segment count;
    FileMetaTuple tuple[MAX_FILE_SEGMENT_COUNT];
} FileMeta;

uint64_t metaSize = 0;
char *data = (char *)malloc(TESTFILESIZE);

void init() {
    memset(data, 'a', TESTFILESIZE);
    cout << "init ok\n";
}

void printMetaFile(FileMeta *metaFile) {
    Debug::debugTitle("printMetaFile:");
    Debug::debugItem("metaFile->size:%lu,count:%lu\n", metaFile->size,
                     metaFile->count);
    for (int i = 0; i <= (int)metaFile->count; i++) {
        Debug::debugItem("metaFile->tuple[%d].indexSegment:%lu,indexBlockStart:"
                         "%lu,countBlock:%lu",
                         i, metaFile->tuple[i].indexSegment,
                         metaFile->tuple[i].indexBlockStart,
                         metaFile->tuple[i].countBlock);
    }
}

bool writeDataByAddress(FileMeta *metaFile, char *buffer) {
    char buf[TESTFILESIZE];
    memcpy(buf, (char *)(metaFile->tuple[0].indexSegment +
                         metaFile->tuple[0].indexBlockStart * BLOCK_SIZE),
           50);
    //    memcpy(buf, buffer, 100);
    return true;
}

bool write(FreeList *fl, char *buffer, uint64_t size, uint64_t offset) {
    Debug::debugTitle("write:");
    uint32_t log_tail = 0;
    char buf[TESTFILESIZE];

    FileMeta *metaFile = (FileMeta *)malloc(sizeof(FileMeta));
    freeNode *node = fl->freelist_new();

    if (((0xFFFFFFFFFFFFFFFF - offset) < size) || (size == 0)) {
        return false;
    } else {

        uint32_t count_blk_cur = 0;
        uint64_t size_align = ALIGN((size + offset), BLOCK_SIZE);
        uint32_t block_count_used = size_align / BLOCK_SIZE;
        uint32_t block_count_used_mod = block_count_used % BLOCK_COUNT;
        int segment = size_align / SEGMENT_SIZE;

        if ((log_tail + block_count_used_mod) >= BLOCK_COUNT) {
            for (int i = 0; i <= segment; i++) {
                metaFile->tuple[segment].hashNode = hashLocalNode;
                metaFile->tuple[segment].indexSegment = node->addr;
                metaFile->tuple[segment].indexBlockStart = log_tail;
                if (i != segment) { // wrong.eg: (1 << 22) + 1;
                    metaFile->tuple[segment].countBlock =
                        BLOCK_COUNT - log_tail;
                    count_blk_cur += metaFile->tuple[segment].countBlock;
                    node = fl->freelist_new();
                    log_tail = 0;
                } else {
                    metaFile->tuple[segment].countBlock =
                        block_count_used - count_blk_cur;
                    count_blk_cur += metaFile->tuple[segment].countBlock;
                    node = fl->freelist_new();
                    log_tail += block_count_used - count_blk_cur;
                }
            }
            metaFile->timeLastModified = time(NULL);
            metaFile->size = (offset + size) > metaFile->size ? (offset + size)
                                                              : metaFile->size;
            metaFile->count = segment;

        } else { // the same segment.
            metaFile->size = (offset + size) > metaFile->size ? (offset + size)
                                                              : metaFile->size;
            metaFile->count = 0; // count of segment.
            metaFile->tuple[0].hashNode = hashLocalNode;
            metaFile->tuple[0].indexSegment = node->addr;
            metaFile->tuple[0].indexBlockStart = log_tail;
            metaFile->tuple[0].countBlock = block_count_used;
            log_tail += block_count_used; // update metadata. possible bug.
        }
        /**
        if (metaSize == 0 ||
            ((offset + size - 1) / BLOCK_SIZE > (metaSize - 1) / BLOCK_SIZE)) {
            for (int i = 0; i <= segment; i++) {
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
        } */

        printMetaFile(metaFile);

        return true;
    }
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
        cout << fl->getSize();
       delete fl;*/
}
