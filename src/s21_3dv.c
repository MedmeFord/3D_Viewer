#include "s21_3dv.h"

int open_file(char* FILENAME, FILE** fp) {
  int status = 0;
  if (((*fp) = fopen(FILENAME, "r")) == NULL) {
    status = 1;
  }
  return status;
}

void parse_counter_v_f(char* buf, struct data* obj) {
  int i = 0;
  while (*(buf + i)) {
    if (*(buf + i) == 'v' && *(buf + i + 1) == ' ') {
      obj->count_of_vertexes += 3;
    }
    if (*(buf + i) == 'f' && *(buf + i + 1) == ' ') {
      char* tok = strtok(buf, " ");
      while (tok != NULL) {
        if (*(tok) != 'f' && *(tok) != '\n') {
          obj->count_of_facets += 2;
        }
        tok = strtok(NULL, " ");
      }
    }
    i++;
  }
}

void parse_obj_file(char* FILENAME, struct data* obj) {
  FILE* fp;
  if (open_file(FILENAME, &fp) == 0) {
    char buf[256];
    while (fgets(buf, 256, fp) != NULL) {
      parse_counter_v_f(buf, obj);
    }
  }
  fclose(fp);
}

void fill_data_struct(char* FILENAME, struct data* obj) {
  FILE* fp;
  if (open_file(FILENAME, &fp) == 0) {
    fill_vertex_arr(obj, fp);
  }
  fclose(fp);
}

void fill_vertex_arr(struct data* obj, FILE* fp) {
  char buf[256];
  int x = 3;
  while (fgets(buf, 256, fp) != NULL) {
    if (*(buf) == 'v' && *(buf + 1) == ' ') {
      char* tok = strtok(buf, " ");
      while (tok != NULL) {
        if (*(tok) != 'v') {
          obj->vertex_arr[x] = (double)atof(tok);
          x++;
        }
        tok = strtok(NULL, " ");
      }
    }
  }
}

char* return_vertex(char* tok) {
  int j = 0;
  while (*(tok + j)) {
    if (*(tok + j) == '/') {
      *(tok + j) = '\0';
      break;
    }
    j++;
  }
  return tok;
}

void fill_facets_arr(char* FILENAME, struct data* obj) {
  FILE* fp;
  if (open_file(FILENAME, &fp) == 0) {
    char buf[256];
    int x = 0;
    while (fgets(buf, 256, fp) != NULL) {
      if (*(buf) == 'f' && *(buf + 1) == ' ') {
        char* tok = strtok(buf, " ");
        int y = 1;
        int xbuf = 0;
        while (tok != NULL) {
          if (*(tok) != 'f' && *(tok) != '\n') {
            if (y == 1) {
              obj->facets_arr[x] = atoi(return_vertex(tok));
              xbuf = obj->facets_arr[x];
              x++;
              y++;
            } else if (y == 2) {
              obj->facets_arr[x] = atoi(return_vertex(tok));
              obj->facets_arr[x + 1] = obj->facets_arr[x];
              x += 2;
            }
          }
          tok = strtok(NULL, " ");
        }
        obj->facets_arr[x] = xbuf;
        x++;
      }
    }
  }
  fclose(fp);
}

void init_data_struct(char* FILENAME, struct data* obj) {
  obj->count_of_vertexes = 3;
  obj->count_of_facets = 0;
  parse_obj_file(FILENAME, obj);
  obj->facets_arr = (int*)calloc(obj->count_of_facets, sizeof(int));
  obj->vertex_arr = (double*)calloc((obj->count_of_vertexes), sizeof(double));
}

void read_obj_file(char* FILENAME, struct data* obj) {
  init_data_struct(FILENAME, obj);
  fill_data_struct(FILENAME, obj);
  for (int i = 0; i < 27; i++) {
    if ((i + 1) % 3 == 0) {
    }
  }
  fill_facets_arr(FILENAME, obj);
}

void move_obj(struct data* obj, double step, int coords) {
  int i = 3;
  if (coords == 2) {
    i = 4;
  } else if (coords == 3) {
    i = 5;
  }
  for (; i < obj->count_of_vertexes; i += 3) {
    obj->vertex_arr[i] += step;
  }
}

void scale_obj(struct data* obj, double step) {
  for (int i = 0; i < obj->count_of_vertexes; i++) {
    obj->vertex_arr[i] *= step;
  }
}

void rotate_x(struct data* obj, int rot, int coords) {
  double rad = rot * M_PI / 180;
  double s = sin(rad), c = cos(rad);

  for (int i = 3; i < obj->count_of_vertexes; i += 3) {
    double x1 = obj->vertex_arr[i];
    double y1 = obj->vertex_arr[i + 1];
    double z1 = obj->vertex_arr[i + 2];

    if (coords == 0) {
      obj->vertex_arr[i + 1] = y1 * c - s * z1;
      obj->vertex_arr[i + 2] = y1 * s + c * z1;
    } else if (coords == 1) {
      obj->vertex_arr[i] = x1 * c - s * y1;
      obj->vertex_arr[i + 1] = x1 * s + c * y1;
    } else if (coords == 2) {
      obj->vertex_arr[i] = x1 * c + s * z1;
      obj->vertex_arr[i + 2] = -x1 * s + c * z1;
    }
  }
}
