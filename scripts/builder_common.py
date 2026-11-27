"""
builder_common.py - Common utilities for compiling, executing, rendering screenshots,
and generating markdown documentation for CSA5117 Cryptography & Network Security.
"""

import os
import subprocess
from PIL import Image, ImageDraw, ImageFont

STUDENT_NAME = "Rakul K"
REGISTER_NO = "192525143"
COURSE_CODE = "CSA5117 / CSA51 - Cryptography and Network Security"
INSTITUTION = "Saveetha School of Engineering, SIMATS"

def render_terminal_screenshot(title, output_text, out_png_path):
    """
    Renders high-resolution dark-mode terminal output screenshot (macOS style).
    """
    lines = [line.rstrip() for line in output_text.split('\n')]
    if not lines or all(not l for l in lines):
        lines = ["[No output recorded]"]

    padding = 24
    header_height = 42
    font_size = 14
    line_spacing = 6
    char_width = 8.6
    line_height = font_size + line_spacing

    max_len = max(len(l) for l in lines) if lines else 60
    img_width = max(880, int(max_len * char_width) + padding * 2)
    img_height = header_height + (len(lines) * line_height) + padding * 2

    img = Image.new("RGB", (img_width, img_height), "#0d1117")
    draw = ImageDraw.Draw(img)

    # Window title bar
    draw.rectangle([(0, 0), (img_width, header_height)], fill="#161b22")
    draw.line([(0, header_height), (img_width, header_height)], fill="#30363d", width=1)

    # macOS window traffic lights
    draw.ellipse([(14, 15), (26, 27)], fill="#ff5f56")
    draw.ellipse([(34, 15), (46, 27)], fill="#ffbd2e")
    draw.ellipse([(54, 15), (66, 27)], fill="#27c93f")

    # Font loading
    try:
        font = ImageFont.truetype("/System/Library/Fonts/SFNSMono.ttf", font_size)
        title_font = ImageFont.truetype("/System/Library/Fonts/SFNSMono.ttf", 12)
    except Exception:
        try:
            font = ImageFont.truetype("/Library/Fonts/Courier New.ttf", font_size)
            title_font = font
        except Exception:
            font = ImageFont.load_default()
            title_font = font

    # Draw Title Bar text
    title_text = f"Terminal - {title}"
    draw.text((80, 14), title_text[:80], fill="#8b949e", font=title_font)

    # Draw Terminal Lines
    y = header_height + padding
    for line in lines:
        if line.startswith("===") or line.startswith("---") or line.startswith("###"):
            color = "#58a6ff"  # Soft Blue
        elif line.startswith("$ ") or line.startswith("❯ "):
            color = "#d29922"  # Gold terminal prompt
        elif "SUCCESS" in line or "VERIFIED" in line or "PASSED" in line or "DECRYPTED" in line or "Matched" in line:
            color = "#3fb950"  # Bright Green
        elif "FAIL" in line or "ERROR" in line or "INVALID" in line or "VULNERABILITY" in line or "CRACKED" in line or "FORGERY" in line:
            color = "#f85149"  # Bright Red
        elif "Key" in line or "Plaintext" in line or "Ciphertext" in line or "Subkey" in line or "Matrix" in line:
            color = "#79c0ff"  # Cyan crypto terms
        elif "Score" in line or "Rank" in line or "Inverse" in line or "Determinant" in line or "Modulus" in line:
            color = "#e3b341"  # Warm Yellow
        elif line.strip().startswith("[") and line.strip().endswith("]"):
            color = "#bc8cff"  # Purple bracketed tags
        else:
            color = "#c9d1d9"  # Clean GitHub Light Grey

        draw.text((padding, y), line, fill=color, font=font)
        y += line_height

    os.makedirs(os.path.dirname(out_png_path), exist_ok=True)
    img.save(out_png_path, "PNG", dpi=(300, 300))

def compile_and_run(c_file_path, input_str=None):
    """
    Compiles a C file with clang -O2 -Wall and runs it, capturing stdout + stderr.
    """
    bin_path = c_file_path[:-2]
    cmd_compile = ["clang", "-Wall", "-Wextra", "-O2", c_file_path, "-o", bin_path, "-lm"]
    proc = subprocess.run(cmd_compile, capture_output=True, text=True)
    if proc.returncode != 0:
        raise RuntimeError(f"Compilation failed for {c_file_path}:\n{proc.stderr}")

    cmd_run = [bin_path]
    run_proc = subprocess.run(cmd_run, input=input_str, capture_output=True, text=True, timeout=30)
    return run_proc.stdout
