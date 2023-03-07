<h5 align = center> Copyright Cretu Mihnea Tudor 315CAa 2022 - 2023 </h5> 
<h5 align = center> 3rd Homework for Programming Languages Class, Year I - Faculty of Automation Control and Computer Science, Polytechnic University of Bucharest </h5>

<h1 align=center> PPM and PGM Image Editor </h1>
<i align=center> Program finished, README under construction </i>
<h4> 1) Introduction: </h4>
<p align = left>    This is a PPM and PGM image editing program. The program is designed to support both ASCII and binary 
    formats, and offers a wide range of features such as cropping, histogram creation, image equalization, 
    and image filtering. The user interface is easy to navigate, making it suitable for both professional
    and amateur photographers. With this program, you can easily open, edit and save RGB or grayscale images. </p>

<h4> 2) Installation: </h4> 
<p>    Download or clone the repository to your local machine. </p>
<p>    Navigate to the root directory of the project in your terminal. </p>
<p>    Run the command <make build> to build the program </p>
<p>    Once the build is successful, you can run the program by using the command ./image_editor </p>
<p>    To clean the generated files from the build process, use the command {make clean} </p>

<h4> 3) Usage: </h4>
<p>    {input} --> mandatory input </p>
<p>     [input] --> optional input </p>
<p> </p>
<p>     Use the following commands to edit your image: </p>
<p> </p>
<p>     LOAD {file_name} {file_type} - open a file, file_type can be P2, P3, P5, P6 </p>
<p>     SAVE {file_name} [ascii] - save the current image in ascii (specify it) or binary format </p>
<p>     HISTOGRAM {max_stars} {bins} - create the histogram of a grayscale image with X max. number of stars and Y bins </p>
<p>     EQUALIZE - perform histogram equalization on a grayscale image </p>
<p>     SELECT {x1} {y1} {x2} {y2} - select the area of given coordinates </p>
<p>    SELECT ALL - select the area of the whole image </p>
<p>     CROP - crop the image with the area of previous selected coordinates </p>
<p>     APPLY {parameter} - applies filter to the image or its selected coordinates, parameter can be SHARPEN, EDGE, BLUR, GAUUSIAN_BLUR </p>

<h4> 4) File Formats: </h4>
<p> This program supports the following file formats: </p>
<p>    -> PGM (Portable Gray Map) ASCII and binary </p>
<p>    -> PPM (Portable Pixmap) ASCII and binary </p>
<p>    Both PGM and PPM are image file formats that are used to store digital images. PGM is used for grayscale images 
    while PPM is used for color images. The ASCII version of these file formats stores the image data in a 
    human-readable text format, while the binary version stores the data in a compact binary format. </p>

<h4> 5) Examples: </h4>
<p>    Open a binary PGM image "image.pgm" and create a histogram with 20 bins and 50 max stars: </p>
<p>        LOAD image.pgm </p>
<p>        HISTOGRAM 50 8 </p>
<p> </p>
<p>    Save the image with the name "image_histogram.pgm" in binary format: </p>
<p>        SAVE image_histogram.pgm </p>
<p> </p>
<p>    Perform histogram equalization on a grayscale image: </p>
<p>        LOAD image.pgm </p>
<p>        EQUALIZE </p>
<p>        SAVE image_equalized.pgm ascii </p>
<p> </p>
<p>    Crop a rectangular area from an RGB image: </p>
<p>        LOAD image.ppm </p>
<p>        SELECT 100 200 400 500 </p>
<p>        CROP </p>
<p>        SAVE image_cropped.ppm </p>
<p> </p>
<p>    Apply the Gaussian Blur filter to an RGB image: </p>
<p>        LOAD image.ppm </p>
<p>        APPLY GAUSSIAN_BLUR </p>
<p>        SAVE image_blurred.ppm ascii </p>
<p> </p>
<p>    It is important to note that the program only allows one image to be loaded at a time, and any subsequent
    image loading will overwrite the previous image. Also, before saving an image, the user must first load
    an image or perform an operation on the previously loaded image. </p>

<h4> 6) Troubleshooting </h4>
<p>    If you encounter any issues while building or running the program, please check the following: </p>
<p>    Ensure that you are running the program in the correct directory and that all the files are in the same directory </p>
<p>    If you are having trouble loading a file, make sure that the file name is entered correctly </p>
<p>    If you are having trouble saving a file, make sure that the file name and file type are entered correctly </p>
<p>    If you are having trouble applying a filter, make sure that the filter parameter is entered correctly </p>

<h4> 7) Technical Details </h4>
<p>    All the functions and methods used for making or using this program are detailed in the source code,
    the functions are explained in function.c, the arguments for functions are explained in function.h and the general
    code is explained in image_editor.c </p>
