from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib.pagesizes import A3, landscape
from reportlab.lib.utils import ImageReader


ROOT = Path.cwd()
OUT_DIR = ROOT / "output" / "pdf"
OUT_DIR.mkdir(parents=True, exist_ok=True)

PNG_PATH = OUT_DIR / "甲状腺功能亢进相关并发症预控预警地图.png"
PDF_PATH = OUT_DIR / "甲状腺功能亢进相关并发症预控预警地图_严格配色版_大红中列.pdf"
A3_PAGE_PNG_PATH = OUT_DIR / "甲状腺功能亢进相关并发症预控预警地图_严格配色版_大红中列_A3预览.png"

W, H = 4800, 4250
NAVY = (3, 13, 49)
BLACK = (18, 18, 18)
WHITE = (255, 255, 255)
YELLOW_FILL = (255, 246, 150)
RED_FILL = (255, 70, 70)
LIGHT_BLUE_FILL = (205, 232, 255)
ORANGE_FILL = (255, 222, 166)

FONT = "C:/Windows/Fonts/simhei.ttf"
FONT_REGULAR = "C:/Windows/Fonts/msyh.ttc"


def font(size, regular=False):
    return ImageFont.truetype(FONT_REGULAR if regular else FONT, size)


F_TITLE = font(74)
F_LABEL = font(68)
F_BODY = font(66)
F_SMALL = font(61)
F_TINY = font(56)
F_ROW1 = font(82)
F_ROW3 = font(76)
F_ROW5 = font(68)


img = Image.new("RGB", (W, H), WHITE)
draw = ImageDraw.Draw(img)


def rect(x1, y1, x2, y2, width=6, fill=None):
    if fill is not None:
        draw.rectangle((x1, y1, x2, y2), fill=fill)
    draw.rectangle((x1, y1, x2, y2), outline=NAVY, width=width)


def center_text(text, box, fnt=F_BODY):
    x1, y1, x2, y2 = box
    lines = text.split("\n")
    line_h = int(fnt.size * 1.24)
    total_h = line_h * len(lines)
    y = y1 + (y2 - y1 - total_h) / 2
    for line in lines:
        bbox = draw.textbbox((0, 0), line, font=fnt)
        tw = bbox[2] - bbox[0]
        draw.text((x1 + (x2 - x1 - tw) / 2, y), line, fill=BLACK, font=fnt)
        y += line_h


def wrapped_lines(text, max_width, fnt):
    wrapped = []
    for raw_line in text.split("\n"):
        if raw_line == "":
            wrapped.append("")
            continue
        prefix = ""
        dot_index = raw_line.find(".")
        if 0 < dot_index <= 2:
            prefix = " " * (dot_index + 1)
        current = ""
        for char in raw_line:
            candidate = current + char
            if current and draw.textlength(candidate, font=fnt) > max_width:
                wrapped.append(current)
                current = prefix + char if prefix else char
            else:
                current = candidate
        if current:
            wrapped.append(current)
    return wrapped


def body_text(text, box, fnt=F_BODY, pad=34, line_gap=10):
    x1, y1, x2, y2 = box
    max_width = x2 - x1 - pad * 2
    lines = wrapped_lines(text, max_width, fnt)
    line_h = int(fnt.size * 1.10) + line_gap
    available_h = y2 - y1 - pad * 2
    if lines and line_h * len(lines) > available_h:
        line_h = max(int(fnt.size * 1.02), available_h // len(lines))
    y = y1 + pad
    for line in lines:
        draw.text((x1 + pad, y), line, fill=BLACK, font=fnt)
        y += line_h


def line(points, width=6):
    draw.line(points, fill=BLACK, width=width, joint="curve")


def arrow_down(x, y1, y2, width=6, head=32):
    line((x, y1, x, y2 - head), width)
    draw.polygon([(x - head, y2 - head), (x + head, y2 - head), (x, y2)], fill=BLACK)


def arrow_down_from_line(x, y1, y2):
    arrow_down(x, y1, y2, 6, 34)


def connect_down(box1, box2):
    x = (box1[0] + box1[2]) // 2
    arrow_down(x, box1[3], box2[1])


# Left row labels, matched to the original map structure.
labels = {
    "临床表现": (5, 780, 396, 1008),
    "并发症": (5, 1440, 396, 1688),
    "病因": (5, 2118, 396, 2280),
    "预控": (5, 2841, 396, 3093),
    "应急处理": (5, 3656, 396, 3932),
}
for text, box in labels.items():
    rect(*box)
    center_text(text, box, F_LABEL)


title = (2356, 4, 3168, 176)
rect(*title)
center_text("甲状腺功能亢进并发症", title, F_TITLE)


# Clinical manifestations.
c1 = (965, 459, 1715, 1318)
c2 = (2475, 459, 3065, 1326)
c3 = (3838, 459, 4796, 1319)
for box in (c1, c2, c3):
    rect(*box, fill={c1: YELLOW_FILL, c2: RED_FILL, c3: ORANGE_FILL}[box])

body_text(
    "1.怕热、多汗\n"
    "2.心悸、手抖\n"
    "3.易激动、失眠\n"
    "4.多食、体重下降",
    c1,
    F_ROW1,
)
body_text("1.胸闷气短\n2.心动过速\n3.心律失常", c2, F_ROW1)
body_text(
    "1.高热（>39℃）\n"
    "2.大汗、谵妄\n"
    "3.恶心呕吐、腹泻\n"
    "4.心动过速或房颤\n"
    "5.血压异常\n"
    "6.脱水、休克\n"
    "7.昏迷",
    c3,
    F_ROW1,
)


# Top branching arrows.
title_center_x = (title[0] + title[2]) // 2
arrow_down(title_center_x, title[3], 322)
branch_left_x = (c1[0] + c1[2]) // 2
branch_right_x = (c3[0] + c3[2]) // 2
line((branch_left_x, 322, branch_right_x, 322))
arrow_down_from_line((c1[0] + c1[2]) // 2, 322, c1[1])
arrow_down_from_line((c2[0] + c2[2]) // 2, 322, c2[1])
arrow_down_from_line((c3[0] + c3[2]) // 2, 322, c3[1])


# Complication boxes.
comp1 = (976, 1440, 1718, 1688)
comp2 = (2360, 1440, 3110, 1688)
comp3 = (3835, 1440, 4796, 1688)
for box, text in [
    (comp1, "甲亢性\n周期性麻痹"),
    (comp2, "甲亢性心脏病"),
    (comp3, "甲状腺危象"),
]:
    fill = {comp1: YELLOW_FILL, comp2: RED_FILL, comp3: ORANGE_FILL}[box]
    rect(*box, fill=fill)
    center_text(text, box, F_LABEL)


# Cause boxes.
cause1 = (692, 1810, 1984, 2588)
cause2 = (2035, 1810, 3473, 2588)
cause3 = (3712, 1810, 4796, 2588)
for box in (cause1, cause2, cause3):
    rect(*box, fill={cause1: YELLOW_FILL, cause2: RED_FILL, cause3: ORANGE_FILL}[box])

body_text(
    "1.甲状腺激素过多使钾离子向细胞内转移\n"
    "2.高碳水饮食、剧烈运动、饮酒等诱发\n"
    "3.未规范控制甲亢导致反复发作\n"
    "4.低钾可引起肌无力及心律失常",
    cause1,
    F_ROW3,
)
body_text(
    "1.甲状腺激素过多导致交感兴奋、心率增快\n"
    "2.心肌耗氧量增加，可诱发房颤、心衰\n"
    "3.长期未控制甲亢可导致心脏扩大\n"
    "4.老年或原有心脏病者风险更高",
    cause2,
    F_ROW3,
)
body_text(
    "1.严重甲亢未控制\n"
    "2.感染、手术、创伤\n"
    "3.突然停用抗甲状腺药\n"
    "4.妊娠分娩、碘剂或造影剂刺激等",
    cause3,
    F_ROW3,
)


# Prevention boxes.
prev1 = (735, 2746, 1876, 3188)
prev2 = (2035, 2746, 3473, 3188)
prev3 = (3576, 2746, 4796, 3188)
for box in (prev1, prev2, prev3):
    rect(*box, fill={prev1: YELLOW_FILL, prev2: RED_FILL, prev3: ORANGE_FILL}[box])

body_text("监测血钾、心电图及甲状腺功能\n避免高糖饮食、过劳、饮酒\n遵医嘱规范抗甲状腺治疗", prev1, F_SMALL)
body_text("1.监测心电图\n2.监测心脏彩超\n3.监测心率、BNP、甲状腺功能\n4.遵医嘱控制心率并治疗甲亢", prev2, F_SMALL)
body_text("1.监测甲状腺功能\n2.遵医嘱服药，不随意停药或减量\n3.积极控制感染，术前充分准备\n4.避免诱因：感染、手术、创伤、碘负荷等", prev3, F_SMALL)


# Emergency boxes.
emg1 = (925, 3344, 1680, 4244)
emg2 = (2035, 3344, 3473, 4244)
emg3 = (3558, 3344, 4796, 4244)
for box in (emg1, emg2, emg3):
    rect(*box, fill={emg1: YELLOW_FILL, emg2: RED_FILL, emg3: ORANGE_FILL}[box])

body_text(
    "1.监测生命体征\n"
    "2.卧床休息，防跌倒\n"
    "3.遵医嘱补钾，严禁自行大量补钾\n"
    "4.出现心悸、呼吸困难时立即就医\n"
    "5.请内分泌科会诊",
    emg1,
    F_ROW5,
)
body_text(
    "1.监测生命体征、心电图\n"
    "2.遵医嘱吸氧、控制心率\n"
    "3.急查心肌酶、BNP、电解质、血气分析\n"
    "4.评估心衰、房颤等情况并请心内科会诊\n"
    "5.必要时按转运分级标准转运患者",
    emg2,
    F_ROW5,
)
body_text(
    "1.建立静脉通道，遵医嘱给予急救药物\n"
    "2.保持呼吸道通畅，必要时吸氧或气管插管\n"
    "3.物理降温，补液并纠正电解质紊乱\n"
    "4.遵医嘱使用抗甲状腺药、β受体阻滞剂、\n  碘剂和糖皮质激素\n"
    "5.严密监测生命体征和出入量，联系ICU转运",
    emg3,
    F_ROW5,
)


# Vertical arrows for each branch.
for top, mid, cause, prev, emg in [
    (c1, comp1, cause1, prev1, emg1),
    (c2, comp2, cause2, prev2, emg2),
    (c3, comp3, cause3, prev3, emg3),
]:
    connect_down(top, mid)
    connect_down(mid, cause)
    connect_down(cause, prev)
    connect_down(prev, emg)


img.save(PNG_PATH, quality=95)

# Preserve the reference A4 landscape layout while enlarging every physical
# measurement proportionally onto an A3 landscape page.
a4_page_w = 841.9000244140625
page_w, page_h = landscape(A3)
page_scale = page_w / a4_page_w
left_margin = 72 * page_scale
right_margin = 72 * page_scale
top_margin = 90.1500015258789 * page_scale
bottom_margin = 90.1500015258789 * page_scale
diagram_w = 504.5 * page_scale
diagram_h = 371.5 * page_scale
diagram_x = left_margin + ((page_w - left_margin - right_margin) - diagram_w) / 2
diagram_y = bottom_margin
title_font_size = 14 * page_scale
title_baseline_offset = 13 * page_scale

pdfmetrics.registerFont(TTFont("SimHei", FONT))
c = canvas.Canvas(str(PDF_PATH), pagesize=(page_w, page_h))
c.setTitle("甲状腺功能亢进相关并发症预控预警地图 - 严格配色版 - 大红中列")
c.setFont("SimHei", title_font_size)
page_title = "甲状腺功能亢进相关并发症预控预警"
page_title_w = pdfmetrics.stringWidth(page_title, "SimHei", title_font_size)
c.drawString(
    (page_w - page_title_w) / 2,
    page_h - top_margin + title_baseline_offset,
    page_title,
)
c.drawImage(
    ImageReader(str(PNG_PATH)),
    diagram_x,
    diagram_y,
    width=diagram_w,
    height=diagram_h,
    preserveAspectRatio=False,
    mask="auto",
)
c.showPage()
c.save()

# A raster preview of the A3 page for quick visual QA.
scale = 3
page_img = Image.new("RGB", (int(page_w * scale), int(page_h * scale)), WHITE)
page_draw = ImageDraw.Draw(page_img)
preview_title = "甲状腺功能亢进相关并发症预控预警"
preview_font = font(round(title_font_size * scale))
preview_bbox = page_draw.textbbox((0, 0), preview_title, font=preview_font)
page_draw.text(
    (
        int((page_w * scale - (preview_bbox[2] - preview_bbox[0])) / 2),
        int((top_margin - 30 * page_scale) * scale),
    ),
    preview_title,
    fill=BLACK,
    font=preview_font,
)
page_img.paste(
    img.resize((int(diagram_w * scale), int(diagram_h * scale))),
    (int(diagram_x * scale), int((page_h - diagram_y - diagram_h) * scale)),
)
page_img.save(A3_PAGE_PNG_PATH, quality=95)

print(PNG_PATH)
print(PDF_PATH)
print(A3_PAGE_PNG_PATH)
