

# Image Processing Application using Qt and OpenCV

This is a simple image processing application created using Qt and OpenCV. It allows users to load images, apply basic image processing operations (such as grayscale and blur), and save the processed images.

## Prerequisites

Before using this application, ensure that you have the following software installed:

- Qt Framework: You can download and install Qt from the [official Qt website](https://www.qt.io/download).

OpenCV: OpenCV is a computer vision library. You can download and install it from the [OpenCV website](https://opencv.org/releases.html) or install it using package managers like `apt` (for Linux) or Visual Studio (for Windows).

## Getting Started

1. Clone this repository to your local machine or download the source code.

2. Open the project in Qt Creator or your preferred integrated development environment (IDE).

3. Build the project to generate the executable.

4. Run the executable to open the image processing application.

## Features

The application provides the following features:

-**Load Image**: Users can load an image of various formats (e.g., PNG, JPEG, BMP) using the "Load Image" button.

-**Blur Image**: Apply Gaussian blur to the loaded image using the "Blur" button. The blur intensity can be adjusted using the slider.

-**Rotate Image**: Rotate the image by 90 degrees clockwise or counterclockwise using the "Rotate" and "Right Rotate" buttons.

-**Grayscale**: Convert the image to grayscale using the "Gray" button.

-**Resize Image**: Resize the image to 75% of its original size using the "Resize" button. This can be repeated multiple times.

-**Clear Image**: Restore the original image by clearing any applied filters or transformations.

-**Sharpness**: Apply a sharpening filter to enhance image details using the "Sharp" button.

-**Flip Image**: Flip the image horizontally using the "Flip" button.

-**Enlarge Image**: Increase the image size by 25% using the "Enlarge" button.

-**Brightness and Contrast**: Adjust image brightness and contrast using sliders provided under the "Brightness" and "Contrast" buttons.

-**White Balance**: Automatically balance white levels in the image using the "Color" button.

-**Crop Image**: Select a region in the image to crop using the "Crop" button. Click and drag to select the cropping area.

-**Save Image**: Save the processed image to your desired location and format (e.g., PNG, JPEG, BMP) using the "Save" button.

## Usage

1. Launch the application.

2. Click the "Load Image" button to open an image from your computer.

3. Use the "Grayscale" and "Blur" buttons to apply image processing operations to the loaded image.

4. Click the "Save Image" button to save the processed image to your computer.


## Acknowledgments

- This application was created using the Qt Framework and OpenCV library.

- Special thanks to the [OpenCV community](https://opencv.org/) for their contributions to computer vision and image processing.

