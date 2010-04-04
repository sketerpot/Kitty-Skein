#ifndef __MIX_H
#define __MIX_X

/* Take A and rotate it SHIFT bits to the left. Both A and SHIFT
   should be simple variables or constants, for safety. */
#define ROTATE_LEFT(A, SHIFT) (A << SHIFT | A >> (sizeof(A) * 8 - SHIFT))

/* The MIX_{d,j} function takes inputs (x0, x1) and gives outputs (y0,
   y1). It depends on the rotation constant given, which should be
   specified as an argument to the macro. */
#define MIX(ROTCONST, X0, X1, Y0, Y1) do { \
  Y0 = X0 + X1; \
  Y1 = ROTATE_LEFT(X1, ROTCONST) ^ Y0; \
  } while (0)

#endif
