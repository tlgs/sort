import random
import sys

with open(sys.argv[2], "w") as f:
    for _ in range(int(sys.argv[1])):
        f.write(f"{random.randint(-2**31, 2**31 - 1)}\n")
