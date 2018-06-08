print("Brute force")
def isRotationBruteForce(s1, s2):
    orig = s2

    if len(s1) != len(s2):
        print(s2 + " and " + s1 + " are not of the same length")
        return False

    for i in range(len(s1)):
        for j in range(len(s1)):
            if s1[j] != s2[j]:
                break
            if j == len(s1)-1:
                print(orig + " is a rotation of " + s1)
                return True
        s2 = s2[1:] + s2[0]

    print(orig + " is not a rotation of " + s1)
    return False

isRotationBruteForce("testthis", "thistest")
isRotationBruteForce("testthat", "thistest")
isRotationBruteForce("notsame", "length")

# Caso promedio: (n/2)*(n/2) => O(n^2)
# Peor caso: n*n => O(n^2)


print("\nKMP:")

def compPrefix(s):
    n = len(s)

    p = list(range(n))
    p[0] = 0

    k = 0
    
    for i in range(1, n):
        while k > 0 and s[k+1] != s[i]:
            k = p[k]
        if s[k+1] == s[i]:
            k += 1
        p[i] = k

    return p

def isRotationKMP(t, p):
    orig = p
    
    n = len(t)
    m = len(p)

    if n != m:
        print(p + " and " + t + " are not of the same length")
        return False
    
    q = 0
    
    for c in range(n):
        pref = compPrefix(p)
        for i in range(n):
            while q > 0 and p[q] != t[i]:
                q = pref[q-1]

            if p[q] == t[i]:
                q += 1

            if q == m:
                print(orig + " is a rotation of " + t)
                q = pref[q-1]
                return True

        p = p[1:] + p[0]
                
    print(p + " is not a rotation of " + t)
    return False

isRotationKMP("testthis", "thistest")
isRotationKMP("testthat", "thistest")
isRotationKMP("notsame", "length")


print("\nKMP improved:")

def isRotationKMPImproved(t, p):
    orig = t
    
    if len(t) != len(p):
        print(p + " and " + t + " are not of the same length")
        return False
    
    t = t + t
    q = 0
    m = len(p)
    n = len(t)

    pref = compPrefix(p)
    for i in range(n):
        while q > 0 and p[q] != t[i]:
            q = pref[q-1]

        if p[q] == t[i]:
            q += 1

        if q == m:
            print(p + " is a rotation of " + orig)
            q = pref[q-1]
            return True

    print(p + " is not a rotation of " + orig)
    return False

isRotationKMPImproved("testthis", "thistest")
isRotationKMPImproved("testthat", "thistest")
isRotationKMPImproved("notsame", "length")
