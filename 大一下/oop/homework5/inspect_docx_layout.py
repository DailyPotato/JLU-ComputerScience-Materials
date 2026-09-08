from __future__ import annotations

import re
import zipfile
from pathlib import Path


DOCX = Path("2026.2.18糖尿病并发症预控预警地图_一页版.docx")


def main() -> None:
    with zipfile.ZipFile(DOCX) as zf:
        xml = zf.read("word/document.xml").decode("utf-8", errors="ignore")

    styles = re.findall(r'<v:shape[^>]*style="([^"]*)"', xml)
    print("vshape styles", len(styles))
    for style in styles[:25]:
        parts: dict[str, str] = {}
        for part in style.split(";"):
            if ":" in part:
                key, value = part.split(":", 1)
                parts[key.strip()] = value.strip()
        print(
            "top=", parts.get("margin-top") or parts.get("top"),
            "height=", parts.get("height"),
            "width=", parts.get("width"),
            "raw=", style[:160],
        )

    print("page sizes", re.findall(r"<w:pgSz[^>]*/>", xml)[:3])
    print("page margins", re.findall(r"<w:pgMar[^>]*/>", xml)[:3])
    print("wp:extent count", xml.count("<wp:extent"))
    print("wps text boxes", xml.count("<wps:txbx"))
    print("v text boxes", xml.count("<v:textbox"))
    print("paragraphs", xml.count("<w:p"))
    print("manual page breaks", xml.count('w:type="page"'))
    print("last rendered page breaks", xml.count("<w:lastRenderedPageBreak"))


if __name__ == "__main__":
    main()
