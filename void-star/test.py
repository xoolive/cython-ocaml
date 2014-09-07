""" Sample programm using pywrapper.

The two class presented here implement distance at runtime. They are still
evaluated by the cpp code.
Mission accomplished!

"""

import pywrapper
from math import sqrt, cos, pi


class CartesianPoint(object):

    """  Class representing a point from its x and y coordinates. """

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def distance(self, point):
        """ Distance to another point (@return double). """
        assert(isinstance(point, CartesianPoint))
        return sqrt((point.x - self.x) ** 2 + (point.y - self.y) ** 2)


class PolarPoint(object):

    """ Class representing a point from its radius and angle coordinates. """

    def __init__(self, radius, angle):
        self.radius = radius
        self.angle = angle

    def distance(self, point):
        """ Distance to another point (@return double). """
        assert(isinstance(point, PolarPoint))
        return sqrt(self.radius ** 2 + point.radius ** 2 -
                    2 * self.radius * point.radius *
                    cos(self.angle - point.angle))

a = CartesianPoint(2., 4.)
b = CartesianPoint(1., -3.)

c = PolarPoint(1., 0.)
d = PolarPoint(1., pi / 2.)

pywrapper.test(a, b)
pywrapper.test(c, d)
