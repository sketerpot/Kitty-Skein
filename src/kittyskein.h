#ifndef __KITTYSKEIN_H
#define __KITTYSKEIN_H

#include <stdint.h>

void threefish512_encrypt_block(uint64_t *dest, uint64_t *src, 
				uint64_t *key, uint64_t *tweak);

void threefish512_decrypt_block(uint64_t *dest, uint64_t *src, 
				uint64_t *key, uint64_t *tweak);

void threefish256_encrypt_block(uint64_t *dest, uint64_t *src, 
				uint64_t *key, uint64_t *tweak);

void threefish256_decrypt_block(uint64_t *dest, uint64_t *src, 
				uint64_t *key, uint64_t *tweak);


#endif
