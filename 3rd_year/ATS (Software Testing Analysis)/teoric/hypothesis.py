import pytest
from hypothesis import given
from hypothesis.strategies import lists, integers

def mulLR(list_nums):
    if len(list_nums) == 0:
        return 0
    else:
        return list_nums[0] * mulLR(list_nums[1:])
    
def mulLI(list_nums):
    res = 0
    for n in list_nums:
        res *= n
    return res


@given(lists(integers(min_value=1)))
def test_reverse(x: list):
    assert mulLI(x) == mulLI(x.reverse())
    assert mulLR(x) == mulLR(x.reverse())


@given(lists(integers(),min_size=1,max_size=1))
def test_singleton(x:list):
    assert mulLI(x) == x[0]
    assert mulLR(x) == x[0]

