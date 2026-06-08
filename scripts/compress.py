from PIL import Image
import os

folder = os.path.join(os.path.dirname(__file__), '..', 'data', 'resources')
folder = os.path.normpath(folder)

for f in os.listdir(folder):
    if f.lower().endswith(('.jpg', '.jpeg')):
        path = os.path.join(folder, f)
        before = os.path.getsize(path) // 1024
        img = Image.open(path)
        w, h = img.size
        if w > 800:
            img = img.resize((800, int(h * 800 / w)), Image.LANCZOS)
        img.save(path, quality=60, optimize=True)
        after = os.path.getsize(path) // 1024
        print(f'{f}: {before}KB -> {after}KB')
