#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
  int count_of_vertexes;
  int count_of_facets;
  double *vertex_arr;
  int *facets_arr;
};

void parse_obj_file(char *FILENAME, struct data *obj);

int open_file(char *FILENAME, FILE **fp);

void init_data_struct(char *FILENAME, struct data *obj);

void parse_counter_v_f(char *buf, struct data *obj);

void fill_vertex_arr(struct data *obj, FILE *fp);

char *return_vertex(char *tok);

void fill_data_struct(char *FILENAME, struct data *obj);

void fill_facets_arr(char *FILENAME, struct data *obj);

void read_obj_file(char *FILENAME, struct data *obj);

void scale_obj(struct data *obj, double step);

void move_obj(struct data *obj, double step, int coords);

void rotate_x(struct data *obj, int rot, int coords);
