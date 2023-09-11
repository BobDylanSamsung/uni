import json
name="2flourobutane/flourobutane_s"
with open(f"{name}.json", "r") as f:
    mol = json.load(f)

with open("PeriodicTableJSON.json", "r") as f:
    pt = json.load(f)["elements"]





aid = mol["PC_Compounds"][0]["atoms"]["aid"]
elements = mol["PC_Compounds"][0]["atoms"]["element"]
x = mol["PC_Compounds"][0]["coords"][0]["conformers"][0]["x"]
y = mol["PC_Compounds"][0]["coords"][0]["conformers"][0]["y"]
z = mol["PC_Compounds"][0]["coords"][0]["conformers"][0]["z"]

b1 = mol["PC_Compounds"][0]["bonds"]["aid1"]
b2 = mol["PC_Compounds"][0]["bonds"]["aid2"]
b_order = mol["PC_Compounds"][0]["bonds"]["order"]
bosmap = ["-", "=", "#"]
bonds = zip(b1,b2, b_order)


print(elements)


data = zip(aid, elements, x, y, z)

with open(f"{name}.txt", "w") as f:
    f.write("ELEMENTS {\n")
    for i, e, x, y, z in data:
        f.write(f"    {i},   {pt[e-1]['symbol']},    {x},    {y},    {z};\n")
    f.write("}\n\n")
    f.write("BONDS {\n")
    for b1, b2, o in bonds:
        f.write(f"    {b1}{bosmap[o-1]}{b2};\n")
    f.write("}\n")
