#include "brain.h"



// int main () {
//     double arr2[] = {1.000000, 0.100000, 0.000000, 0.100000, 0.100000, 0.000000, 0.100000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.100000, 0.100000, 0.100000, 0.100000, 0.100000, 0.100000, 0.000000, 0.100000, 0.000000, 0.000000, 0.100000};
//     double *arr = arr2;
//     // for (int i = 0; i < 24; i++) {
//     //     printf("%lf ", arr[i]);
//     // }
//     int vert = 8;
//     // int a = 1;
//     // int cor = 1;
//     // int dir = 1;

//     double angle = 45.0;
//     int rcor = 1; 


//     //  LomatMatrix(&arr, vert, a, cor, dir);
//    Rmat(&arr, angle, rcor, vert);
     
//      for (int i = 0; i < 24; i++) {
//         printf("%lf ", arr[i]);
//     }
// }

double *matrixshift_to_arr(matrix_t *mat) {
    int c = 0;
    int memory = mat->rows * mat->cols;
    // printf("%d", memory);
    double *arr = (double*)calloc(memory, sizeof(double));
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
                arr[c] = mat->matrix[i][j];
                // printf("%lf", mat->matrix_3d.matrix[i][j]);
                // printf("%lf", arr[c]);
                c++;
            }
            // printf("\n");
        }
    return arr;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    if (A->rows) A->rows = 0;
    if (A->cols) A->cols = 0;
    if (A->matrix[0]) {
      free(A->matrix[0]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int code = 2;
    // if (!check(A) && !check(B)) code = 0;

    if (A->cols != B->rows && code != 1) code = 2;
    s21_create_matrix(A->rows, B->cols, result);
    if (code == 0) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->cols; j++) {
                result->matrix[i][j] = 0;
                for (int k = 0; k < B->rows; k++) {
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
    }
    return code;
}




void LomatMatrix(double **arr, int vert, double a, int cor, int dir) {
    matrix_t mat;
    s21_create_matrix(arr,vert, &mat);
    move_x(&mat, a, cor, dir);
    *arr = matrixshift_to_arr(&mat);

}

void Rmat(double **arr, double angle, int rcor, int vert) {
    matrix_t mat;
    s21_create_matrix(arr,vert, &mat);
    rotation_by_ox(&mat, angle, rcor);
    *arr = matrixshift_to_arr(&mat);
}

void rotation_by_ox(matrix_t *A, double angle, int rcor) {
        if (rcor == 0) {
	    for (int i = 0; i < A->rows; i++) {
            double temp_x = A->matrix[i][0];
		    double temp_y = A->matrix[i][1];
		    double temp_z = A->matrix[i][2];
		    A->matrix[i][1] = temp_y * cos(angle) - temp_z * sin(angle);
		    A->matrix[i][2] = temp_y * sin(angle) + temp_z * cos(angle);
	    }
    }
    else if (rcor == 1) {
	    for (int i = 0; i < A->rows; i++) {
            double temp_x = A->matrix[i][0];
		    double temp_y = A->matrix[i][1];
		    double temp_z = A->matrix[i][2];
		    A->matrix[i][0] = temp_x * cos(angle) + temp_z * sin(angle);
		    A->matrix[i][2] = -temp_x * sin(angle) +  temp_z * cos(angle);
	    }
    }
    else if (rcor == 2) {
        for (int i = 0; i < A->rows; i++) {
            double temp_x = A->matrix[i][0];
		    double temp_y = A->matrix[i][1];
		    double temp_z = A->matrix[i][2];
		    A->matrix[i][0] = temp_x  * cos(angle) + temp_y * sin(angle);
		    A->matrix[i][1] = -temp_x * sin(angle) + temp_y * cos(angle);
	    }
    }
}

void less(matrix_t *A, int moreless) {
    if(!moreless) {
	    for (int i = 0; i < A->rows; i++) {
            double temp_x = A->matrix[i][0];
		    double temp_y = A->matrix[i][1];
		    double temp_z = A->matrix[i][2];
		    A->matrix[i][0] = temp_x / 2;
		    A->matrix[i][1] = temp_y / 2;
		    A->matrix[i][2] = temp_z / 2;
	    }
    }
    else if (moreless) {
         for (int i = 0; i < A->rows; i++) {
            double temp_x = A->matrix[i][0];
		    double temp_y = A->matrix[i][1];
		    double temp_z = A->matrix[i][2];
		    A->matrix[i][0] = temp_x * 2;
		    A->matrix[i][1] = temp_y * 2;
		    A->matrix[i][2] = temp_z * 2;
	    }
    }
}

void lesser(double **arr, int vert, int moreless) {
    matrix_t mat;
    s21_create_matrix(arr,vert, &mat);
    less(&mat, moreless);
    *arr = matrixshift_to_arr(&mat);
}





int s21_create_matrix(double **arr,int rows, matrix_t *mat) {
  int err = 0;
  int cols = 3;
  mat->rows = rows ;
  mat->cols = cols;
  if ((rows > 0) && (cols > 0)) {
      mat->matrix = (double**)calloc(mat->rows, sizeof(double*));
    for (int i = 0; i < mat->rows; i++) {
        mat->matrix[i] = (double*)calloc(3, sizeof(double));
    }
  }

  int k = 0;
  for (int i = 0; i < mat->rows; i++) {
      for (int j = 0; j < 3; j++) {
          mat->matrix[i][j] = arr[0][k++];
      }

  }
  return err;
}


void move_x(matrix_t *A, double a, int b, int dir) {
    if (dir) {
	for (int i = 0; i < A->rows; i++) A->matrix[i][b] += a;
}
if (!dir) {
    for (int i = 0; i < A->rows; i++) A->matrix[i][b] -= a;
}
}

