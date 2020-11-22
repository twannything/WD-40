#pragma once
#include "Arithmetic.h"
#include "Basic Operation.h"

/**
* @brief bi_reduction : y�� x�� r�� modular ���� �����ִ� �Լ�
* @param bigint** y : ��ѹ� y
* @param bigint* x : ��ѹ� x
* @param int r : x�� ����
*/
void bi_reduction(bigint** y, bigint* x, int r) {
	{
		word a = 1;
		int k = r / WORD_BITLEN;
		int rem = r % WORD_BITLEN;
		if (r > x->wordlen * WORD_BITLEN) {
			bi_assign(y, x); return;
		}
		else if (rem == 0) {
			bi_new(y, k);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & (((long long)a << WORD_BITLEN) - 1); return;
			}
		}
		else {
			bi_new(y, k + 1);
			for (int i = 0; i < k; i++) {
				(*y)->a[i] = x->a[i] & (((long long)a << WORD_BITLEN) - 1);
			}
			(*y)->a[k] = x->a[k] & ((a << rem) - 1);
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

	if (*z == NULL) bi_new(z, (x->wordlen + 1));


	if (x->wordlen > y->wordlen)
		for (int i = y->wordlen; i < x->wordlen; i++)
			y->a[i] = 0;

	c = 0;

	for (int i = 0; i < x->wordlen; i++)
		c = S_ADDABc(x->a[i], y->a[i], z, c, i);

	(*z)->a[x->wordlen] = c;

	if ((*z)->a[x->wordlen] == 0) bi_refine(*z);
}
/**
* @brief ADD : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void ADD(bigint* x, bigint* y, bigint** z) {


	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		return;
	}
	if (bi_is_zero(y) == 1) {
		bi_assign(z, x);
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		SUB(x, y, z);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		flip_sign_bi(&x);
		SUB(y, x, z);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE) {
		if (x->wordlen >= y->wordlen) {
			M_ADD(x, y, z);
			flip_sign_bi(z);
			return;
		}
		else {
			M_ADD(y, x, z);
			flip_sign_bi(z);
			return;
		}
	}
	if (x->wordlen >= y->wordlen) {
		M_ADD(x, y, z);
		return;
	}
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
int S_SUBABb(bigint* x, bigint* y, bigint** z, int b, int j) {

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
* @param bigint* x : �������ϴ� ��ѹ� x
* @param bigint* y : �������ϴ� ��ѹ� y
* @param bigint** z : �� ���� ������ ��ѹ� z
*/
void SUB_C(bigint* x, bigint* y, bigint** z) {
	bi_new(z, x->wordlen);

	for (int i = y->wordlen; i < (*z)->wordlen; i++)
		(*z)->a[i] = 0;
	int b = 0;
	for (int j = 0; j < (*z)->wordlen; j++) {
		b = S_SUBABb(x, y, z, b, j);
	}
	bi_refine(*z);
}


/**
* @brief SUB : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @param bigint* x : �������ϴ� ��ѹ� x
* @param bigint* y : �������ϴ� ��ѹ� y
* @param bigint** z : �� ���� ������ ��ѹ� z
*/
void SUB(bigint* x, bigint* y, bigint** z) {
	if (bi_is_zero(x) == 1) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	if (bi_is_zero(y) == 1) {
		bi_assign(z, x);
		return;
	}

	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) >= 0) {
		SUB_C(x, y, z);
		return;
	}
	else if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) == -1) {
		SUB_C(y, x, z);
		flip_sign_bi(z);
		return;
	}
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) >= 0) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(y, x, z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	else if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) == -1) {
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	else {
		flip_sign_bi(&y);
		M_ADD(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&y);
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
void MULC(bigint* x, bigint* y, bigint** z, int i, int j) {

	word a0, a1, b0, b1, c0, c1, t0, t1, t, a = 1;

	a0 = x->a[i] & MASKMUL;
	a1 = x->a[i] >> (sizeof(word) * 4);
	b0 = y->a[j] & MASKMUL;
	b1 = y->a[j] >> (sizeof(word) * 4);
	t0 = a1 * b0;
	t1 = a0 * b1;
	t0 = (t0 + t1) & MASK;
	t1 = t0 < t1;


	c0 = a0 * b0;
	c1 = a1 * b1;
	t = c0;
	c0 = ((c0 + (t0 << (sizeof(word) * 4))) & MASK);

	c1 = c1 + (t1 << (sizeof(word) * 4)) + (t0 >> (sizeof(word) * 4)) + (c0 < t);
	(*z)->a[0] = c0;
	(*z)->a[1] = c1;
}
/**
* @brief MUL : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @param bigint* x :���ϰ����ϴ� ��ѹ� x
* @param bigint* y :���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void MUL(bigint* x, bigint* y, bigint** z) {

	if (bi_is_zero(x) == 1 || bi_is_zero(y) == 1) {
		bi_set_zero(z);
		return;
	}

	if (bi_is_one(x) == 1) {
		bi_assign(z, y);
		return;
	}

	if (bi_is_one(x) == 1 && get_sign_bi(x) == NEGATIVE) {
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}

	if (bi_is_one(y) == 1) {
		bi_assign(z, x);
		return;
	}

	if (bi_is_one(y) == 1 && get_sign_bi(y) == NEGATIVE) {
		bi_assign(z, x);
		flip_sign_bi(z);
		return;
	}

	Schoolbook_MUL(x, y, z);
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE) {
		(*z)->sign = NONNEGATIVE;
		return;
	}
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		(*z)->sign = NONNEGATIVE;
		return;
	}
	else {
		(*z)->sign = NEGATIVE;
		return;
	}
}
/**
* @brief Schoolbook_MUL : ���̰� 2�̻��� �� ��ѹ� x , y�� ���ϴ� �Լ�
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z) {

	int i, j, k, c = 0;
	int len_short = 0; int len_long = 0;
	bigint* tmp = NULL;


	bi_new(&tmp, 2);
	bi_new(z, (x->wordlen + y->wordlen));

	if (x->wordlen >= y->wordlen) {
		len_short = y->wordlen;
		len_long = x->wordlen;
	}
	else {
		len_short = x->wordlen;
		len_long = y->wordlen;
	}
	word* tmp_arr = NULL;
	tmp_arr = (word*)calloc(sizeof(word), (len_long + 1));

	for (i = 0; i < x->wordlen; i++) {
		for (j = 0; j < y->wordlen; j++) {
			MULC(x, y, &tmp, j, i);

			tmp_arr[j] += c;
			c = (tmp_arr[j] < c);

			tmp_arr[j] += tmp->a[0];
			c += (tmp_arr[j] < tmp->a[0]);

			tmp_arr[j + 1] += c;
			c = (tmp_arr[j + 1] < c);

			tmp_arr[j + 1] += tmp->a[1];
			c += (tmp_arr[j + 1] < tmp->a[1]);
		}
		c = 0;
		for (k = 0; k < len_long + 1; k++) {
			(*z)->a[i + k] += c;
			c = ((*z)->a[i + k] < c);

			(*z)->a[i + k] += tmp_arr[k];
			c += ((*z)->a[i + k] < tmp_arr[k]);
		}
		memset(tmp_arr, 0, len_long + 1);
	}
	free(tmp);
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

	l = (
		max(x->wordlen, y->wordlen) + 1) >> 1;

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


	bi_delete(&a0);
	bi_delete(&a1);
	bi_delete(&b0);
	bi_delete(&b1);
	bi_delete(&t0);
	bi_delete(&t1);
	bi_delete(&s0);
	bi_delete(&s1);
	bi_delete(&R);
	bi_delete(&S);

	free(a0);
	free(a1);
	free(b0);
	free(b1);
	free(t0);
	free(t1);
	free(s0);
	free(s1);
	free(R);
	free(S);
}

void Squaring_word(bigint* dst, word a) {

	word a0 = a & MASKMUL;
	word a1 = a >> (sizeof(word) * 4);

	dst->a[0] = a0 * a0;
	dst->a[1] = a1 * a1;

	word s0 = (a1 * a0) << (sizeof(word) * 4);
	word s1 = (a1 * a0) >> (sizeof(word) * 4);

	dst->a[0] += s0;
	dst->a[1] += s1;
	if (dst->a[0] < s0)
		dst->a[1] += 1;

	dst->a[0] += s0;
	dst->a[1] += s1;
	if (dst->a[0] < s0)
		dst->a[1] += 1;
}

void Squaring_Schoolbook(bigint* x, bigint** z) {

	int i, j, c = 0;
	if (*z != NULL)
		bi_delete(z);
	bigint* c1 = NULL;
	bigint* c2 = NULL;
	bigint* t1 = NULL;
	bigint* t2 = NULL;
	bi_new(&c1, 2 * x->wordlen);
	bi_new(&c2, 2 * x->wordlen);
	bi_new(&t1, 2);
	bi_new(&t2, 2);
	bi_new(z, (2 * x->wordlen));


	for (j = 0; j < x->wordlen; j++) {
		Squaring_word(t1, x->a[j]);
		c1->a[2 * j] += t1->a[0];
		c1->a[(2 * j) + 1] += t1->a[1];
		for (i = j + 1; i < x->wordlen; i++) {
			MULC(x, x, &t2, j, i);
			c2->a[j + i] += t2->a[0];
			c2->a[j + i + 1] += t2->a[1];
		}
	}
	bi_leftshift(&c2, 1);
	ADD(c1, c2, z);
}
/**
* @date 2020-11-23 01:49
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

void bi_binary_long_division(bigint* a, bigint* b, bigint** q, bigint** r) {
	int aj = 0;
	bigint* tmp = NULL;
	bi_new(&tmp, (b->wordlen) + 1);
	bi_new(r, b->wordlen - 1);
	bi_new(q, (a->wordlen) - (b->wordlen) + 1);

	for (int i = (a->wordlen) - 1; i >= 0; i--) {
		for (int j = WORD_BITLEN - 1; j >= 0; j--) {
			aj = a->a[i] & (long long)1 << j ? 1 : 0;
			bi_leftshift(&tmp, 1);
			bi_leftshift(q, 1);
			tmp->a[0] += aj;
			if (compareAB(tmp, b) >= 0) {
				SUB(tmp, b, r);
				(*q)->a[0]++;
				bi_assign(&tmp, (*r));
			}
		}
	}
	bi_delete(&tmp);
}


void add_test() {
	bigint* x = NULL;
	bigint* y = NULL;
	bigint* z = NULL;

	int i = 20;
	while (i >= 0) {

		bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 5); // squaring ������ �Ⱦ�

		printf("x=");
		bi_show_hex(x);
		printf("y="); // squaring ������ �Ⱦ�
		bi_show_hex(y); // squaring ������ �Ⱦ�
		ADD(x, y, &z);

		printf("x + y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y); // squaring ������ �Ⱦ�
		bi_delete(&z);

		free(x);
		free(y); // squaring ������ �Ⱦ�
		free(z);
		i--;
	}
}
void sub_test() {
	bigint* x = NULL;
	bigint* y = NULL;
	bigint* z = NULL;

	int i = 20;
	while (i >= 0) {

		bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 5); // squaring ������ �Ⱦ�

		printf("x=");
		bi_show_hex(x);
		printf("y="); // squaring ������ �Ⱦ�
		bi_show_hex(y); // squaring ������ �Ⱦ�
		SUB(x, y, &z);

		printf("x - y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y); // squaring ������ �Ⱦ�
		bi_delete(&z);

		free(x);
		free(y); // squaring ������ �Ⱦ�
		free(z);
		i--;
	}
}

void  mul_test() {
	bigint* x = NULL;
	bigint* y = NULL;
	bigint* z = NULL;

	int i = 20;
	while (i >= 0) {

		bi_gen_rand(&x, 5);
		bi_gen_rand(&y, 5); // squaring ������ �Ⱦ�

		printf("x=");
		bi_show_hex(x);
		printf("y="); // squaring ������ �Ⱦ�
		bi_show_hex(y); // squaring ������ �Ⱦ�
		MUL(x, y, &z);

		printf("x * y ==");
		bi_show_hex(z);

		bi_delete(&x);
		bi_delete(&y); // squaring ������ �Ⱦ�
		bi_delete(&z);

		free(x);
		free(y); // squaring ������ �Ⱦ�
		free(z);
		i--;
	}
}


void bi_binary_long_division_test() {
	bigint* x[10] = { NULL, };
	bigint* y[10] = { NULL, };
	bigint* q[10] = { NULL, };
	bigint* r[10] = { NULL, };
	for (int i = 0; i < 10; i++) {
		bi_gen_rand(&x[i], 3);
		bi_gen_rand(&y[i], 2);
	}

	for (int i = 0; i < 10; i++) {
		bi_binary_long_division(x[i], y[i], &q[i], &r[i]);
		bi_show_bin(x[i]); printf("/"); bi_show_bin(y[i]);
		printf(" == ");
		bi_show_bin(q[i]); printf("\n");
		printf("remainder == "); bi_show_bin(r[i]); printf("\n");
	}

}






