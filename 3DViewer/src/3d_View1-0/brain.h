#ifndef BRAIN_H
#define BRAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Matrix {
	double **matrix;
	int rows;
	int cols;
} matrix_t;

typedef struct facets {
	int *vertexes;
	int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
	int count_of_vertexes;
	int count_of_facets;
	matrix_t matrix_3d;
	polygon_t *polygons;
}test;



void counter(int *cov, int *cof, char *obj);
int converter(double **arr, int **arr2, int *count_of_facets, int *max, int *min, int *vert, char *filename_global);
void free_matrix(test *hren);
void init_matrix(test *hren);
void init_polygons(test *hren);
void fullvert(char *obj, test *hren, int *min, int *max);
void init_vertexes(test *hren);
void free_polygons_vertexes(test *hren);
void number_of_elements(char *obj, test *hren);
double *result(test *hren);
double *matrix_to_arr(test *hren);
int *facets_to_arr(test *hren, int *res_count_of_facets);
//move
void LomatMatrix(double **arr, int vert, double a, int cor, int dir);
int s21_create_matrix(double **arr,int rows, matrix_t *mat);
void move_x(matrix_t *A, double a,  int b, int dir);
void s21_remove_matrix(matrix_t *A);
double *matrixshift_to_arr(matrix_t *mat);
//rotate
void rotation_by_ox(matrix_t *A, double angle, int rcor);
void Rmat(double **arr, double angle, int rcor, int vert);
void less(matrix_t *A, int moreless);
void lesser(double **arr, int vert, int moreless);

#endif
