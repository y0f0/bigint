import random

l = 1e200
r = 1e300
a = random.randint(l, r)
b = random.randint(l, r)

operation = "-"

# ++
with open("in/++.in", "w+") as f:
    f.write(str(a) + "\n")
    f.write(str(b) + "\n")
    f.write(operation)

with open("out/++.out", "w+") as f:
    f.write(str(a - b))

# +-
with open("in/+-.in", "w+") as f:
    f.write(str(a) + "\n")
    f.write(str(-b) + "\n")
    f.write(operation)

with open("out/+-.out", "w+") as f:
    f.write(str(a - -b))

# -+
with open("in/-+.in", "w+") as f:
    f.write(str(-a) + "\n")
    f.write(str(b) + "\n")
    f.write(operation)

with open("out/-+.out", "w+") as f:
    f.write(str(-a - b))

# --
with open("in/--.in", "w+") as f:
    f.write(str(-a) + "\n")
    f.write(str(-b) + "\n")
    f.write(operation)

with open("out/--.out", "w+") as f:
    f.write(str(-a - - b))

# +0
with open("in/+0.in", "w+") as f:
    f.write(str(a) + "\n")
    f.write(str(0) + "\n")
    f.write(operation)

with open("out/+0.out", "w+") as f:
    f.write(str(a - 0))

# 0+
with open("in/0+.in", "w+") as f:
    f.write(str(0) + "\n")
    f.write(str(a) + "\n")
    f.write(operation)

with open("out/0+.out", "w+") as f:
    f.write(str(0 - a))

# -0
with open("in/-0.in", "w+") as f:
    f.write(str(-a) + "\n")
    f.write(str(0) + "\n")
    f.write(operation)

with open("out/-0.out", "w+") as f:
    f.write(str(-a - 0))

# 0-
with open("in/0-.in", "w+") as f:
    f.write(str(0) + "\n")
    f.write(str(-a) + "\n")
    f.write(operation)

with open("out/0-.out", "w+") as f:
    f.write(str(0 - -a))

# 00
with open("in/00.in", "w+") as f:
    f.write(str(0) + "\n")
    f.write(str(0) + "\n")
    f.write(operation)

with open("out/00.out", "w+") as f:
    f.write(str(0 - 0))
