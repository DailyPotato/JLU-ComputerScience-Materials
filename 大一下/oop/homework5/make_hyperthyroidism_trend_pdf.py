from reportlab.lib.colors import Color, black
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.pdfgen import canvas


PAGE_W = 1584
PAGE_H = 1188

X = [41.33, 219.48, 401.40, 586.70, 772.00, 960.80, 1153.45, 1347.45, 1541.25]
Y_TOP = [
    128.22, 188.02, 246.02, 304.02, 363.57, 421.57, 479.57, 537.57, 595.57,
    653.57, 711.57, 769.57, 827.57, 885.57, 943.57, 1001.57, 1059.57, 1118.07,
]

RED = Color(1, 0, 0)
ORANGE = Color(1, 0.753, 0)
GRAY = Color(0.745, 0.745, 0.745)
BROWN1 = Color(0.533, 0.376, 0)
BROWN2 = Color(0.596, 0.435, 0)
DARK_ORANGE = Color(0.592, 0.278, 0.024)
GREEN = Color(0.573, 0.816, 0.314)
YELLOW = Color(1, 1, 0)
TEAL = Color(0.49, 0.875, 0.843)


def y_from_top(top):
    return PAGE_H - top


def center_text(c, text, x0, x1, top, bottom, size=21, font="SimSun"):
    c.setFont(font, size)
    width = pdfmetrics.stringWidth(text, font, size)
    x = (x0 + x1 - width) / 2
    y = PAGE_H - ((top + bottom) / 2) - size * 0.34
    c.drawString(x, y, text)


def fill_cell(c, row, col, color):
    # row is 1-based body row; col is 0-based time column.
    x0 = X[2 + col]
    x1 = X[3 + col]
    top = Y_TOP[row]
    bottom = Y_TOP[row + 1]
    c.setFillColor(color)
    c.rect(x0, y_from_top(bottom), x1 - x0, bottom - top, stroke=0, fill=1)


def draw_grid(c):
    c.setStrokeColor(black)
    c.setLineWidth(0.24)

    group_boundaries = {0, 1, 2, 5, 7, 10, 12, 14, 16, 17}
    for i, top in enumerate(Y_TOP):
        x0 = X[0] if i in group_boundaries else X[1]
        c.line(x0, y_from_top(top), X[-1] + 0.12, y_from_top(top))

    for x in X:
        c.line(x, y_from_top(Y_TOP[0] - 0.12), x, y_from_top(Y_TOP[-1] + 0.12))


def build(output_path):
    pdfmetrics.registerFont(TTFont("SimSun", r"C:\Windows\Fonts\simsun.ttc"))
    c = canvas.Canvas(output_path, pagesize=(PAGE_W, PAGE_H))
    c.setTitle("甲亢并发症趋势图")

    # Color blocks. The palette and full-cell fills intentionally follow the source PDF.
    fills = {
        1: [(0, RED), (1, RED), (2, ORANGE)],
        2: [(0, RED), (1, RED), (2, ORANGE)],
        3: [(0, RED), (1, RED), (2, ORANGE)],
        4: [(0, ORANGE), (1, ORANGE), (2, ORANGE)],
        5: [(1, BROWN1), (2, BROWN2), (3, BROWN2), (4, BROWN2), (5, BROWN2)],
        6: [(2, DARK_ORANGE), (3, DARK_ORANGE), (4, DARK_ORANGE), (5, DARK_ORANGE)],
        7: [(3, BROWN2), (4, BROWN2), (5, BROWN2)],
        8: [(1, YELLOW), (2, YELLOW), (3, GRAY)],
        9: [(0, RED), (1, RED)],
        10: [(0, YELLOW), (1, YELLOW), (2, YELLOW)],
        11: [(0, YELLOW), (1, YELLOW), (2, GRAY)],
        12: [(0, DARK_ORANGE), (1, DARK_ORANGE), (2, DARK_ORANGE), (3, DARK_ORANGE)],
        13: [(0, ORANGE), (1, ORANGE)],
        14: [(3, ORANGE), (4, ORANGE), (5, ORANGE)],
        15: [(0, RED), (1, RED), (2, ORANGE), (3, ORANGE)],
        16: [(4, TEAL), (5, TEAL)],
    }
    for row, cells in fills.items():
        for col, color in cells:
            fill_cell(c, row, col, color)

    draw_grid(c)

    c.setFillColor(black)
    center_text(c, "甲亢并发症趋势图", 0, PAGE_W, 74, 128, size=26)

    headers = ["", "甲亢并发症", "初诊当日", "治疗1-3周", "治疗4-7周", "治疗1月", "治疗3月", "3月后"]
    for i, text in enumerate(headers):
        if text:
            center_text(c, text, X[i], X[i + 1], Y_TOP[0], Y_TOP[1], size=21)

    groups = [
        ("危急重症", 1, 1),
        ("循环系统", 2, 4),
        ("眼部系统", 5, 6),
        ("骨骼肌肉", 7, 9),
        ("肝胆代谢", 10, 11),
        ("神经精神", 12, 13),
        ("生殖妊娠", 14, 15),
        ("皮肤系统", 16, 16),
    ]
    for label, start, end in groups:
        center_text(c, label, X[0], X[1], Y_TOP[start], Y_TOP[end + 1], size=21)

    rows = [
        "甲亢危象",
        "心律失常",
        "心力衰竭",
        "心绞痛/高血压",
        "Graves眼病",
        "角膜损伤",
        "骨质疏松",
        "甲亢性肌病",
        "周期性麻痹",
        "肝功能异常",
        "糖代谢异常",
        "焦虑失眠",
        "精神障碍",
        "月经紊乱",
        "妊娠并发症",
        "胫前黏液水肿",
    ]
    for idx, text in enumerate(rows, start=1):
        size = 18 if len(text) >= 7 else 21
        center_text(c, text, X[1], X[2], Y_TOP[idx], Y_TOP[idx + 1], size=size)

    c.showPage()
    c.save()


if __name__ == "__main__":
    build(r"output\pdf\甲亢并发症趋势图.pdf")
