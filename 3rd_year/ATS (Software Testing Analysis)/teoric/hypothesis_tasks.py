import pytest
from hypothesis import given, assume, settings, event
from hypothesis.strategies import integers, lists, composite
from math import prod

def mulLR(list_nums):
    if len(list_nums) == 0:
        return 0
    elif len(list_nums) == 1:
        return list_nums[0]
    else:
        return list_nums[0] * mulLR(list_nums[1:])
    
def mulLI(list_nums):
    res = 1
    for n in list_nums:
        res *= n
    return res


@given(lists(integers(),min_size=1).filter(lambda x: x is not None))
def test_reverse(x):
    l = list(x)
    l.reverse()
    assert mulLI(x) == mulLI(l)
    assert mulLR(x) == mulLR(l)

@given(integers())
def test_one(x):
    l = [x]
    assert mulLI(l) == x
    assert mulLR(l) == x

@given(lists(integers(), min_size=1).filter(lambda x: x is not None))
def test_prod(x):
    assert mulLI(x) == prod(x)
    assert mulLR(x) == prod(x)


def myIndex(input_list, value):
    if len(input_list) == 0:
        raise ValueError("Value not found in list")
    try:
        if value == input_list[0]:
            return 0    
    except:
        if value != input_list[0]:
            return 1 + myIndex(input_list[1:], value)
        else:
            raise ValueError("Value not found in list")
        
def test_index():
    assert [1,2,3,4,1].index(1) == 0
    assert myIndex([1,2,3,4,1],1) == 0

@given(integers())
def test_positive(x):
    assume(x > 0)
    assert (x * x * x) > 0

@given(integers(min_value=1, max_value=1000))
def test_positive2(x):
    assert (x * x * x) > 0

def isSorted(list_nums):
    return False not in [a <= b for (a,b) in zip(list_nums, list_nums[1:])]

def insert(elem, list_nums):
    i = 0
    r = []
    while (i < len(list_nums) and elem > list_nums[i]):
        r.append(list_nums[i])
        i += 1
    r.append(elem)
    while (i < len(list_nums)):
        r.append(list_nums[i])
        i += 1
    return r

@given(integers(), lists(integers(),min_size=5).filter(lambda x: x is not None))
@settings(max_examples=500)
def test_sorted(x,l):
    assume(isSorted(l))
    r = insert(x,l)
    assert isSorted(r)

@given(integers(), lists(integers(),min_size=5).filter(lambda x: x is not None))
@settings(max_examples=500)
def test_sorted_events(x,l):
    assume(isSorted(l))
    r = insert(x,l)
    assert isSorted(r)
    event('input_list_length={}'.format(len(l)))

@composite
def sorted_intLists(draw, max_size=None):
    lst = draw(lists(integers(), max_size=max_size))
    return sorted(lst)

@given(sorted_intLists(max_size=10))
def test_sorted_intLists(l):
    assert isSorted(l)

@given(integers(), sorted_intLists(max_size=10))
def test_insert_sorted_intLists(x,l):
    r = insert(x,l)
    assert isSorted(r)