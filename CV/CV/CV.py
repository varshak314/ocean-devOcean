
import cv2
import math
import numpy as np
from PIL import Image, ImageFilter
from matplotlib import pyplot as plt
####https://www.geeksforgeeks.org/detect-an-object-with-opencv-python/ 

# Opening image
#img = Image.open("test.jpeg")
img = Image.open("redbag.jpg")
#img.show()
img = img.resize((400, 300), Image.ANTIALIAS)
origCV = cv2.cvtColor(np.array(img), cv2.COLOR_RGB2BGR)
#img.save("bag.jpg", dpi = (400, 300))
w, h = img.size
img = img.filter(ImageFilter.BoxBlur(5))
#img.show()
rgbA = np.array(img)
avgR = np.average(rgbA[:,:,0])
avgG = np.average(rgbA[:,:,1])
avgB = np.average(rgbA[:,:,2])
blueArray = rgbA[:, :, 2]
blueRatioA = blueArray/avgB;
redArray = rgbA[:, :, 0]
redRatioA = redArray/avgR;
blue2white = blueRatioA<.5
red2white = redRatioA>1 
trash = np.logical_and(blue2white, red2white)
notTrash = ~trash
rgbA[trash, :] = 255
rgbA[notTrash, :] = 0
thresh = Image.fromarray(rgbA)
thresh.show()
#centroid code from: https://learnopencv.com/find-center-of-blob-centroid-using-opencv-cpp-python/
thresh = cv2.cvtColor(np.array(thresh), cv2.COLOR_RGB2BGR)  #https://stackoverflow.com/questions/14134892/convert-image-from-pil-to-opencv-format

gray_image = cv2.cvtColor(thresh, cv2.COLOR_BGR2GRAY)

# convert the grayscale image to binary image
ret,thresh = cv2.threshold(gray_image,127,255,0)
#imPIL = thresh.save("threshPIL.jpg")
#thresh = cv2.imread("threshPIL.jpg")
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE ,cv2.CHAIN_APPROX_SIMPLE)
centroids = [] 
for c in contours:
   # calculate moments for each contour
   M = cv2.moments(c)
   # calculate x,y coordinate of center
   if M["m00"] != 0:
       cX = int(M["m10"] / M["m00"])
       cY = int(M["m01"] / M["m00"])
   #else:   
       #cX, cY = 0, 0
   #cX = int(M["m10"] / M["m00"])
   #cY = int(M["m01"] / M["m00"])
       centroids.append((cX, cY))
       origCV = cv2.circle(origCV, (cX, cY), 5, (255, 255, 255), -1)
       origCV = cv2.putText(origCV, "centroid", (cX - 25, cY - 25),cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
# display the image
print(centroids)
cv2.imshow("Image", origCV)
cv2.waitKey(0)
print("done")
