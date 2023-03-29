# TODO
from cs50 import get_int


def main():

    while True:
        height = get_int("Height: ")
        if 1 <= height <= 8:
            break

    for row in range(height):

        for space in range(height - row - 1, 0, -1):
            print(" ", end="")

        for hash in range(row + 1):
            print("#", end="")

        print("  ", end="")

        for right_hash in range(row + 1):
            print("#", end="")

        print("\n", end="")


if __name__ == "__main__":
    main()