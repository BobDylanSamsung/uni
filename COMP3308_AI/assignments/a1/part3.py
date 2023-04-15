import re


def task3(message_filename, dictionary_filename, threshold):
    words = set()
    with open(dictionary_filename, "r") as f:
        for line in f.readlines():
            words.add(re.sub(r"[^a-zA-Z0-9]", '', line.strip().lower()))

    num_valid = 0
    num_invalid = 0

    with open(message_filename, "r") as f:
        text = f.read().split()
        for word in text:
            if re.sub(r"[^a-zA-Z0-9]", '', word).lower() in words:
                num_valid += 1
            else:
                num_invalid += 1

    accuracy = round((num_valid / (num_valid + num_invalid)) * 100, 2)
    return "{}\n{:0.2f}".format((accuracy >= threshold), accuracy)


if __name__ == '__main__':
    # Example function calls below, you can add your own to test the task3 function
    print(task3('jingle_bells.txt', 'dict_xmas.txt', 90))
    print(task3('fruit_ode.txt', 'dict_fruit.txt', 80))
    print(task3('amazing_poetry.txt', 'common_words.txt', 95))