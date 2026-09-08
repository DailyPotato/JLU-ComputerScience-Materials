from __future__ import annotations

import re
import zipfile
from pathlib import Path
from xml.etree import ElementTree as ET

from reportlab.lib import colors
from reportlab.lib.pagesizes import landscape, A4
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.cidfonts import UnicodeCIDFont
from reportlab.pdfgen import canvas


SRC_DOCX = Path(r"C:\Users\Potato\Desktop\2026.2.18糖尿病并发症预控预警地图.docx")
OUT_PDF = Path(r"C:\Users\Potato\Desktop\JLU-ComputerScience-Materials\大一下\oop\homework5\2026.2.18糖尿病并发症预控预警地图_A4一页矢量版.pdf")

NS = {
    "w": "http://schemas.openxmlformats.org/wordprocessingml/2006/main",
    "v": "urn:schemas-microsoft-com:vml",
}

FONT = "STSong-Light"
YELLOW = colors.Color(1, 1, 0.10)
RED = colors.Color(1, 0.13, 0.02)
LIGHT_BLUE = colors.Color(0.68, 0.88, 1.0)


def shape_texts() -> list[str]:
    with zipfile.ZipFile(SRC_DOCX) as zf:
        xml = zf.read("word/document.xml")
    root = ET.fromstring(xml)
    out: list[str] = []
    for shape in root.findall(".//v:shape", NS):
        text = "".join(t.text or "" for t in shape.findall(".//w:t", NS))
        out.append(re.sub(r"\s+", " ", text).strip())
    return out


def wrap_text(text: str, font_size: float, max_width: float) -> list[str]:
    lines: list[str] = []
    for paragraph in text.splitlines() or [text]:
        protected = re.sub(r"(\d)\.(\d)", r"\1§\2", paragraph)
        parts = re.split(r"(?=(?:\d+\.|[一二三四五六七八九十]+、))", protected)
        for raw in parts:
            raw = raw.replace("§", ".").strip()
            if not raw:
                continue
            line = ""
            for ch in raw:
                test = line + ch
                if line and pdfmetrics.stringWidth(test, FONT, font_size) > max_width:
                    lines.append(line)
                    line = ch
                else:
                    line = test
            if line:
                lines.append(line)
    return lines


def clean_hypoglycemia_emergency(text: str) -> str:
    text = re.sub(r"胰高\s*糖素\s*0\.5\s*-\s*1\.0\s*mg\s*肌注", "胰高糖素0.5-1.0mg肌注", text, flags=re.I)
    text = re.sub(r"/\s*胰高糖素0\.5-1\.0mg肌注", "/\n胰高糖素0.5-1.0mg肌注", text, flags=re.I)
    text = re.sub(r"(24-48h)\s*9\s*$", r"\1", text)
    return text


def fit_font(text: str, max_width: float, max_height: float, start: float, min_size: float = 4.2) -> float:
    size = start
    while size >= min_size:
        lines = wrap_text(text, size, max_width)
        if len(lines) * 10 <= max_height:
            return size
        size -= 0.2
    return min_size


def draw_box(
    c: canvas.Canvas,
    x: float,
    top: float,
    w: float,
    h: float,
    text: str,
    fill: colors.Color | None = None,
    font_size: float = 7.0,
    min_font_size: float = 4.2,
    center: bool = False,
    bold: bool = False,
) -> None:
    page_w, page_h = landscape(A4)
    y = page_h - top - h
    c.setStrokeColor(colors.black)
    c.setLineWidth(0.9)
    c.setFillColor(fill or colors.white)
    c.rect(x, y, w, h, stroke=1, fill=1)

    c.setFillColor(colors.black)
    c.setFont(FONT, font_size)
    if center:
        c.drawCentredString(x + w / 2, y + h / 2 - font_size / 3, text)
        return

    pad_x = 4
    pad_top = 5
    available_w = w - pad_x * 2
    size = fit_font(text, available_w, h - pad_top - 2, font_size, min_size=min_font_size)
    lines = wrap_text(text, size, available_w)
    c.setFont(FONT, size)
    text_y = y + h - pad_top - size
    for line in lines:
        if text_y < y + 2:
            break
        c.drawString(x + pad_x, text_y, line)
        text_y -= 10


def arrow_down(c: canvas.Canvas, x: float, top_from: float, top_to: float) -> None:
    _, page_h = landscape(A4)
    y1 = page_h - top_from
    y2 = page_h - top_to
    c.setStrokeColor(colors.black)
    c.setFillColor(colors.black)
    c.setLineWidth(0.8)
    c.line(x, y1, x, y2 + 5)
    c.line(x, y2, x - 3, y2 + 6)
    c.line(x, y2, x + 3, y2 + 6)


def main() -> None:
    pdfmetrics.registerFont(UnicodeCIDFont(FONT))
    texts = shape_texts()
    c = canvas.Canvas(str(OUT_PDF), pagesize=landscape(A4))
    page_w, _ = landscape(A4)

    # Title and root.
    c.setFillColor(colors.black)
    c.setFont(FONT, 14)
    c.drawCentredString(page_w / 2, 578, "糖尿病并发症预控预警地图")
    root_x, root_top, root_w, root_h = 385, 28, 72, 22
    draw_box(c, root_x, root_top, root_w, root_h, texts[46] or "糖尿病并发症", font_size=7.5, center=True)

    labels = {
        "临床表现": (8, 120),
        "并发症": (8, 198),
        "病因": (8, 282),
        "预控": (8, 365),
        "应急处理": (8, 486),
    }
    for label, (x, top) in labels.items():
        draw_box(c, x, top, 58, 20, label, font_size=7.5, center=True)

    col_x = [82 + i * 83 for i in range(9)]
    col_w = 74
    disease_names = [texts[i] for i in [51, 50, 59, 52, 58, 56, 57, 55, 49]]
    clinical = [texts[i] for i in [60, 61, 62, 68, 67, 66, 65, 64, 63]]
    causes = [texts[i] for i in [19, 24, 43, 23, 22, 21, 20, 10, 9]]
    causes[6] = re.sub(r"(?<!\d)2\.\s*", "", causes[6], count=1)
    causes[8] = re.sub(r"(?<!\d)\d+\.\s*", "", causes[8])
    prevention = [texts[i] for i in [75, 76, 77, 69, 74, 73, 72, 71, 70]]
    emergency = [texts[i] for i in [82, 83, 84, 85, 86, 81, 80, 79, 78]]
    emergency[2] = clean_hypoglycemia_emergency(emergency[2])

    fills = [YELLOW, YELLOW, YELLOW, RED, YELLOW, RED, LIGHT_BLUE, RED, RED]

    # Main three rows.
    for i, x in enumerate(col_x):
        draw_box(c, x, 60, col_w, 125, clinical[i], fill=fills[i], font_size=7.0)
        arrow_down(c, x + col_w / 2, 185, 198)
        draw_box(c, x, 198, col_w, 18, disease_names[i], fill=fills[i], font_size=7.0, center=True)
        arrow_down(c, x + col_w / 2, 216, 228)
        draw_box(c, x, 228, col_w, 70, causes[i], fill=fills[i], font_size=7.0)
        arrow_down(c, x + col_w / 2, 298, 312)
        draw_box(c, x, 312, col_w, 82, prevention[i], fill=fills[i], font_size=6.8)

    # Header arrows.
    c.line(root_x + root_w / 2, 595.3 - (root_top + root_h), root_x + root_w / 2, 595.3 - 56)
    c.line(col_x[0] + col_w / 2, 595.3 - 56, col_x[-1] + col_w / 2, 595.3 - 56)
    for x in col_x:
        arrow_down(c, x + col_w / 2, 56, 60)

    # Emergency row. Each box is directly under its own column; long entries
    # use a smaller font instead of occupying neighboring columns.
    emergency_top = 424
    emergency_h = 158
    emergency_font = [6.6, 6.6, 4.8, 6.4, 6.4, 6.4, 6.4, 6.4, 5.8]
    for i, x in enumerate(col_x):
        arrow_down(c, x + col_w / 2, 394, emergency_top)
        fill = fills[i]
        draw_box(
            c,
            x,
            emergency_top,
            col_w,
            emergency_h,
            emergency[i],
            fill=fill,
            font_size=emergency_font[i],
            min_font_size=3.1,
        )

    c.showPage()
    c.save()
    print(OUT_PDF)


if __name__ == "__main__":
    main()
