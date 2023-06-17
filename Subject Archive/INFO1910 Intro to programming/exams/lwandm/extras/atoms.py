from random import random

class GenericAtom:
    ign_prob = None
    ign_repr = ('G',)

    def __init__(self):
        self.ignited = False

    def is_ignited(self):
        return self.ignited

    def ignite(self):
        if self.__class__.ign_prob is None:
            raise NotImplementedError('GenericAtom cannot be ignited.')
        if random() < self.__class__.ign_prob:
            self.ignited = True
        return self.ignited

    def __str__(self):
        return self.__class__.ign_repr[int(self.ignited)]


class U235(GenericAtom):
    ign_prob = 0.82145
    ign_repr = ('U', 'X')


class U238(GenericAtom):
    ign_prob = 0.19324
    ign_repr = ('u', 'x')

