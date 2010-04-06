pattern512 = '''  v0 += k%d; v1 += k%s; v2 += k%s; v3 += k%s; v4 += k%s;
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

pattern256 = '''  v0 += k%d; v1 += k%d + t%s; v2 += k%d + t%s; v3 += k%s + %s;
  MIXPERMUTE(0); MIXPERMUTE(1); MIXPERMUTE(2); MIXPERMUTE(3);
  v0 += k%d; v1 += k%d + t%s; v2 += k%d + t%s; v3 += k%s + %s;
  MIXPERMUTE(4); MIXPERMUTE(5); MIXPERMUTE(6); MIXPERMUTE(7);'''

def subkey512(s):
    t = s+1
    print pattern512%((s+0) % 9, (s+1) % 9, (s+2) % 9, (s+3) % 9, (s+4) % 9,
                      (s+5) % 9, s % 3, (s+6) % 9, (s+1) % 3, (s+7) % 9, s,
                      (t+0) % 9, (t+1) % 9, (t+2) % 9, (t+3) % 9, (t+4) % 9,
                      (t+5) % 9, t % 3, (t+6) % 9, (t+1) % 3, (t+7) % 9, t)
    
def subkey256(s):
    t = s+1
    print pattern256%((s+0) % 5, (s+1) % 5, s % 3, (s+2) % 5, (s+1) % 3,
                      (s+3) % 5, s,
                      (t+0) % 5, (t+1) % 5, t % 3, (t+2) % 5, (t+1) % 3,
                      (t+3) % 5, t)

for s in range(0, 18, 2):
    subkey256(s)
