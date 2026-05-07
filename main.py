import cv2 as cv

cap = cv.VideoCapture(0)

while(cap.isOpened()):
    retval, image = cap.read()
    if retval == True:
        gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
        cv.imshow('frame', gray)
        if cv.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        break