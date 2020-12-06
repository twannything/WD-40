#pragma once
#include "Basic Operation.h"
 

// Chapter 3.2 ���� ����
int S_ADDABc(word x, word y, bigint** z, int carry, int r);
int S_ADDABc_print(word x, word y, bigint** z, int carry, int r);
void M_ADD(bigint* x, bigint* y, bigint** z);
void M_ADD_print(bigint* x, bigint* y, bigint** z);
void ADD(bigint* x, bigint* y, bigint** z);
void ADD_print(bigint* x, bigint* y, bigint** z);

// Chapter 3.3 ���� ����
int S_SUBABb(bigint* x, bigint* y, bigint** z, unsigned int b, int j);
int S_SUBABb_print(bigint* x, bigint* y, bigint** z, unsigned int b, int j);
void SUB_C(bigint* x, bigint* y, bigint** z);
void SUB_C_print(bigint* x, bigint* y, bigint** z);
void SUB(bigint* x, bigint* y, bigint** z);
void SUB_print(bigint* x, bigint* y, bigint** z);

// Chapter 3.4 ���� ����
void MULC(word x, word y, word* tmp);
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z);
void Schoolbook_MUL_print(bigint* x, bigint* y, bigint** z);
void MUL(bigint* x, bigint* y, bigint** z);
void MUL_print(bigint* x, bigint* y, bigint** z);

// Chapter 3.5 ������ ����
void binary_long_division(int a, int b, int* q, int* r);
void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r);
void bi_binary_long_division_print(bigint* a, bigint* b, bigint** q, bigint** r);
void long_division_2word(bigint* x, bigint* y, bigint** q, bigint** r);
void divcc(bigint* x, bigint* y, bigint** q, bigint** r);
void divc(bigint* x, bigint* y, bigint** q, bigint** r);
void bi_div(bigint* x, bigint* y, bigint** q, bigint** r);
void bi_div_print(bigint* x, bigint* y, bigint** q, bigint** r);

// Chapter 3.6 ���� ����
void Squaring_word(word* dst, word a);
void Squaring_Schoolbook(bigint* x, bigint** z);
void Squaring_Schoolbook_print(bigint* x, bigint** z);
void SQU(bigint* x, bigint** z);
void SQU_print(bigint* x, bigint** z);

// Chapter 3.7 ��ⷯ ������ ����
void left_to_right(bigint* x, bigint** z, int n);
void left_to_right_mod_bi(bigint* x, bigint* y, bigint* b, bigint** t);
void right_to_left(bigint* x, bigint** z, int n);
void right_to_left_mod_bi(bigint* x, bigint* y, bigint* b, bigint** t);
void Mul_N_Squ(bigint* x, bigint** z, int n);
void Mul_N_Squ_mod_bi(bigint* x, bigint* y, bigint* b, bigint** t);

void left_to_right_print(bigint* x, bigint** z, int n);
void left_to_right_mod_bi_print(bigint* x, bigint* y, bigint* b, bigint** t);
void right_to_left_print(bigint* x, bigint** z, int n);
void right_to_left_mod_bi_print(bigint* x, bigint* y, bigint* b, bigint** t);
void Mul_N_Squ_print(bigint* x, bigint** z, int n);
void Mul_N_Squ_mod_bi_print(bigint* x, bigint* y, bigint* b, bigint** t);

void bi_modular(bigint* x, bigint* y, bigint** z);
void bi_modular_print(bigint* x, bigint* y, bigint** z);