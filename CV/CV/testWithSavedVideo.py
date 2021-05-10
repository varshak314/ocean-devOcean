import cv2
print("testing")
from CV import *
# Opens the Video file
cap= cv2.VideoCapture('redvid.mp4')
print(cap)
i=0
print("hello are you even working")
while(cap.isOpened()):
    ret, frame = cap.read()
    print(ret)
    if ret == False:
        break
    cv2.imwrite('testImage'+str(i)+'.jpg',frame)
    find_Centroid("testImage.jpg")
    i+=1
 
cap.release()
cv2.destroyAllWindows()
