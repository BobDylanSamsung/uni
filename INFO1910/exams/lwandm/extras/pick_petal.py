from random import random

def pick_petal(pref_pronoun):
    while True:
        yield '{} loves me!'.format(pref_pronoun)
        if random() < 0.1:
            return
        yield '{} loves me not.'.format(pref_pronoun)
        if random() < 0.1:
            return

def main():
    for p in pick_petal('It'):
        print(p)

if __name__=='__main__':
    main()
