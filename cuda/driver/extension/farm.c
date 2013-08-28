/*
 * Copyright (C) 2012 Yusuke Fujii
 * Ritsumeikan University
 *
 */

#include "cuda.h"
#include "../gdev_cuda.h"
#include "gdev_api.h"
#include "farm.h"
/*
 * 
 *
*/

CUresult cuSendCmdFuc(uint32_t cmd, uint32_t data){

    Ghandle handle;
    CUresult res;
    struct CUctx_st *ctx;

    if (!gdev_initialized)
	return CUDA_ERROR_NOT_INITIALIZED;

    res = cuCtxGetCurrent(&ctx);
    if (res != CUDA_SUCCESS)
	return res;

    handle = ctx->gdev_handle;
   
    printf("[farm] Command Send To FUC %08x:%08x\n",cmd,data);
    gsendcmd_micro(handle,cmd,data);
    return CUDA_SUCCESS;
}
CUresult cuMemcpyFuc(uint32_t dst, uint32_t src, uint32_t size){

    Ghandle handle;
    CUresult res;
    struct CUctx_st *ctx;

    if (!gdev_initialized)
	return CUDA_ERROR_NOT_INITIALIZED;

    res = cuCtxGetCurrent(&ctx);
    if (res != CUDA_SUCCESS)
    handle = ctx->gdev_handle;
    
    gmemcpy_fuc(handle, dst, src, size, FUC_MEMCPY_SYNC);
    return CUDA_SUCCESS;
}
CUresult cuMemcpyFucAsync(uint32_t dst, uint32_t src, uint32_t size){

    Ghandle handle;
    CUresult res;
    struct CUctx_st *ctx;

    if (!gdev_initialized)
	return CUDA_ERROR_NOT_INITIALIZED;

    res = cuCtxGetCurrent(&ctx);
    if (res != CUDA_SUCCESS)
    handle = ctx->gdev_handle;
   
    gmemcpy_fuc(handle, dst, src, size, FUC_MEMCPY_ASYNC);
    return CUDA_SUCCESS;
}
