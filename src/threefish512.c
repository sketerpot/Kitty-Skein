/* Threefish-512 Tweakable Block Cipher */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rotation_constants.h"
#include "mix.h"

/* Perform a mixing and permutation step */
#define MIXPERMUTE(D) do {						\
    MIX(RC512_##D##0, v0, v1, f0, f1);					\
    MIX(RC512_##D##1, v2, v3, f2, f3);					\
    MIX(RC512_##D##2, v4, v5, f4, f5);					\
    MIX(RC512_##D##3, v6, v7, f6, f7);					\
    v0 = f2; v1 = f1; v2 = f4; v3 = f7; v4 = f6; v5 = f5; v6 = f0; v7 = f3; \
  } while (0)

/* Encrypt a 512-byte block of data, n times. */
void threefish512_encrypt_block(uint64_t *dest, uint64_t *src, 
				uint64_t *key, uint64_t *tweak, int n) {
  /* Grab the 8 words of state into registers */
  uint64_t v0 = src[0]; uint64_t v1 = src[1];
  uint64_t v2 = src[2]; uint64_t v3 = src[3];
  uint64_t v4 = src[4]; uint64_t v5 = src[5];
  uint64_t v6 = src[6]; uint64_t v7 = src[7];
  /* Snag the key as well */
  uint64_t k0 = key[0]; uint64_t k1 = key[1];
  uint64_t k2 = key[2]; uint64_t k3 = key[3];
  uint64_t k4 = key[4]; uint64_t k5 = key[5];
  uint64_t k6 = key[6]; uint64_t k7 = key[7];
  uint64_t k8 = 6148914691236517205 ^ k0 ^ k1 ^ k2 ^ k3 ^ k4 ^ k5 ^ k6 ^ k7;
  /* And the tweak */
  uint64_t t0 = tweak[0]; uint64_t t1 = tweak[1];
  uint64_t t2 = t0 ^ t1;
  /* Some temporary variables: */
  uint64_t f0, f1, f2, f3, f4, f5, f6, f7;

  //  printf("%lu,%lu,%lu,%lu\n%lu,%lu,%lu,%lu\n\n",
  //	 v0, v1, v2, v3, v4, v5, v6, v7);
  int i;
  for (i=0; i < n; i++) {
    v0 += k0; v1 += k1; v2 += k2; v3 += k3; v4 += k4;
    v5 += k5 + t0; v6 += k6 + t1; v7 += k7 + 0;
    MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
    v0 += k1; v1 += k2; v2 += k3; v3 += k4; v4 += k5;
    v5 += k6 + t1; v6 += k7 + t2; v7 += k8 + 1;
    MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
    v0 += k2; v1 += k3; v2 += k4; v3 += k5; v4 += k6;
    v5 += k7 + t2; v6 += k8 + t0; v7 += k0 + 2;
    MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
    v0 += k3; v1 += k4; v2 += k5; v3 += k6; v4 += k7;
    v5 += k8 + t0; v6 += k0 + t1; v7 += k1 + 3;
    MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
    v0 += k4; v1 += k5; v2 += k6; v3 += k7; v4 += k8;
    v5 += k0 + t1; v6 += k1 + t2; v7 += k2 + 4;
    MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
    v0 += k5; v1 += k6; v2 += k7; v3 += k8; v4 += k0;
    v5 += k1 + t2; v6 += k2 + t0; v7 += k3 + 5;
    MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
    v0 += k6; v1 += k7; v2 += k8; v3 += k0; v4 += k1;
    v5 += k2 + t0; v6 += k3 + t1; v7 += k4 + 6;
    MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
    v0 += k7; v1 += k8; v2 += k0; v3 += k1; v4 += k2;
    v5 += k3 + t1; v6 += k4 + t2; v7 += k5 + 7;
    MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
    v0 += k8; v1 += k0; v2 += k1; v3 += k2; v4 += k3;
    v5 += k4 + t2; v6 += k5 + t0; v7 += k6 + 8;
    MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
    v0 += k0; v1 += k1; v2 += k2; v3 += k3; v4 += k4;
    v5 += k5 + t0; v6 += k6 + t1; v7 += k7 + 9;
    MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
    v0 += k1; v1 += k2; v2 += k3; v3 += k4; v4 += k5;
    v5 += k6 + t1; v6 += k7 + t2; v7 += k8 + 10;
    MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
    v0 += k2; v1 += k3; v2 += k4; v3 += k5; v4 += k6;
    v5 += k7 + t2; v6 += k8 + t0; v7 += k0 + 11;
    MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
    v0 += k3; v1 += k4; v2 += k5; v3 += k6; v4 += k7;
    v5 += k8 + t0; v6 += k0 + t1; v7 += k1 + 12;
    MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
    v0 += k4; v1 += k5; v2 += k6; v3 += k7; v4 += k8;
    v5 += k0 + t1; v6 += k1 + t2; v7 += k2 + 13;
    MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
    v0 += k5; v1 += k6; v2 += k7; v3 += k8; v4 += k0;
    v5 += k1 + t2; v6 += k2 + t0; v7 += k3 + 14;
    MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
    v0 += k6; v1 += k7; v2 += k8; v3 += k0; v4 += k1;
    v5 += k2 + t0; v6 += k3 + t1; v7 += k4 + 15;
    MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
    v0 += k7; v1 += k8; v2 += k0; v3 += k1; v4 += k2;
    v5 += k3 + t1; v6 += k4 + t2; v7 += k5 + 16;
    MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
    v0 += k8; v1 += k0; v2 += k1; v3 += k2; v4 += k3;
    v5 += k4 + t2; v6 += k5 + t0; v7 += k6 + 17;
    MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
    v0 += k0; v1 += k1; v2 += k2; v3 += k3; v4 += k4;
    v5 += k5 + t0; v6 += k6 + t1; v7 += k7 + 18;
  }
  /* Store result */
  dest[0] = v0; dest[1] = v1; dest[2] = v2; dest[3] = v3;
  dest[4] = v4; dest[5] = v5; dest[6] = v6; dest[7] = v7;  

  //printf("%lu,%lu,%lu,%lu\n%lu,%lu,%lu,%lu\n",
  //	 v0, v1, v2, v3, v4, v5, v6, v7);
}

uint64_t xormsg(uint64_t *msg) {
  int i; uint64_t acc = 0;
  for (i=0; i < 8; i++)
    acc ^= msg[i];
  return acc;
}

int main(int argc, char **argv) {
  /* Note that these are padded by one for the \0 character */
  char t_ek[65] = "key of 32,64 or 128 bytes lengthkey of 32,64 or 128 bytes length";
  char t_et[17] = "tweak: 16 bytes ";
  char t_msg[65] = "block of data,same length as keyblock of data,same length as key";
  char ciphertext[65];
  int n;

  if (argc != 2) {
    fprintf(stderr, "usage: %s [iterations]\n", argv[0]);
    exit(1);
  }

  n = atoi(argv[1]);
  
  threefish512_encrypt_block((uint64_t *)t_msg,
			     (uint64_t *)t_msg,
			     (uint64_t *)t_ek,
			     (uint64_t *)t_et, n);
  
  printf("%lu\n", xormsg((uint64_t *)t_msg));
  return 0;
}
