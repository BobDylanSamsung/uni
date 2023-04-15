import re


class Node:
    def __init__(self, key, message: str, depth, children=None):
        self.key = key
        self.message = message
        self.depth = depth
        self.children: list[Node] = [] if children is None else children
        self.accuracy: float = -1

    def set_children(self, children):
        self.children = children

    def add_child(self, child):
        self.children.append(child)

    def create_children(self, keys):
        for key in keys:
            encoded = decode(key, [*self.message])
            child_key = self.key + key[0] + key[1]
            child = Node(child_key, encoded, self.depth + 1)
            self.add_child(child)

    def calc_accuracy(self, compare_words):
        num_valid = 0
        num_invalid = 0

        text = self.message.split()
        for word in text:
            if re.sub(r"[^a-zA-Z0-9]", "", word).lower() in compare_words:
                num_valid += 1
            else:
                num_invalid += 1

        self.accuracy = round((num_valid / (num_valid + num_invalid)) * 100, 2)
        # return "{}\n{:0.2f}".format((accuracy >= threshold), accuracy)


def decode(letters_to_swap, string_to_decode):
    k = [*letters_to_swap]
    letters = [*string_to_decode]

    num_swaps = 0
    for i in range(len(letters)):
        if letters[i] == k[0].upper():
            letters[i] = k[1].upper()
            num_swaps += 1
        elif letters[i] == k[0].lower():
            letters[i] = k[1].lower()
            num_swaps += 1
        elif letters[i] == k[1].upper():
            letters[i] = k[0].upper()
            num_swaps += 1
        elif letters[i] == k[1].lower():
            letters[i] = k[0].lower()
            num_swaps += 1

    return "".join(str(l) for l in letters)


def calc_accuracy(msg, valid_words):
    num_valid = 0
    num_invalid = 0

    for word in msg.split(" "):
        if re.sub(r"[^a-zA-Z0-9]", "", word).lower() in valid_words:
            num_valid += 1
        else:
            num_invalid += 1

    accuracy = round((num_valid / (num_valid + num_invalid)) * 100, 2)
    return accuracy


def generate_subtree(elements, path, words, msg, threshold):
    if elements is None:
        return None

    decoded_message = (
        decode(
            path[-1],
            msg,
        )
        if len(path) > 0
        else msg
    )
    accuracy = calc_accuracy(decoded_message, words)
    meets_threshold = accuracy > threshold
    children = [
        generate_subtree(
            elements=elements[:i] + elements[i + 1 :],
            path=path + [k],
            words=words,
            msg=decoded_message,
            threshold=threshold,
        )
        for i, k in enumerate(elements)
    ]

    return Node(
        path=path,
        decoded_message=decoded_message,
        accuracy=accuracy,
        meets_threshold=meets_threshold,
        children=children,
    )


def print_tree(node):
    if node is None:
        return
    print(f"{' ' * len(node.path) * 2}{node.path}\t{node.accuracy}")
    for child in node.children:
        print_tree(child)


def format_response(node, verbose, max_fringe, max_depth, expanded):
    max_depth = max(max_depth, len(node.path))
    verbose_out = "Fist few expanded states:\n" + "\n\n".join(
        [n.key for n in node.path[:10]]
    )
    if node.accuracy == 1:
        return (
            f"Solution: {node.msg}"
            + f"Key: {node.key}\n"
            + f"Path Cost: ????\n\n"
            + f"Num nodes expanded: {expanded}"
            + f"Max fringe size: {max_fringe}\n"
            + f"Max depth: {max_depth}"
            + verbose_out
        )

    return (
        "No solution found"
        + f"Num nodes expanded: {expanded}"
        + f"Max fringe size: {max_fringe}\n"
        + f"Max depth: {max_depth}"
        + verbose_out
    )


# def dfs_rec(
#     fringe, keys, words, msg, num_nodes_expanded, verbose, max_fringe, max_depth
# ):
#     if len(fringe) == 0:
#         node = Node(path=[], decoded_message=msg, key="", subkey="")
#         decoded_message = msg
#     else:
#         node = fringe[0]
#         fringe = fringe[1:]
#
#         decoded_message = decode(
#             node.key,
#             msg,
#         )
#     accuracy = calc_accuracy(decoded_message, words)
#
#     if accuracy == 1 or num_nodes_expanded == 999:
#         return format_response(node, verbose, max_fringe, max_depth, num_nodes_expanded)
#     else:
#         children = [
#             Node(
#                 path=node.path + [node],
#                 decoded_message=decoded_message,
#                 key=node.key + "".join(k),
#                 subkey=k,
#                 accuracy=accuracy,
#             )
#             for k in keys
#         ]
#         node.children = children
#         return dfs(
#             children + fringe,
#             keys,
#             words,
#             msg,
#             num_nodes_expanded + 1,
#             verbose,
#             max(max_fringe, len(fringe)),
#             max(max_depth, len(node.path + [node])),
#         )
