// Copyright Cretu Mihnea Tudor 315CAa 2022 - 2023

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "function.h"
#define SIZE_STRING 100
#define COMMENT_SIZE 300

int main()
{
    char command[SIZE_STRING], comment_string[COMMENT_SIZE], save_file_name[SIZE_STRING];
    char *aux_string = NULL;
    char file_name[SIZE_STRING];
    char file_type[3]; // 3 is the dimension for "P[NUMBER][end_of_string]"
    int rows, cols, load_count = 0, x1, y1, x2, y2, image_type, rgb_count = 0, aux_x1, aux_x2, aux_y1, aux_y2;
    unsigned long int position_char;
    int **matrix = NULL; int **matrixr = NULL; int **matrixg = NULL; int **matrixb = NULL; 
    FILE *image = NULL;
    FILE *save_file = NULL;
    while(1) 
    {
        char string_command[SIZE_STRING];
        fgets(string_command, SIZE_STRING, stdin);
        for(position_char = 0; position_char < strlen(string_command); position_char++) 
            if(string_command[position_char] == '\n') string_command[position_char] = '\0';
        aux_string = strtok(string_command, " \n");
        strcpy(command, aux_string);
        if(strcmp(command, "LOAD") == 0) 
        {
            aux_string = strtok(NULL, " \n");
            strcpy(file_name, aux_string);
            // freeing the previously allocated memory of a loaded matrix
            if(load_count == 1) {
                if(matrix != NULL) {free_matrix(matrix, rows); matrix = NULL;}
                if(matrixr != NULL) {free_matrix(matrixr, rows); matrixr = NULL;}
                if(matrixg != NULL) {free_matrix(matrixg, rows); matrixg = NULL;}
                if(matrixb != NULL) {free_matrix(matrixb, rows); matrixb = NULL;}
            }
            image = fopen(file_name, "r");
            if(!image) 
            {
                printf("Failed to load %s\n", file_name);
                load_count = 0;
            }
            else 
            {
                printf("Loaded %s\n", file_name); 
                fscanf(image, "%s", file_type);
                check_for_comment(image, comment_string);
                fscanf(image, "%d %d", &cols, &rows);
                x1 = 0; y1 = 0; x2 = cols; y2 = rows;  // setting the "select" coordinates for the whole matrix
                aux_x1 = x1; aux_y1 = y1; aux_x2 = x2; aux_y2 = y2;
                check_for_comment(image, comment_string);
                fscanf(image, "%d ", &image_type);
                check_for_comment(image, comment_string);
                if(image_type == 255) // verify that the image is gray-scale or RGB colored
                {
                    if(strcmp(file_type, "P2") == 0) // gray-scale ASCII
                    {
                        matrix = matrix_allocation(rows, cols);
                        for(int i = 0; i < rows; i++)
                            for(int j = 0; j < cols; j++) {
                                int element;
                                fscanf(image, "%d ", &element);
                                matrix[i][j] = element;
                            }
                        load_count = 1;
                        rgb_count = 0;
                    }
                    if(strcmp(file_type, "P3") == 0) // RGB ASCII
                    {
                        matrixr = matrix_allocation(rows, cols);
                        matrixg = matrix_allocation(rows, cols);
                        matrixb = matrix_allocation(rows, cols);
                        for(int i = 0; i < rows; i++)
                            for(int j = 0; j < cols; j++) {
                                int element;
                                fscanf(image, "%d ", &element);
                                matrixr[i][j] = element;
                                fscanf(image, "%d ", &element);
                                matrixg[i][j] = element;
                                fscanf(image, "%d ", &element);
                                matrixb[i][j] = element;
                            }
                        load_count = 1;
                        rgb_count = 1;
                    }
                    if(strcmp(file_type, "P5") == 0) // gray-scale Binary
                    {
                        matrix = matrix_allocation(rows, cols);
                        for(int i = 0; i < rows; i++)
                            for(int j = 0; j < cols; j++) {
                                unsigned char element;
                                fread(&element, sizeof(unsigned char), 1, image);
                                matrix[i][j] = element;
                            }
                        load_count = 1;
                        rgb_count = 0;
                    }
                    if(strcmp(file_type, "P6") == 0) // RGB Binary
                    {
                        matrixr = matrix_allocation(rows, cols);
                        matrixg = matrix_allocation(rows, cols);
                        matrixb = matrix_allocation(rows, cols);
                        for(int i = 0; i < rows; i++)
                            for(int j = 0; j < cols; j++) {
                                unsigned char element;
                                fread(&element, sizeof(unsigned char), 1, image);
                                matrixr[i][j] = element;
                                fread(&element, sizeof(unsigned char), 1, image);
                                matrixg[i][j] = element;
                                fread(&element, sizeof(unsigned char), 1, image);
                                matrixb[i][j] = element;
                            }
                        load_count = 1;
                        rgb_count = 1;
                    }
                }
                fclose(image);
            }
        }
        else if(strcmp(command, "SELECT") == 0)
        {
            char all[4];
            int enough_values = 1;
            aux_string = strtok(NULL, " \n");
            strcpy(all, aux_string);
            if(!aux_string) {enough_values = 0; printf("Invalid command\n"); continue;}
            if(strcmp(all, "ALL") != 0)
            {
                int general_aux, numbers_count = 0, digit = 1;
                // the lines 134-183 check if the input is of a valid format
                if(enough_values == 1 && digit == 1)
                {
                    if((aux_string[0] >= '0' && aux_string[0] <= '9') || aux_string[0] == '-') 
                    {
                        numbers_count++;
                        x1 = atoi(aux_string);
                    }
                    else digit = 0;
                }
                aux_string = strtok(NULL, " \n");
                if(!aux_string) {enough_values = 0; x1 = aux_x1; x2 = aux_x2; y1 = aux_y1; y2 = aux_y2; printf("Invalid command\n"); continue;}
                if(enough_values == 1 && digit == 1)
                {
                    if((aux_string[0] >= '0' && aux_string[0] <= '9') || aux_string[0] == '-') 
                    {
                        numbers_count++;
                        y1 = atoi(aux_string);
                    }
                    else digit = 0;
                }
                aux_string = strtok(NULL, " \n");
                if(!aux_string) {enough_values = 0; x1 = aux_x1; x2 = aux_x2; y1 = aux_y1; y2 = aux_y2; printf("Invalid command\n"); continue;}
                if(enough_values == 1 && digit == 1)
                {
                    if((aux_string[0] >= '0' && aux_string[0] <= '9') || aux_string[0] == '-') 
                    {
                        numbers_count++;
                        x2 = atoi(aux_string);
                    }
                    else digit = 0;
                }
                aux_string = strtok(NULL, " \n");
                if(!aux_string) {enough_values = 0; x1 = aux_x1; x2 = aux_x2; y1 = aux_y1; y2 = aux_y2; printf("Invalid command\n"); continue;}
                if(enough_values == 1 && digit == 1)
                {
                    if((aux_string[0] >= '0' && aux_string[0] <= '9') || aux_string[0] == '-') 
                    {
                        numbers_count++;
                        y2 = atoi(aux_string);
                    }
                    else digit = 0;
                }
                if(numbers_count < 4 || digit == 0) 
                {
                    printf("Invalid command\n"); 
                    x1 = aux_x1; x2 = aux_x2;
                    y1 = aux_y1; y2 = aux_y2;
                    continue;
                }
                if(load_count == 1)
                {   
                    if(y2 <= rows && x2 <= cols && x1 >= 0 && y1 >= 0 && x1 != x2 && y1 != y2)
                    {
                        if(x1 > x2) 
                        {
                            general_aux = x1; x1 = x2; x2 = general_aux;
                        }
                        if(y1 > y2)
                        {
                            general_aux = y1; y1 = y2; y2 = general_aux;
                        }
                        if(x1 < x2 && y1 < y2) 
                        {
                            printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
                            aux_x1 = x1, aux_y1 = y1, aux_x2 = x2, aux_y2 = y2;
                        }
                    }
                    else
                    {
                        printf("Invalid set of coordinates\n");
                        x1 = aux_x1; y1 = aux_y1; x2 = aux_x2; y2 = aux_y2;
                    }
                }
                else printf("No image loaded\n");
            }
            else if(strcmp(all, "ALL") == 0) 
            {
                if(load_count == 1)
                {
                    x1 = 0; y1 = 0; x2 = cols; y2 = rows;
                    aux_x1 = x1; aux_y1 = y1; aux_x2 = x2; aux_y2 = y2;
                    printf("Selected ALL\n");
                }
                else printf("No image loaded\n");
            }
        }
        else if(strcmp(command, "HISTOGRAM") == 0)
        {
            int max_stars, bins, count_numbers = 0;
            aux_string = strtok(NULL, " \n");
            while(aux_string)
            {
                count_numbers++;
                if(count_numbers == 1) max_stars = atoi(aux_string);
                if(count_numbers == 2) bins = atoi(aux_string);
                aux_string = strtok(NULL, " \n");
            }
            if(load_count == 1)
            {
                if(count_numbers != 2) {printf("Invalid command\n"); continue;}
                histogram_creation(file_type, bins, max_stars, rows, cols, matrix);
            }
            else printf("No image loaded\n");
        }
        else if(strcmp(command, "EQUALIZE") == 0)
        {
            if(load_count == 1)
            {
                equalize(file_type, rows, cols, matrix);
            }
            else printf("No image loaded\n");
        }
        else if(strcmp(command, "CROP") == 0)
        {
            if(load_count == 1)
            {
                if(x1 == 0 && y1 == 0 && x2 == cols && y2 == rows) printf("Image cropped\n");
                else 
                {   
                    int new_rows = y2 - y1, new_cols = x2 - x1, old_rows = rows;
                    if(rgb_count == 0) // cropping P2 & P5 
                    {
                        int **cropped_matrix = matrix_allocation(new_rows, new_cols);
                        crop_gray_image(x1, x2, y1, y2, matrix, cropped_matrix);
                        rows = new_rows; cols = new_cols; 
                        x2 = new_cols; y2 = new_rows; x1 = 0; y1 = 0; // in case CROP twice
                        aux_x1 = x2; aux_x2 = x2; aux_y1 = y1; aux_y2 = y2;
                        free_matrix(matrix, old_rows);
                        matrix = matrix_allocation(rows, cols);
                        printf("Image cropped\n");
                        for(int i = 0; i < rows; i++)
                            for(int j = 0; j < cols; j++) matrix[i][j] = cropped_matrix[i][j];
                        free_matrix(cropped_matrix, rows);
                    }
                    else if(rgb_count == 1)  // cropping P3 & P6
                    {
                        int **cropped_matrixr = matrix_allocation(new_rows, new_cols);
                        int **cropped_matrixg = matrix_allocation(new_rows, new_cols);
                        int **cropped_matrixb = matrix_allocation(new_rows, new_cols);
                        crop_rgb_image(x1, x2, y1, y2, cropped_matrixr, cropped_matrixg, cropped_matrixb, matrixr, matrixg, matrixb);
                        rows = new_rows; cols = new_cols;
                        x1 = 0; x2 = new_cols; y1 = 0; y2 = new_rows; // in case CROP twice
                        aux_x1 = x2; aux_x2 = x2; aux_y1 = y1; aux_y2 = y2;
                        free_matrix(matrixr, old_rows);
                        free_matrix(matrixg, old_rows);
                        free_matrix(matrixb, old_rows);
                        matrixr = matrix_allocation(rows, cols);
                        matrixg = matrix_allocation(rows, cols);
                        matrixb = matrix_allocation(rows, cols);
                        for(int i = 0; i < rows; i++) 
                            for(int j = 0; j < cols; j++) {
                                matrixr[i][j] = cropped_matrixr[i][j]; 
                                matrixg[i][j] = cropped_matrixg[i][j]; 
                                matrixb[i][j] = cropped_matrixb[i][j];
                            }
                        free_matrix(cropped_matrixr, rows); 
                        free_matrix(cropped_matrixg, rows); 
                        free_matrix(cropped_matrixb, rows);
                        printf("Image cropped\n");
                    }
                }
            }
            else if(load_count == 0) printf("No image loaded\n");
        }
        else if(strcmp(command, "APPLY") == 0)
        {
            if(load_count == 1) 
            {
                char apply[] = "";
                int count_words = 0;
                aux_string = strtok(NULL, " \n");
                if(aux_string) 
                {
                    count_words++;
                    strcpy(apply, aux_string);
                }
                if(count_words == 0) {printf("Invalid command\n"); continue;}
                if(strcmp(file_type, "P3") == 0 || strcmp(file_type, "P6") == 0) 
                {
                        int okay_blur = 0, okay_gblur = 0, kernel[3][3], okay_apply = 0;
                        int **aux_matrixr = matrix_allocation(rows, cols);
                        int **aux_matrixg = matrix_allocation(rows, cols);
                        int **aux_matrixb = matrix_allocation(rows, cols);
                        for(int i = 0; i < rows; i++)
                            for(int j = 0; j < cols; j++) {
                                aux_matrixr[i][j] = matrixr[i][j];
                                aux_matrixg[i][j] = matrixg[i][j];
                                aux_matrixb[i][j] = matrixb[i][j];
                            }
                        apply_building_kernel(apply, &okay_apply, kernel, &okay_blur, &okay_gblur);
                        if(okay_apply == 1) 
                        {
                            apply_matrix(y1, y2, x1, x2, rows, cols, matrixr, matrixg, matrixb, kernel, 
                                okay_blur, okay_gblur, aux_matrixr, aux_matrixg, aux_matrixb);
                            for(int i = y1; i < y2; i++)
                                for(int j = x1; j < x2; j++) {
                                    matrixr[i][j] = aux_matrixr[i][j];
                                    matrixg[i][j] = aux_matrixg[i][j];
                                    matrixb[i][j] = aux_matrixb[i][j];
                                }
                            printf("APPLY %s done\n", apply);
                            free_matrix(aux_matrixr, rows); 
                            free_matrix(aux_matrixb, rows); 
                            free_matrix(aux_matrixg, rows);
                        }
                }
                else if(strcmp(file_type, "P2") == 0 || strcmp(file_type, "P5") == 0) printf("Easy, Charlie Chaplin\n");
            }
            else printf("No image loaded\n");
        }
        else if(strcmp(command, "SAVE") == 0)
        {
            int number_of_words = 0, ascii_file = 0, binary_file = 0;
            aux_string = strtok(NULL, " \n");
            strcpy(save_file_name, aux_string);
            while(aux_string)
            {
                number_of_words++;
                aux_string = strtok(NULL, " ");
            }
            if(number_of_words == 2) ascii_file = 1;
            else binary_file = 1;
            if(load_count == 1) save_image(save_file, save_file_name, ascii_file, binary_file, 
                                    file_type, cols, rows, image_type, matrix, matrixr, matrixg, matrixb);
            else printf("No image loaded\n");
        }
        else if(strcmp(command, "EXIT") == 0)
        {
            exit_freeing_memory(load_count, matrix, matrixr, matrixg, matrixb, rows);
            break;
        }
        else 
        {
            printf("Invalid command\n");
            while(aux_string) aux_string = strtok(NULL, " \n");
        }
    }
    return 0;
}