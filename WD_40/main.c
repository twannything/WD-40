#define _CRT_SECURE_NO_WARNINGS
#include "Basic Operation.h"
#include "Arithmetic.h"
//#include <vld.h> // �޸� ������ Ȯ�� �ϰ� ������ ���

/** @mainpage BIGINT LIBRARY : WD-40
* @section devleoper ������
* - ���¿�, ������
* @image html 1.jpg
* @section advenced  ���߸���
* - C��� �Թ��ڵ��� ���� ���α׷��� �ǽ� ������
* @version ver 1.0
* @date 2020.12.05
*/

int main() {

	errno_t err;
	FILE* fp = NULL;
	err = fopen_s(&fp, "C:\\Users\\user\\Desktop\\data.sage", "w");//���� ��°��� �´��� Ȯ���ϴ� �Լ��̴�.
	if (fp == NULL) {
		puts("���� ���� ����\n");
		return -1;
	}
	//add_test(fp);
	//sub_test(fp);
	//mul_test(fp);
	//Ka_mul_test(fp);
	//bi_binary_long_division_test(fp);
	//long_division_2word_test(fp);
	//divcc_test();
	//div_test();
	//divc_test();
	//Squaring_test(fp);
	L2R_test(fp);
	//L2R_bi_test(fp);
	//L2R_Modular_bi_test(fp);
	//R2L_test(fp);
	//R2L_bi_test(fp);
	//R2L_Modular_bi_test(fp);
	//Mul_N_Squ_test(fp);
	//Mul_N_Squ_bi_test(fp);
	//Mul_N_Squ_mod_bi_test(fp);
}
