import random
import math

operation = "~"


def sqrt_(y: int) -> str:  # need wolfram because sqrt() dont work
    left = 0
    right = y + 1
    while left != right - 1:
        m = (left + right) // 2
        if m * m <= y:
            left = m
        else:
            right = m
    return str(left)


def create_test(path):
    l = 1e50
    r = 1e100
    a = random.randint(l, r)

    with open("in/" + path + ".in", "w+") as file:
        file.write(str(a) + "\n")
        file.write(operation)

    with open("out/" + path + ".out", "w+") as file:
        file.write(sqrt_(a))


for i in range(5):
    create_test(str(i))

with open("in/NaN.in", "w+") as f:
    f.write(str(-1) + "\n")
    f.write(operation)

with open("out/NaN.out", "w+") as f:
    f.write(str("NaN"))
