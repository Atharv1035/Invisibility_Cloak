# The Invisibility Cloak

Hey there, Potterheads !! This project demonstrates a real-time **invisibility cloak effect** with **OpenCV**'s image capture and processing capabilities in **C++**. The application captures a live video stream, isolates a monochromatic object of your choice, and renders that colored region invisible!!

## Table of Contents

1. [Objective](#1-objective)  
2. [Repository Structure](#2-repository-structure)   
3. [Installation & Build Instructions](#3-installation--build-instructions)  
4. [Usage Guide](#4-usage-guide)  


## Objective
This project demonstrates the classic **Invisibility Cloak effect** using **OpenCV** and **C++**.  
The program captures a live video stream, identifies a cloak of a specific color, and replaces it with the background, making the cloak appear invisible.

---
## 2. Repository Structure

```
. Invisibility_Cloak
├── 📁assets 
├── 📁include
│   └── 📄invisibility_cloak.hpp
├── 📁src
|   └── 📄invisibility_cloak.cpp
├── 📄main.cpp
├── 📄Makefile
└── 📄README.md
```
---
## 3. Installation & Prerequisites
### Setup
- C++ compiler()
- OpenCV (v3.0+ recommended)
- Linux with webcam support

### Installation
- Clone the repository using GUI or paste following text in terminal : 
```bash
 git clone --recursive https://github.com/Atharv1035/Invisibility_Cloak.git

 cd Invisibility_Cloak
 ```

---
## 4.Usage Guide
Now, once you are setup with the repository locally and the all the prerequisites ,its time to run the script.
Open your terminal and type in : 
```bash
cd Invisibility_Cloak
```
- When inside the directory, run : 
```bash
make clean
make SRC=main.cpp link=src/invisibility_cloak.cpp
```
- After the target build is completed ,you should be able to see your binary executable in your directory tree
- Simply run,
```bash
./invisibility_cloak
```
- __Step 01__ : Background Frame Capture ( stay out of frame to capture the background first)
- __Step 02__ : Once bg is captured ,get in frame and press I ;this will allow you to select the ROI/cloak(NOTE : Choose a solid color object for best results)
- __Step 03__ : Click on the ROI to set it as your cloak and see the magic unfold!!
   
### How the code works

#### 1. Capture Video Input
- Open the webcam using OpenCV:
```cpp
   cv::VideoCapture video(0);
```
- Allow a few seconds for the camera to open.

#### 2. Capture the Background

- The webcam feed is opened and 100 frames are read to capture a clean **background** image (without the subject in frame).  
- This background will later replace the cloak region.

```cpp
for (int i = 0; i < 100; i++) {
    cv::Mat temp;
    video.read(temp);
    bg = temp.clone();
    cv::imshow("Background", bg);
    cv::waitKey(30);
}
```

#### Selecting the ROI/Cloak
- On selection of the ROI by the user, the HSV values of the ROI are extracted from the frame.
- These values are stored and will be used for defining the cloak mask.
```cpp
cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
cv::Vec3b pixel = hsv.at<cv::Vec3b>(selectedPoint);
h = pixel[0]; s = pixel[1]; v = pixel[2];
```

#### Application of "Invisible" effect
- Using simple image Masking, the selected ROI and background are superimposed ,giving the illusion of invisibility.
```cpp
cv::inRange(hsv, lower, upper, cloak);
bg.copyTo(cloak_area, cloak);
frame.copyTo(visible, inv_mask);
final_output = cloak_area + visible;
```


