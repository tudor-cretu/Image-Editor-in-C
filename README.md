<h5 align = center> Copyright Cretu Mihnea Tudor 315CAa 2022 - 2023 </h5> 
<h5 align = center> 3rd Homework for Programming Languages Class, Year I - Faculty of Automation Control and Computer Science, Polytechnic University of Bucharest </h5>

<h1 align=center> PPM and PGM Image Editor </h1>

<h4> 1) Introduction: </h4>
<p align = left>    This is a PPM and PGM image editing program. The program is designed to support both ASCII and binary 
    formats, and offers a wide range of features such as cropping, histogram creation, image equalization, 
    and image filtering. The user interface is easy to navigate, making it suitable for both professional
    and amateur photographers. With this program, you can easily open, edit and save RGB or grayscale images. </p>

<h4> 2) Installation: </h4> 
<p align = left>    Download or clone the repository to your local machine.
    Navigate to the root directory of the project in your terminal.
    Run the command <make build> to build the program
    Once the build is successful, you can run the program by using the command ./image_editor
    To clean the generated files from the build process, use the command <make clean> </p>

<h4> 3) Usage: </h4>
<p>    {input} --> mandatory input </p>
<p>     [input] --> optional input </p>
<p>     Use the following commands to edit your image: </p>
<p>     LOAD {file_name} {file_type} - open a file, file_type can be P2, P3, P5, P6 </p>
<p>     SAVE {file_name} [ascii] - save the current image in ascii (specify it) or binary format </p>
<p>     HISTOGRAM {max_stars} {bins} - create the histogram of a grayscale image with X max. number of stars and Y bins </p>
<p>     EQUALIZE - perform histogram equalization on a grayscale image </p>
<p>     SELECT {x1} {y1} {x2} {y2} - select the area of given coordinates </p>
<p>    SELECT ALL - select the area of the whole image </p>
<p>     CROP - crop the image with the area of previous selected coordinates </p>
<p>     APPLY {parameter} - applies filter to the image or its selected coordinates, parameter can be SHARPEN, EDGE, BLUR, GAUUSIAN_BLUR </p>

    <h4> 4) File Formats: </h4>
    This program supports the following file formats:
    -> PGM (Portable Gray Map) ASCII and binary
    -> PPM (Portable Pixmap) ASCII and binary
    Both PGM and PPM are image file formats that are used to store digital images. PGM is used for grayscale images 
    while PPM is used for color images. The ASCII version of these file formats stores the image data in a 
    human-readable text format, while the binary version stores the data in a compact binary format.

    <h4> 5) Examples: </h4>
    Open a binary PGM image "image.pgm" and create a histogram with 20 bins and 50 max stars:
        LOAD image.pgm
        HISTOGRAM 50 8
    Save the image with the name "image_histogram.pgm" in binary format:
        SAVE image_histogram.pgm
    Perform histogram equalization on a grayscale image:
        LOAD image.pgm
        EQUALIZE
        SAVE image_equalized.pgm ascii
    Crop a rectangular area from an RGB image:
        LOAD image.ppm
        SELECT 100 200 400 500
        CROP
        SAVE image_cropped.ppm
    Apply the Gaussian Blur filter to an RGB image:
        LOAD image.ppm
        APPLY GAUSSIAN_BLUR
        SAVE image_blurred.ppm ascii
    It is important to note that the program only allows one image to be loaded at a time, and any subsequent
    image loading will overwrite the previous image. Also, before saving an image, the user must first load
    an image or perform an operation on the previously loaded image.

6) Troubleshooting
    If you encounter any issues while building or running the program, please check the following:
    Ensure that you are running the program in the correct directory and that all the files are in the same directory
    If you are having trouble loading a file, make sure that the file name is entered correctly
    If you are having trouble saving a file, make sure that the file name and file type are entered correctly
    If you are having trouble applying a filter, make sure that the filter parameter is entered correctly

7) Technical Details
    All the functions and methods used for making or using this program are detailed in the source code,
    the functions are explained in function.c, the arguments for functions are explained in function.h and the general
    code is explained in image_editor.c
