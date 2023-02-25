import numpy as np
from functools import partials

min_dim_size = 3
max_dim_size = 10

r_array_size = lambda min_dim_size, max_dim_size, random_number: (
    np.dot (
        random_number, (max_dim_size - min_dim_size))
         + min_dim_size
         ).astype(np.int32)

r_array_size = partial(
    r_array_size,
    min_dim_size,
    max_dim_size)

r_array_gen = lambda: n.random.random(
    r_array_size(
        np.random.random(
            r_array_size(
                np.random.random()
                ))))

rand_array = r_array_gen()


print(rand_array.shape)