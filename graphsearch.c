#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphsearch.h"

// dealing with sets of integers. We wrote these in class.
LLint *add_to_set(LLint *set, int val) {
  LLint *newfront = calloc(1, sizeof(LLint));
  newfront->val = val;
  newfront->next = set;

  return newfront;
}

bool set_contains(LLint *set, int val) {
  if (set == NULL) {
    return false;
  } else if (set->val == val) {
    return true;
  } else {
    return set_contains(set->next, val);
  }
}

// Linked lists of paths. You'll need to implement these.

// Returns the new front of the queue, for a queue of Path structs.
// Usually this will be the old front of the queue, but if q is NULL, then it
// will allocate a new linked list node and return that.
LLPath *enqueue_path(LLPath *q, Path path) {
  if(!q){
    LLPath* out= (LLPath*)calloc(1, sizeof(LLPath));
    out->val = path;
    return out;
  }
  
  LLPath* here = q;
  while(here->next != NULL){
    here = here->next;
  }

  LLPath* next = (LLPath*)calloc(1, sizeof(LLPath));
  next->val = path;
  here->next= next;

  return q;
}

LLPath *push_path(LLPath *q, Path path) {

  LLPath* next = (LLPath*)calloc(1, sizeof(LLPath));
  next->val = path;
  next->next= q;
  return next;
}

bool dequeue_path(LLPath **q, Path *ret) {
  if(!q || !(*q)){
    return false;
  }

  *ret = (*q)->val;
  LLPath* freethis = *q;
  *q = (*q)->next;
  free(freethis);
  freethis = NULL;

  return true;
}

// We wrote these in class.
Graph *graph_create(int vertices) {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  g->vertices = vertices;
  g->matrix = (int **)calloc(vertices, sizeof(int*));
  for (int i=0; i < vertices; i++) {
    g->matrix[i] = (int *)calloc(vertices, sizeof(int));
  }
  return g;
}

void graph_add_edge(Graph *g, int i, int j) {
  g->matrix[i][j] = 1;
}

bool graph_has_edge(Graph *g, int i, int j) {
  return g->matrix[i][j];
}

// Convenience method for you -- returns a new Path where you have added another
// vertex along the path.
Path path_extend(Path path, int new_vertex) {
  Path out;
  out.steps = path.steps;

  for (int i=0; i < path.steps; i++) {
    out.vertices_visited[i] = path.vertices_visited[i];
  }
  out.vertices_visited[path.steps] = new_vertex;
  out.steps += 1;
  return out;
}

// Print out a path nicely for the user.
void print_path(Path path) {
  if (path.steps == 0) {
    puts("(empty path)");
  }
  for (int i=0; i < path.steps; i++) {
    printf("%s%d",
        (i == 0) ? "" : " -> ",
        path.vertices_visited[i]);
  }
  puts("");
}

void freegraph(Graph *g){
  for(int i = 0; i < g->vertices; i++){
    free(g->matrix[i]);
  }
  free(g->matrix);
  free(g);
}

void free_lp(LLPath *set){
  if(!set){
    return;
  }
  free_lp(set->next);
  free(set);
}

void free_ll(LLint *set){
  if(!set){
    return;
  }
  free_ll(set->next);
  free(set);
}


// Breadth-first search!
Path graph_find_path_bfs(Graph *g, int i, int j) {
  // YOUR CODE HERE.
  LLPath *to_visit = NULL;

  LLint *visited = NULL;

  Path initial;
  initial.steps = 1;
  initial.vertices_visited[0] = i;

  to_visit = enqueue_path(to_visit, initial);

  while(to_visit != NULL){
    Path current;
    dequeue_path(&to_visit, &current);

    if(current.vertices_visited[(current.steps)-1] == j){
      free_ll(visited);
      free_lp(to_visit);
      return current;
    }

    if(!set_contains(visited, current.vertices_visited[(current.steps)-1])){
      visited = add_to_set(visited, current.vertices_visited[(current.steps)-1]);
    }

    for(int k = 0; k < g->vertices; k++){
      if(graph_has_edge(g, current.vertices_visited[(current.steps)-1], k)){
        if(!set_contains(visited, k)){
          Path next = path_extend(current, k);
          to_visit = enqueue_path(to_visit, next);
        }
      }
    }
  }  
  free_ll(visited);
  free_lp(to_visit);
  Path empty = {0, {0}};
  return empty;
}


// Depth-first search!
Path graph_find_path_dfs(Graph *g, int i, int j){
  // YOUR CODE HERE.
  LLPath *to_visit = NULL;

  LLint *visited = NULL;

  Path initial;
  initial.steps = 1;
  initial.vertices_visited[0] = i;

  to_visit = push_path(to_visit, initial);

  while(to_visit != NULL){
    Path current;
    dequeue_path(&to_visit, &current);

    if(current.vertices_visited[(current.steps)-1] == j){
      free_ll(visited);
      free_lp(to_visit);
      return current;
    }

    if(!set_contains(visited, current.vertices_visited[(current.steps)-1])){
      visited = add_to_set(visited, current.vertices_visited[(current.steps)-1]);
    }

    for(int k = 0; k < g->vertices; k++){
      if(graph_has_edge(g, current.vertices_visited[(current.steps)-1], k)){
        if(!set_contains(visited, k)){
          Path next = path_extend(current, k);

          to_visit = push_path(to_visit, next);
        }
      }
    }
  }
  free_ll(visited);
  free_lp(to_visit);
  
  Path empty = {0, {0}};
  return empty;
}
