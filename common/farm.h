#ifndef __FARM_H__
#define __FARM_H__

struct fuc_send{
    uint32_t cmd;
    uint32_t data;
    uint32_t status;
};
struct fuc{
    uint32_t dst_addr;
    uint32_t src_addr;
    uint32_t size;
    uint32_t status;
};

#define FUC_MEMCPY_ASYNC 0x1
#define FUC_MEMCPY_SYNC 0x2



#endif

