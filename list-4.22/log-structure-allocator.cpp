#include <iostream>
#include "list.hpp"
#include "debug.hpp"

#define ALIGN(num, align) (((num) + ((align) - 1)) & ~((align) - 1))

uint32_t segmentCreatedNum(uint32_t log_tail_bak, uint32_t block_count_used) {
    uint32_t segment = 0;
    uint32_t log_tail = log_tail_bak;
    uint32_t count = 0;
    if ((log_tail_bak + block_count_used) >=
        BLOCK_COUNT) { // segment need be created.
        if ((log_tail_bak + block_count_used) == BLOCK_COUNT) { // ok.
            segment = 0; // freelist_new();
            log_tail = 0;
            Debug::debugItem("log_tail:%lu,segment:%lu", log_tail, segment);
            return segment;
        } else {
            uint32_t seg = block_count_used / BLOCK_COUNT;
            if (seg == 0) { // ok.
                segment++; // fill into metaFile.
                log_tail = ((log_tail_bak + block_count_used) % BLOCK_COUNT);
                Debug::debugItem("log_tail:%lu,segment:%lu", log_tail, segment);
                return segment;
            } else {
                for (uint32_t i = 0; i <= seg; i++) {
                    if (i == 0) {
                        count = BLOCK_COUNT - log_tail;
                        log_tail = 0;
                        segment = 0;
                    } else if (i != seg) {
                        count += BLOCK_COUNT;
                        log_tail = 0;
                        segment++;
                    } else {
                        if ((block_count_used - count) < BLOCK_COUNT) {
                            log_tail += ((block_count_used - count));
                            segment++;
                        } else if ((block_count_used - count) == BLOCK_COUNT) {
                            segment++;
                            log_tail = 0;
                        } else {
                            log_tail +=
                                (block_count_used - count - BLOCK_COUNT);
                            segment += 2;
                        }
                    }
                }
                if (log_tail ==
                    ((log_tail_bak + block_count_used) % BLOCK_COUNT)) {
                    Debug::debugItem("log_tail:%lu,segment:%lu", log_tail,
                                     segment);
                    return segment;
                } else {
                    Debug::debugItem("count error.");
                    return 0;
                }
            }
        }
    } else {
        segment = 0;
        log_tail += block_count_used;
        Debug::debugItem("log_tail:%lu,segment:%lu", log_tail, segment);
        return segment;
    }
}

int main() {
    /**
    Debug::debugTitle("main......");
    int num = 4096;
    int align = 4096;
    std::cout << ALIGN(num, align);*/
    int J = 6;
    uint32_t tail = 1022;
//  uint32_t block[] = { 1, 2, 3, 1025, 1026, 1027 };// ok
    uint32_t block[] = {1024, 2048, 4096, 0, 92160, 102400};
    for (int j = 0; j < J; j++) {
        segmentCreatedNum(tail, block[j]);
    }
}
