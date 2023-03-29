# TODO

from cs50 import get_string


def main():

    text = get_string("Text: ")

    index = coleman_liau(text)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade ", index)

    return


def coleman_liau(text):

    letter = 0
    sentence = 0
    word = 1

    for i in text:
        if i.isalpha() == True:
            letter += 1
        elif i.isspace() == True:
            word += 1
        elif i == '.' or i == '?' or i == '!':
            sentence += 1

    L = letter * 100 / word
    S = sentence * 100 / word

    index = 0.0588 * L - 0.296 * S - 15.8

    index = round(index)

    return index


if __name__ == "__main__":
    main()