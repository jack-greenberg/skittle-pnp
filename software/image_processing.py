from PIL import Image, ImageOps
import scipy.ndimage as ndimage
import matplotlib.pyplot as plt
import cv2

def estimate_color(c, bit, c_error):
    c_new= c -  c_error
    if c_new > 127:
        c_bit= bit
        c_error= 255 - c_new
    else:
        c_bit= 0
        c_error= -c_new
    return c_bit, c_error

def image2cga(im):
    "Produce a sequence of CGA pixels from image im"
    im_width= im.size[0]
    for index, (r, g, b) in enumerate(im.getdata()):
        if index % im_width == 0: # start of a line
            r_error= g_error= 0
        r_bit, r_error= estimate_color(r, 1, r_error)
        g_bit, g_error= estimate_color(g, 2, g_error)
        yield r_bit|g_bit

def cvt2cga(imgfn):
    "Convert an RGB image to (K, R, G, Y) CGA image"
    inp_im= Image.open(imgfn).convert('L') # assume it's RGB
    # gray = cv2.cvtColor(inp_im, cv2.COLOR_BGR2GRAY)
    out_im= Image.new("P", inp_im.size, None)
    out_im.putpalette( (
        76, 56, 47,
        160, 55, 54,
        240, 113, 15,
        205, 191, 9
    ) )
    out_im.putdata(list(image2cga(inp_im)))
    return out_im

if __name__ == "__main__":
    import sys, os

    for imgfn in sys.argv[1:]:
        image = Image.open(imgfn)
        k = imgfn.rsplit("/",2)[2]
        new_image = image.resize((125, 125))
        # new_image = ImageOps.grayscale(new_image)
        
        new_image.save("./images/new_"+k)
        im= cvt2cga("./images/new_"+k)
        dirname, filename= os.path.split("./images/new_"+k)
        name, ext= os.path.splitext(filename)
        newpathname= os.path.join(dirname, "cga-%s.png" % name)
        #img = ndimage.gaussian_filter(im, sigma=(5, 5, 0), order=0)
        im.save(newpathname)
        img = cv2.imread(newpathname)
        img = ndimage.gaussian_filter(img, sigma=(1, 1, 1), order=0)
        plt.imshow(img)#, interpolation='nearest')
        plt.show()
        #plt.imsave( "./images/test_sample7.png", img)
