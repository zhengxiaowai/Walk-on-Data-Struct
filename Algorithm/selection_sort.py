#!/usr/bin/env python
# -*- coding:utf-8 -*-

from __future__ import absolute_import

import sys as _sys
_sys.path.append('..')

from random import randrange
from Utils import TestHelper


def selection_sort(array, key=lambda x: x):
    for idx, el in enumerate(array):
        if not array[idx+1:]:
            return

        min_elem = min(array[idx+1:], key=key)
        min_index = array.index(min_elem)

        if array[idx] > array[min_index]:
            array[idx], array[min_index] = array[min_index], array[idx]


if __name__ == '__main__':
    test_array = TestHelper.generate_test_array(20000, randrange, 1, 10000)
    TestHelper.algorithm_test('Selection Sort', selection_sort, list(test_array))
