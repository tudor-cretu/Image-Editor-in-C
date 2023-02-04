// Copyright Cretu Mihnea Tudor 315CAa 2022 - 2023

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "function.h"
#define SIZE_STRING 100
#define COMMENT_SIZE 300

// function used to dynamically allocate memory for a 2D matrix of integers
int **matrix_allocation(int rows, int cols)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (!matrix)
    {
        printf("malloc() failed\n");
        free(matrix);
        return NULL;
    }
    for (int j = 0; j < rows; j++)
    {
        matrix[j] = (int *)malloc(cols * sizeof(int));
        if (!matrix[j])
        {
            printf("malloc() failed\n");
            while (--j >= 0)
            {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

//  function used to free the memory allocated for a 2D matrix of integers
void free_matrix(int **matrix, int rows)
{
    for(int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}
// function used to check if a file that is being read has a comment row or not
void check_for_comment(FILE *image, char *comment_string)
{
    int position = ftell(image);
    fgets(comment_string, COMMENT_SIZE, image);
    fgets(comment_string, COMMENT_SIZE, image);
    if(comment_string[0] != '#') fseek(image, position, SEEK_SET);
}

// function used to create a histogram of an image and display it in the stdout
void histogram_creation(char *file_type, int bins, int max_stars, int rows, int cols, int **matrix)
{
    if(strcmp(file_type, "P2") == 0 || strcmp(file_type, "P5") == 0)
    {
        int interval_checker = 256 / bins, bins_count = 0, maxfrequence = 0;
        int frequence[257] = {0}, interval_frequence[256] = {0};
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++) frequence[matrix[i][j]]++; // checks the frequence of every pixel in the matrix
        for(int i = 1; i <= bins; i++) {
            for(int j = interval_checker * i - interval_checker; j < interval_checker * i; j++)
                interval_frequence[bins_count] += frequence[j]; //checks the frequence of every interval depending on the bins number
            if(maxfrequence < interval_frequence[bins_count]) maxfrequence = interval_frequence[bins_count];
            bins_count++;
        }
        bins_count--;
        double number_of_stars;
        for(int i = 0; i <= bins_count; i++) {
            number_of_stars = interval_frequence[i] * max_stars / maxfrequence; // finding the number of stars in a row
            int aproximate_stars = (int)number_of_stars;
            printf("%d\t|\t", aproximate_stars);
            for(int j = 0; j < aproximate_stars; j++) printf("*");
            printf("\n");
        }
    }
    else printf("Black and white image needed\n"); 
}

// function used to perform histogram equalization on a black and white image
void equalize(char *file_type, int rows, int cols, int **matrix)
{
    if(strcmp(file_type, "P2") == 0 || strcmp(file_type, "P5") == 0)
    {
        int frequence[257] = {0};
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++) frequence[matrix[i][j]]++;
        double area = rows * cols, sum = 0;
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++) {
                sum = 0;
                for(int k = 0; k <= matrix[i][j]; k++) sum += frequence[k];
                matrix[i][j] = round(255 * sum / area);
                if(matrix[i][j] > 255) matrix[i][j] = 255;
                if(matrix[i][j] < 0) matrix[i][j] = 0;
            }
        printf("Equalize done\n");
    }
    else printf("Black and white image needed\n");
}

// function gives the values of a cropped area to another matrix later to be used for cropping
void crop_gray_image(int x1, int x2, int y1, int y2, int **matrix, int **cropped_matrix)
{
    int l = 0, k = 0;
    for(int i = y1; i < y2; i++) {
        l = 0;
        for(int j = x1; j < x2; j++) {
            cropped_matrix[k][l] = matrix[i][j];
            l++;
        }
        k++;
    }
}

// function gives the values of a cropped area to another set of matrices later to be used for cropping
void crop_rgb_image(int x1, int x2, int y1, int y2, int **cropped_matrixr, int **cropped_matrixg, int **cropped_matrixb, int **matrixr, int **matrixg, int **matrixb)
{
    int l = 0, k = 0;
    for(int i = y1; i < y2; i++) {
        l = 0;
        for(int j = x1; j < x2; j++) {
            cropped_matrixr[k][l] = matrixr[i][j];
            cropped_matrixg[k][l] = matrixg[i][j];
            cropped_matrixb[k][l] = matrixb[i][j];
            l++;
        }
        k++;
    }
}

// function builds the kernel matrix depending on the applying value
void apply_building_kernel(char *apply, int *okay_apply, int (*kernel)[3], int *okay_blur, int *okay_gblur)
{
    if(strcmp(apply, "EDGE") == 0) 
    {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++) {
                kernel[i][j] = -1;
                if(i == 1 && j == 1) kernel[i][j] = 8;
            }
        *okay_apply = 1;
    }
    else if(strcmp(apply, "SHARPEN") == 0)
    {
        kernel[0][0] = 0; kernel[0][2] = 0; kernel[2][0] = 0; kernel[2][2] = 0;
        kernel[0][1] = -1; kernel[1][0] = -1; kernel[1][2] = -1; kernel[2][1] = -1;
        kernel[1][1] = 5;
        *okay_apply = 1;
    }
    else if(strcmp(apply, "BLUR") == 0)
    {   
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++) {
                kernel[i][j] = 1;
            }
        *okay_blur = 1;
        *okay_apply = 1;
    }
    else if(strcmp(apply, "GAUSSIAN_BLUR") == 0)
    {
        kernel[0][0] = 1; kernel[0][2] = 1; kernel[2][0] = 1; kernel[2][2] = 1;
        kernel[0][1] = 2; kernel[1][0] = 2; kernel[1][2] = 2; kernel[2][1] = 2;
        kernel[1][1] = 4;
        *okay_gblur = 1;
        *okay_apply = 1;
    }
    else printf("APPLY parameter invalid\n");
}

// function used to apply the kernel matrix on an RGB image
void apply_matrix(int y1, int y2, int x1, int x2, int rows, int cols, int **matrixr, int **matrixg, int **matrixb, int (*kernel)[3], int okay_blur, int okay_gblur, int **aux_matrixr, int **aux_matrixg, int **aux_matrixb)
{   
    double red = 0, green = 0, blue = 0;
    for(int i = y1; i < y2; i++)
        for(int j = x1; j < x2; j++) 
        {
            if(i != 0 && j != 0 && i != rows - 1 && j != cols - 1)
            {
                red = 0; blue = 0; green = 0;
                red = matrixr[i-1][j-1] * kernel[0][0] + matrixr[i-1][j] * kernel[0][1] + matrixr[i-1][j+1] * kernel[0][2]
                + matrixr[i][j-1] * kernel[1][0] + matrixr[i][j] * kernel[1][1] + matrixr[i][j+1] * kernel[1][2] +
                matrixr[i+1][j-1] * kernel[2][0] + matrixr[i+1][j] * kernel[2][1] + matrixr[i+1][j+1] * kernel[2][2];
                blue = matrixb[i-1][j-1] * kernel[0][0] + matrixb[i-1][j] * kernel[0][1] + matrixb[i-1][j+1] * kernel[0][2]
                + matrixb[i][j-1] * kernel[1][0] + matrixb[i][j] * kernel[1][1] + matrixb[i][j+1] * kernel[1][2] +
                matrixb[i+1][j-1] * kernel[2][0] + matrixb[i+1][j] * kernel[2][1] + matrixb[i+1][j+1] * kernel[2][2]; 
                green = matrixg[i-1][j-1] * kernel[0][0] + matrixg[i-1][j] * kernel[0][1] + matrixg[i-1][j+1] * kernel[0][2]
                + matrixg[i][j-1] * kernel[1][0] + matrixg[i][j] * kernel[1][1] + matrixg[i][j+1] * kernel[1][2] +
                matrixg[i+1][j-1] * kernel[2][0] + matrixg[i+1][j] * kernel[2][1] + matrixg[i+1][j+1] * kernel[2][2];
                if(okay_blur == 1) {red /= 9; blue /= 9; green /= 9;}
                if(okay_gblur == 1) {red /= 16; blue /= 16; green /= 16;}
                if(red > 255) red = 255;
                else if(red < 0) red = 0;
                if(blue > 255) blue = 255;
                else if(blue < 0) blue = 0;
                if(green > 255) green = 255;
                else if(green < 0) green = 0;
                aux_matrixr[i][j] = round(red); 
                aux_matrixb[i][j] = round(blue); 
                aux_matrixg[i][j] = round(green);
            }
        }
}

// function used to save an image into a file, converting the type of the image, if necessary (binary / text)
void save_image(FILE *save_file, char *save_file_name, int ascii_file, int binary_file, char *file_type, int cols, int rows, int image_type, int **matrix, int **matrixr, int **matrixg, int **matrixb)
{
    save_file = fopen(save_file_name, "w");
    if(ascii_file == 1) 
    {
        if(strcmp(file_type, "P5") == 0) strcpy(file_type, "P2");
        if(strcmp(file_type, "P6") == 0) strcpy(file_type, "P3");
        if(strcmp(file_type, "P2") == 0 || strcmp(file_type, "P3") == 0) 
        {
            fprintf(save_file, "%s\n", file_type);
            fprintf(save_file, "%d %d\n", cols, rows);
            fprintf(save_file, "%d\n", image_type);
            if(strcmp(file_type, "P2") == 0)
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < cols; j++) fprintf(save_file, "%d ", matrix[i][j]);
                    fprintf(save_file, "\n");
                }
            if(strcmp(file_type, "P3") == 0)
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < cols; j++) {
                        fprintf(save_file, "%d ", matrixr[i][j]);
                        fprintf(save_file, "%d ", matrixg[i][j]);
                        fprintf(save_file, "%d ", matrixb[i][j]);
                    }
                    fprintf(save_file, "\n");
                }
        }
    }
    else if(binary_file == 1)
    {
        if(strcmp(file_type, "P2") == 0) strcpy(file_type, "P5");
        if(strcmp(file_type, "P3") == 0) strcpy(file_type, "P6");
        if(strcmp(file_type, "P5") == 0 || strcmp(file_type, "P6") == 0) 
        {
            fprintf(save_file, "%s\n", file_type);
            fprintf(save_file, "%d %d\n", cols, rows);
            fprintf(save_file, "%d\n", image_type);
            if(strcmp(file_type, "P5") == 0)
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < cols; j++) fwrite(&matrix[i][j], sizeof(unsigned char), 1, save_file);
                }
            if(strcmp(file_type, "P6") == 0)
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < cols; j++) {
                        fwrite(&matrixr[i][j], sizeof(unsigned char), 1, save_file);
                        fwrite(&matrixg[i][j], sizeof(unsigned char), 1, save_file);
                        fwrite(&matrixb[i][j], sizeof(unsigned char), 1, save_file);
                    }
                }
        }
    }
    printf("Saved %s\n", save_file_name);
    fclose(save_file);
}

// function frees all the memory that remains before exiting the program
void exit_freeing_memory(int load_count, int **matrix, int **matrixr, int **matrixg, int **matrixb, int rows)
{
    if(load_count == 0) printf("No image loaded\n");
    if(matrix != NULL) free_matrix(matrix, rows);
    if(matrixr != NULL) free_matrix(matrixr, rows);
    if(matrixg != NULL) free_matrix(matrixg, rows);
    if(matrixb != NULL) free_matrix(matrixb, rows);
}