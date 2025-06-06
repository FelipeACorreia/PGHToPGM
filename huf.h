#ifndef HUF_H
#define HUF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXSYMBS 256
#define MAXNODES 511

typedef struct {
    int freq;
    int father;
    int left;
    int right;
} nodetype;

extern nodetype node[MAXNODES];

int pqmindelete(int *rootnodes);
int pqinsert(int *rootnodes, int newnode);
void shownodes(int root, int n);
int buildTree(int *h, int mn);
void reverse(char *str);
void code(int n, int p, char *str);
void drawLinks(FILE *dot, int root);
void createDot(int root);
void displayCalcs(int *h, int n);
void huf_tree(int *h, int mn, int dot);


#endif // HUF_H
