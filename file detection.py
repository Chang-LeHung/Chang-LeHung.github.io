
import os
import argparse
import time
from datetime import datetime
import sys
from PIL import Image, ImageDraw, ImageFont


def add_watermark(path):
	im = Image.open(path).convert('RGBA')
	txt = Image.new('RGBA', im.size, (0,0,0,0))
	fnt = ImageFont.truetype("c:/Windows/fonts/simhei.ttf", 20)
	d = ImageDraw.Draw(txt)
	d.text((txt.size[0]-120,txt.size[1]-30),"@牧牛的铃铛",font=fnt, fill="black")
	out = Image.alpha_composite(im, txt)
	out.save(path)

def preprocessing(path):
	files = []
	num = 0
	for file in os.listdir(path):
		try:
			n = int(file[:-4])
			if n > num:
				num = n
			files.append(file)
		except Exception:
			print("Exception file", file)
	return files, num

def detection(path, fill, sleep):
	
	files, num = preprocessing(path)
	while True:
		iters = os.listdir(path)
		iters = [ file for file in iters if file.endswith(("png", 'jpg'))]
		for file in iters:
			if file not in files:
				num += 1
				name = f"{num}.png".rjust(fill, "0")
				os.rename(os.path.join(path, file),
					os.path.join(path, name))
				files.append(name)
				now = datetime.now()
				s = now.strftime("%Y-%m-%d %H:%M:%S")
				image_dir = os.path.join(path, name)
				add_watermark(image_dir)
				print(s, "File",
					"was detected", "markdown path:", 
					f"![{image_dir}]({image_dir})")
		time.sleep(0.5)
		sys.stdout.flush()


if __name__ == '__main__':
	parse = argparse.ArgumentParser()
	parse.add_argument("--path", type=str, default="./")
	parse.add_argument("--num", type=int, default=6)
	parse.add_argument("--sleep", type=float, default=0.5)
	args = parse.parse_args()
	detection(args.path, args.num, args.sleep)
