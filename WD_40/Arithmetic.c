#pragma once
#include "Arithmetic.h"
#include "Basic Operation.h"
/**
* @brief bi_reduction : function of x mod r = y
* @param bigint** y : ������� ������ ��ѹ� y
* @param bigint* x : ��ⷯ ������ ���� ��ѹ� x
* @param int r : mod r
*/
void bi_reduction(bigint** y, bigint* x, int r) {
	{
		long long k = r / WORD_BITLEN;
		long long rem = r % WORD_BITLEN;
		if (r > x->wordlen * WORD_BITLEN) {
			bi_assign(y, x); return;
		}
		else if (rem == 0) {
			bi_new(y, k);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & ((1 << sizeof(word)) - 1); 
				return;
			}
		}
		else {
			bi_new(y, k + 1);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & ((1 << sizeof(word)) - 1);
			}
			(*y)->a[k] = x->a[k] & ((1 << rem) - 1);
			return;
		}
	}
}


/**
* @brief S_ADDABc : �� ���� ������ ���� ������ carry�� = d�� �����ϴ� �Լ�
* @param word x : ���ϰ����ϴ� ����
* @param word y : ���ϰ����ϴ� ����
* @param bigint** z : ���Ѱ��� ������ ��ѹ�
* @param int carry : ���� ���꿡�� �߻��� carry
* @param int r : ���� ���� z�� r��° �迭�� ����
* return d (carry ��)
*/
int S_ADDABc(word x, word y, bigint** z, int carry, int r) {

	int d = 0;

	(*z)->a[r] = (x + y) & MASK;
	if ((*z)->a[r] < x) d = 1;

	(*z)->a[r] = ((*z)->a[r] + carry);
	if ((*z)->a[r] < carry) d = 1;

	return d;
}
/**
* @brief M_ADD : ���̰� 2�̻��� �� ��ѹ� x,y�� ���ϴ� �Լ� x�� wordlen�� �׻� y�� wordlen �̻��̶�� ����
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z: ���Ѱ��� ������ ��ѹ� z (z->wordlen = max(x->wordlen, y->wordlen) + 1)
*/
void M_ADD(bigint* x, bigint* y, bigint** z) {
	int c = 0;

	if (*z != NULL)
		bi_delete(z);

	bi_new(z, x->wordlen + 1);
	if ((y) == NULL)
		return;
	y->a = (word*)realloc(y->a, (x->wordlen * sizeof(word)));

	// word ���̰� ���̳� �� ���� ��ŭ ª�� ��ѹ��� left word�� 0���� ä����
	if (x->wordlen >= y->wordlen)
		for (int i = y->wordlen; i < x->wordlen; i++) 
			y->a[i] = 0;
	 
	c = 0;

	for (int i = 0; i < x->wordlen; i++)
		c = S_ADDABc(x->a[i], y->a[i], z, c, i);

	(*z)->a[x->wordlen] = c;

	if ((*z)->a[x->wordlen] == 0) bi_refine(z);
}
/**
* @brief ADD : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void ADD(bigint* x, bigint* y, bigint** z) {

	// x = 0 �̸� x + y = y
	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		return;
	}
	// y = 0 �̸� x + y = x
	if (bi_is_zero(y) == 1) 
	 {
		bi_assign(z, x);
		return;
	}
	// x > 0 , y < 0 �̸� x + (-y) = x - y
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		SUB(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	// x < 0 , y > 0 �̸� (-x) + y = -x + y = y - x
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		flip_sign_bi(&x);
		SUB(y, x, z);
		flip_sign_bi(&x);
		return;
	}
	// x < 0 , y < 0 �϶�
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE) {
		// |x| > |y| �̸� x + y = - (|x| + |y|)
		if (x->wordlen >= y->wordlen) {
			M_ADD(x, y, z);
			flip_sign_bi(z);
			return;
		}
		// |x| < |y| �̸� x + y = - (|y| + |x|)
		else {
			M_ADD(y, x, z);
			flip_sign_bi(z);
			return;
		}
	}
	// x >= y > 0 �� ��
	if (x->wordlen >= y->wordlen) {
		M_ADD(x, y, z);
		return;
	}
	// y > x > 0 �� ��
	else {
		M_ADD(y, x, z);
		return;
	}
}
/**
* @brief S_SUBABb : �� ���尣�� ���������ϴ� �Լ� borrow ���� ����
* @param bigint* x : �������ϴ� ��ѹ� x
* @param bigint* y : �������ϴ� ��ѹ� y
* @param bigint** z : �� ���� ������ ��ѹ� z
* @param int b : ���� borrow ��
* @param int j : �� ���� z�� j��° �迭�� ����
* @return b (borrow ��)
*/
int S_SUBABb(bigint* x, bigint* y, bigint** z, unsigned int b, int j) {

	(*z)->a[j] = x->a[j] - b;

	if (x->a[j] < b)  b = 1;
	else b = 0;

	if ((*z)->a[j] < y->a[j]) b += 1;
	if (j < y->wordlen)
		(*z)->a[j] -= y->a[j];
	return b;
}
/**
* @brief SUB_C : ���̰� 2�̻��� �� ��ѹ� x,y�� ���� �Լ� x�� wordlen�� �׻� y�� wordlen �̻��̶�� ����
* @param bigint* x : �������ϴ� ��ѹ� x  (�׻� y ���� ũ�ų� ����)
* @param bigint* y : �������ϴ� ��ѹ� y
* @param bigint** z : �� ���� ������ ��ѹ� z
*/
void SUB_C(bigint* x, bigint* y, bigint** z) {
	
	bi_new(z, x->wordlen);

	y->a = (word*)realloc(y->a, (x->wordlen * sizeof(word)));

	// wordlen�� ���̰� ���ٸ� ���̸�ŭ ª�� ��ѹ��� left word�� 0���� �߰�����
	for (int i = y->wordlen; i < x->wordlen; i++) 
		y->a[i] = 0;

	int b = 0;
	for (int j = 0; j < (*z)->wordlen; j++) {
		b = S_SUBABb(x, y, z, b, j);
	}
	bi_refine(z);
}


/**
* @brief SUB : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @param bigint* x : �������ϴ� ��ѹ� x
* @param bigint* y : �������ϴ� ��ѹ� y
* @param bigint** z : �� ���� ������ ��ѹ� z
*/
void SUB(bigint* x, bigint* y, bigint** z) {
	// x = 0 �̸� x - y = -y
	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	// y = 0 �̸� x - y = -x
	if (bi_is_zero(y) == 1) {
		bi_assign(z, x);
		return;
	}
	// x >= y > 0 �� ��
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) >= 0) {
		SUB_C(x, y, z);
		return;
	}
	// y > x > 0 �� ��
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) == -1) {
		SUB_C(y, x, z);
		flip_sign_bi(z);
		return;
	}
	// 0 >= x > y �� ��
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) >= 0) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(y, x, z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	// 0 > y > x �� ��
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) == -1) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	// x > 0 , y < 0 & |x| > |y| �̸� x - y = x + |y|
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y) >= 0) {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	// x > 0 , y < 0 & |x| < |y| �̸� x - y = |y| + x
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y)== -1) {
		flip_sign_bi(&y);
		M_ADD(y, x, z);
		flip_sign_bi(&y);
		return;
	}// x < 0 , y > 0 & |x| > |y| �̸� x - y = -(x + y)
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) >= 0) {
		flip_sign_bi(&x);
		M_ADD(x, y, z);
		flip_sign_bi(&x);
		flip_sign_bi(z);
		return;
	}// x < 0 , y > 0 & |x| < |y| �̸� x - y = -(y + x)
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) == -1) {
		flip_sign_bi(&x);
		M_ADD(y, x, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
		return;
	}
}
/**
* @brief MULC : �� ���尣�� ����(x�� i��° ���� * y�� j��° ����)�� ó���ϴ� �Լ�
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
* @param int i : x�� i��° word�� ��Ÿ�� ���� i
* @param int j : y�� j��° word�� ��Ÿ�� ���� j
*/

void MULC(word x, word y, word* tmp) {

	word a0, a1, b0, b1, c0, c1, t0, t1, t;

	a0 = x & MASKMUL;
	a1 = x >> (sizeof(word) * 4);
	b0 = y & MASKMUL;
	b1 = y >> (sizeof(word) * 4);
	t0 = a1 * b0;
	t1 = a0 * b1;
	t0 = (t0 + t1) & MASK;
	t1 = t0 < t1;


	c0 = a0 * b0;
	c1 = a1 * b1;
	t = c0;
	c0 = ((c0 + (t0 << (sizeof(word) * 4))) & MASK);

	c1 = c1 + (t1 << (sizeof(word) * 4)) + (t0 >> (sizeof(word) * 4)) + (c0 < t);
	tmp[0] = c0;
	tmp[1] = c1;
}


/**
* @brief MUL : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @param bigint* x :���ϰ����ϴ� ��ѹ� x
* @param bigint* y :���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void MUL(bigint* x, bigint* y, bigint** z) {
	
	// x �Ǵ� y �� 0�̸� x * y = 0
	if (bi_is_zero(x) == 1 || bi_is_zero(y) == 1) { 
		bi_set_zero(z);
		return;
	}
	// x = 1 �̸� x * y = y
	if (bi_is_one(x) == 1) { 
		bi_assign(z, y);
		return;
	}
	// x = -1 �̸� x * y = -y
	if (bi_is_one(x) == 1 && get_sign_bi(x) == NEGATIVE) { 
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	// y = 1 �̸� x * y = x
	if (bi_is_one(y) == 1) { 
		bi_assign(z, x);
		return;
	}
	// y = -1 �̸� x * y = -x
	if (bi_is_one(y) == 1 && get_sign_bi(y) == NEGATIVE) {
		bi_assign(z, x);
		flip_sign_bi(z);
		return;
	}

	//karatsuba_MUL(x, y, z);
	Schoolbook_MUL(x, y, z);

	(*z)->sign = (x->wordlen + y->wordlen) % 2;
}
/**
* @brief Schoolbook_MUL : ���̰� 2�̻��� �� ��ѹ� x , y�� ���ϴ� �Լ�
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z) {

	int i, j, k;
	unsigned int c = 0;
	int len_short = 0; int len_long = 0;
	
	bi_new(z, (x->wordlen + y->wordlen));



	if (x->wordlen >= y->wordlen) {
		len_short = y->wordlen;
		len_long = x->wordlen;
	}
	else {
		len_short = x->wordlen;
		len_long = y->wordlen;
	}
	word tmp[2] = { 0, };
	word* tmp_arr = NULL;
	tmp_arr = (word*)calloc(sizeof(word), (len_long + 1));

	for (i = 0; i < len_long; i++) {
		for (j = 0; j < len_short; j++) {
			if (len_short == y->wordlen)
				MULC(x->a[i], y->a[j], tmp);
			else MULC(x->a[j], y->a[i], tmp);

			tmp_arr[j] += c; 
			c = (tmp_arr[j] < c);

			tmp_arr[j] += tmp[0];
			c += (tmp_arr[j] < tmp[0]);

			tmp_arr[j + 1] += c;
			c = (tmp_arr[j + 1] < c);
			tmp_arr[j + 1] += tmp[1];
			c += (tmp_arr[j + 1] < tmp[1]);
		}
		c = 0;
		// ������� ���ϸ鼭 �߻��ϴ� carry ó���ϸ鼭 z�� ����
		for (k = 0; k < len_long + 1; k++) {
			(*z)->a[i + k] += c; 
			c = ((*z)->a[i + k] < c);

			(*z)->a[i + k] += tmp_arr[k];
			c += ((*z)->a[i + k] < tmp_arr[k]);
		}
		memset(tmp_arr, 0, ((len_long + 1)*sizeof(word)));
	}
	free(tmp_arr);
}
/**
* @brief karatsuba_MUL : ���̰� 2�̻��� �� ��ѹ� x , y�� ���ϴ� �Լ�
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void karatsuba_MUL(bigint* x, bigint* y, bigint** z) {

	int flag = 0, m;
	m = min(x->wordlen, y->wordlen);

	if (flag >= m) {
		Schoolbook_MUL(x, y, z);
		return;
	}
	int l = 0;

	l = (max(x->wordlen, y->wordlen) + 1) >> 1;

	bigint* a0 = NULL;
	bigint* a1 = NULL;
	bigint* b0 = NULL;
	bigint* b1 = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;
	bigint* s0 = NULL;
	bigint* s1 = NULL;
	bigint* R = NULL;
	bigint* S = NULL;
	bigint* tmp = NULL;

	bi_new(&a0, (l / 2));
	bi_new(&a1, (l / 2));
	bi_new(&b0, (l / 2));
	bi_new(&b1, (l / 2));
	bi_new(&t0, l);
	bi_new(&t1, l);
	bi_new(&s0, l);
	bi_new(&s1, l);
	bi_new(&R, (2 * l));
	bi_new(&S, (2 * l));
	bi_new(z, (x->wordlen + y->wordlen));


	for (int i = 0; i < (l / 2); i++) {
		a0->a[i] = x->a[i];
		b0->a[i] = y->a[i];
	}

	for (int i = 0; i < (l / 2); i++) {
		a1->a[i] = x->a[(l / 2) + i];
		b1->a[i] = y->a[(l / 2) + i];
	}

	karatsuba_MUL(a0, b0, &t0);
	karatsuba_MUL(a1, b1, &t1);
	for (int i = 0; i < R->wordlen; i++) {
		if (i < R->wordlen)
			R->a[i] = t0->a[i];
		else
			R->a[i] = t1->a[i - (R->wordlen / 2)];
	}

	SUB(b1, b0, &s0);
	SUB(a0, a1, &s1);

	if (s0->sign == NEGATIVE)
		flip_sign_bi(&s0);
	if (s1->sign == NEGATIVE)
		flip_sign_bi(&s1);
	karatsuba_MUL(s0, s1, &S);
	if (bi_is_zero(s0) == 1 || bi_is_zero(s1) == 1)
		S->sign = NONNEGATIVE;
	else
		S->sign = s0->sign ^ s1->sign;

	ADD(S, t1, &S);
	ADD(S, t0, &S);
	bi_leftshift(&S, l);
	ADD(*z, S, z);
}

/**
* @brief Squaring_word : ��ѹ� �������꿡 ���Ǵ� �� word ������ ����
* @param word* dst : ������ ����� �����ϴ� ����
* @param word a : �����ϰ����ϴ� a (1word)
*/
void Squaring_word(word* dst, word a) {

	word a0 = a & MASKMUL;
	word a1 = a >> (sizeof(word) * 4);

	dst[0] = a0 * a0;
	dst[1] = a1 * a1;

	word s0 = (a1 * a0) << (sizeof(word) * 4);
	word s1 = (a1 * a0) >> (sizeof(word) * 4);

	dst[0] += s0;
	dst[1] += s1;
	if (dst[0] < s0)
		dst[1] += 1;

	dst[0] += s0;
	dst[1] += s1;
	if (dst[0] < s0)
		dst[1] += 1;
}

//void Squaring_Schoolbook(bigint* x, bigint** z) {
//
//
//	if (x->a[0] == 0x01) {
//		bi_new(z, 1);
//		(*z)->a[0] = 0x01;
//		return;
//	}
//	int i, j;
//	unsigned int c = 0;
//	unsigned int cc = 0;
//
//	bigint* c1 = NULL;
//	bigint* c2 = NULL;
//	bigint* t1 = NULL;
//	bigint* t2 = NULL;
//	bi_new(&c1, 2 * x->wordlen);
//	bi_new(&c2, 2 * x->wordlen);
//	bi_new(&t1, 2);
//	bi_new(&t2, 2);
//	bi_new(z, (2 * x->wordlen));
//
//	word* tmp_arr = NULL;
//	tmp_arr = (word*)calloc(sizeof(word), (1 + x->wordlen));
//
//	for (j = 0; j < x->wordlen; j++) {
//		Squaring_word(t1->a, x->a[j]);
//
//		c1->a[2 * j] += c;
//		c = (c1->a[2 * j] < c);
//
//		c1->a[2 * j] += t1->a[0];
//		c += (c1->a[2 * j] < t1->a[0]);
//
//		c1->a[(2 * j) + 1] += c;
//		c = (c1->a[(2 * j) + 1] < c);
//
//		c1->a[(2 * j) + 1] += t1->a[1];
//		c += (c1->a[(2 * j) + 1] < t1->a[1]);
//
//		for (i = j + 1; i < x->wordlen; i++) {
//			MULC(x->a[j], x->a[i], t2->a);
//
//			c2->a[i + j + 1] += cc;
//			cc = (c2->a[i + j] < cc);
//
//			c2->a[i + j] += t2->a[0];
//			cc += (c2->a[i + j] < t2->a[0]);
//
//			c2->a[i + j + 1] += cc;
//			cc = (c2->a[i + j + 1] < cc);
//
//			c2->a[i + j + 1] += t2->a[1];
//			cc += (c2->a[i + j + 1] < t2->a[1]);
//			if (cc == 1) {
//				c2->a[i + j + 2] += cc;
//				cc = 0;
//			}
//
//			printf("i + j = %d,  t2 = ", (i + j));
//			bi_show_hex(t2);
//			printf("\n");
//
//			printf("c2 = ");
//			bi_show_hex(c2);
//			printf("\n");
//		}
//	}
//	bi_leftshift(&c2, 1);
//
//	printf("c1 = ");
//	bi_show_hex(c1);
//	printf("\n");
//	printf("c2 = ");
//	bi_show_hex(c2);
//	printf("\n");
//
//
//	ADD(c1, c2, z);
//
//	bi_delete(&c1);
//	bi_delete(&c2);
//	bi_delete(&t1);
//	bi_delete(&t2);
//}

/**
* @brief Squaring_Schoolbook : ����� ����� ��ѹ� ��������
* @param bigint* x  : �����ϰ����ϴ� ��ѹ� x
* @param bigint** z  : ������ ����� �����ϴ� ��ѹ� z
*/

void Squaring_Schoolbook(bigint* x, bigint** z) {


	if (bi_is_one(x)) {  // x�� 1�̸� �����ص� 1
		bi_set_zero(z);
		return;
	}
	int i, j;
	unsigned int c = 0;
	unsigned int cc = 0;

	bigint* c1 = NULL;
	bigint* c2 = NULL;
	bigint* t1 = NULL;
	bigint* t2 = NULL;
	bi_new(&c1, 2 * x->wordlen);
	bi_new(&c2, 2 * x->wordlen);
	bi_new(&t1, 2);
	bi_new(&t2, 2);
	bi_new(z, (2 * x->wordlen));

	word* tmp_arr = NULL;
	tmp_arr = (word*)calloc(sizeof(word), (1 + x->wordlen));
	// c1 : �� ������ ������ �������� ����
	for (j = 0; j < x->wordlen; j++) { 
		Squaring_word(t1->a, x->a[j]);

		c1->a[2 * j] += c;
		c = (c1->a[2 * j] < c);

		c1->a[2 * j] += t1->a[0];
		c += (c1->a[2 * j] < t1->a[0]);

		c1->a[(2 * j) + 1] += c;
		c = (c1->a[(2 * j) + 1] < c);

		c1->a[(2 * j) + 1] += t1->a[1];
		c += (c1->a[(2 * j) + 1] < t1->a[1]);
		// c2 : �ߺ��� ���Ե� ���尣�� ���� ����� ������ ����
		for (i = j + 1; i < x->wordlen; i++) { 
			MULC(x->a[j], x->a[i], t2->a);

			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j] < cc);

			c2->a[i + j] += t2->a[0];
			cc += (c2->a[i + j] < t2->a[0]);

			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j + 1] < cc);

			c2->a[i + j + 1] += t2->a[1];
			cc += (c2->a[i + j + 1] < t2->a[1]);
			// ������� ĳ���� �߻��Ͽ��� �� ����ó��
			if (cc == 1) {
				c2->a[i + j + 2] += cc;
				if (c2->a[i + j + 2] < cc) {
					c2->a[i + j + 3] += cc;
					if (c2->a[i + j + 3] < cc) {
						c2->a[i + j + 4] += cc;
					}
				}
			}
			cc = 0;
		}
	}
	bi_leftshift(&c2, 1);
	ADD(c1, c2, z);

	bi_delete(&c1);
	bi_delete(&c2);
	bi_delete(&t1);
	bi_delete(&t2);
}


/**
* @brief bit_length : ����� ����� ��ѹ� ��������
* @param unsigned int a :
*/
int bit_length(unsigned int a) {
	int cnt = 32;
	unsigned int x = 0x80000000;

	for (int i = 0; i < 32; i++) {
		if ((a & x) != 0) break;
		else {
			cnt--;
			x = x >> 1;
		}

	}
	return cnt;
}

/**
* @brief binary_long_division : �Ϲ����� ���� �� �����
* @param int a : ������ a = b*q + r
* @param int b : ������ b
* @param int* q : a�� b�� ���� ��
* @param int* r : a�� b�� ���� ������
*/
void binary_long_division(int a, int b, int* q, int* r) {
	int aj = 0;
	for (int i = bit_length(a) - 1; i >= 0; i--) {
		aj = a & (1 << i) ? 1 : 0;
		(*r) = ((*r) << 1) + aj;
		if ((*r) >= b) {
			(*q) = (*q) + (1 << i);
			(*r) = (*r) - b;
		}
	}
}


/**
* @brief binary_long_division : ��ѹ������� ���� �� �����
* @param bigint* a : ������ a = b*q + r
* @param bigint* b : ������ b
* @param bigint** q : a�� b�� ���� ��
* @param bigint** r : a�� b�� ���� ������
*/
void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r) {
	int aj = 0;
	bigint* tmp = NULL;
	bigint* q_tmp = NULL;
	bigint* one = NULL;
	bi_set_one(&one);
	bi_new(&tmp, b->wordlen + 1);
	bi_new(r, b->wordlen - 1);
	bi_new(q, (a->wordlen) - (b->wordlen) + 1);



	if (b->sign == NEGATIVE) {
		return;
	}
	if (a->sign == NONNEGATIVE && compareAB(b, a) == 1) {
		bi_set_zero(q);
		bi_assign(r, a);
		return;
	}
	if (bi_is_zero(b)) {
		bi_assign(q, a);
		bi_set_zero(r);
	}
	else {
		for (int i = (a->wordlen) - 1; i >= 0; i--) {
			for (int j = WORD_BITLEN - 1; j >= 0; j--) {
				aj = a->a[i] & ((unsigned long long)1 << j) ? 1 : 0;
				bi_leftshift(&tmp, (unsigned long long)1); tmp->a[0] += aj;
				bi_leftshift(q, (unsigned long long)1);
				if (compareAB(tmp, b) >= 0) {
					SUB(tmp, b, r);
					(*q)->a[0]++;
					bi_assign(&tmp, (*r));
				}
			}
		}
		bi_assign(r, tmp);
		if (a->sign == NEGATIVE) {
			bi_assign(&q_tmp, *q);
			flip_sign_bi(&q_tmp);
			SUB(q_tmp, one, q);
			SUB(b, tmp, r);
		}
		bi_delete(&tmp);
		bi_delete(&q_tmp);
		bi_delete(&one);
	}
}

/**
* @brief binary_long_division : ��ѹ������� �� ��������� ���� ����������� �� �����
* @param bigint* x : ������ x = b*q + r
* @param bigint* y : ������ y
* @param bigint** q : a�� b�� ���� ��
* @param bigint** r : a�� b�� ���� ������
*/
void long_division_2word(bigint* x, bigint* y, bigint** q, bigint** r) {
	bi_set_zero(q);
	bi_new(r, 1);
	bigint* tmp1 = NULL;
	bigint* tmp2 = NULL;
	(*r)->a[0] = x->a[1];
	for (int i = WORD_BITLEN - 1; i >= 0; i--) {
		int ai = (x->a[0] & (unsigned long long)1 << i) ? 1 : 0;
		if ((*r)->a[0] >= (unsigned long long)1 << (WORD_BITLEN - 1)) {
			(*q)->a[0] += (unsigned long long)1 << i;
			//(*r)->a[0] ^= ai;
			bi_assign(&tmp1, *r);
			tmp1->a[0] += ai;
			SUB(y, *r, &tmp2);
			SUB(tmp1, tmp2, r);
		}
		else {
			bi_leftshift(r, 1);
			(*r)->a[0] += ai;
			if (compareAB(*r, y) >= 0) {
				(*q)->a[0] += (unsigned long long)1 << i;
				bi_assign(&tmp1, *r);
				SUB(tmp1, y, r);
			}
		}
	}
	bi_delete(&tmp1);
	bi_delete(&tmp2);
}
/**
* @brief int_to_binary : ���������� ���� ���� �迭�� ǥ�����ִ� �Լ�
* @param int decimal : �������� ǥ���� ���� 
* @param int* binary : �������� ������ �迭
*/
int int_to_binary(int decimal, int* binary ){
	
	int position = 0;
	while (1)
	{
		binary[position] = decimal % 2;// 2�� �������� �� �������� �迭�� ����    
		decimal = decimal / 2;  // 2�� ���� ���� ����

		position++;    // �ڸ��� ����

		if (decimal == 0)    // ���� 0�� �Ǹ� �ݺ��� ����
			break;
	}
	// �迭�� ������ �������� ���� EX : 6-> 110 ������ �迭���� 011�� �����.
	return position;
}

/**
* @brief left_to_right : Left to Right ����� ��ѹ� ������ ����
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint** t : ����� ������ ��ѹ� t
* @param int n : x�� ��� �������� �����ִ� ���� n
*/
void left_to_right(bigint* x, bigint** t, int n) {

	int l;
	int* ll = { 0x00 };
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	int r = n / 2 + 1;
	ll = (int*)calloc(1,r);
	l = int_to_binary(n, ll);
	
	bi_new(t, 1);

	(*t)->a[0] = 0x01;

	for (int i = l - 1; i >= 0; i--) {
		bi_assign(&tmp, *t);
		Squaring_Schoolbook(tmp, &ttmp);
		bi_assign(t, ttmp);
		if (ll[i] == 1) { // n�� i��° ��Ʈ�� 1�� ��
			bi_assign(&tmp, *t);
			MUL(tmp, x, &ttmp);
			bi_assign(t, ttmp);
		}
		else { // n�� i��° ��Ʈ�� 0�� ��
			bi_assign(&tmp, *t);
			bi_assign(t, ttmp);
		}
	}
	bi_delete(&tmp);
	bi_delete(&ttmp);
}



//void left_to_right(bigint* x, bigint** t, int n) {
//
//	int l;
//	int ll[100] = { 0, };
//	bigint* tmp = NULL;
//	bigint* ttmp = NULL;
//	l = int_to_binary(n, ll);
//
//	printf("n�� ��Ʈ���� %d \n", l);
//	for (int i = 0; i < l; i++)
//		printf("%d", ll[i]);
//	printf("\n");
//
//	bi_new(t, 1);
//	(*t)->a[0] = 0x01;
//	
//	for (int i = l - 1; i >= 0; i--) {
//		bi_assign(&tmp, *t);
//		printf("tmp = ");
//		bi_show_hex(tmp);
//		printf("\n");
//		Squaring_Schoolbook(tmp, &ttmp);
//		printf("t^2 ���� tmp = ");
//		bi_show_hex(ttmp);
//		printf("\n");
//		bi_assign(t, ttmp);
//		printf("t^2 = "); 
//		bi_show_hex(*t);
//		printf("\n");
//		if (ll[i] == 1) {
//			bi_assign(&tmp, *t);
//			printf("tmp = ");
//			bi_show_hex(tmp);
//			printf("\n");
//			MUL(tmp, x, &ttmp);
//			printf("x*t ���� tmp = ");
//			bi_show_hex(ttmp);
//			printf("\n");
//			bi_assign(t, ttmp);
//			printf("t * x = ");
//			bi_show_hex(*t);
//			printf("\n");
//		}
//	}
//	bi_delete(&tmp);
//	bi_delete(&ttmp);
//}

/**
* @date 2020-11-28 20:17
*/


