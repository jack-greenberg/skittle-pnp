from PIL import Image

im = Image.open("./images/sample.jpg")

im1 = Image.Image.split(im)

im1[0].show()
im1[1].show()
im1[2].show()