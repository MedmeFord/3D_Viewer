#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define F_OPEN "../test.txt";

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
void converter(double **arr, int **arr2, int *count_of_facets, int *max, int *min, int *vert);
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


int main() {
    double *arr = NULL;
    int *arr2 = NULL;
    int count_of_facets = 0;
    int min = 0;
    int max = 0;
    int vert = 0;
    converter(&arr, &arr2, &count_of_facets, &min, &max, &vert);

    // for (int i = 0; i < 30; i++) {
    //     printf("%lf, ", arr[i]);
    // }

    // printf("\n");

    // for (int i = 0; i < count_of_facets; i++) {
    //     printf("%d, ", arr2[i]);
    // }


    // printf("\n");

    // printf("%d", count_of_facets);

    // printf("\nmin: %d\nmax: %d", min, max);

     printf("%d", vert);



    free(arr);
    free(arr2);
    

    return 0;
}

int *facets_to_arr(test *hren, int *res_count_of_facets) {
    int c = 0;
    int memory = hren->matrix_3d.rows * hren->matrix_3d.cols;
    // printf("%d", memory);
    // printf("\n");
    memory = 0;
        for (int i = 0; i < hren->count_of_facets; i++) {
            for (int j = 0; j < hren->polygons[i].numbers_of_vertexes_in_facets; j++) {
                memory++;
            }
        }
    // printf("%d", memory);
    int *arr = (int*)calloc(memory*3, sizeof(int));
    int last_num = 0;
    for (int i = 0; i < hren->count_of_facets; i++) {
        for (int j = 0; j < hren->polygons[i].numbers_of_vertexes_in_facets; j++) {
            for (int k = 0; k < 2; k++) {
                if (j == 0 && k == 0) {
                    last_num = hren->polygons[i].vertexes[j] - 1;
                    continue;
                } 
                if (j == hren->polygons[i].numbers_of_vertexes_in_facets)
                continue;
                arr[c] = hren->polygons[i].vertexes[j] - 1;
                // printf("%d ", arr[c]); 
                c++;
            }
                // printf("%lf", hren->matrix_3d.matrix[i][j]); 
            }
            arr[c] = last_num;
            c++;
            // printf("\n");
        }
    *res_count_of_facets = c;
    
    return arr;
}

void converter(double **arr, int **arr2, int *count_of_facets, int *max, int *min, int *vert) {   
    char obj[150] = F_OPEN;
    int cov = 0;
    int cof = 0;
    counter(&cov, &cof, obj);
    test hren;
    hren.count_of_facets = cof;
    hren.count_of_vertexes = cov;
    hren.matrix_3d.rows = cov;
    hren.matrix_3d.cols = 3;
    init_matrix(&hren);
    init_polygons(&hren);
    number_of_elements(obj, &hren);
    init_vertexes(&hren);
    fullvert(obj, &hren, max, min);
    double *res_arr = matrix_to_arr(&hren);
    int res_count_of_facets = 0;
    int *res_arr2 = facets_to_arr(&hren, &res_count_of_facets);
    *count_of_facets = res_count_of_facets;
    *arr = res_arr;
    *arr2 = res_arr2;
    // free(res_arr);
    // free(res_arr2);
    *vert = hren.count_of_vertexes;

    free_matrix(&hren);
    free_polygons_vertexes(&hren);

}

double *matrix_to_arr(test *hren) {
    int c = 0;
    int memory = hren->matrix_3d.rows * hren->matrix_3d.cols;
    // printf("%d", memory);
    double *arr = (double*)calloc(memory, sizeof(double));
    for (int i = 0; i < hren->matrix_3d.rows; i++) {
        for (int j = 0; j < hren->matrix_3d.cols; j++) {
                arr[c] = hren->matrix_3d.matrix[i][j];
                // printf("%lf", hren->matrix_3d.matrix[i][j]);
                // printf("%lf", arr[c]);
                c++;
            }
            // printf("\n");
        }
    return arr;
}



double *result(test *hren) {
    int memory = 0, c = 0;
    for (int i = 0; i < hren->count_of_facets; i++) {
        memory += hren->polygons[i].numbers_of_vertexes_in_facets * 6;
    }
    double *arr = (double*)calloc(memory, sizeof(double));
    for (int i = 0; i < hren->count_of_facets; i++) {
        for (int j = 0; j < hren->polygons[i].numbers_of_vertexes_in_facets; j++) {
            for (int d =0; d < 2; d++) {
                for (int k = 0; k < 3; k++) {
                    arr[c] = hren->matrix_3d.matrix[hren->polygons[i].vertexes[j] - 1][k];
                    // printf("%lf ", arr[c]);
                    c++;
                }
            }
            // printf("\n");
        }
    }
    return arr;
}

void init_vertexes(test *hren) {
    for (int i = 0; i < hren->count_of_facets; i++) {
        hren->polygons[i].vertexes = (int*)calloc(hren->polygons[i].numbers_of_vertexes_in_facets, sizeof(int));
    }
}

void init_polygons(test *hren) {
    hren->polygons = (polygon_t*)calloc(hren->count_of_facets, sizeof(polygon_t));
}


void init_matrix(test *hren) {
    // printf("%d", hren->count_of_vertexes);
    hren->matrix_3d.matrix = (double**)calloc(hren->count_of_vertexes, sizeof(double*));
    for (int i = 0; i < hren->count_of_vertexes; i++) {
        hren->matrix_3d.matrix[i] = (double*)calloc(3, sizeof(double));
    }
}

void free_matrix(test *hren) {
    for(int i = 0; i < hren->count_of_vertexes; i++) {
        free(hren->matrix_3d.matrix[i]);
    }
    free(hren->matrix_3d.matrix);
}

void free_polygons_vertexes(test *hren) {
    for (int i = 0; i < hren->count_of_facets; i++) {
        free(hren->polygons[i].vertexes);
    }
    free(hren->polygons);
}

void number_of_elements(char *obj, test *hren) {
    char str[512] = {'\0'};
    int kal = 0;
    FILE *txt =  fopen(obj, "rt");
      if (txt != NULL) {
          while(fgets(str, 511, txt) != NULL) {
                int count_of_spaces = 0;
                if (str[0] == 'f' && str[1] == ' ') {
                    int a = strlen(str);
                    for (int i = 1; i < a; i++) {
                        if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0' && str[i + 1] != '\n') {
                            count_of_spaces += 1;
                        }
                    }
                    hren->polygons[kal++].numbers_of_vertexes_in_facets = count_of_spaces;
                }
            }
             fclose(txt);
        }
      else {
          printf("NETU NIHUYA!");
      }
}

void fullvert(char *obj, test *hren, int *min, int *max) {
    FILE *txt =  fopen(obj, "rt");
      if (txt != NULL) {
          char str[512] = {'\0'};
          char buff[30] = {'\0'};
          int j = 0;
          int kal = 0;
          int flag = 1;
          while(fgets(str, 511, txt) != NULL) {
              int l = 0;
              if (str[0] == 'v' && str[1] == ' ') {
                  int a = strlen(str);
                  for (int i = 2, k = 0; i < a; i++) {
                      if (str[i] == ' ' || str[i] == '\n') {
                          double buff_double = atof(buff);
                          if(flag) {
                              *max = (int)ceil(buff_double);
                              *min = -1;
                              flag = 0;
                          }
                          if (*min > (int)floor(buff_double)) *min = (int)floor(buff_double);
                          if (*max < (int)ceil(buff_double)) *max = (int)ceil(buff_double);
                          hren->matrix_3d.matrix[j][l++] = buff_double;
                          k = 0;
                          for (int i = 0; buff[i] != '\0'; i++) {
                            buff[i] = '\0';
                          }
                          if (str[i] == '\n') break;
                          continue;
                        }
                        buff[k++] = str[i];
                    }
                    j++;
                }
                if (str[0] == 'f' && str[1] == ' ') {
                    int a = strlen(str);
                    char buff[50] = {'\0'};
                    int flag = 0;
                    for (int i = 0, j = 0, k = 0; i < a; i++) {
                        // printf("%c\n", str[i]);
                        // if(str[i + 2] == '\n') break;
                        // (str[i + 1] <= '9' && str[i + 1] >= '0')
                        if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\n') flag = 1;
                        if (flag) {
                            if(str[i + 1] == '/' || str[i + 1] == ' ' || str[i + 1] == '\n' ) {
                                int integer = 0;
                                if (buff[1] != '\0') {
                                    integer = atoi(buff);
                                } else {
                                    integer = buff[0] - '0';
                                }
                                hren->polygons[kal].vertexes[j] = integer;
                                j++;
                                k = 0;
                                flag = 0;
                                for (int m = 0; buff[m] != '\0'; m++) {
                                    buff[m] = '\0';
                                }
                            } else {
                                buff[k++] = str[i + 1];
                            }
                            // printf("%d ", hren->polygons[kal].vertexes[j]);
                        }
                    }
                    kal++;
                }
                for (int x = 0; str[x] != '\0'; x++) {
                    str[x] = '\0';
                }
            }
             fclose(txt);
        }
      else {
          printf("NETU NIHUYA!");
      }
}

void counter(int *cov, int *cof, char *obj) {
    FILE *txt = fopen(obj, "rt");
      if (txt != NULL) {
          char str[512] = {'\0'};
          while(fgets(str, 511, txt) != NULL) {
                  if (str[0] == 'v' && str[1] == ' ') {
                      *cov += 1;
                  }
                   if (str[0] == 'f' && str[1] == ' ') {
                      *cof += 1;
                  }
              }
              fclose(txt);
        //   printf("%d", *cov);
        //   printf("\n");
          }
      else {
          printf("NETU NIHUYA!");
      }
}

