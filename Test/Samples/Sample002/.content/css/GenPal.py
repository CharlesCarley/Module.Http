import math


def l_hex(n):
    v = abs(n)
    s = ""
    while (v > 0):
        r = v % 16
        v = int(v / 16)
        if (r >= 10):
            s = chr(ord('a') + r - 10) + s
        else:
            s = chr(ord('0') + r) + s
    return s.rjust(2, '0')


def color(idx, n, m, flr, flg, flb):
    return [
        idx, 
        "%s%s%s;" % (l_hex(n + flr), l_hex(n + flg), l_hex(n + flb)),
        "%s%s%s;" % (l_hex(m + flb), l_hex(m + flg), l_hex(m + flr))
        ]


def flip_sign(x):
    return -x


def pivot(n, inp, steps, flr, flg, flb):
    h = (n / 2)
    ih = int(h)
 
    root = []

    hs = inp * 2
    inp -= steps * abs(ih)
    for i in range(-ih, 0):
        root.append(color(i, inp, hs, flr, flg, flb))
        inp += steps
        hs += steps

    root.append(color(0, inp, hs, flr, flg, flb))
    inp += steps
    hs += steps

    for i in range(1, ih + 1):
        root.append(color(i, inp, hs, flr, flg, flb))
        inp += steps
        hs += steps
    return root


root = pivot(18, 0x3B, 4, 0, 0, 3)

print(":root {")
print("""
    --a-0: #509BD2;
    --a-1: #d25084;
    --a-2: #84d250;
""")
for el in root:
    print("  --c%i: #%s" % (el[0], el[1]))
for el in root:
    print("  --c2%i: #%s" % (el[0], el[2]))
print("}")

for el in root:
    print(".b%i { background-color: var(--c%i); }" % (el[0], el[0]))
    print(".f%i { color: var(--c2%i); }" % (el[0], el[0]))
    print(".bc%i { border-color: var(--c2%i); }" % (el[0], el[0]))
