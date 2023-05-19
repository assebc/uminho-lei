from hypothesis import given
from hypothesis.strategies import integers, floats, sampled_from, builds, composite, lists

@composite
def gen_name(draw):
    f_name = draw(sampled_from(["Joao", "Jose", "Alberto", "Rui", "Marcelo", "Joana", "Ana", "Maria", "Sofia", "Ines"]))
    l_name = draw(sampled_from(["Mesquita", "Santos", "Bessa", "Silva", "Matos", "Freitas", "Martins", "Costa", "Cunha", "Ribeiro"]))
    return f"{f_name} {l_name}"

@composite
def gen_resolution(draw):
    return draw(sampled_from(["(1280x720)","(1980x1080)","(2160x1440)","(1024x768)","(3840x2160)","(1366x768)"]))

@composite
def gen_divisao(draw):
    div = draw(sampled_from(["Ninho", "Sala", "Cozinha", "Quarto", "Suite", "Corredor", "Casa de Banho", "Hall", "Escritorio", "Jardim", "Garagem"]))
    return f"Divisao:{div}"

@composite
def gen_fornecedor_aux(draw):
    suppliers = ["EDP", "Iberdola", "Endesa", "Gold Energy", "MEO Energia", "SU Eletricidade"]
    index = draw(integers(min_value=0, max_value=len(suppliers)-1))
    return suppliers[index]

@given(gen_fornecedor_aux())
def gen_fornecedor(forn):
    return f"Fornecedor:{forn}"

def gen_fornecedor_2(forns):
    lst = []
    for forn in forns:
        lst.append(f"Fornecedor:{forn}\n")
    return lst

def gen_fornecedor_3(forn):
    return f"Fornecedor:{forn}"

@composite
def gen_smart_bulb(draw):
    mode = draw(sampled_from(["Cold", "Neutral", "Warm"]))
    dimension = draw(integers(min_value=1, max_value=25))
    consume = draw(floats(min_value=1,max_value=20))
    consume = format(consume, ".2f")
    return f"SmartBulb:{mode},{dimension},{consume}"

@composite
def gen_smart_camera(draw):
    res = draw(gen_resolution())
    dimension = draw(integers(min_value=10, max_value=200))
    consume = draw(floats(min_value=1,max_value=20))
    consume = format(consume, ".2f")
    return f"SmartCamera:{res},{dimension},{consume}"


@composite
def gen_smart_speaker(draw):
    volume = draw(integers(min_value=1, max_value=100))
    name = draw(gen_name())
    brand = draw(sampled_from(["JBL", "Marshall", "Sony", "LG", "XIAOMI", "Goodis", "Sonos", "Echo", "Apple", "Bose", "Anker", "Alcatel", "Amazon", "Next"]))
    consume = draw(floats(min_value=1,max_value=20))
    consume = format(consume, ".2f")
    return f"SmartSpeaker:{volume},{name},{brand},{consume}"

@composite
def gen_casa(draw):
    name = gen_name().example()
    nif = draw(integers(min_value=1000000000,max_value=999999999))
    fornecedor = gen_fornecedor_aux()
    return f"Casa:{name},{nif},{fornecedor}"

@composite
def gen_casa_2(draw, forn):
    name = draw(gen_name())
    nif = draw(integers(min_value=100000000, max_value=999999999))
    return f"Casa:{name},{nif},{forn}"

@composite
def gen_casa_3(draw, forns):
    fornecedor = draw(sampled_from(forns))
    casa = draw(gen_casa_2(fornecedor))
    return casa + "\n"

@composite
def gen_house(draw,fornecedores):
    house = []
    casa = draw(gen_casa_3(fornecedores))
    smart_bulbs = ""
    smart_cameras = ""
    smart_speakers = ""
    n_divis = draw(integers(min_value=1,max_value=3))
    house.append(casa)
    for _ in range(n_divis):
        division = draw(gen_divisao()) + "\n"
        n_smart_bulbs = draw(integers(min_value=0, max_value=5))
        n_smart_cameras = draw(integers(min_value=0, max_value=5))
        n_smart_speakers = draw(integers(min_value=0, max_value=5))
        for _ in range(n_smart_bulbs):
            smart_bulbs = smart_bulbs + draw(gen_smart_bulb()) + "\n"
        for _ in range(n_smart_cameras):
            smart_cameras = smart_cameras + draw(gen_smart_camera()) + "\n"
        for _ in range(n_smart_speakers):
            smart_speakers = smart_speakers + draw(gen_smart_speaker()) + "\n"
        house.append(division + smart_bulbs + smart_cameras + smart_speakers)
        smart_bulbs = ""
        smart_cameras = ""
        smart_speakers = ""
    return house

@composite
def gen_suppliers(draw, max_size: int):
    suppliers = draw(lists(gen_fornecedor_aux(), min_size=1, max_size=max_size))
    while len(set(suppliers)) != len(suppliers):
        suppliers = draw(lists(gen_fornecedor_aux(), min_size=1, max_size=max_size))
    return suppliers

@composite
def gen_city(draw, forns, max_size: int):
    return draw(lists(gen_house(forns), min_size=1, max_size=max_size))

def main():
    forn = gen_suppliers(max_size=5).example()
    fornecedores = gen_fornecedor_2(forn)
    cy = gen_city(forn, max_size=3)
    city = cy.example()
    file = open("data2.txt", "w+")
    file.writelines(fornecedores)
    for ct in city:
        file.writelines(ct)
    file.close()

if __name__ == "__main__":
    main()
