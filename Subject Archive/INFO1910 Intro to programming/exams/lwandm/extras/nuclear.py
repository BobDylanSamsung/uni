from sys import exit
from time import sleep
from atoms import U235, U238
from random import random

# Make sure all trials use same random number generation
random.seed(0)

# Create size x size grid, with approximately percentage_u235% u235 atoms
def create_grid(size, percentage_u235):
    return list(
            list(
                U235() if (random.random() < percentage_u235) else U238()
                for __ in range(size)
            )
            for _ in range(size)
        )

# Print grid
def print_grid(grid):
    print('+' + '-' * len(grid) + '+')
    for row in grid:
        print('|' + ''.join(str(x) for x in row) + '|')
    print('+' + '-' * len(grid) + '+')

# Ignite atom as position (x, y)
def ignite_position(grid, x, y, disp=0):
    #TODO: recursively ignite atom at (x, y) and if successful, ignite its neighbours
    #      note: p(ignition) = 0.75 for u235, 0.25 for u238
    #      if disp is set, print grid at each ignition, then sleep disp seconds
    #      print terminal code '\033[2J' to clear screen before printing grid
    

# Calculate probability of successful ignition
def prob_ignition_successful(size, percentage_u235, n_trials=100, disp=0):
    #TODO: Calculate probability of successful ignition (i.e more than 75% of atoms 
    #      ignited, given a grid size and a percentage of u235 atoms.
    #      Do this by running n_trials trials and determining for each whether ignition
    #      was successful.


def main():
    # Example main() code below: iterate over grid sizes 5-30 in steps of 5
    #                            iterate over u235 percentage 0-100 in steps of 10
    #                            calculate and print success rate

    for size in range(5, 31, 5):
        print('Grid size for experiment is {0}x{0}'.format(size))
        for jj in range(0, 101, 10):
            print('\t{}% u235 has success rate: {}'.format(jj, prob_ignition_successful(size, jj/100.)))
    pass

if __name__ == '__main__':
    exit(main())
