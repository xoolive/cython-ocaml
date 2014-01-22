import sample
from math import sqrt


class Pair(object):

    """  docstring. """

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def distance(self, pair):
        """ docstring. """
        sqrt((pair.x - self.x) ** 2 + (pair.y - self.y) ** 2)


a = Pair(2, 4)
b = Pair(1, -3)

sample.test(a, b)
