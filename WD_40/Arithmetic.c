#pragma once
#include "Arithmetic.h"


/**
* @brief S_ADDABc : �� ���� ������ ���� ������ carry�� = d�� �����ϴ� �Լ�
* @param word x : ���ϰ����ϴ� ����
* @param word y : ���ϰ����ϴ� ����
* @param bigint** z : ���Ѱ��� ������ ��ѹ�
* @param int carry : ���� ���꿡�� �߻��� carry
* @param int r : ���� ���� z�� r��° �迭�� ����
* return d (carry ��)
*/

int maxlen(int a, int b) {
	return a >= b ? a : b;
}

int minlen(int a, int b) {
	return a < b ? a : b;
}
int S_ADDABc(word x, word y, bigint** z, int carry, int r) {

	int d = 0;

	(*z)->a[r] = (x + y) & MASK;
	if ((*z)->a[r] < x) d = 1;

	(*z)->a[r] = ((*z)->a[r] + carry);
	if ((*z)->a[r] < carry) d = 1;


	return d;
}

/**
* @brief S_ADDABc_print : �� ���� ������ ���� ������ carry�� = d�� �����ϴ� �Լ�
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param word x : ���ϰ����ϴ� ����
* @param word y : ���ϰ����ϴ� ����
* @param bigint** z : ���Ѱ��� ������ ��ѹ�
* @param int carry : ���� ���꿡�� �߻��� carry
* @param int r : ���� ���� z�� r��° �迭�� ����
* return d (carry ��)
*/
int S_ADDABc_print(word x, word y, bigint** z, int carry, int r) {

	int d = 0;

	printf("x�� %d��° ���� = ", r);
	word_show_hex(x);
	printf("\n");
	printf("y�� %d��° ���� = ", r);
	word_show_hex(y);
	printf("\n");
	printf("������ �߻��� carry = %d\n", carry);

	(*z)->a[r] = (x + y) & MASK;
	if ((*z)->a[r] < x) d = 1;

	(*z)->a[r] = ((*z)->a[r] + carry);
	if ((*z)->a[r] < carry) d = 1;

	printf("%d��° ���尣�� ���� ���� �� = ", r);
	word_show_hex((*z)->a[r]);
	printf("\n");
	printf("�߻��� carry = %d\n", d);
	printf("%d��° ���� ���� �� \n", r);
	bi_show_hex(*z);
	printf("\n\n");

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
* @brief M_ADD_print : ���̰� 2�̻��� �� ��ѹ� x,y�� ���ϴ� �Լ� x�� wordlen�� �׻� y�� wordlen �̻��̶�� ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z: ���Ѱ��� ������ ��ѹ� z (z->wordlen = max(x->wordlen, y->wordlen) + 1)
*/
void M_ADD_print(bigint* x, bigint* y, bigint** z) {
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
		c = S_ADDABc_print(x->a[i], y->a[i], z, c, i);


	(*z)->a[x->wordlen] = c;

	if ((*z)->a[x->wordlen] == 0) bi_refine(z);
}

/**
* @brief ADD : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
* @image html add.jpg 
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
	// x > 0 , y < 0 �̸� x + y = x - |y|
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		flip_sign_bi(&y);
		SUB(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	// x < 0 , y > 0 �̸� x + y = -|x| + y = y - |x|
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
* @brief ADD_print : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void ADD_print(bigint* x, bigint* y, bigint** z) {
	// x = 0 �̸� x + y = y
	if (bi_is_zero(x) == 1) {
		printf("Case : x = 0 then x + y = y\n\n");
		bi_assign(z, y);
		return;
	}
	// y = 0 �̸� x + y = x
	if (bi_is_zero(y) == 1)
	{
		printf("Case : y = 0 then x + y = x\n\n");
		bi_assign(z, x);
		return;
	}
	// x > 0 , y < 0 �̸� x + y = x - |y|
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE) {
		printf("Case : x > 0, y < 0 then x + y = x - |y|\n\n");
		flip_sign_bi(&y);
		SUB_print(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	// x < 0 , y > 0 �̸� x + y = -|x| + y = y - |x|
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE) {
		printf("Case : x < 0, y > 0 then x + y = y - |x|\n\n");
		flip_sign_bi(&x);
		SUB_print(y, x, z);
		flip_sign_bi(&x);
		return;
	}
	// x < 0 , y < 0 �϶�
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE) {
		// |x| > |y| �̸� x + y = - (|x| + |y|)
		if (x->wordlen >= y->wordlen) {
			printf("Case : x < 0, y < 0 , |x| > |y| then x + y = -(|x| - |y|)\n\n");
			M_ADD_print(x, y, z);
			flip_sign_bi(z);
			return;
		}
		// |x| < |y| �̸� x + y = - (|y| + |x|)
		else {
			printf("Case : x < 0, y < 0 , |x| < |y| then x + y = -(|y| - |x|)\n\n");
			M_ADD_print(y, x, z);
			flip_sign_bi(z);
			return;
		}
	}
	// x >= y > 0 �� ��
	if (x->wordlen >= y->wordlen) {
		printf("Case : x >= y > 0 then x + y = x + y\n\n");
		M_ADD_print(x, y, z);
		return;
	}
	// y > x > 0 �� ��
	else {
		printf("Case : y > x > 0 then x + y = y + x\n\n");
		M_ADD_print(y, x, z);
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
* @brief S_SUBABb_print : �� ���尣�� ���������ϴ� �Լ� borrow ���� ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �������ϴ� ��ѹ� x
* @param bigint* y : �������ϴ� ��ѹ� y
* @param bigint** z : �� ���� ������ ��ѹ� z
* @param int b : ���� borrow ��
* @param int j : �� ���� z�� j��° �迭�� ����
* @return b (borrow ��)
*/
int S_SUBABb_print(bigint* x, bigint* y, bigint** z, unsigned int b, int j) {

	printf("x�� %d��° ���� = ", j);
	word_show_hex(x->a[j]);
	printf("\n");
	printf("y�� %d��° ���� = ", j);
	word_show_hex(y->a[j]);
	printf("\n");
	printf("������ �߻��� borrow = %d\n", b);

	(*z)->a[j] = x->a[j] - b;

	if (x->a[j] < b)  b = 1;
	else b = 0;

	if ((*z)->a[j] < y->a[j]) b += 1;
	if (j < y->wordlen)
		(*z)->a[j] -= y->a[j];

	printf("%d��° ���尣�� ���� ���� �� = ", j);
	word_show_hex((*z)->a[j]);
	printf("\n");
	printf("�߻��� borrow = %d\n", b);
	printf("%d��° ���� ���� �� \n", j);
	bi_show_hex(*z);
	printf("\n\n");

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
* @brief SUB_C_print : ���̰� 2�̻��� �� ��ѹ� x,y�� ���� �Լ� x�� wordlen�� �׻� y�� wordlen �̻��̶�� ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �������ϴ� ��ѹ� x  (�׻� y ���� ũ�ų� ����)
* @param bigint* y : �������ϴ� ��ѹ� y
* @param bigint** z : �� ���� ������ ��ѹ� z
*/
void SUB_C_print(bigint* x, bigint* y, bigint** z) {

	bi_new(z, x->wordlen);

	y->a = (word*)realloc(y->a, (x->wordlen * sizeof(word)));

	// wordlen�� ���̰� ���ٸ� ���̸�ŭ ª�� ��ѹ��� left word�� 0���� �߰�����
	for (int i = y->wordlen; i < x->wordlen; i++)
		y->a[i] = 0;

	int b = 0;
	for (int j = 0; j < (*z)->wordlen; j++) {
		b = S_SUBABb_print(x, y, z, b, j);
	}
	bi_refine(z);
}


/**
* @brief SUB : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @param bigint* x : �������ϴ� ��ѹ� x
* @param bigint* y : �������ϴ� ��ѹ� y
* @param bigint** z : �� ���� ������ ��ѹ� z
* - Pseudo Code
* @image html sub.jpg
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
	// x = y �̸� x - y = 0
	if (compareAB(x, y) == 0) {
		bi_set_zero(z);
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
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y) == -1) {
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
* @brief SUB_print : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �������ϴ� ��ѹ� x
* @param bigint* y : �������ϴ� ��ѹ� y
* @param bigint** z : �� ���� ������ ��ѹ� z
*/
void SUB_print(bigint* x, bigint* y, bigint** z) {
	// x = 0 �̸� x - y = -y
	if (bi_is_zero(x) == 1) {
		printf("Case : x = 0 then x - y = -y\n\n");
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	// y = 0 �̸� x - y = -x
	if (bi_is_zero(y) == 1) {
		printf("Case : y = 0 then x - y = -x\n\n");
		bi_assign(z, x);
		return;
	}
	// x = y �̸� x - y = 0
	if (compareAB(x, y) == 0) {
		printf("Case : x = y then x - y = 0\n\n");
		bi_set_zero(z);
		return;
	}

	// x >= y > 0 �� ��
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) >= 0) {
		printf("Case : x >= y > 0 then x - y = x - y\n\n");
		SUB_C_print(x, y, z);
		return;
	}
	// y > x > 0 �� ��
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareAB(x, y) == -1) {
		printf("Case : y > x > 0 then x - y = y - x\n\n");
		SUB_C_print(y, x, z);
		flip_sign_bi(z);
		return;
	}
	// 0 >= x > y �� ��
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) >= 0) {
		printf("Case : 0 >= x > y then x - y = |y| - |x|\n\n");
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C_print(y, x, z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	// 0 > y > x �� ��
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NEGATIVE && compareAB(x, y) == -1) {
		printf("Case : 0 > y > x then x - y = - (|x| - |y|)\n\n");
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		SUB_C_print(x, y, z);
		flip_sign_bi(z);
		flip_sign_bi(&x);
		flip_sign_bi(&y);
		return;
	}
	// x > 0 , y < 0 & |x| > |y| �̸� x - y = x + |y|
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y) >= 0) {
		printf("Case : x > 0 ,y < 0 , |x| > |y| then x - y = x + |y|\n\n");
		flip_sign_bi(&y);
		M_ADD_print(x, y, z);
		flip_sign_bi(&y);
		return;
	}
	// x > 0 , y < 0 & |x| < |y| �̸� x - y = |y| + x
	if (get_sign_bi(x) == NONNEGATIVE && get_sign_bi(y) == NEGATIVE && compareABS(x, y) == -1) {
		printf("Case : x > 0 ,y < 0 , |x| < |y| then x - y = |y| + x\n\n");
		flip_sign_bi(&y);
		M_ADD_print(y, x, z);
		flip_sign_bi(&y);
		return;
	}// x < 0 , y > 0 & |x| > |y| �̸� x - y = -(x + y)
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) >= 0) {
		printf("Case : x < 0 ,y > 0 , |x| > |y| then x - y = - (|x| + y)\n\n");
		flip_sign_bi(&x);
		M_ADD_print(x, y, z);
		flip_sign_bi(&x);
		flip_sign_bi(z);
		return;
	}// x < 0 , y > 0 & |x| < |y| �̸� x - y = -(y + x)
	if (get_sign_bi(x) == NEGATIVE && get_sign_bi(y) == NONNEGATIVE && compareABS(x, y) == -1) {
		printf("Case : x < 0 ,y > 0 , |x| < |y| then x - y = - (y + |x|)\n\n");
		flip_sign_bi(&x);
		M_ADD_print(y, x, z);
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
* - Pseudo Code
* @image html mul.jpg
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

	(*z)->sign = (x->sign + y->sign) % 2;
}

/**
* @brief MUL_print : �������� ���Ǵ� ��� ��츦 ó���ϴ� �Լ�
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x :���ϰ����ϴ� ��ѹ� x
* @param bigint* y :���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void MUL_print(bigint* x, bigint* y, bigint** z) {

	// x �Ǵ� y �� 0�̸� x * y = 0
	if (bi_is_zero(x) == 1 || bi_is_zero(y) == 1) {
		printf("Case : x = 0 or y = 0 then x * y = 0\n\n");
		bi_set_zero(z);
		return;
	}
	// x = 1 �̸� x * y = y
	if (bi_is_one(x) == 1) {
		printf("Case : x = 1 then x * y = y\n\n");
		bi_assign(z, y);
		return;
	}
	// x = -1 �̸� x * y = -y
	if (bi_is_one(x) == 1 && get_sign_bi(x) == NEGATIVE) {
		printf("Case : x = -1 then x * y = -y\n\n");
		bi_assign(z, y);
		flip_sign_bi(z);
		return;
	}
	// y = 1 �̸� x * y = x
	if (bi_is_one(y) == 1) {
		printf("Case : y = 1 then x * y = x\n\n");
		bi_assign(z, x);
		return;
	}
	// y = -1 �̸� x * y = -x
	if (bi_is_one(y) == 1 && get_sign_bi(y) == NEGATIVE) {
		printf("Case : y = -1 then x * y = -x\n\n");
		bi_assign(z, x);
		flip_sign_bi(z);
		return;
	}

	printf("Case : x * y = x * y\n\n");
	Schoolbook_MUL_print(x, y, z);

	(*z)->sign = (x->sign + y->sign) % 2;
}

/**
* @brief Schoolbook_MUL : ���̰� 2�̻��� �� ��ѹ� x , y�� ���ϴ� �Լ�
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void Schoolbook_MUL(bigint* x, bigint* y, bigint** z) {
	if ((*z) != NULL)
		bi_delete(z);

	int i, j, k;
	unsigned int c = 0;
	int len_short = 0; int len_long = 0;
	int len;
	bi_new(z, (x->wordlen + y->wordlen));

	if (x->wordlen >= y->wordlen) {
		len_short = y->wordlen;
		len_long = x->wordlen;
	}
	else {
		len_short = x->wordlen;
		len_long = y->wordlen;
	}
	len = len_long + len_short;
	word tmp[2] = { 0, };
	word* tmp_arr = NULL;
	tmp_arr = (word*)calloc(sizeof(word), (len + 1));

	for (i = 0; i < len_long; i++) {
		for (j = 0; j < len_short; j++) {
			if (len_short == y->wordlen)
				MULC(x->a[i], y->a[j], tmp);
			else 
				MULC(x->a[j], y->a[i], tmp);
							
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
		for (k = 0; k < len_short + 1; k++) {
			(*z)->a[i + k] += c;
			c = ((*z)->a[i + k] < c);
			(*z)->a[i + k] += tmp_arr[k];
			c += ((*z)->a[i + k] < tmp_arr[k]);
		}
		memset(tmp_arr, 0, ((len + 1) * sizeof(word)));
	}
	free(tmp_arr);
}

/**
* @brief Schoolbook_MUL_print : ���̰� 2�̻��� �� ��ѹ� x , y�� ���ϴ� �Լ�
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : ���ϰ����ϴ� ��ѹ� x
* @param bigint* y : ���ϰ����ϴ� ��ѹ� y
* @param bigint** z : ���� ���� ������ ��ѹ� z
*/
void Schoolbook_MUL_print(bigint* x, bigint* y, bigint** z) {
	if ((*z) != NULL)
		bi_delete(z);

	int i, j, k;
	unsigned int c = 0;
	int len_short = 0; int len_long = 0;
	int len;
	bi_new(z, (x->wordlen + y->wordlen));

	if (x->wordlen >= y->wordlen) {
		len_short = y->wordlen;
		len_long = x->wordlen;
	}
	else {
		len_short = x->wordlen;
		len_long = y->wordlen;
	}
	len = len_long + len_short;
	word tmp[2] = { 0, };
	word* tmp_arr = NULL;
	tmp_arr = (word*)calloc(sizeof(word), (len + 1));

	for (i = 0; i < len_long; i++) {
		for (j = 0; j < len_short; j++) {
			if (len_short == y->wordlen) {
				MULC(x->a[i], y->a[j], tmp);
				printf("x�� %d��° ���� = ", i);
				word_show_hex(x->a[i]);
				printf("\n");
				printf("y�� %d��° ���� = ", j);
				word_show_hex(y->a[j]);
				printf("\n");
				printf("���尣�� ���� ���� �� = ");
				word_show_hex(tmp[1]);
				word_show_hex(tmp[0]);
				printf("\n");

			}
			else {
				MULC(x->a[j], y->a[i], tmp);
				printf("x�� %d��° ���� = ", j);
				word_show_hex(x->a[j]);
				printf("\n");
				printf("y�� %d��° ���� = ", i);
				word_show_hex(y->a[i]);
				printf("\n");
				printf("���尣�� ���� ���� �� = ");
				word_show_hex(tmp[1]);
				word_show_hex(tmp[0]);
				printf("\n");

			}

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
		for (k = 0; k < len_short + 1; k++) {
			(*z)->a[i + k] += c;
			c = ((*z)->a[i + k] < c);
			(*z)->a[i + k] += tmp_arr[k];
			c += ((*z)->a[i + k] < tmp_arr[k]);
		}
		printf("carry ó���� ������ ���尣�� ���� �߰� �� = ");
		bi_show_hex(*z);
		printf("\n\n");
		memset(tmp_arr, 0, ((len + 1) * sizeof(word)));
	}
	free(tmp_arr);
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


/**
* @brief Squaring_Schoolbook : ����� ����� ��ѹ� ��������
* @param bigint* x  : �����ϰ����ϴ� ��ѹ� x
* @param bigint** z  : ������ ����� �����ϴ� ��ѹ� z
*/
void Squaring_Schoolbook(bigint* x, bigint** z) {

	if ((*z) != NULL)
		bi_delete(z);

	int i = 0;
	int j = 0;
	unsigned int c = 0;
	unsigned int cc = 0;
	bigint* c1 = NULL;
	bigint* c2 = NULL;
	word t1[2] = { 0, };
	word t2[2] = { 0, };

	bi_new(&c1, (2 * x->wordlen));
	bi_new(&c2, (2 * x->wordlen));
	bi_new(z, (2 * x->wordlen));

	//word* tmp_arr = NULL;
	//tmp_arr = (word*)calloc(sizeof(word), (1 + x->wordlen));
	// c1 : �� ������ ������ �������� ����
	for (j = 0; j < x->wordlen; j++) {
		Squaring_word(t1, x->a[j]);

		c1->a[2 * j] += c;
		c = (c1->a[2 * j] < c);

		c1->a[2 * j] += t1[0];
		c += (c1->a[2 * j] < t1[0]);

		c1->a[(2 * j) + 1] += c;
		c = (c1->a[(2 * j) + 1] < c);

		c1->a[(2 * j) + 1] += t1[1];
		c += (c1->a[(2 * j) + 1] < t1[1]);

		// c2 : �ߺ��� ���Ե� ���尣�� ���� ����� ������ ����
		for (i = j + 1; i < x->wordlen; i++) {
			MULC(x->a[j], x->a[i], t2);
			
			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j] < cc);

			c2->a[i + j] += t2[0];
			cc += (c2->a[i + j] < t2[0]);

			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j + 1] < cc);

			c2->a[i + j + 1] += t2[1];
			cc += (c2->a[i + j + 1] < t2[1]);
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
}

/**
* @brief Squaring_Schoolbook_print : ����� ����� ��ѹ� ��������
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x  : �����ϰ����ϴ� ��ѹ� x
* @param bigint** z  : ������ ����� �����ϴ� ��ѹ� z
*/
void Squaring_Schoolbook_print(bigint* x, bigint** z) {

	if ((*z) != NULL)
		bi_delete(z);

	int i = 0;
	int j = 0;
	unsigned int c = 0;
	unsigned int cc = 0;
	bigint* c1 = NULL;
	bigint* c2 = NULL;
	word t1[2] = { 0, };
	word t2[2] = { 0, };

	bi_new(&c1, (2 * x->wordlen));
	bi_new(&c2, (2 * x->wordlen));
	bi_new(z, (2 * x->wordlen));

	//word* tmp_arr = NULL;
	//tmp_arr = (word*)calloc(sizeof(word), (1 + x->wordlen));
	// c1 : �� ������ ������ �������� ����
	for (j = 0; j < x->wordlen; j++) {
		Squaring_word(t1, x->a[j]);

		printf("x�� %d��° ���� = ", j);
		word_show_hex(x->a[j]);
		printf("\n");
		printf("x�� %d��° ���� ���� ��� = ", j);
		word_show_hex(t1[1]);
		word_show_hex(t1[0]);
		printf("\n");

		c1->a[2 * j] += c;
		c = (c1->a[2 * j] < c);

		c1->a[2 * j] += t1[0];
		c += (c1->a[2 * j] < t1[0]);

		c1->a[(2 * j) + 1] += c;
		c = (c1->a[(2 * j) + 1] < c);

		c1->a[(2 * j) + 1] += t1[1];
		c += (c1->a[(2 * j) + 1] < t1[1]);

		printf("carry ó���� ������ c1 �߰� �� = ");
		bi_show_hex(c1);
		printf("\n");
		// c2 : �ߺ��� ���Ե� ���尣�� ���� ����� ������ ����
		for (i = j + 1; i < x->wordlen; i++) {
			MULC(x->a[j], x->a[i], t2);
			printf("x�� %d��° ���� = ", j);
			word_show_hex(x->a[j]);
			printf("\n");
			printf("x�� %d��° ���� = ", i);
			word_show_hex(x->a[i]);
			printf("\n");

			printf("���尣�� ���� ���� �� = ");
			word_show_hex(t2[1]);
			word_show_hex(t2[0]);
			printf("\n");

			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j] < cc);

			c2->a[i + j] += t2[0];
			cc += (c2->a[i + j] < t2[0]);

			c2->a[i + j + 1] += cc;
			cc = (c2->a[i + j + 1] < cc);

			c2->a[i + j + 1] += t2[1];
			cc += (c2->a[i + j + 1] < t2[1]);
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
		printf("carry ó���� ������ c2 �߰� �� = ");
		bi_show_hex(c2);
		printf("\n\n");
	}
	printf("���� c1 = ");
	bi_show_hex(c1);
	printf("\n");
	printf("���� c2 = ");
	bi_show_hex(c2);
	printf("\n");
	bi_leftshift(&c2, 1);
	printf("c2 << 1 = ");
	bi_show_hex(c2);
	printf("\n");
	ADD(c1, c2, z);
	printf("c1 + c2 = ");
	bi_delete(&c1);
	bi_delete(&c2);
}

/**
* @brief SQU : ��ѹ� ��������
* @param bigint* x  : �����ϰ����ϴ� ��ѹ� x
* @param bigint** z  : ������ ����� �����ϴ� ��ѹ� z
* - Pseudo Code
* @image html squ.jpg
*/
void SQU(bigint* x, bigint** z) {

	// x �� 0 �̳� 1 �Ǵ� -1 �� ��
	if (bi_is_zero(x) == 1 || bi_is_one(x) == 1 || bi_is_one(x) == -1) {
		bi_assign(z, x);
		return;
	}
	Squaring_Schoolbook(x, z);
}

/**
* @brief SQU_print : ��ѹ� ��������
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x  : �����ϰ����ϴ� ��ѹ� x
* @param bigint** z  : ������ ����� �����ϴ� ��ѹ� z
*/
void SQU_print(bigint* x, bigint** z) {

	// x �� 0 �̳� 1 �Ǵ� -1 �� ��
	if (bi_is_zero(x) == 1 || bi_is_one(x) == 1 || bi_is_one(x) == -1) {
		bi_assign(z, x);
		return;
	}
	Squaring_Schoolbook_print(x, z);
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

	if (b->sign == NEGATIVE || bi_is_zero(b)) {
		bi_set_zero(q);
		bi_set_zero(r);
		return;
	}
	if (a->sign == NONNEGATIVE && compareAB(b, a) == 1) {
		bi_set_zero(q);
		bi_assign(r, a);
		return;
	}
	if (bi_is_one(b)) {
		bi_assign(q, a);
		bi_set_zero(r);
		return;

	}
	else {
		int max_len = maxlen(a->wordlen, b->wordlen);
		int min_len = minlen(a->wordlen, b->wordlen);
		bigint* tmp = NULL;
		bigint* q_tmp = NULL;
		bigint* one = NULL;
		bi_set_one(&one);
		bi_new(&tmp, b->wordlen + 1);
		bi_new(r, b->wordlen);
		bi_new(q, max_len-min_len + 1);
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

void bi_binary_long_division_print(bigint* a, bigint* b, bigint** q, bigint** r) {

	if (b->sign == NEGATIVE || bi_is_zero(b)) {
		printf(" Y IS NEGATIVE OR ZERO!!\n");
		bi_set_zero(q);
		bi_set_zero(r);
		return;
	}
	if (a->sign == NONNEGATIVE && compareAB(b, a) == 1) {
		bi_set_zero(q);
		bi_assign(r, a);
		return;
	}
	if (bi_is_one(b)) {
		bi_assign(q, a);
		bi_set_zero(r);
		return;

	}

	int max_len = maxlen(a->wordlen, b->wordlen);
	int min_len = minlen(a->wordlen, b->wordlen);
	int aj = 0;
	bigint* tmp = NULL;
	bigint* q_tmp = NULL;
	bigint* one = NULL;
	bi_set_one(&one);
	bi_new(&tmp, b->wordlen + 1);
	bi_new(r, b->wordlen);
	bi_new(q, max_len - min_len + 1);
		for (int i = (a->wordlen) - 1; i >= 0; i--) {
			for (int j = WORD_BITLEN - 1; j >= 0; j--) {
				aj = a->a[i] & ((unsigned long long)1 << j) ? 1 : 0;
				bi_leftshift(&tmp, (unsigned long long)1); tmp->a[0] += aj;
				bi_leftshift(q, (unsigned long long)1);
				if (compareAB(tmp, b) >= 0) {
					SUB(tmp, b, r);
					(*q)->a[0]++;
					bi_assign(&tmp, (*r));
					printf("remainder : ");
					bi_show_hex(tmp);
					printf("\n");
					printf("quotient : ");
					bi_show_hex(*q);
					printf("\n");
				}
			}
		}
		bi_assign(r, tmp);
		if (a->sign == NEGATIVE) {
			printf("If X is NEGATIVE , X = (-Q-1)Y + (B-R)\n");
			bi_assign(&q_tmp, *q);
			flip_sign_bi(&q_tmp);
			SUB(q_tmp, one, q);
			SUB(b, tmp, r);
		}
		bi_delete(&tmp);
		bi_delete(&q_tmp);
		bi_delete(&one);
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
* @brief divcc : 
* @param bigint* x : ������ x = b*q + r
* @param bigint* y : ������ y
* @param bigint** q : a�� b�� ���� ��
* @param bigint** r : a�� b�� ���� ������
*/
void divcc(bigint* x, bigint* y, bigint** q, bigint** r) {
	int x_len = x->wordlen;
	int y_len = y->wordlen;
	bigint* tmp = NULL;
	bigint* r_tmp = NULL;
	bigint* q_tmp = NULL;
	bigint* bq = NULL;
	bigint* one = NULL;
	bigint* a = NULL;
	bigint* b = NULL;
	bi_new(&b, 1);
	bi_new(&a, 2);

	bi_set_one(&one);
	bi_new(&q_tmp, x_len - y_len + 1);
	bi_new(&tmp, 1);
	if (x_len == y_len) {
		(*q)->a[0] = (x->a[x_len - 1] / y->a[y_len - 1]);
	}
	if (x_len == y_len + 1) {
		if (x->a[x_len - 1] == y->a[y_len - 1])
			(*q)->a[0] = MASK;
		else {
			a->a[a->wordlen - 1] = x->a[x->wordlen - 1];
			a->a[a->wordlen - 2] = x->a[x->wordlen - 2];
			b->a[b->wordlen - 1] = y->a[y->wordlen - 1];
			long_division_2word(a, b, q, &tmp);
		}
	}
	MUL(y, (*q), &bq);
	SUB(x, bq, r);
	while ((*r)->sign == NEGATIVE) {
		SUB(*q, one, &q_tmp);
		bi_assign(q, q_tmp);
		ADD(*r, y, &r_tmp);
		bi_assign(r, r_tmp);
	}
	bi_delete(&tmp);
	bi_delete(&r_tmp);
	bi_delete(&q_tmp);
	bi_delete(&bq);
	bi_delete(&one);
	bi_delete(&a);
	bi_delete(&b);

}

/**
* @brief divc :
* @param bigint* x : ������ x = b*q + r
* @param bigint* y : ������ y
* @param bigint** q : a�� b�� ���� ��
* @param bigint** r : a�� b�� ���� ������
*/
void divc(bigint* x, bigint* y, bigint** q, bigint** r) {
	int x_len = x->wordlen;
	int y_len = y->wordlen;
	bigint* y_tmp = NULL;
	bi_new(r, y_len);
	bi_assign(&y_tmp, y);
	int k = 0;
	if (compareAB(y, x) == 1) {
		bi_set_zero(q);
		bi_assign(r, x);
		bi_delete(&y_tmp);
		return;
	}
	while (!((y_tmp->a[y_len - 1] & ((unsigned long long)1 << (WORD_BITLEN - 1))) ? 1 : 0)) {
		y_tmp->a[y_len - 1] = y_tmp->a[y_len - 1] << 1;
		k++;
	}
	bi_delete(&y_tmp);
	bi_leftshift(&x, k);
	bi_leftshift(&y, k);
	divcc(x, y, q, r);
	bi_rightshift(r, k);
	bi_rightshift(&x, k);
	bi_rightshift(&y, k);
	bi_delete(&y_tmp);
}

/**
* @brief bi_div : ��ѹ� ���������� 
* @param bigint* x  : ���������ϴ� ��ѹ� x
* @param bigint* y  : ������ ��ѹ� y
* @param bigint** q  : ���� �����ϴ� ��ѹ� q
* @param bigint** r  : �������� �����ϴ� ��ѹ� r
* - Pseudo Code
* @image html div.jpg
*/
void bi_div(bigint* x, bigint* y, bigint** q, bigint** r) {
	int x_len1 = x->wordlen;
	int y_len1 = y->wordlen;
	bigint* r_tmp1 = NULL;
	bigint* q_tmp1 = NULL;
	bigint* q_tmp = NULL;
	bigint* one = NULL;
	bigint* tmp = NULL;
	bi_set_one(&one);

	if (y->sign == NEGATIVE) {
		bi_set_zero(q);
		bi_set_zero(r);//printf("Invalid operation!!!!");
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}
	if (x->sign == NONNEGATIVE && compareAB(y, x) == 1) {
		bi_set_zero(q);
		bi_assign(r, x);
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}

	if (bi_is_one(y)) {
		bi_assign(q, x);
		bi_set_zero(r);
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}

	//bi_new(r, y_len1);
	bi_new(&r_tmp1, y_len1);
	//bi_new(q, x_len1 - y_len1 + 1);
	bi_new(&q_tmp1, 1);
	bi_set_zero(q);
	bi_set_zero(r);

	for (int i = x_len1 - 1; i >= 0; i--) {
		bi_leftshift(r, WORD_BITLEN);
		(*r)->a[0] += x->a[i];
		bi_assign(&r_tmp1, *r);
		divc(r_tmp1, y, &q_tmp1, r);
		bi_leftshift(q, WORD_BITLEN);
		(*q)->a[0] += q_tmp1->a[0];
	}

	if (x->sign == NEGATIVE) {
		bi_assign(&q_tmp, *q);
		bi_assign(&tmp, *r);
		flip_sign_bi(&q_tmp);
		SUB(q_tmp, one, q);
		SUB(y, tmp, r);

	}
	bi_delete(&q_tmp);
	bi_delete(&tmp);
	bi_delete(&one);
	bi_delete(&r_tmp1);
	bi_delete(&q_tmp1);
}

void bi_div_print(bigint* x, bigint* y, bigint** q, bigint** r) {

	int x_len1 = x->wordlen;
	int y_len1 = y->wordlen;
	bigint* r_tmp1 = NULL;
	bigint* q_tmp1 = NULL;
	bigint* q_tmp = NULL;
	bigint* one = NULL;
	bigint* tmp = NULL;
	bi_set_one(&one);

	if (y->sign == NEGATIVE || bi_is_zero(y)) {
		bi_set_zero(q);
		bi_set_zero(r);
		printf("Y IS NEGATIVE OR ZERO!!!\n");
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}
	if (y->sign == NONNEGATIVE && compareAB(y, x) == 1) {
		bi_set_zero(q);
		bi_assign(r, x);
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}

	if (bi_is_one(y)) {
		bi_assign(q, x);
		bi_set_zero(r);
		bi_delete(&q_tmp);
		bi_delete(&tmp);
		bi_delete(&one);
		bi_delete(&r_tmp1);
		bi_delete(&q_tmp1);
		return;
	}

	//bi_new(r, y_len1);
	bi_new(&r_tmp1, y_len1);
	//bi_new(q, x_len1 - y_len1 + 1);
	bi_new(&q_tmp1, 1);
	bi_set_zero(q);
	bi_set_zero(r);

	for (int i = x_len1 - 1; i >= 0; i--) {
		bi_leftshift(r, WORD_BITLEN);
		(*r)->a[0] += x->a[i];
		bi_assign(&r_tmp1, *r);
		divc(r_tmp1, y, &q_tmp1, r);
		bi_leftshift(q, WORD_BITLEN);
		(*q)->a[0] += q_tmp1->a[0];
		printf("remainder : ");
		bi_show_hex(r_tmp1);
		printf("\n");
		printf("quotient : ");
		bi_show_hex(*q);
		printf("\n");
	}

	if (x->sign == NEGATIVE) {
		bi_assign(&q_tmp, *q);
		bi_assign(&tmp, *r);
		flip_sign_bi(&q_tmp);
		SUB(q_tmp, one, q);
		SUB(y, tmp, r);

	}
	bi_delete(&q_tmp);
	bi_delete(&tmp);
	bi_delete(&one);
	bi_delete(&r_tmp1);
	bi_delete(&q_tmp1);
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
* - Pseudo Code
* @image html l2r.jpg
*/
void left_to_right(bigint* x, bigint** t, int n) {

	int l;
	int ll[100] = { 0, };
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = int_to_binary(n, ll);
	bi_set_one(&tmp);

	for (int i = l - 1; i >= 0; i--) {
		SQU(tmp, &ttmp);
		if (ll[i] == 1) {
			MUL(ttmp, x, &tmp);
			bi_show_hex(tmp);
			printf("\n");
		}
		else bi_assign(&tmp, ttmp);
	}
	bi_assign(t, tmp);
	bi_refine(t);

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_print : Left to Right ����� ��ѹ� ������ ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint** t : ����� ������ ��ѹ� t
* @param int n : x�� ��� �������� �����ִ� ���� n
*/
void left_to_right_print(bigint* x, bigint** t, int n) {

	int l;
	int ll[100] = { 0, };
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	l = int_to_binary(n, ll);

	printf("n�� ��Ʈ���� %d \n", l);
	for (int i = 0; i < l; i++)
		printf("%d", ll[i]);
	printf("\n\n");

	bi_set_one(&tmp);

	for (int i = l - 1; i >= 0; i--) {
		printf("%d��° t ^ 2 �ܰ� ����\n\n", i);
		printf("t = ");
		bi_show_hex(tmp);
		printf("\n");
		SQU(tmp, &ttmp);
		printf("t^2 = ");
		bi_show_hex(ttmp);
		printf("\n");
		if (ll[i] == 1) {
			printf("y�� %d��° ��Ʈ == 1 �̹Ƿ� t * x �ܰ� ����\n\n", i);
			MUL(ttmp, x, &tmp);
			printf("t * x ���� t = ");
			bi_show_hex(tmp);
			printf("\n");
		}
		else bi_assign(&tmp, ttmp);
	}
	bi_assign(t, tmp);
	bi_refine(t);

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_bi : Left to Right ����� ��ѹ� �ŵ����� ����
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint* y : x�� ��� �������� �����ִ� ��ѹ� y
* @param bigint** t : ����� ������ ��ѹ� t
*/
void left_to_right_bi(bigint* x, bigint* y, bigint** t) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = get_bit_length(y);

	bi_new(t, 1);
	(*t)->a[0] = 0x01;

	for (int i = l - 1; i >= 0; i--) {
		bi_assign(&tmp, *t);
		Squaring_Schoolbook(tmp, &ttmp);
		bi_assign(t, ttmp);
		// y�� i��° ��Ʈ�� 1�� ��
		if (bit_of_bi(y, i) == 1) {
			bi_assign(&tmp, *t);
			MUL(tmp, x, &ttmp);
			bi_assign(t, ttmp);
		}
		// y�� i��° ��Ʈ�� 0�� ��
		else;
	}
	// x�� �����̰�, Ȧ���� �����Ҷ� z�� ������ �ȴ�.
	if (x->sign == NEGATIVE && bit_of_bi(y, 0) == 1)
		(*t)->sign = NEGATIVE;

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_bi_print : Left to Right ����� ��ѹ� �ŵ����� ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint* y : x�� ��� �������� �����ִ� ��ѹ� y
* @param bigint** t : ����� ������ ��ѹ� t
*/
void left_to_right_bi_print(bigint* x, bigint* y, bigint** t) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = get_bit_length(y);
	printf("y�� bitlen = %d\n\n", l);

	bi_new(t, 1);
	(*t)->a[0] = 0x01;

	for (int i = l - 1; i >= 0; i--) {
		int a = bit_of_bi(y, i);
		printf("%d", a);
	}
	printf("\n\n");

	for (int i = l - 1; i >= 0; i--) {
		bi_assign(&tmp, *t);
		printf("�������� t = ");
		bi_show_hex(tmp);
		printf("\n\n");
		SQU(tmp, &ttmp);
		printf("�������� t = ");
		bi_show_hex(ttmp);
		printf("\n\n");
		bi_assign(t, ttmp);
		// y�� i��° ��Ʈ�� 1�� ��
		if (bit_of_bi(y, i) == 1) {
			printf("y�� %d��° ��Ʈ == 1 �̹Ƿ� x * t �ܰ� ����\n\n", i);
			bi_assign(&tmp, *t);
			printf("x * t ���� t = ");
			bi_show_hex(tmp);
			printf("\n\n");
			MUL(tmp, x, &ttmp);
			printf("x * t ���� t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(t, ttmp);
		}
		// y�� i��° ��Ʈ�� 0�� ��
		else
			printf("y�� %d��° ��Ʈ == 0 �̹Ƿ� �ƹ� ��ġ ��������\n\n", i);
	}
	// x�� �����̰�, Ȧ���� �����Ҷ�
	if (x->sign == NEGATIVE && bit_of_bi(y, 0) == 1)
		(*t)->sign = NEGATIVE;

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_bi : Left to Right ����� ��ѹ� �ŵ����� ������ ����
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint* y : x�� ��� �������� �����ִ� ��ѹ� y
* @param bigint* b : ��ⷯ ���꿡 ������ �Ǵ� ��ѹ�
* @param bigint** t : ����� ������ ��ѹ� t
* - Pseudo Code
* @image html l2rmod.jpg
*/
void left_to_right_mod_bi(bigint* x, bigint* y, bigint* b, bigint** t) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = get_bit_length(y);

	bi_set_one(t);

	for (int i = l - 1; i >= 0; i--) {
		bi_assign(&tmp, *t);
		SQU(tmp, &ttmp);
		bi_modular(ttmp, b, &tmp);
		bi_assign(t, tmp);
		// y�� i��° ��Ʈ�� 1�� ��
		if (bit_of_bi(y, i) == 1) {
			bi_assign(&ttmp, *t);
			MUL(ttmp, x, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(t, ttmp);
		}
		// y�� i��° ��Ʈ�� 0�� ��
		else;
	}

	// x�� �����̰�, Ȧ���� �����Ҷ� z�� ������ �ȴ�. 
	/*if (x->sign == NEGATIVE && bit_of_bi(y, 0) == 1)
		(*t)->sign = NEGATIVE;*/

	bi_delete(&tmp);
	bi_delete(&ttmp);
}

/**
* @brief left_to_right_mod_bi_print : Left to Right ����� ��ѹ� �ŵ����� ������ ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint* y : x�� ��� �������� �����ִ� ��ѹ� y
* @param bigint* b : ��ⷯ ���꿡 ������ �Ǵ� ��ѹ�
* @param bigint** t : ����� ������ ��ѹ� t
*/
void left_to_right_mod_bi_print(bigint* x, bigint* y, bigint* b, bigint** t) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;

	l = get_bit_length(y);

	bi_new(t, 1);
	(*t)->a[0] = 0x01;

	for (int i = l - 1; i >= 0; i--) {
		bi_assign(&tmp, *t);
		printf("�������� t = ");
		bi_show_hex(tmp);
		printf("\n\n");
		Squaring_Schoolbook(tmp, &ttmp);
		printf("�������� t = ");
		bi_show_hex(ttmp);
		printf("\n\n");
		bi_modular(ttmp, b, &tmp);
		printf("��ⷯ���� t = ");
		bi_show_hex(tmp);
		printf("\n\n");
		bi_assign(t, tmp);
		// y�� i��° ��Ʈ�� 1�� ��
		if (bit_of_bi(y, i) == 1) {
			printf("y�� %d��° ��Ʈ == 1 �̹Ƿ� x * t �ܰ� ����\n\n", i);
			bi_assign(&ttmp, *t);
			printf("t * x ���� t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			MUL(ttmp, x, &tmp);
			printf("t * x ���� t = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_modular(tmp, b, &ttmp);
			printf("��ⷯ���� t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(t, ttmp);
		}
		// y�� i��° ��Ʈ�� 0�� ��
		else
			printf("y�� %d��° ��Ʈ == 0 �̹Ƿ� �ƹ� ��ġ ��������\n\n", i);
	}

	// x�� �����̰�, Ȧ���� �����Ҷ�
	/*if (x->sign == NEGATIVE && bit_of_bi(y, 0) == 1)
		(*t)->sign = NEGATIVE;*/

	bi_delete(&tmp);
	bi_delete(&ttmp);
}


/**
* @brief right_to_left : Right to Left ����� ��ѹ� ������ ����
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint** z : ����� ������ ��ѹ� z
* @param int n : x�� ��� �������� �����ִ� ���� n
* - Pseudo Code
* @image html r2l.jpg
*/
void right_to_left(bigint* x, bigint** z, int n) {

	int l;
	int ll[100] = { 0x00 };
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = int_to_binary(n, ll);

	bi_new(&t0, 1);
	t0->a[0] = 0x01;
	bi_assign(&t1, x);

	for (int i = 0; i < l; i++) {
		// n�� i��° ��Ʈ�� 1�� ��
		if (ll[i] == 1) {
			MUL(t1, t0, &tmp);
			bi_assign(&t0, tmp);
		}
		else;
		SQU(t1, &tmp);
		bi_assign(&t1, tmp);
	}
	bi_assign(z, t0);
	if (x->sign == NEGATIVE && ll[0] == 1)
		(*z)->sign = NEGATIVE;
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief right_to_left_print : Right to Left ����� ��ѹ� ������ ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint** z : ����� ������ ��ѹ� z
* @param int n : x�� ��� �������� �����ִ� ���� n
*/
void right_to_left_print(bigint* x, bigint** z, int n) {

	int l;
	int ll[100] = { 0x00 };
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = int_to_binary(n, ll);

	printf("n�� ��Ʈ���� %d \n", l);
	for (int i = 0; i < l; i++)
		printf("%d", ll[i]);
	printf("\n\n");

	bi_set_one(&t0);
	bi_assign(&t1, x);

	for (int i = 0; i < l; i++) {
		if (ll[i] == 1) {
			printf("y�� %d��° ��Ʈ == 1 -> t1 * t0 �ܰ� ����\n\n", i);
			printf("t0 = ");
			bi_show_hex(t0);
			printf("\n");
			printf("t1 = ");
			bi_show_hex(t1);
			printf("\n");
			MUL(t1, t0, &tmp);
			printf("t1 * t0  = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_assign(&t0, tmp);
		}
		else {
			printf("y�� %d��° ��Ʈ == 0 PASS\n\n", i);

		}
		printf("%d��° t1^2 �ܰ� ����\n\n", i);
		printf("t1 = ");
		bi_show_hex(t1);
		printf("\n");
		SQU(t1, &tmp);
		printf("t1^2 = ");
		bi_show_hex(tmp);
		printf("\n\n");
		bi_assign(&t1, tmp);
	}
	bi_assign(z, t0);
	if (x->sign == NEGATIVE && ll[0] == 1)
		(*z)->sign = NEGATIVE;
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief right_to_left_bi : Right to Left ����� ��ѹ��� ����
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint* y : x�� ��� �������� �����ִ� ��ѹ� y
* @param bigint** z : ����� ������ ��ѹ� z
*/
void right_to_left_bi(bigint* x, bigint* y, bigint** z) {

	int l = 0;
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_set_one(&t0);
	bi_assign(&t1, x);


	for (int i = 0; i < l; i++) {
		// y�� i��° ��Ʈ�� 1�� ��
		if (bit_of_bi(y, i) == 1) {
			MUL(t1, t0, &tmp);
			bi_assign(&t0, tmp);
		}
		else;
		SQU(t1, &tmp);
		bi_assign(&t1, tmp);
	}
	bi_assign(z, t0);
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);

}

/**
* @brief right_to_left_mod_bi : Right to Left ����� ��ѹ� �ŵ����� ������ ����
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint* y : x�� ��� �������� �����ִ� ��ѹ� y
* @param bigint* b : ��ⷯ ���꿡 ������ �Ǵ� ��ѹ�
* @param bigint** z : ����� ������ ��ѹ� z
* - Pseudo Code
* @image html r2lmod.jpg
*/
void right_to_left_mod_bi(bigint* x, bigint* y, bigint* b, bigint** z) {
	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_new(&t0, 1);
	t0->a[0] = 0x01;
	bi_assign(&t1, x);


	for (int i = 0; i < l; i++) {
		// y�� i��° ��Ʈ�� 1�� ��
		if (bit_of_bi(y, i) == 1) {
			MUL(t1, t0, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t0, ttmp);
		}
		else;
		SQU(t1, &tmp);
		bi_modular(tmp, b, &ttmp);
		bi_assign(&t1, ttmp);
	}
	bi_assign(z, t0);
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&ttmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief right_to_left_mod_bi_print : Right to Left ����� ��ѹ� �ŵ����� ������ ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint* y : x�� ��� �������� �����ִ� ��ѹ� y
* @param bigint* b : ��ⷯ ���꿡 ������ �Ǵ� ��ѹ�
* @param bigint** z : ����� ������ ��ѹ� z
*/
void right_to_left_mod_bi_print(bigint* x, bigint* y, bigint* b, bigint** z) {
	int l = 0;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_set_one(&t0);
	bi_assign(&t1, x);


	for (int i = 0; i < l; i++) {
		// y�� i��° ��Ʈ�� 1�� ��
		if (bit_of_bi(y, i) == 1) {
			printf("y�� %d��° ��Ʈ == 1 �̹Ƿ� t0 * t1 �ܰ� ����\n\n", i);
			printf("t0 * t1 ���� t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			MUL(t1, t0, &tmp);
			printf("t * x ���� t = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("��ⷯ���� t = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t0, ttmp);
		}
		else {
			printf("y�� %d��° ��Ʈ == 0 �̹Ƿ� PASS\n\n", i);
		}
		printf("�������� t = ");
		bi_show_hex(t0);
		printf("\n\n");
		SQU(t1, &tmp);
		printf("�������� t = ");
		bi_show_hex(tmp);
		printf("\n\n");
		bi_modular_print(tmp, b, &ttmp);
		printf("��ⷯ���� t = ");
		bi_show_hex(ttmp);
		printf("\n\n");
		bi_assign(&t1, ttmp);
	}
	bi_assign(z, t0);
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&ttmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief Mul_N_Squ : Montgomery Ladder ����� ��ѹ� ������ ����
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint** z : ����� ������ ��ѹ� z
* @param int n : x�� ��� �������� �����ִ� ���� n
* - Pseudo Code
* @image html mns.jpg
*/
void Mul_N_Squ(bigint* x, bigint** z, int n) {

	int l;
	int ll[100] = { 0x00 };
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = int_to_binary(n, ll);

	bi_set_one(&t0);
	bi_assign(&t1, x);
	for (int i = l - 1; i >= 0; i--) {
		// n�� i��° ��Ʈ�� 1�� ��
		if (ll[i] == 1) {
			MUL(t1, t0, &tmp);
			bi_assign(&t0, tmp);
			SQU(t1, &tmp);
			bi_assign(&t1, tmp);
		}
		// n�� i��° ��Ʈ�� 0�� ��
		else {
			MUL(t1, t0, &tmp);
			bi_assign(&t1, tmp);
			SQU(t0, &tmp);
			bi_assign(&t0, tmp);
			
		}
	}
	bi_assign(z, t0);
	bi_refine(z);


	if (x->sign == NEGATIVE && ll[0] == 1)
		(*z)->sign = NEGATIVE;

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief Mul_N_Squ_print : Montgomery Ladder ����� ��ѹ� ������ ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint** z : ����� ������ ��ѹ� z
* @param int n : x�� ��� �������� �����ִ� ���� n
*/
void Mul_N_Squ_print(bigint* x, bigint** z, int n) {

	int l;
	int ll[100] = { 0x00 };
	bigint* tmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = int_to_binary(n, ll);

	printf("n�� ��Ʈ���� %d \n", l);
	for (int i = 0; i < l; i++)
		printf("%d", ll[i]);
	printf("\n\n");

	bi_set_one(&t0);
	printf("���� t0 = ");
	bi_show_hex(t0);
	printf("\n\n");
	bi_assign(&t1, x);
	printf("���� t1 = ");
	bi_show_hex(t1);
	printf("\n\n");
	for (int i = l - 1; i >= 0; i--) {
		// n�� i��° ��Ʈ�� 1�� ��
		if (ll[i] == 1) {
			printf("n�� %d��° ��Ʈ = 1\n\n", ll[i]);
			MUL(t1, t0, &tmp);
			bi_assign(&t0, tmp);
			printf("t0 = t1 * t0 = ");
			bi_show_hex(t0);
			printf("\n\n");
			Squaring_Schoolbook(t1, &tmp);
			bi_assign(&t1, tmp);
			printf("t1 = t1 ^ 2 = ");
			bi_show_hex(t1);
			printf("\n\n");
		}
		// n�� i��° ��Ʈ�� 0�� ��
		else {
			printf("n�� %d��° ��Ʈ = 0\n\n", ll[i]);
			MUL(t1, t0, &tmp);
			bi_assign(&t1, tmp);
			printf("t1 = t1 * t0 = ");
			bi_show_hex(t1);
			printf("\n\n");
			SQU(t0, &tmp);
			bi_assign(&t0, tmp);
			printf("t0 = t0 ^ 2 = ");
			bi_show_hex(t0);
			printf("\n\n");
		}
	}
	bi_assign(z, t0);
	bi_refine(z);


	if (x->sign == NEGATIVE && ll[0] == 1)
		(*z)->sign = NEGATIVE;

	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief Mul_N_Squ_mod_bi : Montgomery Ladder ����� ��ѹ� �ŵ����� ������ ����
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint* y : x�� ��� �������� �����ִ� ��ѹ� y
* @param bigint* b : ��ⷯ ���꿡 ������ �Ǵ� ��ѹ�
* @param bigint** z : ����� ������ ��ѹ� z
* - Pseudo Code
* @image html mnsmod.jpg
*/
void Mul_N_Squ_mod_bi(bigint* x, bigint* y, bigint* b, bigint** z){

	int l;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_set_one(&t0);
	bi_assign(&t1, x);
	for (int i = l - 1; i >= 0; i--) {
		// n�� i��° ��Ʈ�� 1�� ��
		if (bit_of_bi(y, i) == 1) {
			MUL(t1, t0, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t0, ttmp);
			SQU(t1, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t1, ttmp);
		}
		// n�� i��° ��Ʈ�� 0�� ��
		else {
			MUL(t1, t0, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t1, ttmp);
			SQU(t0, &tmp);
			bi_modular(tmp, b, &ttmp);
			bi_assign(&t0, ttmp);
		}
	}
	bi_assign(z, t0);
	bi_refine(z);
	bi_delete(&ttmp);
	bi_delete(&tmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief Mul_N_Squ_mod_bi_print : Montgomery Ladder ����� ��ѹ� �ŵ����� ������ ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : �ŵ������� ��ѹ� x
* @param bigint* y : x�� ��� �������� �����ִ� ��ѹ� y
* @param bigint* b : ��ⷯ ���꿡 ������ �Ǵ� ��ѹ�
* @param bigint** z : ����� ������ ��ѹ� z
*/
void Mul_N_Squ_mod_bi_print(bigint* x, bigint* y, bigint* b, bigint** z) {

	int l;
	bigint* tmp = NULL;
	bigint* ttmp = NULL;
	bigint* t0 = NULL;
	bigint* t1 = NULL;

	l = get_bit_length(y);

	bi_set_one(&t0);
	bi_assign(&t1, x);

	for (int i = l - 1; i >= 0; i--) {
		// n�� i��° ��Ʈ�� 1�� ��
		if (bit_of_bi(y, i) == 1) {
			printf("y�� %d��° ��Ʈ == 1 �̹Ƿ� t0 = t0*t1 & t1 = t1^2\n\n", i);
			printf("t0 * t1 ���� t0 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			MUL(t1, t0, &tmp);
			printf("t0 * t1 ���� t0 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("��ⷯ���� t0 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t0, ttmp);
			printf("t1^2 ���� t1 = ");
			bi_show_hex(t1);
			printf("\n\n");
			SQU(t1, &tmp);
			printf("t1^2 ���� t1 = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("��ⷯ���� t1 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t1, ttmp);
		}
		// n�� i��° ��Ʈ�� 0�� ��
		else {
			printf("y�� %d��° ��Ʈ == 0 �̹Ƿ� t1 = t0*t1 & t0 = t0^2\n\n", i);
			printf("t0 * t1 ���� t1 = ");
			bi_show_hex(t1);
			printf("\n\n");
			MUL(t1, t0, &tmp);
			printf("t0 * t1 ���� t1 = ");
			bi_show_hex(tmp);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("��ⷯ���� t1 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t1, ttmp);
			printf("t0^2 ���� t0 = ");
			bi_show_hex(t1);
			printf("\n\n");
			SQU(t0, &tmp);
			printf("t0^2 ���� t0 = ");
			bi_show_hex(t1);
			printf("\n\n");
			bi_modular_print(tmp, b, &ttmp);
			printf("��ⷯ���� t0 = ");
			bi_show_hex(ttmp);
			printf("\n\n");
			bi_assign(&t0, ttmp);
		}
	}
	bi_assign(z, t0);
	bi_refine(z);

	bi_delete(&tmp);
	bi_delete(&ttmp);
	bi_delete(&t0);
	bi_delete(&t1);
}

/**
* @brief modular : ��ѹ� Modular ����
* @param bigint* x : mod ������ ���� ��ѹ� x
* @param bigint* y : mod�� ������ �Ǵ� ��ѹ� y
* @param bigint** z : ����� ������ ��ѹ� z = x (mod y)
*/
void bi_modular(bigint* x, bigint* y, bigint** z) {
	
	// x�� y�� ���������� r�� z �� ����
	
	bigint* q = NULL;
	bigint* r = NULL;

	if (compareABS(x, y) == -1) {
		bi_assign(z,x);
		return;
	}

	/*if (*z != NULL)
		bi_delete(z);*/
	
	bi_div(x, y, &q, &r);
	bi_assign(z, r);

	bi_delete(&q);
	bi_delete(&r);
}

/**
* @brief bi_modular_print : ��ѹ� Modular ����
* @brief �߰������� �ܼ�â�� ����Ͽ� ���� ���� �� ���� �߻� ���� Ȯ�ΰ���
* @param bigint* x : mod ������ ���� ��ѹ� x
* @param bigint* y : mod�� ������ �Ǵ� ��ѹ� y
* @param bigint** z : ����� ������ ��ѹ� z = x (mod y)
*/
void bi_modular_print(bigint* x, bigint* y, bigint** z) {

	// x�� y�� ���������� r�� z �� ����

	bigint* q = NULL;
	bigint* r = NULL;

	if (compareABS(x, y) == -1) {
		bi_assign(z, x);
		return;
	}

	printf("��ⷯ ����\n\n");
	if (*z != NULL)
		bi_delete(z);
	printf("z �ʱ�ȭ \n\n");

	printf("������ ����\n\n");
	bi_div(x, y, &q, &r);
	printf("��ⷯ ������ ������ �� = ");
	bi_show_hex(r);
	printf("\n\n");
	bi_assign(z, r);
	printf("r�� x�� ������ �� = ");
	bi_show_hex(*z);
	printf("\n\n");

	bi_delete(&q);
	bi_delete(&r);
}

/**
* @date 2020-12-07 09:00
*/


