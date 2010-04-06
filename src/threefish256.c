/* Threefish-256 Tweakable Block Cipher */

#include <stdint.h>
#include <stdio.h>
#include "kittyskein.h"
#include "rotation_constants.h"
#include "mix.h"

/* Perform a mixing and permutation step */
#define MIXPERMUTE(D) do {						\
    MIX(RC256_##D##0, v0, v1, f0, f1);					\
    MIX(RC256_##D##1, v2, v3, f2, f3);					\
    v0 = f0; v1 = f3; v2 = f2; v3 = f1;					\
  } while (0)

/* Perform a mixing and permutation step */
#define MIXPERMUTEINV(D) do {						\
    f0 = v0; f1 = v3; f2 = v2; f3 = v1;					\
    MIXINV(RC256_##D##0, v0, v1, f0, f1);				\
    MIXINV(RC256_##D##1, v2, v3, f2, f3);				\
  } while (0)


/* Encrypt a 256-byte block of data */
void threefish256_encrypt_block(uint64_t *dest, uint64_t *src, 
				uint64_t *key, uint64_t *tweak) {
  /* Grab the 8 words of state into registers */
  uint64_t v0 = src[0]; uint64_t v1 = src[1];
  uint64_t v2 = src[2]; uint64_t v3 = src[3];
  /* Snag the key as well */
  uint64_t k0 = key[0]; uint64_t k1 = key[1];
  uint64_t k2 = key[2]; uint64_t k3 = key[3];
  uint64_t k4 = 6148914691236517205 ^ k0 ^ k1 ^ k2 ^ k3;
  /* And the tweak */
  uint64_t t0 = tweak[0]; uint64_t t1 = tweak[1];
  uint64_t t2 = t0 ^ t1;
  /* Some temporary variables: */
  uint64_t f0, f1, f2, f3;

  v0 += k0; v1 += k1 + t0; v2 += k2 + t1; v3 += k3 + 0;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k1; v1 += k2 + t1; v2 += k3 + t2; v3 += k4 + 1;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
  v0 += k2; v1 += k3 + t2; v2 += k4 + t0; v3 += k0 + 2;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k3; v1 += k4 + t0; v2 += k0 + t1; v3 += k1 + 3;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
  v0 += k4; v1 += k0 + t1; v2 += k1 + t2; v3 += k2 + 4;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k0; v1 += k1 + t2; v2 += k2 + t0; v3 += k3 + 5;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
  v0 += k1; v1 += k2 + t0; v2 += k3 + t1; v3 += k4 + 6;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k2; v1 += k3 + t1; v2 += k4 + t2; v3 += k0 + 7;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
  v0 += k3; v1 += k4 + t2; v2 += k0 + t0; v3 += k1 + 8;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k4; v1 += k0 + t0; v2 += k1 + t1; v3 += k2 + 9;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
  v0 += k0; v1 += k1 + t1; v2 += k2 + t2; v3 += k3 + 10;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k1; v1 += k2 + t2; v2 += k3 + t0; v3 += k4 + 11;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
  v0 += k2; v1 += k3 + t0; v2 += k4 + t1; v3 += k0 + 12;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k3; v1 += k4 + t1; v2 += k0 + t2; v3 += k1 + 13;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
  v0 += k4; v1 += k0 + t2; v2 += k1 + t0; v3 += k2 + 14;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k0; v1 += k1 + t0; v2 += k2 + t1; v3 += k3 + 15;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
  v0 += k1; v1 += k2 + t1; v2 += k3 + t2; v3 += k4 + 16;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k2; v1 += k3 + t2; v2 += k4 + t0; v3 += k0 + 17;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);
  v0 += k3; v1 += k4 + t0; v2 += k0 + t1; v3 += k1 + 18;

  /* Store result */
  dest[0] = v0; dest[1] = v1; dest[2] = v2; dest[3] = v3;
}

/* Encrypt a 256-byte block of data */
void threefish256_decrypt_block(uint64_t *dest, uint64_t *src,
				uint64_t *key, uint64_t *tweak) {
  /* Grab the 8 words of state into registers */
  uint64_t v0 = src[0]; uint64_t v1 = src[1];
  uint64_t v2 = src[2]; uint64_t v3 = src[3];
  /* Snag the key as well */
  uint64_t k0 = key[0]; uint64_t k1 = key[1];
  uint64_t k2 = key[2]; uint64_t k3 = key[3];
  uint64_t k4 = 6148914691236517205 ^ k0 ^ k1 ^ k2 ^ k3;
  /* And the tweak */
  uint64_t t0 = tweak[0]; uint64_t t1 = tweak[1];
  uint64_t t2 = t0 ^ t1;
  /* Some temporary variables: */
  uint64_t f0, f1, f2, f3;

  v0 -= k3; v1 -= k4 + t0; v2 -= k0 + t1; v3 -= k1 + 18;
  MIXPERMUTEINV(7); MIXPERMUTEINV(6); MIXPERMUTEINV(5); MIXPERMUTEINV(4);
  v0 -= k2; v1 -= k3 + t2; v2 -= k4 + t0; v3 -= k0 + 17;
  MIXPERMUTEINV(3); MIXPERMUTEINV(2); MIXPERMUTEINV(1); MIXPERMUTEINV(0);
  v0 -= k1; v1 -= k2 + t1; v2 -= k3 + t2; v3 -= k4 + 16;
  MIXPERMUTEINV(7); MIXPERMUTEINV(6); MIXPERMUTEINV(5); MIXPERMUTEINV(4);
  v0 -= k0; v1 -= k1 + t0; v2 -= k2 + t1; v3 -= k3 + 15;
  MIXPERMUTEINV(3); MIXPERMUTEINV(2); MIXPERMUTEINV(1); MIXPERMUTEINV(0);
  v0 -= k4; v1 -= k0 + t2; v2 -= k1 + t0; v3 -= k2 + 14;
  MIXPERMUTEINV(7); MIXPERMUTEINV(6); MIXPERMUTEINV(5); MIXPERMUTEINV(4);
  v0 -= k3; v1 -= k4 + t1; v2 -= k0 + t2; v3 -= k1 + 13;
  MIXPERMUTEINV(3); MIXPERMUTEINV(2); MIXPERMUTEINV(1); MIXPERMUTEINV(0);
  v0 -= k2; v1 -= k3 + t0; v2 -= k4 + t1; v3 -= k0 + 12;
  MIXPERMUTEINV(7); MIXPERMUTEINV(6); MIXPERMUTEINV(5); MIXPERMUTEINV(4);
  v0 -= k1; v1 -= k2 + t2; v2 -= k3 + t0; v3 -= k4 + 11;
  MIXPERMUTEINV(3); MIXPERMUTEINV(2); MIXPERMUTEINV(1); MIXPERMUTEINV(0);
  v0 -= k0; v1 -= k1 + t1; v2 -= k2 + t2; v3 -= k3 + 10;
  MIXPERMUTEINV(7); MIXPERMUTEINV(6); MIXPERMUTEINV(5); MIXPERMUTEINV(4);
  v0 -= k4; v1 -= k0 + t0; v2 -= k1 + t1; v3 -= k2 + 9;
  MIXPERMUTEINV(3); MIXPERMUTEINV(2); MIXPERMUTEINV(1); MIXPERMUTEINV(0);
  v0 -= k3; v1 -= k4 + t2; v2 -= k0 + t0; v3 -= k1 + 8;
  MIXPERMUTEINV(7); MIXPERMUTEINV(6); MIXPERMUTEINV(5); MIXPERMUTEINV(4);
  v0 -= k2; v1 -= k3 + t1; v2 -= k4 + t2; v3 -= k0 + 7;
  MIXPERMUTEINV(3); MIXPERMUTEINV(2); MIXPERMUTEINV(1); MIXPERMUTEINV(0);
  v0 -= k1; v1 -= k2 + t0; v2 -= k3 + t1; v3 -= k4 + 6;
  MIXPERMUTEINV(7); MIXPERMUTEINV(6); MIXPERMUTEINV(5); MIXPERMUTEINV(4);
  v0 -= k0; v1 -= k1 + t2; v2 -= k2 + t0; v3 -= k3 + 5;
  MIXPERMUTEINV(3); MIXPERMUTEINV(2); MIXPERMUTEINV(1); MIXPERMUTEINV(0);
  v0 -= k4; v1 -= k0 + t1; v2 -= k1 + t2; v3 -= k2 + 4;
  MIXPERMUTEINV(7); MIXPERMUTEINV(6); MIXPERMUTEINV(5); MIXPERMUTEINV(4);
  v0 -= k3; v1 -= k4 + t0; v2 -= k0 + t1; v3 -= k1 + 3;
  MIXPERMUTEINV(3); MIXPERMUTEINV(2); MIXPERMUTEINV(1); MIXPERMUTEINV(0);
  v0 -= k2; v1 -= k3 + t2; v2 -= k4 + t0; v3 -= k0 + 2;
  MIXPERMUTEINV(7); MIXPERMUTEINV(6); MIXPERMUTEINV(5); MIXPERMUTEINV(4);
  v0 -= k1; v1 -= k2 + t1; v2 -= k3 + t2; v3 -= k4 + 1;
  MIXPERMUTEINV(3); MIXPERMUTEINV(2); MIXPERMUTEINV(1); MIXPERMUTEINV(0);
  v0 -= k0; v1 -= k1 + t0; v2 -= k2 + t1; v3 -= k3 + 0;

  //  printf("%lu,%lu,%lu,%lu\n", v0, v1, v2, v3);

  /* Store result */
  dest[0] = v0; dest[1] = v1; dest[2] = v2; dest[3] = v3;

}


