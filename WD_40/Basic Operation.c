#pragma once
#include "Basic Operation.h"
#define ZERORIZE

/**
* @brief array_init : bi_delete �� ���Ǵ� �Լ� ��ѹ� x�� �޸𸮸� �ݳ��ϱ��� 0���� �ʱ�ȭ
* @param word* a : �ʱ�ȭ �� ���忭
* @param wordlen : �ʱ�ȭ �� ���忭�� ����
*/
void array_init(word* a, int wordlen) {
	memset(a, 0, wordlen*sizeof(word));
}

/**
* @brief array_copy : ��ѹ� ���� �����ϴ� bi_assign�Լ��� ���
* @param word* a : ������ ���忭
* @param word* b : ������� ���忭
* @param int wordlen : ������ ����
*/
void array_copy(word* a, word* b, int wordlen) {
	for (int i = 0; i < wordlen; i++)
		a[i] = b[i];
}
/**
* @brief array_rand : �迭�� ������ �Է� bi_gen_rand�� ���
* @param word* dst : �������� ���� ���ڿ�
* @param int wordlen : �Է¹��� ����
*/
void array_rand(word* dst, int wordlen) {
	byte* p = (byte*)dst;
	int cnt = wordlen * sizeof(word);
	while (cnt > 0) {
		*p = rand() & 0xff;
		p++;
		cnt--;
	}
}
/**
* @brief bi_delete : ��ѹ� x�� �Ҵ��ߴ� �޸𸮸� �ݳ��ϴ� �Լ�
* @param bigint** x : �ݳ��� ��ѹ�
*/
void bi_delete(bigint** x) {
	if (*x == NULL) return;

#ifdef ZERORIZE
	array_init((*x)->a, (*x)->wordlen);
#endif
	free((*x)->a);
	free(*x);
	*x = NULL;
}

/**
* @brief bi_new : �ش� wordlen ��ŭ ��ѹ� x�� �޸𸮸� �Ҵ����ִ� �Լ�
* @param bigint** x : �޸𸮸� �Ҵ���� ��ѹ� x
* @param int wordlen : �Ҵ���� ������ ����
*/
void bi_new(bigint** x, int wordlen) {
	if (*x != NULL)
		bi_delete(x);

	*x = (bigint*)malloc(sizeof(bigint));
	if ((*x) == NULL )
		return;
	(*x)->sign = NONNEGATIVE;
	(*x)->wordlen = wordlen;
	(*x)->a = (word*)calloc(wordlen, sizeof(word));
}

/**
* @brief bi_set_by_array : �迭�� ��ѹ� ���� ���� ��, �迭�� x->a �迭�� ���Խ��� �ִ� �Լ�
* @param bigint** x : ���� ������ ��ѹ� x
* @param int sign : x�� ��ȣ
* @param word* a : ������ ��ѹ� �迭
* @param int wordlen : x�� �������
*/
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen) {
	int i, j;
	if (*x != NULL)
		bi_delete(x);
	bi_new(x, wordlen);
	(*x)->sign = sign;
	for (i = 0, j = wordlen - 1; i < wordlen, j >= 0; i++, j--)
		(*x)->a[i] = a[j];
}
/**
* @brief bi_set_by_string : word �迭 ��, word ���ڿ��� ��ѹ� ���� ���� ��, ���ڿ��� x->a�� ���Խ����ִ� �Լ�
* @param bigint** x :���� ������ ��ѹ� x
* @param int sign :x�� ��ȣ
* @param char* str : ������ ��ѹ� ���ڿ�
* @param word base :x�� �������
*/
void bi_set_by_string(bigint** x, int sign, char* str, word base) {
	if (*x != NULL)
		bi_delete(x);
}

/**
* @brief bi_show_hex : (*x)->a ���� WOREBITLEN�� �°� 16���� ���
* @param bigint* x : ����� ��ѹ� x
*/
void bi_show_hex(bigint* x) {
	if (x->sign == NEGATIVE)
		printf("-0x");
	else
		printf("0x");
	for (int i = (x->wordlen - 1); i >= 0; i--) {
#if (WORD_BITLEN == 8)
		printf("%02x", x->a[i]);
#elif (WORD_BITLEN == 32)
		printf("%08x", x->a[i]);
#else
		printf("%016llx", x->a[i]);
#endif
	}
}

/**
* @brief word_show_hex : 1 word ���� 16���� ���
* @param word x : ����� word x
*/
void word_show_hex(word x) {
	
	
#if (WORD_BITLEN == 8)
		printf("%02x", x);
#elif (WORD_BITLEN == 32)
		printf("%08x", x);
#else
		printf("%016llx", x);
#endif
	
}

/**
* @brief bi_show_bin : (*x)->a ���� WOREBITLEN�� �°� 2���� ���
* @param bigint* x : ����� ��ѹ� x
*/
void bi_show_bin(bigint* x) {
	if (x->sign == NEGATIVE) printf("-");
	printf("0b");
	for (int i = x->wordlen - 1; i >= 0; i--) {
		for (int j = WORD_BITLEN - 1; j >= 0; j--) {
			int mask = 1 << j;
			printf("%d", x->a[i] & mask ? 1 : 0);
		}
	}
}

/**
* @brief File_print : ���Ͽ� ��ѹ� ���� 16������ ����� �� ���Ǵ� �Լ�
* @param bigint* x : ����� ��ѹ� x
* @param FILE* fp : ��°��� ���� ����
*/
void File_print(bigint* x, FILE* fp) {


	if (x->sign == NEGATIVE)
		fprintf(fp, "-0x");
	else
		fprintf(fp, "0x");

	for (int i = (x->wordlen - 1); i >= 0; i--) {
#if (WORD_BITLEN == 8)
		fprintf(fp, "%02x", x->a[i]);
#elif (WORD_BITLEN == 32)
		fprintf(fp, "%08x", x->a[i]);
#else
		fprintf(fp, "%016llx", x->a[i]);
#endif
	}
}

/**
* @brief bi_refine : x->a = 0x0000ffff ó�� �տ� ���������� �ʿ���� �޸𸮰� ���������� x->a = 0xffff�� �ٿ��ִ� �Լ�
* @param bigint* x : refine �� ��ѹ� x
*/
void bi_refine(bigint** x) {
	if ((*x) == NULL)
		return;

	int new_wordlen = (*x)->wordlen;
	while (new_wordlen > 1) {
		if ((*x)->a[new_wordlen - 1] != 0)
			break;
		new_wordlen--;
	}
	// 0���� ä���� ���常ŭ ���� ���̸� ���δ�.

	if ((*x)->wordlen != new_wordlen) {

		(*x)->wordlen = new_wordlen;
		(*x)->a = (word*)realloc((*x)->a, sizeof(word) * new_wordlen);
	}
	// �پ�� new_wordlen ��ŭ ��ѹ� ���� �Ҵ�
	if (((*x)->wordlen == 1) && ((*x)->a[0] == 0x0))
		(*x)->sign = NONNEGATIVE;
	// 0�� ���, ��ȣ�� ����� ��
}

/**
* @brief bi_assign : ��ѹ� y�� ��ѹ�x�� �������ִ� �Լ�
* @param bigint** y : ������ ���� ���� ��ѹ� y
* @param bigint* x : ������ ��ѹ� x
*/
void bi_assign(bigint** y, bigint* x) {
	if (*y != NULL)
		bi_delete(y);

	bi_new(y, x->wordlen);
	(*y)->sign = x->sign;
	array_copy((*y)->a, x->a, x->wordlen);
}

/**
* @brief bi_gen_rand : ��ȣ�� ���� ������ ��ѹ� x�� ����� �ִ� �Լ�
* @param bigint** x : ������ ��ѹ� x
* @param int wordlen : ��ѹ� x�� ���� ����
*/
void bi_gen_rand(bigint** x, int sign,int wordlen) {
	bi_new(x, wordlen);
	(*x)->sign = sign;
	array_rand((*x)->a, wordlen);

	bi_refine(x);
}

/**
* @brief get_word_length : ��ѹ� x�� wordlen�� ����
* @param bigint* x : ��ѹ� x
*/
int get_word_length(bigint* x) {
	return x->wordlen;
}

/**
 * @brief get_bit_length : ��ѹ� x�� ��Ʈ���̸� ����
 * @param bigint* x : ��ѹ� x
 * @return total
 */
int get_bit_length(bigint* x) {
	int total = x->wordlen * WORD_BITLEN; // x�� wordlen�� 5 �̸� total = 5 * WORD_BITLEN 

	for (int j = total - 1; j > 0; j--) {
		if (bit_of_bi(x, j) == 0)
			total--;
		else return total;
	}
	return total;
}

/**
* @brief bit_of_bi : ��ѹ� x�� j��° ��Ʈ���� ����
* @param bigint* x :��ѹ� x
* @param int j : x�� j��° ��Ʈ�� ǥ��
* @return (x->a[j_word] & mask) >> rem
*/
int bit_of_bi(bigint* x, int j) {
	int rem = j % WORD_BITLEN;
	int j_word = j / WORD_BITLEN;
	int mask = (unsigned long long)1 << rem;

	return (x->a[j_word] & mask) >> rem;
}

/**
* @brief get_sign_bi : x�� ��ȣ ����
* @param bigint* x : ��ѹ� x
* @return NEGATIVE or NONNEGATIVE
*/
int get_sign_bi(bigint* x) {
	return x->sign;
}

/**
* @brief flip_sign_bi : x�� ��ȣ �ݴ�ó���ϴ� �Լ�
* @param bigint** x : ��ѹ� x
*/ 
void flip_sign_bi(bigint** x) {
	if ((*x)->sign == NONNEGATIVE)
		(*x)->sign = NEGATIVE;
	else (*x)->sign = NONNEGATIVE;
}

/**
* @brief bi_set_one : x�� 1�� �ٲ��ִ� �Լ�
* @param bigint** x : ��ѹ� x
*/
void bi_set_one(bigint** x) {
	bi_new(x, 1);
	(*x)->sign = NONNEGATIVE;
	(*x)->a[0] = 0x1;
}

/**
* @brief bi_set_zero : x�� 0���� �ٲ��ִ� �Լ�
* @param : bigint** x : ��ѹ� x
*/
void bi_set_zero(bigint** x) {
	if (x != NULL)
		bi_delete(x);

	bi_new(x, 1);
	(*x)->sign = NONNEGATIVE;
	(*x)->a[0] = 0x0;
}

/**
* @brief bi_is_zero : x�� 0���� Ȯ���ϴ� �Լ�: x�� 0�̸� 1�� ����
* @param bigint* x :��ѹ� x
* @return 0 or 1
*/
int bi_is_zero(bigint* x) {
	if (x->sign == NEGATIVE || x->a[0] != 0) return 0;
	else {
		for (int j = x->wordlen - 1; j > 0; j--)
			if (x->a[j] != 0) return 0;
	}
	return 1;
}

/**
* @brief bi_is_one : x�� 1�� Ȯ���ϴ� �Լ�: x�� 1�̸� 1, -1 �̸� -1�� ����
* @param bigint* x : ��ѹ� x
* @return 0 or 1 or -1
*/
int bi_is_one(bigint* x) {
	if (x->a[0] != 1) return 0;
	else {
		for (int j = x->wordlen - 1; j > 0; j--)
			if (x->a[j] != 0) return 0;
	}
	if (x->sign == NEGATIVE) return -1;
	return 1;
}

/**
* @brief compareABS : x �� y�� ���밪ũ�� �� : x�� ũ�� 1, ������ -1, ������ 0�� ����
* @param bigint* x : ��ѹ� x
* @param bigint* y : ��ѹ� y
* @return -1 , 0, 1
*/
int compareABS(bigint* x, bigint* y)
{
	int i, n, m;
	n = x->wordlen;
	m = y->wordlen;

	if (n > m) return 1; // |x| > |y| 
	else if (n < m) return -1; // |x| < |y|
	else if (n == m) {
		for (i = n - 1; i >= 0; i--)
		{
			if (x->a[i] > y->a[i]) return 1; // |x| > |y|
			else if (x->a[i] < y->a[i]) return -1; // |x| < |y|
		}
	}
	return 0; // |x| = |y|
}

/**
* @brief compareAB : x�� y�� ũ�� �� : x�� ũ�� 1, ������ -1, ������ 0�� ����
* @param bigint* x : ��ѹ� x
* @param bigint* y : ��ѹ� y
* @return -1, 0, 1
*/
int compareAB(bigint* x, bigint* y)
{
	int ret;

	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) return -1; // x < 0 , y > 0 
	else if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) return 1; // x > 0 , y < 0

	ret = compareABS(x, y); // x < 0 , y < 0 �̰ų� x > 0, y > 0 �� ��� compareABS �Լ��� ���밪 ��
	if (get_sign_bi(x) == NONNEGATIVE) return ret; // x > 0 , y > 0 �� ���
	else return ret * (-1); // x < 0 , y < 0 �� ���

}

/**
* @brief bi_leftshift : x�� r��Ʈ��ŭ leftShift ���ִ� �Լ�
* @param bigint** x : ��ѹ� x
* @param int r : leftShift Ƚ��
*/
void bi_leftshift(bigint** x, int r)
{
	int k, rp, a;
	k = r / WORD_BITLEN;
	rp = r % WORD_BITLEN;
	word tmp = 0;
	word ttmp = 0;

	if (r % WORD_BITLEN == 0) // word������ shift ���길 ������ɶ�
	{
		a = (*x)->wordlen;
		(*x)->wordlen += k;
		(*x)->a = (word*)realloc((*x)->a, (*x)->wordlen * sizeof(word));
		for (int i = a - 1; i >= 0; i--)
			(*x)->a[i + k] = (*x)->a[i];
		for (int j = 0; j < k; j++)
			(*x)->a[j] = 0x00;

	}
	else { // bit������ shift ����
		a = (*x)->wordlen;
		(*x)->wordlen += 1 + k;
		(*x)->a = (word*)realloc((*x)->a, (*x)->wordlen * sizeof(word));
		tmp = (*x)->a[0];
		(*x)->a[0] = (*x)->a[0] << rp;
		for (int i = 1; i < a; i++) {
			ttmp = (*x)->a[i];
			(*x)->a[i] = ((*x)->a[i] << rp) ^ (tmp >> (WORD_BITLEN - rp));
			tmp = ttmp;
			ttmp = (*x)->a[i + 1];
		}
		(*x)->a[a] = tmp >> (WORD_BITLEN - rp);
		for (int i = a + 1; i >= 0; i--)
			(*x)->a[i + k] = (*x)->a[i];
		for (int j = 0; j < k; j++)
			(*x)->a[j] = 0x00;
	}
	bi_refine(x);

}

/**
* @brief bi_rightshift : x�� r��Ʈ��ŭ  rightShift ���ִ� �Լ�
* @param bigint** x : ��ѹ� x
* @param int r : rightShift Ƚ��
*/
void bi_rightshift(bigint** x, int r)
{
	int i, j, k, rp, a;
	k = r / WORD_BITLEN; // shift �ؾ��ϴ� word�� ��
	rp = r % WORD_BITLEN; // shift �ؾ��ϴ� bit�� ��
	if (r == 0) return;

	a = (*x)->wordlen;

	if (k >= (*x)->wordlen) { // shift ����� 0 �϶�
		bi_set_zero(x);
		return;
	}

	if (r % WORD_BITLEN == 0) // r�� word_bitlen�� ������ word������ shift�� ���ָ� ��
	{
		for (i = 0; i < a - k; i++) // word ���� right shift ����
			(*x)->a[i] = ((*x)->a[k + i]);
		for (j = i; j < a; j++) // shift �� ��ŭ ���� word�� 0���� set�ϴ� ����
			(*x)->a[j] = 0x00;
	}
	else {
		for (i = 0; i < a - k - 1; i++)  // bit ���� right shift ����
			(*x)->a[i] = ((*x)->a[i + k] >> rp) ^ ((*x)->a[i + k + 1] << (WORD_BITLEN - rp));
		(*x)->a[a - k - 1] = (*x)->a[a - k - 1] >> rp;
		for (i = a - k; i < a; i++) // shift �� ��ŭ ���� word�� 0���� set�ϴ� ���� // shift �� ��ŭ ���� word�� 0���� set�ϴ� ����
			(*x)->a[i] = 0x00;
	}
	bi_refine(x);
}

/**
* @brief bi_reduction : function of x mod r = y
* @param bigint** y : ������� ������ ��ѹ� y
* @param bigint* x : ��ⷯ ������ ���� ��ѹ� x
* @param int r : mod r
*/
void bi_reduction(bigint** y, bigint* x, int r) {
	int k = r / WORD_BITLEN;
	int rem = r % WORD_BITLEN;
	if (r > x->wordlen * WORD_BITLEN) {
		bi_assign(y, x); return;
	}
	else if (rem == 0) {
		bi_new(y, k);
		for (int i = 0; i < k; i++) {
			(*y)->a[i] = x->a[i] & MASK;
			return;
		}
	}
	else {
		bi_new(y, k + 1);
		for (int i = 0; i < k; i++) {
			(*y)->a[i] = x->a[i] & ((1 << sizeof(word)) - 1);
		}
		(*y)->a[k] = x->a[k] & MASK;
		return;
	}
}

