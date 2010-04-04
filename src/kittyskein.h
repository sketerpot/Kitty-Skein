#ifndef __KITTYSKEIN_H
#define __KITTYSKEIN_H

#include <stdint.h>

void threefish512_encrypt_block(uint64_t *dest, uint64_t *src, 
				uint64_t *key, uint64_t *tweak, int n);

#endif
