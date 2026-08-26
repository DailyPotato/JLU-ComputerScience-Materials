from argparse import ArgumentParser
from pathlib import Path

from pypdf import PdfReader, PdfWriter, Transformation
from pypdf.generic import RectangleObject
from reportlab.lib.pagesizes import A3, landscape


def scale_a4_page_to_a3(source_path: Path, output_path: Path) -> float:
    reader = PdfReader(source_path)
    writer = PdfWriter()
    a3_width, a3_height = landscape(A3)
    scale_factors = []

    for page in reader.pages:
        source_width = float(page.mediabox.width)
        source_height = float(page.mediabox.height)
        scale = min(a3_width / source_width, a3_height / source_height)
        offset_x = (a3_width - source_width * scale) / 2
        offset_y = (a3_height - source_height * scale) / 2

        page.add_transformation(
            Transformation().scale(scale, scale).translate(offset_x, offset_y)
        )
        a3_box = RectangleObject((0, 0, a3_width, a3_height))
        page.mediabox = a3_box
        page.cropbox = a3_box
        page.trimbox = a3_box
        page.bleedbox = a3_box
        page.artbox = a3_box
        writer.add_page(page)
        scale_factors.append(scale)

    writer.add_metadata(
        {
            "/Title": "Hyperthyroidism complication warning map - A3",
            "/Subject": "A4 page and all content proportionally enlarged to A3",
        }
    )

    output_path.parent.mkdir(parents=True, exist_ok=True)
    temporary_path = output_path.with_suffix(".tmp.pdf")
    with temporary_path.open("wb") as stream:
        writer.write(stream)
    temporary_path.replace(output_path)
    return scale_factors[0]


def main() -> None:
    parser = ArgumentParser(description="Scale every element on an A4 PDF page to A3.")
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    scale = scale_a4_page_to_a3(args.source, args.output)
    print(f"Scale: {scale * 100:.4f}%")
    print(args.output.resolve())


if __name__ == "__main__":
    main()
