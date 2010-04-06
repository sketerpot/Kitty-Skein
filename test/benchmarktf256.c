#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "kittyskein.h"

uint64_t xormsg(uint64_t *msg) {
  int i; uint64_t acc = 0;
  for (i=0; i < 4; i++)
    acc ^= msg[i];
  return acc;
}

int main(int argc, char **argv) {
  /* Note that these are padded by one for the \0 character */
  char t_ek[65] = "key of 32,64 or 128 bytes length";
  char t_et[17] = "tweak: 16 bytes ";
  char t_msg[65] = "block of data,same length as key";
  int n, i;

  if (argc != 3) {
    fprintf(stderr, "usage: %s [e/d] [iterations]\n", argv[0]);
    exit(1);
  }

  n = atoi(argv[2]);
  
  if (argv[1][0] == 'e')
    for (i=0; i < n; i++)
      threefish256_encrypt_block((uint64_t *)t_msg,
				 (uint64_t *)t_msg,
				 (uint64_t *)t_ek,
				 (uint64_t *)t_et);
  else
    for (i=0; i < n; i++)
      threefish256_decrypt_block((uint64_t *)t_msg,
				 (uint64_t *)t_msg,
				 (uint64_t *)t_ek,
				 (uint64_t *)t_et);
  
  printf("%lu\n", xormsg((uint64_t *)t_msg));
  return 0;
}
