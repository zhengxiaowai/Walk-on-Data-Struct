#!/usr/bin/env python
# -*- coding:utf-8 -*-


def insertion_sort(arr):
    for i, elem in enumerate(arr):
        idx = i
        while idx > 0 and elem < arr[idx-1]:
            arr[idx-1], arr[idx] = arr[idx], arr[idx-1]
            idx -= 1


def optimization_insertion_sort(arr):
    for i, elem in enumerate(arr):
        idx = tmp_idx = i
        while idx > 0 and elem < arr[idx - 1]:
            arr[idx] = arr[idx-1]
            idx -= 1
        arr[tmp_idx] = elem



