from PIL import Image
import numpy as np

image = Image.open("generated/source_map.png").convert("RGB")
arr = np.array(image)
dark = (arr[:, :, 0] < 80) & (arr[:, :, 1] < 80) & (arr[:, :, 2] < 100)
row = dark.sum(axis=1)
col = dark.sum(axis=0)

def groups(items):
    result = []
    current = []
    for i, v in items:
        if not current or i <= current[-1][0] + 1:
            current.append((i, v))
        else:
            result.append(current)
            current = [(i, v)]
    if current:
        result.append(current)
    return [
        (g[0][0], g[-1][0], max(v for _, v in g), sum(v for _, v in g))
        for g in result
    ]

rows = [(i, int(v)) for i, v in enumerate(row) if v > 500]
cols = [(i, int(v)) for i, v in enumerate(col) if v > 300]
print("size", image.size)
print("rows")
for g in groups(rows):
    print(g)
print("cols")
for g in groups(cols):
    print(g)
