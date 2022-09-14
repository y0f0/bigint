import random

a = random.randint(1e200, 1e300)
b = random.randint(1e200, 1e300)

with open("out/+.out", "w+") as f:
    f.write(str(a * b))

with open("out/-.out", "w+") as f:
    f.write(str(-a * b))

with open("out/0.out", "w+") as f:
    f.write(str(0))

# ++
with open("in/++.in", "w+") as f:
    f.write(str(a) + "\n")
    f.write(str(b) + "\n")
    f.write("*")

# +-
with open("in/+-.in", "w+") as f:
    f.write(str(a) + "\n")
    f.write(str(-b) + "\n")
    f.write("*")

# -+
with open("in/-+.in", "w+") as f:
    f.write(str(-a) + "\n")
    f.write(str(b) + "\n")
    f.write("*")

# --
with open("in/--.in", "w+") as f:
    f.write(str(-a) + "\n")
    f.write(str(-b) + "\n")
    f.write("*")

# +0
with open("in/+0.in", "w+") as f:
    f.write(str(a) + "\n")
    f.write(str(0) + "\n")
    f.write("*")

# 0+
with open("in/0+.in", "w+") as f:
    f.write(str(0) + "\n")
    f.write(str(a) + "\n")
    f.write("*")

# -0
with open("in/-0.in", "w+") as f:
    f.write(str(-a) + "\n")
    f.write(str(0) + "\n")
    f.write("*")

# 0-
with open("in/0-.in", "w+") as f:
    f.write(str(0) + "\n")
    f.write(str(-a) + "\n")
    f.write("*")

# 00
with open("in/00.in", "w+") as f:
    f.write(str(0) + "\n")
    f.write(str(0) + "\n")
    f.write("*")
