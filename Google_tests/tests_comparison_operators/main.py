import random


def create_three_test(operator):
    small = random.randint(1e100, 1e150)
    big = random.randint(small, 1e300)

    with open("in/" + operator + "s.in", "w+") as f:
        f.write(str(big) + "\n")
        f.write(str(small) + "\n")
        f.write(operator)

    with open("in/" + operator + "b.in", "w+") as f:
        f.write(str(small) + "\n")
        f.write(str(big) + "\n")
        f.write(operator)

    with open("in/" + operator + "e.in", "w+") as f:
        f.write(str(small) + "\n")
        f.write(str(small) + "\n")
        f.write(operator)


for operator in {"<", "<=", ">", ">=", "==", "!="}:
    create_three_test(operator)
