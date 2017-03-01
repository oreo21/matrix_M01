#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  // matrix operation demo!
  srand(time(NULL));
  int i, j, n = (rand() % 9) + 4;
  struct matrix *a, *b;
  a = new_matrix(4, 4), b = new_matrix(4, n);
  for(i = 0; i < (*a).rows; i++)
    for(j = 0; j < (*a).cols; j++)
      (*a).m[i][j] = (float)(rand() % 10);
  for(i = 0; i < (*b).rows; i++)
    for(j = 0; j < (*b).cols; j++)
      (*b).m[i][j] = (float)(rand() % 10);
  printf("\ninitializing matrix-a...\n"), print_matrix(a);
  printf("\ninitializing matrix-b...\n"), print_matrix(b);
  n = rand() % 50 + 1, scalar_mult((float)n, b);
  printf("\nperforming scalar mult., matrix-b x %d...\n", n), print_matrix(b);
  matrix_mult(a, b);
  printf("\nperforming matrix mult., matrix-a x matrix-b...\n"), print_matrix(b);
  ident(a);
  printf("\nconverting matrix-a to identity matrix...\n"), print_matrix(a);
  matrix_mult(b, a);
  printf("\nmultipling matrix-b by identity matrix to confirm the multiplicative identity...\n"), print_matrix(b);
  free_matrix(a), free_matrix(b);
  // endof demo!

  // image creation
  screen s;
  color c;
  c.red = 142, c.green = 68, c.blue = 173;
  clear_screen(s);

  struct matrix *edges;
  edges = new_matrix(4, 4);
  for(i = 0; i < 4; i++)
    for(j = 0; j < 4; j++)
      (*edges).m[i][j] = 0.0;

  add_edge(edges, 100, 50, 0, 100, 450, 0);
  add_edge(edges, 100, 450, 0, 200, 450, 0);
  add_edge(edges, 200, 450, 0, 200, 150, 0);
  add_edge(edges, 200, 150, 0, 400, 150, 0);
  add_edge(edges, 400, 150, 0, 400, 50, 0);
  add_edge(edges, 400, 50, 0, 100, 50, 0);
  for(i = 100; i <= 200; i++)
    add_edge(edges, i, 50, 0, i, 450, 0);
  for(i = 400; i > 200; i--)
    add_edge(edges, i, 50, 0, i, 150, i);
  
  draw_lines(edges, s, c);
  save_extension(s, "image.png");
  display(s);
  free_matrix(edges);
}  
