# TODO
from cs50 import get_int


def main():

    # Get card number and turn into a list to iterate through it
    card_number = get_int("Number: ")
    card_type = int(str(card_number)[:2])
    card_number = list(map(int, str(card_number)))

    checksum = 0

    # Reverse list and iterate through it
    for digit in enumerate(reversed(card_number)):

        # If odd index multiply card digit and sum the two separate digits
        if digit[0] % 2 > 0:

            result = map(int, str(digit[1] * 2))
            checksum = checksum + sum(result)

        # Sum digits together
        else:
            checksum = checksum + digit[1]

    # Check to see if card is valid
    if checksum % 10 == 0 and 12 < len(card_number) < 17 and len(card_number) != 14:

        if (card_type == 34 or card_type == 37):
            print("AMEX")

        elif (40 <= card_type <= 49):
            print("VISA")

        elif (51 <= card_type <= 55):
            print("MASTERCARD")

        else:
            print("INVALID")

    else:
        print("INVALID")


if __name__ == "__main__":
    main()