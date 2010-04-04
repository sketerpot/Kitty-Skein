pattern = '''  v0 += k%d; v1 += k%s; v2 += k%s; v3 += k%s; v4 += k%s;
  v5 += k%s + t%s; v6 += k%s + t%s; v7 += k%s + %s;
  MIXPERMUTE(0);
  MIXPERMUTE(1);
  MIXPERMUTE(2);
  MIXPERMUTE(3);
  v0 += k%d; v1 += k%s; v2 += k%s; v3 += k%s; v4 += k%s;
  v5 += k%s + t%s; v6 += k%s + t%s; v7 += k%s + %s;
  MIXPERMUTE(4);
  MIXPERMUTE(5);
  MIXPERMUTE(6);
  MIXPERMUTE(7);
'''

def subkey(s):
    t = s+1
    print pattern%((s+0) % 9, (s+1) % 9, (s+2) % 9, (s+3) % 9, (s+4) % 9,
                   (s+5) % 9, s % 3, (s+6) % 9, (s+1) % 3, (s+7) % 9, s,
                   (t+0) % 9, (t+1) % 9, (t+2) % 9, (t+3) % 9, (t+4) % 9,
                   (t+5) % 9, t % 3, (t+6) % 9, (t+1) % 3, (t+7) % 9, t)


for s in range(0, 19, 2):
    subkey(s)
