#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "kittyskein.h"

int main(int argc, char **argv) {
  /* Note that these are padded by one for the \0 character */
  char t_ek[65] = "key of 32,64 or 128 bytes lengthkey of 32,64 or 128 bytes length";
  char t_et[17] = "tweak: 16 bytes ";
  char t_msg[65] = "block of data,same length as keyblock of data,same length as key";
  int i;

  for (i=0; i < 64; i++) printf("%u, ", t_msg[i]); printf("\n");

  threefish512_encrypt_block((uint64_t *)t_msg,
			     (uint64_t *)t_msg,
			     (uint64_t *)t_ek,
			     (uint64_t *)t_et);
  
  threefish512_decrypt_block((uint64_t *)t_msg,
			     (uint64_t *)t_msg,
			     (uint64_t *)t_ek,
			     (uint64_t *)t_et);
 
  for (i=0; i < 64; i++) printf("%u, ", t_msg[i]); printf("\n");

  return 0;
}
