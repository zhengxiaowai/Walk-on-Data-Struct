#!/usr/bin/env python
# -*- coding:utf-8 -*-


def selection_sort(array, key=lambda x: x):
    for idx, el in enumerate(array):
        if not array[idx+1:]:
            return

        min_elem = min(array[idx+1:], key=key)
        min_index = array.index(min_elem)

        if array[idx] > array[min_index]:
            array[idx], array[min_index] = array[min_index], array[idx]


if __name__ == '__main__':
    from Utils import TestHelper
    from random import randrange
    test_array = TestHelper.generate_test_array(10000, randrange, 1, 10000)
    TestHelper.algorithm_test('Selection Sort', selection_sort, list(test_array))
