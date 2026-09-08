from __future__ import annotations

import re
import zipfile
from pathlib import Path
from xml.etree import ElementTree as ET


DOCX = Path("2026.2.18糖尿病并发症预控预警地图_一页版.docx")
NS = {
    "w": "http://schemas.openxmlformats.org/wordprocessingml/2006/main",
    "v": "urn:schemas-microsoft-com:vml",
}


def parse_style(style: str) -> dict[str, str]:
    out = {}
    for part in style.split(";"):
        if ":" in part:
            key, value = part.split(":", 1)
            out[key.strip()] = value.strip()
    return out


def pt(value: str | None) -> float | None:
    if not value:
        return None
    m = re.match(r"(-?\d+(?:\.\d+)?)pt$", value)
    return float(m.group(1)) if m else None


def text_of(el: ET.Element) -> str:
    return "".join(t.text or "" for t in el.findall(".//w:t", NS)).strip()


def main() -> None:
    with zipfile.ZipFile(DOCX) as zf:
        xml = zf.read("word/document.xml")

    root = ET.fromstring(xml)
    rows = []
    for idx, shape in enumerate(root.findall(".//v:shape", NS)):
        style = parse_style(shape.attrib.get("style", ""))
        rows.append(
            {
                "idx": idx,
                "left": pt(style.get("margin-left") or style.get("left")),
                "top": pt(style.get("margin-top") or style.get("top")),
                "width": pt(style.get("width")),
                "height": pt(style.get("height")),
                "text": text_of(shape)[:60],
            }
        )

    for row in rows:
        print(
            f"{row['idx']:02d}",
            f"left={row['left']}",
            f"top={row['top']}",
            f"w={row['width']}",
            f"h={row['height']}",
            row["text"],
        )


if __name__ == "__main__":
    main()
