import string
from hypothesis import given
from hypothesis.strategies import integers, text, dictionaries, lists, composite, sampled_from

class Student:

    def __init__(self, _nome : str, _idade : int, _curso : str, _notas : dict):
        self.name = _nome
        self.age = _idade
        self.course = _curso
        self.grades = _notas
    
    def __str__(self):
        return f"STUDENT: {self.name}, {self.age} years old, studies {self.course} with the following notes {self.grades}"
    
    def avg(self):
        r = 0
        for grades in self.grades.values():
            r += sum(grades) / len(grades)
        return r / len(self.grades.keys())

    def excelent(self):
        for grades in self.grades.values():
            if sum(grades) >= 10*len(grades):
                continue
            else:
                return False
            
        return self.avg() >= 15

@composite
def name_generator(draw):
    return draw(text(alphabet=string.ascii_letters, min_size=1))

@composite
def age_generator(draw):
    return draw(integers(min_value=18, max_value=60))

@composite
def course_generator(draw):
    return draw(sampled_from(["LEI", "LCC"]))

@composite
def grades_generator(draw):
    uc = ["POO", "ATS", "DSS", "PF", "PI", "LI1", "LI2", "LI3", "LI4", "SO", "IPM", "ADI", "IA"]
    return draw(dictionaries(sampled_from(uc),lists(integers(min_value=0,max_value=20),max_size=4,min_size=1),min_size=1))

@composite
def student_generator(draw):
    return Student(draw(name_generator()), 
                        draw(age_generator()), 
                        draw(course_generator()), 
                        draw(grades_generator()))

@given(student_generator())
def test_avg(s):
    assert s.avg() >= 0 and s.avg() <= 20

@given(student_generator())
def test_avg2(s):
    bg = 0
    for v in s.grades.values():
        if max(v) > bg:
            bg = max(v)

    assert int(s.avg()) <= bg

@given(student_generator())
def test_excelent(s):
    if s.excelent():
        assert s.avg()>=15
    else:
        assert s.excelent() < 15

@given(student_generator())
def test_course(s):
    assert s.course in ["LCC", "LEI"]

@given(student_generator())
def test_grades(s):
    assert [x in ["POO", "ATS", "DSS", "PF", "PI", "LI1", "LI2", "LI3", "LI4", "SO", "IPM", "ADI", "IA"] for x in s.grades.keys()]

def print_students(n):
    with open("logs.txt", "w") as file:
        for _ in range(n):
            file.write(str(student_generator().example()) + "\n")

        