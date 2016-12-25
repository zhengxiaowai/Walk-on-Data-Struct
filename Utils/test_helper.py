#!/usr/bin/env python
# -*- coding:utf-8 -*-

from __future__ import print_function

import sys as _sys
import time as _time


__all__ = [
    'TestHelper'
]

PY_MAJOR = _sys.version_info[0]
PY2 = 2 if PY_MAJOR == 2 else None
PY3 = 3 if PY_MAJOR == 3 else None

if PY2:
    _range = xrange
else:
    _range = range


class TestHelper(object):
    def __init__(self):
        pass

    @staticmethod
    def generate_test_array(size, func, *args, **kwargs):
        return (func(*args, **kwargs) for _ in _range(size+1))

    @staticmethod
    def is_sorted(sorted_array, key=lambda x, y: x < y):
        assert all(key(sorted_array[idx - 1], el) for idx, el in enumerate(sorted_array[1:], 1)) is True

    @staticmethod
    def algorithm_test(algorithm_name, algorithm_func, *args, **kwargs):
        start_clock = _time.clock()
        algorithm_func(*args, **kwargs)
        cost_time = _time.clock() - start_clock
        print('{0} cost time: {1}'.format(algorithm_name, cost_time))


if __name__ == '__main__':
    pass
