/*
 * Copyright (C) 2011 Shinpei Kato
 *
 * Systems Research Lab, University of California at Santa Cruz
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __GDEV_CUDA_UTIL_H__
#define __GDEV_CUDA_UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <elf.h>
#include <limits.h>
#if (ULONG_MAX == UINT_MAX)
#define Elf_Ehdr Elf32_Ehdr
#define Elf_Shdr Elf32_Shdr
#define Elf_Phdr Elf32_Phdr
#define Elf_Sym	 Elf32_Sym
#else
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Shdr Elf64_Shdr
#define Elf_Phdr Elf64_Phdr
#define Elf_Sym	 Elf64_Sym
#endif
typedef FILE file_t;
#define FOPEN(fname) fopen(fname, "rb")
#define FSEEK(fp, offset, whence) fseek(fp, 0, whence)
#define FTELL(fp) ftell(fp)
#define FREAD(ptr, size, fp) fread(ptr, size, 1, fp)
#define FCLOSE(fp) fclose(fp)
#define MALLOC(x) malloc(x)
#define FREE(x) free(x)
#define GDEV_PRINT(fmt, arg...) fprintf(stderr, "[gdev] " fmt, ##arg)

/* a bit wild coding... */
static inline int __gdev_get_device_count(void)
{
	char fname[256] = "/proc/gdev/virtual_device_count";
	char buf[16];
	int minor = 0;
	FILE *fp;

	if (!(fp = fopen(fname, "r"))) {
		/* this is the case for non-gdev device drivers. */
		struct stat st;
		/* check for Linux open-source drivers first. */
		for (;;) {
			sprintf(fname, "/dev/dri/card%d", minor);
			if (stat(fname, &st))
				break;
			minor++;
		}
		if (minor)
			return minor;
		/* check for NVIDIA BLOB drivers next. */
		for (;;) {
			sprintf(fname, "/dev/nvidia%d", minor);
			if (stat(fname, &st))
				break;
			minor++;
		}
		return minor;
	}
	if (!fgets(buf, 16, fp))
		sprintf(buf, "0");
	fclose(fp);

	sscanf(buf, "%d", &minor);

	return minor;
}


#endif
