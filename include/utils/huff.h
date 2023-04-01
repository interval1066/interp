#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @file    huff.h
 * @author  Tim O'Neil
 * @date    3/9/2018
 *
 * @brief	Probably pretty portable Huffman coder
 *
 * @section	DESCRIPTION
 *
 * Huffman ecoder to compress large blobs of text and anything
 * meant to be read only through an application UI. This file
 * defines some necessary structs and such. See the implementation
 * file for more details.
 */
typedef struct node
{
	char c;
	int freq;
	struct node *link;
	struct node *rlink;
	struct node *llink;
} node_t;

typedef struct List
{
	node_t *head;
} List_t;

typedef struct
{
	unsigned char c : 8;
} code_generated;

typedef struct
{
	int freq;
	unsigned char ch;
} info;

void decode(const char*);
void encode(const char*, char*);
void insert_in_list(List_t*, node_t*);

void init_list(List_t *ptr);
void disp_list(const List_t*);
void make_node(List_t*, int, char);

void make_list(List_t*, int*);
void find_freq(char*, int*);
void make_tree(List_t*, int*);

void find_code(node_t*, char*, char codes[256][40]);
void compress(char*, FILE*, char codes[256][40], int, info*, int*, int num);
unsigned char convert_string_char(char string[8]);

int find_no_of_chars(int*);
void strre(char*, int);
node_t* decode_char(FILE*, node_t*, int, int, node_t*, int*, int);

int create_header(int*, int, info*);
