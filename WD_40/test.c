#pragma once
#include "Arithmetic.h"

/**
* @brief add_test : ���� ������ ���� ��Ȯ�� �׽�Ʈ �ϴ� �Լ�
* @brief ���� : ��ѹ� x �� y �׸��� x + y ���� ������ ��ѹ� z �� ����
* @brief x �� y�� ��ȣ : Random ( NONNEGATIVE or NEGATIVE)
* @brief x �� y�� ��ȣ : Random ( NONNEGATIVE or NEGATIVE)
*/
void add_test(FILE* fp) {
	
	//// 0 �� �� ó���ϴ��� Ȯ��
	//bigint* x = NULL;
	//bigint* y = NULL;
	//bigint* z = NULL;

	//bi_set_zero(&x);
	//bi_gen_rand(&y, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));

	//printf("x=");
	//bi_show_hex(x);
	//printf("\n");
	//printf("y=");
	//bi_show_hex(y);
	//printf("\n");
	//ADD(x, y, &z);

	//printf("x + y ==");
	//bi_show_hex(z);
	//printf("\n");


	//bi_delete(&x);
	//bi_delete(&y);
	//bi_delete(&z);
	
	for (int i = 0; i < TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));
		bi_gen_rand(&y, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));

		fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");

		printf("x=");
		bi_show_hex(x);
		printf("\n");

		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");

		printf("y=");
		bi_show_hex(y);
		printf("\n");

		ADD(x, y, &z);
	
		printf("x + y ==");
		bi_show_hex(z);
		printf("\n");

		fputs("print(x + y ==",fp);
		File_print(z,fp);
		fputs(")", fp);
		fprintf(fp, "\n");
		
		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

void sub_test(FILE* fp) {
	/*
	// 0 �϶� ó���ϴ� �� Ȯ��
	bigint* x = NULL;
	bigint* y = NULL;
	bigint* z = NULL;

	bi_set_zero(&x);
	bi_gen_rand(&y, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));

	printf("x=");
	bi_show_hex(x);
	printf("\n");
	printf("y=");
	bi_show_hex(y);
	printf("\n");
	SUB(x, y, &z);

	printf("x - y ==");
	bi_show_hex(z);
	printf("\n");


	bi_delete(&x);
	bi_delete(&y);
	bi_delete(&z);
	*/
	
	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));
		bi_gen_rand(&y, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));

		fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");

		printf("x=");
		bi_show_hex(x);
		printf("\n");

		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");

		printf("y=");
		bi_show_hex(y);
		printf("\n");

		SUB(x, y, &z);

		printf("x - y ==");
		bi_show_hex(z);
		printf("\n");

		fputs("print(x - y ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

void  mul_test(FILE* fp) {


	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));
		bi_gen_rand(&y, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));

		fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");

		printf("x=");
		bi_show_hex(x);
		printf("\n");

		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");

		printf("y=");
		bi_show_hex(y);
		printf("\n");

		MUL(x, y, &z);

		printf("x * y ==");
		bi_show_hex(z);
		printf("\n");

		fputs("print(x * y ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

void Ka_mul_test(FILE* fp) {

	
	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;

		bi_gen_rand(&x, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));
		bi_gen_rand(&y, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));

		fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");

		printf("x=");
		bi_show_hex(x);
		printf("\n");

		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");

		printf("y=");
		bi_show_hex(y);
		printf("\n");

		karatsuba_MUL(x, y, &z);

		printf("x * y ==");
		bi_show_hex(z);
		printf("\n");

		fputs("print(x * y ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

void bi_binary_long_division_test() {

	for (int i = 0; i < TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* q = NULL;
		bigint* r = NULL;

		bi_gen_rand(&x, rand() % 2, 5);
		bi_gen_rand(&y, rand() % 2, 3);
		bi_binary_long_division(x, y, &q, &r);
		if (bi_is_zero(q) && bi_is_zero(r)) {
			//printf(" Invalid Operation or X is Zero !");
			bi_delete(&x);
			bi_delete(&y);
			bi_delete(&q);
			bi_delete(&r);
		}
		else {
			bi_show_hex(x); printf("=="); printf("("); bi_show_hex(y);
			printf(" * ");
			bi_show_hex(q); printf(")"); printf("+");
			bi_show_hex(r); printf("\n");

			bi_delete(&x);
			bi_delete(&y);
			bi_delete(&q);
			bi_delete(&r);
		}


	}

}

void long_division_2word_test() {
	for (int i = 0; i < 100; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* q = NULL;
		bigint* r = NULL;
		bi_gen_rand(&x, NONNEGATIVE, 2);
		bi_gen_rand(&y, NONNEGATIVE, 1);
		if (x->a[1] >= y->a[0]) {
		}
		else {
			long_division_2word(x, y, &q, &r);
			bi_show_hex(x); printf("=="); printf("("); bi_show_hex(y);
			printf(" * ");
			bi_show_hex(q); printf(")"); printf("+");
			bi_show_hex(r); printf("\n");
		}
		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&q);
		bi_delete(&r);
	}
}

void Squaring_test(FILE* fp) {


	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* z = NULL;
		/* ���ϴ� �迭�� Ȯ�� �ϰ� ���� �� ���*/
		/*bi_gen_rand(&x, 1);
		word arr[7] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
		bi_set_by_array(&x, NONNEGATIVE, arr, 7);*/

		bi_gen_rand(&x, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));

		fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");

		printf("x=");
		bi_show_hex(x);
		printf("\n");

		Squaring_Schoolbook(x, &z);

		printf("power(x,2) ==");
		bi_show_hex(z);
		printf("\n");

		fputs("print(x * x ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");

		bi_delete(&x);
		bi_delete(&z);

	}
}

void Exponentiation_test(FILE* fp) {
	

	for (int i = 0; i <= TEST; i++) {
		
		bigint* x = NULL;
		bigint* z = NULL;
		
		/*
		//���ϴ� �迭�� Ȯ�� �ϰ� ���� �� ���
		bi_gen_rand(&x, rand() % 2, 1);
		word arr[1] = { 0x81 };
		bi_set_by_array(&x, NONNEGATIVE, arr, 1);
		*/


		//bi_gen_rand(&x, 3);
		//int n = 10;

		bi_gen_rand(&x, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));
		int n = ((rand() % UPPERBOUND) + LOWERBOUND);

		fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");

		printf("x=");
		bi_show_hex(x);
		printf("\n");

		fputs("n=", fp);
		fprintf(fp, "%d", n);
		fprintf(fp, "\n");

		printf("n=%d\n", n);

		left_to_right(x, &z, n);

		printf("power(x,n) ==");
		bi_show_hex(z);
		printf("\n");

		fputs("print(power(x,n) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");

		bi_delete(&x);
		bi_delete(&z);
	}
}

void Exponentiation_bi_test(FILE* fp) {


	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL;
		bigint* y = NULL;
		bigint* z = NULL;
		/* ���ϴ� �迭�� Ȯ�� �ϰ� ���� �� ���*/
		/*bi_gen_rand(&x, 1);
		word arr[7] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
		bi_set_by_array(&x, NONNEGATIVE, arr, 7);*/

		//bi_gen_rand(&x, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));
		//bi_gen_rand(&y, NONNEGATIVE, (((rand() % UPPERBOUND) + LOWERBOUND) / 5));
		bi_gen_rand(&x, rand() % 2, 5);
		bi_gen_rand(&y, NONNEGATIVE, 1);

		fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");

		printf("x=");
		bi_show_hex(x);
		printf("\n");

		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");

		printf("y=");
		bi_show_hex(y);
		printf("\n");

		left_to_right_bi(x, y, &z);

		printf("power(x,y) ==");
		bi_show_hex(z);
		printf("\n");

		fputs("print(power(x,y) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&z);
	}
}

void Exponentiation_Modular_bi_test(FILE* fp) {


	for (int i = 0; i <= TEST; i++) {
		bigint* x = NULL; // �ŵ����� �� ��
		bigint* y = NULL; // �ŵ����� Ƚ ��
		bigint* z = NULL; // ��� ���� �� ��
		bigint* p = NULL; // mod ���� �� ����(=��)

		/* ���ϴ� �迭�� Ȯ�� �ϰ� ���� �� ���*/
		/*bi_gen_rand(&x, 1);
		word arr[7] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
		bi_set_by_array(&x, NONNEGATIVE, arr, 7);*/

		bi_gen_rand(&x, rand() % 2, ((rand() % UPPERBOUND) + LOWERBOUND));
		bi_gen_rand(&y, NONNEGATIVE, ((rand() % UPPERBOUND) + LOWERBOUND));
		bi_gen_rand(&p, NONNEGATIVE, ((rand() % UPPERBOUND) + LOWERBOUND));
		//bi_gen_rand(&y, NONNEGATIVE, 2);
		//bi_gen_rand(&p, NONNEGATIVE, 2);

		fputs("x=", fp);
		File_print(x, fp);
		fprintf(fp, "\n");

		printf("x=");
		bi_show_hex(x);
		printf("\n");

		fputs("y=", fp);
		File_print(y, fp);
		fprintf(fp, "\n");

		printf("y=");
		bi_show_hex(y);
		printf("\n");

		fputs("p=", fp);
		File_print(p, fp);
		fprintf(fp, "\n");

		printf("p=");
		bi_show_hex(p);
		printf("\n");
		
		left_to_right_mod_bi(x, y, p, &z);

		printf("power_mod(x,y,p) ==");
		bi_show_hex(z);
		printf("\n");

		fputs("print(power_mod(x,y,p) ==", fp);
		File_print(z, fp);
		fputs(")", fp);
		fprintf(fp, "\n");

		bi_delete(&x);
		bi_delete(&y);
		bi_delete(&p);
		bi_delete(&z);
	}
}

