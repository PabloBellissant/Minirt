from PIL import Image
import sys

def png_to_pgm(input_path, output_path):
    img = Image.open(input_path).convert("L")
    img.save(output_path, format="PPM")

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py input.png output.pgm")
        return
    png_to_pgm(sys.argv[1], sys.argv[2])

if __name__ == "__main__":
    main()

