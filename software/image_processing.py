import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

def palette(path):
    # Load the image and convert to grayscale
    image = cv.imread(path)
    image = cv.resize(image, (100, 100)) # max: 125 x 125
    img = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    cv.imwrite('my_img2.jpeg', img)

    # Define shade bounds
    first_lo=np.array([0])
    first_hi=np.array([63])
    second_lo = np.array([64])
    second_hi = np.array([127])
    third_lo = np.array([128])
    third_hi = np.array([191])
    fourth_lo = np.array([192])
    fourth_hi = np.array([255])

    # Mask image by bounds
    mask1=cv.inRange(img,first_lo,first_hi)
    mask2=cv.inRange(img,second_lo,second_hi)
    mask3=cv.inRange(img,third_lo,third_hi)
    mask4=cv.inRange(img,fourth_lo,fourth_hi)

    # Change image to four colors
    img[mask1 > 0] = 63 # (76, 56, 47)
    img[mask2 > 0] = 91 # (160, 55, 54)
    img[mask3 > 0] = 127 # (240, 113, 15)
    img[mask4 > 0]= 255 # (205, 191, 9)

    # Write resulting image
    cv.imwrite("result7.png", img)
    print(cv.imread("result7.png"))
    plt.imshow(img)
    plt.show()

if __name__ == "__main__":
    # original_image = "./images/sample7.jpg"
    original_image = "./images/sample4.jpg"
    palette(original_image)
    # print(cv.imread(original_image))