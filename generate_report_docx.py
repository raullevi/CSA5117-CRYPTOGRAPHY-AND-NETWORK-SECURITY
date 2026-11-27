#!/usr/bin/env python3
"""
generate_report_docx.py - Generates an academic Word document (.docx)
for all 40 programs in CSA5117 Cryptography & Network Security.
"""

import os
import sys
from docx import Document
from docx.shared import Inches, Pt, RGBColor
from docx.enum.text import WD_ALIGN_PARAGRAPH
from docx.enum.table import WD_TABLE_ALIGNMENT
from docx.oxml import OxmlElement, parse_xml
from docx.oxml.ns import nsdecls, qn

REPO_ROOT = "/Users/raul_levi/.gemini/antigravity/scratch/CSA5117-CRYPTOGRAPHY-AND-NETWORK-SECURITY"
sys.path.insert(0, os.path.join(REPO_ROOT, "scripts"))
from progs_01_10 import PROGS_01_10
from progs_11_20 import PROGS_11_20
from progs_21_30 import PROGS_21_30
from progs_31_40 import PROGS_31_40

ALL_PROGS = PROGS_01_10 + PROGS_11_20 + PROGS_21_30 + PROGS_31_40

def set_cell_background(cell, hex_color):
    shading_elm = parse_xml(f'<w:shd {nsdecls("w")} w:fill="{hex_color}"/>')
    cell._tc.get_or_add_tcPr().append(shading_elm)

def create_report():
    print("Generating comprehensive .docx laboratory report...")
    doc = Document()

    # Set standard 1-inch margins
    sections = doc.sections
    for section in sections:
        section.top_margin = Inches(1)
        section.bottom_margin = Inches(1)
        section.left_margin = Inches(1)
        section.right_margin = Inches(1)

    # Title Page
    p_inst = doc.add_paragraph()
    p_inst.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run_inst = p_inst.add_run("SAVEETHA SCHOOL OF ENGINEERING\nSAVEETHA INSTITUTE OF MEDICAL AND TECHNICAL SCIENCES\n")
    run_inst.bold = True
    run_inst.font.size = Pt(16)
    run_inst.font.color.rgb = RGBColor(0, 51, 102)

    p_dept = doc.add_paragraph()
    p_dept.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run_dept = p_dept.add_run("DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING\n\n")
    run_dept.bold = True
    run_dept.font.size = Pt(13)
    run_dept.font.color.rgb = RGBColor(100, 100, 100)

    p_title = doc.add_paragraph()
    p_title.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run_title = p_title.add_run("CSA5117 / CSA51 - CRYPTOGRAPHY AND NETWORK SECURITY\nLABORATORY RECORD (40 PROGRAMS)\n\n")
    run_title.bold = True
    run_title.font.size = Pt(18)
    run_title.font.color.rgb = RGBColor(0, 51, 102)

    p_meta = doc.add_paragraph()
    p_meta.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run_meta = p_meta.add_run(
        "STUDENT NAME: RAKUL K\n"
        "REGISTER NUMBER: 192525143\n"
        "DEGREE: B.TECH (COMPUTER SCIENCE & ENGINEERING)\n"
        "ACADEMIC YEAR: 2026 - 2027\n\n"
    )
    run_meta.bold = True
    run_meta.font.size = Pt(12)

    doc.add_page_break()

    # Table of Contents Summary
    doc.add_heading("Index of Laboratory Experiments", level=1)
    toc_table = doc.add_table(rows=1, cols=3)
    toc_table.alignment = WD_TABLE_ALIGNMENT.CENTER
    hdr = toc_table.rows[0].cells
    hdr[0].text = "Exp #"
    hdr[1].text = "Program Title"
    hdr[2].text = "Cryptographic Concept"
    for cell in hdr:
        set_cell_background(cell, "003366")
        for p in cell.paragraphs:
            for r in p.runs:
                r.bold = True
                r.font.color.rgb = RGBColor(255, 255, 255)

    for prog in ALL_PROGS:
        row = toc_table.add_row().cells
        row[0].text = f"{prog['num']:02d}"
        row[1].text = prog["title"]
        row[2].text = prog["concept"]
        for cell in row:
            for p in cell.paragraphs:
                p.paragraph_format.space_after = Pt(2)

    doc.add_page_break()

    # Detailed Program Reports
    for prog in ALL_PROGS:
        num = prog["num"]
        slug = prog["slug"]
        prog_dir = os.path.join(REPO_ROOT, slug)
        out_txt_path = os.path.join(prog_dir, "output.txt")
        ss_path = os.path.join(prog_dir, "output_screenshot.png")

        with open(out_txt_path, "r", encoding="utf-8") as f:
            output_content = f.read()

        doc.add_heading(f"Experiment {num:02d}: {prog['title']}", level=1)

        # Meta table
        meta_table = doc.add_table(rows=2, cols=2)
        meta_table.alignment = WD_TABLE_ALIGNMENT.CENTER
        meta_table.rows[0].cells[0].text = "Course: CSA5117 - Cryptography & Network Security"
        meta_table.rows[0].cells[1].text = "Student: Rakul K (192525143)"
        meta_table.rows[1].cells[0].text = f"Domain: {prog['concept']}"
        meta_table.rows[1].cells[1].text = "Status: Completed & Verified"
        for r in meta_table.rows:
            for c in r.cells:
                set_cell_background(c, "F0F4F8")
                for p in c.paragraphs:
                    p.paragraph_format.space_after = Pt(2)
                    for run in p.runs:
                        run.font.size = Pt(9.5)

        doc.add_heading("1. Problem Statement", level=2)
        p_q = doc.add_paragraph(prog["question"])
        p_q.paragraph_format.space_after = Pt(6)

        doc.add_heading("2. Aim & Objective", level=2)
        p_aim = doc.add_paragraph(prog["aim"])
        p_aim.paragraph_format.space_after = Pt(6)

        doc.add_heading("3. Algorithm / Mathematical Formulation", level=2)
        p_algo = doc.add_paragraph(prog["algorithm"])
        p_algo.paragraph_format.space_after = Pt(6)

        doc.add_heading(f"4. C Source Code (prog{num:02d}.c)", level=2)
        code_p = doc.add_paragraph()
        run_code = code_p.add_run(prog["code"])
        run_code.font.name = "Courier New"
        run_code.font.size = Pt(8.5)
        code_p.paragraph_format.space_after = Pt(6)

        doc.add_heading("5. Execution Output", level=2)
        out_p = doc.add_paragraph()
        run_out = out_p.add_run(output_content)
        run_out.font.name = "Courier New"
        run_out.font.size = Pt(8.5)
        out_p.paragraph_format.space_after = Pt(6)

        doc.add_heading("6. Terminal Output Screenshot", level=2)
        if os.path.exists(ss_path):
            doc.add_picture(ss_path, width=Inches(6.0))
        
        doc.add_page_break()

    out_docx_path = os.path.join(REPO_ROOT, "CSA5117_CNS_Lab_Report_40_Programs.docx")
    doc.save(out_docx_path)
    print(f"Report successfully saved to: {out_docx_path}")

    # Copy to user's Downloads folder
    downloads_path = "/Users/raul_levi/Downloads/CSA5117_CNS_Lab_Report_40_Programs.docx"
    doc.save(downloads_path)
    print(f"Report copy saved to: {downloads_path}")

if __name__ == "__main__":
    create_report()
