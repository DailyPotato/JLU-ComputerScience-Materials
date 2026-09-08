from __future__ import annotations

from pathlib import Path

from PIL import Image, ImageChops
from reportlab.lib.utils import ImageReader
from reportlab.pdfgen import canvas


WORK = Path(r"C:\Users\Potato\Desktop\JLU-ComputerScience-Materials\大一下\oop\homework5")
PAGE1 = WORK / "compact_stage1_page-1.png"
PAGE2 = WORK / "compact_stage1_page-2.png"
OUT_PNG = WORK / "2026.2.18糖尿病并发症预控预警地图_A4一页最终版.png"
OUT_PDF = WORK / "2026.2.18糖尿病并发症预控预警地图_A4一页最终版.pdf"


def crop_to_content(img: Image.Image, pad: int = 10) -> Image.Image:
    bg = Image.new(img.mode, img.size, "white")
    diff = ImageChops.difference(img, bg)
    bbox = diff.getbbox()
    if bbox is None:
        return img
    left, top, right, bottom = bbox
    left = max(0, left - pad)
    top = max(0, top - pad)
    right = min(img.width, right + pad)
    bottom = min(img.height, bottom + pad)
    return img.crop((left, top, right, bottom))


def resize_exact(img: Image.Image, width: int, height: int) -> Image.Image:
    return img.resize((width, height), Image.Resampling.LANCZOS)


def main() -> None:
    page1 = Image.open(PAGE1).convert("RGB")
    page2 = Image.open(PAGE2).convert("RGB")

    canvas_img = Image.new("RGB", page1.size, "white")
    width, height = canvas_img.size

    # Page 1 already contains title + clinical/cause/prevention rows.
    # Vertically compress it to create bottom room while keeping full width.
    top_block = crop_to_content(page1, pad=20)
    top_target_h = int(height * 0.66)
    top_block = resize_exact(top_block, width, top_target_h)
    canvas_img.paste(top_block, (0, 0))

    # Page 2 contains the emergency handling row. Crop white margins, then
    # place it at the bottom using the same page width.
    emergency = crop_to_content(page2, pad=16)
    bottom_target_h = height - top_target_h - 18
    emergency = resize_exact(emergency, width, bottom_target_h)
    canvas_img.paste(emergency, (0, top_target_h + 12))

    canvas_img.save(OUT_PNG, quality=95)

    # Keep original A4 landscape page size in points.
    pdf = canvas.Canvas(str(OUT_PDF), pagesize=(841.9, 595.3))
    pdf.drawImage(ImageReader(canvas_img), 0, 0, width=841.9, height=595.3)
    pdf.showPage()
    pdf.save()
    print(f"png={OUT_PNG}")
    print(f"pdf={OUT_PDF}")


if __name__ == "__main__":
    main()
