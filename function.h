// Copyright Cretu Mihnea Tudor 315CAa 2022 - 2023

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define SIZE_STRING 100
#define COMMENT_SIZE 300

// arguments: number of rows and columns of the matrix to be allocated memory for
int **matrix_allocation(int rows, int cols);

// arguments: a matrix and its number of rows
void free_matrix(int **matrix, int rows);

// arguments: the file that contains the image, the comment line (if present)
void check_for_comment(FILE *image, char *comment_string);

// arguments: the image type, the number of bins, the maximum number of "*", the number of rows & columns 
//            and the matrix of the black & white picture
void histogram_creation(char *file_type, int bins, int max_stars, int rows, int cols, int **matrix);

//arguments: the image type, the number of rows and columns, the matrix of the black & white picture
void equalize(char *file_type, int rows, int cols, int **matrix);

// arguments: the coordinates of the selection, the matrix and the cropped matrix of the black & white picture
void crop_gray_image(int x1, int x2, int y1, int y2, int **matrix, int **cropped_matrix);

// arguments: the coordinates of the selection, the cropped matrices and the full matrices for each color (red, green and blue)
void crop_rgb_image(int x1, int x2, int y1, int y2, int **cropped_matrixr, int **cropped_matrixg, int **cropped_matrixb, int **matrixr, int **matrixg, int **matrixb);

// arguments: string for "APPLY" command and its checker, the kernel matrix and the checkers for applying blurring 
void apply_building_kernel(char *apply, int *okay_apply, int (*kernel)[3], int *okay_blur, int *okay_gblur);

// arguments: the coordinates of the selection, the number of rows & columns, the matrixes for RGB and their auxiliaries, 
//            the kernel matrix and the checkers for applying blurring
void apply_matrix(int y1, int y2, int x1, int x2, int rows, int cols, int **matrixr, int **matrixg, int **matrixb, int (*kernel)[3], int okay_blur, int okay_gblur, int **aux_matrixr, int **aux_matrixg, int **aux_matrixb);

// arguments: the save file and its name, the checker for binary/ascii, the type of the picture, the number of columns & rows,
//            the magic number (255), and matrixes for black and white, respectively RGB images
void save_image(FILE *save_file, char *save_file_name, int ascii_file, int binary_file, char *file_type, int cols, int rows, int image_type, int **matrix, int **matrixr, int **matrixg, int **matrixb);

// arguments: the load checker, the 3 matrixes for red, green and blue and also the number of rows
void exit_freeing_memory(int load_count, int **matrix, int **matrixr, int **matrixg, int **matrixb, int rows);