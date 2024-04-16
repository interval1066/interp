#define __STDC_WANT_LIB_EXT1__ 1

#include "huff.h"
#include <string.h>

/**
 * @file    huff.c
 * @author  Tim O'Neil
 * @date    3/9/2018
 *
 * @brief	Probably pretty portable huffman coder
 *
 * @section	DESCRIPTION
 *
 * Huffman coder for making text blobs psuedo-encrypted
 * and psuedo-compressed and editable only through this
 * the application (more or less). This code is not
 * tested with other implementations, so its totally
 * possible to be a wonky, one-off, not comatible, non-
 * standard implementation (if there is such a thing.)
 */

/**
 * @brief			encode coder entrypoint, this one of our public facing
 *						interfaces, the other being decode, below.
 *
 * @details			Given a buffer of text encode it and write the output
 *						to a file.
 * @param			const char*		file_name2: path of output file
 * @param			char* 			buf: string containing text to encode
 */
void
encode(const char* file_name2, char* buf)
{
	FILE* en;
	int freq[256] = {0};
	info header[256];

	char codes[256][40];
	char code[40];
	strcpy(code, "");

	List_t mylist_en;
	size_t num, no_of_chars;
	en = fopen(file_name2, "w");

	if(en) {
		find_freq(buf, freq);
		no_of_chars = strlen(buf);

		if(no_of_chars > 0) {
			make_tree(&mylist_en, freq);
			num = create_header(freq, (int)no_of_chars, header);

			find_code(mylist_en.head, code, codes);
			compress(buf, en, codes, (int)no_of_chars, header, freq, (int)num);
		}
	}
	fclose(en);
}

/**
 * @brief			decode: decode a buffer of huffman encoded text
 *
 * @details			Decode a file and send the output to stdout
 *
 * @param			const char*: file_name1: path of input file
 */
void
decode(const char* file_name1)
{
	info y, * ptrrr;
	FILE* en;
	ptrrr = &y;

	code_generated x, * ptrr;
	ptrr = &x;
	List_t mylist_de;

	int i, num, no_of_chars, count = 0;
	int freq[256] = {0};
	en = fopen(file_name1, "r");

	if(en) {
		fread(ptrr, sizeof(code_generated), 1, en);
		num = ptrr->c;

		for(i = 0; i < num; ++i) {
			fread(ptrrr, sizeof(info), 1, en);
			freq[(int)ptrrr->ch] = ptrrr->freq;
		}

		make_tree(&mylist_de, freq);
		no_of_chars = find_no_of_chars(freq);
		node_t* root = mylist_de.head;

		node_t* ptr = root;
		while(fread(ptrr, sizeof(code_generated), 1, en) == 1)
			ptr = decode_char(stdout, ptr, ptrr->c, 1, root, &count, no_of_chars);
	}
	fclose(en);
}

node_t*
decode_char(FILE* de, node_t* ptr, int x, int y,
	node_t* root, int* count, int no_of_chars)
{
	if(y != 9 &&(*count) != no_of_chars) {
		if(ptr->llink == 0 && ptr->rlink == 0) {
			fputc(ptr->c, de);

			ptr = root;
			++(*count);
			ptr = decode_char(de, ptr, x, y, root, count, no_of_chars);
		}
		else if(x % 2 == 0 && ptr->llink)
			ptr = decode_char(de, ptr->llink, x / 2, ++y, root, count, no_of_chars);
		else if(x%2!=0 && ptr->rlink)
			ptr = decode_char(de, ptr->rlink, x / 2, ++y, root, count, no_of_chars);
	}
	return ptr;
}

void
insert_in_list(List_t*, node_t*);

void
init_list(List_t* ptr)
{
	ptr->head = 0;
}

void
disp_list(const List_t* ptr)
{
	node_t* temp = ptr->head;
	while(temp) {
		printf("%d( %c )\t",temp->freq,temp->c);
		temp = temp->link;
	}
	printf("\n");
}

void
make_node(List_t* ptr, int n, char c)
{
	node_t* temp;
	temp = (node_t*)malloc(sizeof(node_t));
	temp->freq = n;

	temp->c = c;
	temp->link = 0;
	temp->rlink = 0;

	temp->llink = 0;
	insert_in_list(ptr, temp);
}

void
insert_in_list(List_t* ptr, node_t* t)
{
	if(ptr->head == 0)
		ptr->head = t;
	else {
		node_t* prev = 0;
		node_t* pres = ptr->head;

		while(pres && pres->freq <= t->freq) {
			prev = pres;
			pres = pres->link;
		}
		if(pres == ptr->head) {
			ptr->head = t;
			t->link = pres;
		}
		else if(pres == 0)
			prev->link = t;
		else {
			t->link = pres;
			prev->link = t;
		}
	}
}

void
make_list(List_t* ptr, int* freq)
{
	int i;
	for(i = 0; i < 256; ++i) {
		if(freq[i] != 0)
			make_node(ptr, freq[i], i);
	}
}

void
find_freq(char* fp, int* freq)
{
	char c;
    unsigned n = 0;

	while(n < strlen(fp)) {
		c = fp[n++];
		++freq[(int)c];
	}
}

void
make_tree(List_t* ptr, int* freq)
{
	node_t * t1, * t2;
	init_list(ptr);
	make_list(ptr,freq);

	while(ptr->head->link != 0) {
		t1=ptr->head;
		t2=ptr->head->link;

		ptr->head=t2->link;
		t1->link = 0;
		t2->link = 0;

		node_t* temp;
		temp=(node_t*)malloc(sizeof(node_t));
		temp->freq = t1->freq + t2->freq;

		temp->c = 0;
		temp->link = 0;
		temp->rlink = t2;

		temp->llink = t1;
		insert_in_list(ptr, temp);
	}
}

void
find_code(node_t* ptr, char* code, char codes[256][40])
{
	char temp[40];
	if(ptr->rlink == 0 && ptr->llink == 0)
        strcpy(codes[(int)(ptr->c)], code);

	if(ptr->rlink != 0) {
		strcpy(temp, code);
		strcat(temp, "1");

		find_code(ptr->rlink, temp, codes);
	}
	if(ptr->llink != 0) {
		strcpy(temp, code);
		strcat(temp, "0");

		find_code(ptr->llink, temp, codes);
	}
}

int
find_no_of_chars(int* freq)
{
	int i, sum = 0;
	for(i = 0; i < 256; ++i)
		sum = sum + freq[i];

	return sum;
}

void
compress(char* fp, FILE* en, char codes[256][40],
	int no_of_chars, info* header, int* freq, int num)
{
	char ch;
	int n = 0, i = 0, j = 0, count = 0, k, l;
	unsigned char c;
	code_generated x;
	char string_rev[9];
	x.c = num;

	fwrite(&x, sizeof(code_generated), 1 ,en);
	for(k = 0, l = 0; k < 256; ++k) {
		if(freq[k]) {
			fwrite(&header[l], sizeof(info), 1, en);
			++l;
		}
	}
	while((ch = fp[n++]) != EOF) {
		j = 0;
		++count;

		while(codes[(int)ch][j] != '\0') {
			string_rev[i] = codes[(int)ch][j];
			++i; ++j;

			if(i == 8) {
				string_rev[i] = '\0';
				strre(string_rev, (int)strlen(string_rev));

				c = convert_string_char(string_rev);
				strcpy(string_rev, "");
				i = 0; x.c = c;

				fwrite(&x,sizeof(x),1,en);
			}
			if(count == no_of_chars ) {
				while(codes[(int)ch][j]) {
					string_rev[i] = codes[(int)ch][j];

					++i; ++j;
					if(i == 8) {
						string_rev[i] = '\0';

						strre(string_rev, (int)strlen(string_rev));
						c = convert_string_char(string_rev);
						strcpy(string_rev, "");

						i = 0; x.c=c;
						fwrite(&x,sizeof(x),1,en);
					}
				}
				string_rev[i] = '\0';
				strre(string_rev, (int)strlen(string_rev));
				c = convert_string_char(string_rev);

				strcpy(string_rev, "");
				x.c = c;
            fwrite(&x, sizeof(x), 1, en);
			}
		}
	}
}

void
strre(char* str, int n)
{
	int i = 0, j = n - 1;
	char temp;

	while(i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		++i; --j;
	}
	str[n]='\0';
}

int
create_header(int* freq, int no_of_chars, info* header)
{
	int i, j;

	for(i = 0, j = 0; i < 256; ++i) {
		if(freq[i] != 0) {
			header[j].freq = freq[i];
			header[j].ch = i;
			++j;
		}
	}
	return j;
}

unsigned char
convert_string_char(char string[8])
{
	int i=0;
	unsigned char c = 0;

	while(string[i]) {
		if(string[i] == '1') {
			c = c * 2;
			c = c + 1;
		}
		else
			c = c * 2;

		++i;
	}
	return c;
}
