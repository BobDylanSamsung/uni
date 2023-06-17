import itertools
import re
import sys
from utils import Node


def dfs(root, keys, debug, valid_words, threshold, depth_limit=None):
    fringe: list[Node] = [root]
    num_expanded = 0
    max_fringe_len = 0
    max_depth = 0
    first_few_expanded = []
    current = None

    while len(fringe) > 0 and num_expanded < 1000:
        print(num_expanded, id(current) if current is not None else None)
        if len(fringe) > max_fringe_len:
            max_fringe_len = len(fringe)

        current = fringe.pop(0)

        if current.depth > max_depth:
            max_depth = current.depth

        if num_expanded < 10:
            first_few_expanded.append(current.message)

        current.calc_accuracy(valid_words)

        if current.accuracy >= threshold:
            ret = (
                f"Solution: {current.message}\n\n"
                f"Key: {current.key[-2:]}\n"
                f"Path Cost: {current.depth}\n\n"
                f"Num nodes expanded: {num_expanded}\n"
                f"Max fringe size: {max_fringe_len}\n"
                f"Max depth: {max_depth}"
            )
            if debug == "y":
                ret += "\n\nFirst few expanded states:\n"
                ret += "\n\n".join(first_few_expanded)
            print(ret)
            return ret

        num_expanded += 1

        if depth_limit is None or current.depth < depth_limit:
            current.create_children(keys)
            fringe = current.children[::-1] + fringe

    ret = f"""No solution found\n\n
                Key: {current.key[-2:]}\n
                Path Cost: {current.depth}\n\n
                Num nodes expanded: {num_expanded}\n
                Max fringe size: {max_fringe_len}\n
                Max depth: {max_depth}"""
    if debug == "y":
        ret += "First few expanded states:\n"
        ret += "\n\n".join(first_few_expanded)

    return ret, num_expanded


def ids(initial_msg, keys, debug, valid_words, threshold):
    num_expanded = 0
    max_fringe_len = 0
    max_depth = 0
    first_few_expanded = []
    current = None

    depth_limit = 1
    while num_expanded < 1000:
        fringe = [Node("", initial_msg, 0)]
        while len(fringe) > 0:
            print(num_expanded, id(current) if current is not None else None)
            if len(fringe) > max_fringe_len:
                max_fringe_len = len(fringe)

            current = fringe.pop(0)

            if current.depth > max_depth:
                max_depth = current.depth

            if num_expanded < 10:
                first_few_expanded.append(current.message)

            current.calc_accuracy(valid_words)

            if current.accuracy >= threshold:
                ret = (
                    f"Solution: {current.message}\n\n"
                    f"Key: {current.key[-2:]}\n"
                    f"Path Cost: {current.depth}\n\n"
                    f"Num nodes expanded: {num_expanded}\n"
                    f"Max fringe size: {max_fringe_len}\n"
                    f"Max depth: {max_depth}"
                )
                if debug == "y":
                    ret += "\n\nFirst few expanded states:\n"
                    ret += "\n\n".join(first_few_expanded)
                print(ret)
                return ret

            num_expanded += 1

            if depth_limit is None or current.depth < depth_limit:
                current.create_children(keys)
                fringe = current.children[::-1] + fringe

        depth_limit += 1

    ret = f"""No solution found\n\n
                Key: {current.key[-2:]}\n
                Path Cost: {current.depth}\n\n
                Num nodes expanded: {num_expanded}\n
                Max fringe size: {max_fringe_len}\n
                Max depth: {max_depth}"""
    if debug == "y":
        ret += "First few expanded states:\n"
        ret += "\n\n".join(first_few_expanded)

    return ret


def bfs(root, keys, threshold, debug, real_words):
    fringe = [root]
    nx = []
    num_expanded = 0
    max_fringe_len = 1
    max_depth = 0
    first_few_expanded = []

    while fringe and num_expanded < 1000:
        if len(fringe) > max_fringe_len:
            max_fringe_len = len(fringe)

        u = fringe.pop(0)

        if u.depth > max_depth:
            max_depth = u.depth

        if debug == "y" and num_expanded < 10:
            # print(f'message: {u.message}, key: {u.key}')
            first_few_expanded.append(u.message)

        u.calc_accuracy(real_words)

        if u.accuracy >= threshold:
            ret = (
                f"Solution: {u.message}\n\n"
                f"Key: {u.key}\n"
                f"Path Cost: {u.depth}\n\n"
                f"Num nodes expanded: {num_expanded}\n"
                f"Max fringe size: {max_fringe_len}\n"
                f"Max depth: {max_depth}"
            )
            if debug == "y":
                ret += "\n\nFirst few expanded states:\n"
                ret += "\n\n".join(first_few_expanded)
            print(ret)
            return ret
        num_expanded += 1
        u.create_children(keys)
        fringe += u.children

    ret = f"""No solution found\n\n
            Key: {u.key}\n
            Path Cost: {u.depth}\n\n
            Num nodes expanded: {num_expanded}\n
            Max fringe size: {max_fringe_len}\n
            Max depth: {max_depth}"""
    if debug == "y":
        ret += "First few expanded states:\n"
        ret += "\n\n".join(first_few_expanded)

    return ret


def task4(algorithm, message_filename, dictionary_filename, threshold, letters, debug):
    sys.setrecursionlimit(2000)
    letter_array = {*letters}
    # keys = sorted(
    #     itertools.combinations([letter_array], 2),
    #     key=lambda x: (x[0], x[1]) if x[0] < x[1] else (x[1], x[0]),
    # )
    keys = list(itertools.combinations(sorted(letter_array), 2))

    words = set()
    with open(dictionary_filename, "r") as f:
        for line in f.readlines():
            words.add(re.sub(r"[^a-zA-Z0-9]", "", line.strip().lower()))

    with open(message_filename, "r") as f:
        msg = f.read()

    if algorithm == "i":
        return ids(msg, keys, debug, words, threshold)
    if algorithm == "d":
        return dfs(Node("", msg, 0), keys, debug, words, threshold)
    if algorithm == "b":
        return bfs(Node("", msg, 0), keys, threshold, debug, words)


if __name__ == "__main__":
    # Example function calls below, you can add your own to test the task4 function
    # print(task4("i", "cabs.txt", "common_words.txt", 100, "ABC", "y"))
    print(task4("b", "cabs.txt", "common_words.txt", 100, "AAAABBC", "y"))
    # print(task4("d", "cabs.txt", "common_words.txt", 100, "AGDCBC", "y"))
