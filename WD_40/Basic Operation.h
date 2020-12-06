#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "conf.h"

#define _CRT_SECURE_NO_WARNINGS

#if WORD_BITLEN == 64
typedef unsigned long long word;
#define MASK 0xffffffffffffffff
#define MASKMUL 0xffffffff
#elif WORD_BITLEN == 32
typedef unsigned int word;
#define MASK 0xffffffff
#define MASKMUL 0xffff
#else 
typedef unsigned char word;
#define MASK 0xff
#define MASKMUL 0xf
#endif

#define NONNEGATIVE 0
#define NEGATIVE 1

typedef unsigned char byte;
/**
* @brief bigint
*/
typedef struct {
	int sign; /**< ��ѹ��� ��ȣ NEGATIVE or NON-NEGATIVE */
	int wordlen; /**< ��ѹ��� ���� ���� */
	word* a; /**< ��ѹ��� �ּ�*/
}bigint;

// Chapter 2.1 ��ѹ��� �����ϴ� �Լ� & �����ϴ� �Լ�
void bi_delete(bigint** x);
void bi_new(bigint** x, int wordlen);

// Chapter 2.2 �迭�� ���ڿ��� ���� �Է��� ��ѹ��� �����ϴ� �Լ� & ��ѹ��� ����ϴ� �Լ� 
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);
void bi_show_hex(bigint* x);
void bi_show_bin(bigint* x);
void word_show_hex(word x);
void File_print(bigint* x, FILE* fp);

// Chapter 2.3 ��ѹ� 0000017398213 -> 17398213 ���� ����� �ִ� �Լ�
void bi_refine(bigint** x);

// Chapter 2.4 ��ѹ��� �����ϴ� �Լ�
void bi_assign(bigint** y, bigint* x);

// Chapter 2.5 ��ѹ��� �����ϰ� �����ϴ� �Լ�
void bi_gen_rand(bigint** x, int sign, int wordlen);

// Chapter 2.6 ��ѹ��� �������, ��Ʈ����, j��° ��Ʈ�� ����ϴ� �Լ�
int get_word_length(bigint* x);
int get_bit_length(bigint* x);
int bit_of_bi(bigint* x, int j);

// Chapter 2.7 ��ѹ��� �������, ��Ʈ����, j��° ��Ʈ�� ����ϴ� �Լ�
int get_sign_bi(bigint* x);
void flip_sign_bi(bigint** x);

// Chapter 2.8 ��ѹ��� 0 �̳� 1�� set�ϴ� �Լ� & 0 �̳� 1���� Ȯ���ϴ� �Լ�
void bi_set_one(bigint** x);
void bi_set_zero(bigint** x);
int bi_is_zero(bigint* x);
int bi_is_one(bigint* x);

// Chapter 2.9 �� ��ѹ��� ���Ͽ� ������ �� ū�� ����ϴ� �Լ�
int compareABS(bigint* x, bigint* y);
int compareAB(bigint* x, bigint* y);

// Chapter 2.10 ��ѹ��� r��Ʈ left �Ǵ� right�� shift ���ִ� �Լ� 
void bi_leftshift(bigint** x, int r);
void bi_rightshift(bigint** x, int r);

// Chapter 3.1 ��ⷯ ����
void bi_reduction(bigint** y, bigint* x, int r);