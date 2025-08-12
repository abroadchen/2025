"""
@author June
@time 2025/8/9
@description: https://www.yuque.com/icheima/ypa3in/hw2gdc05mwxnkmss
"""
import cv2 as cv


capture = cv.VideoCapture(0)
print(capture.isOpened())

ok, frame = capture.read()
while ok:
    cv.imshow("frame", frame)
    cv.waitKey(50)

    ok, frame = capture.read()