#!/usr/bin/env python
# -*- coding:utf-8 -*-

from copy import deepcopy
from Utils import TestHelper
from random import randrange
from Algorithm.selection_sort import selection_sort
from Algorithm.insertion_sort import insertion_sort, optimization_insertion_sort

if __name__ == '__main__':
    n = 10000
    test_array = list(TestHelper.generate_test_array(n, randrange, 1, n))
    test_array2 = deepcopy(test_array)
    test_array3 = deepcopy(test_array)
    TestHelper.algorithm_test('Selection Sort', selection_sort, test_array)
    TestHelper.algorithm_test('Insertion Sort', insertion_sort, test_array2)
    TestHelper.algorithm_test('Optimization Insertion Sort', optimization_insertion_sort, test_array3)


