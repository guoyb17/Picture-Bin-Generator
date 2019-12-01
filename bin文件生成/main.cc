#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

// [NOTE] Please set input header file and size BELOW!
#include "test.h"
#define X_SIZE 520
#define Y_SIZE 520
#define ARR_NAME test
#define OUT_NAME "test.bin"
// [NOTE] Please set input header file and size ABOVE!

int main() {
	FILE* fp = fopen(OUT_NAME, "wb");

	//char temp[9];
	//int i, j, count = 0;

	// Registers' Usage:
	// $1: current color info
	// $2: current graph mem addr
	// $3: graph mem line start: 0x BA00 0000 + i * 800
	// $4: pixiv per line: 800

	//addiu    $3, $0, 0xba00
	//unsigned int addiu = 0x2403ba00;

	//// addiu $4, $0, 800
	//unsigned int initChange = 0x24040320;

	//// addu $3, $3, $4
	//unsigned int addLine = 0x632021;

	//// addiu $2, $3, 0
	//unsigned int updateAddr = 0x24620000;

	////sll    $2, $3, 16
	////unsigned int sll = 201728;

	////sll    $3, $3, 16
	//unsigned int sll1 = 0x31c00;

	////address: addiu $2, $0, 0x1
	//unsigned int addiuAddr = 604110849;

	//// sb $1, 0($2)
	//unsigned int sb = 2688614400;

	//fwrite(&addiu, sizeof(addiu), 1, fp);
	//fwrite(&initChange, sizeof(initChange), 1, fp);
	////fwrite(&sll, sizeof(sll), 1, fp);
	//fwrite(&sll1, sizeof(sll1), 1, fp);
	//fwrite(&updateAddr, sizeof(updateAddr), 1, fp);

	int cnt = 0;
	for (int i = Y_SIZE - 1; i >= 0; i--) {
		for (int j = 0; j < X_SIZE; j++) {
			// unsigned int temp = 0010 0100 0010 0000 0000 0000 ____ ____;
			unsigned char temp = 0;

			/*unsigned char temp = ((test_pic_cut[i] >> 5) << 5) | ((test_pic_cut[i + 1] >> 6) << 3) || (test_pic_cut[i + 2] >> 5);*/
			temp += (((ARR_NAME[(i * X_SIZE + j) * 3 + 54] >> 7) % 2) << 1);
			temp += (ARR_NAME[(i * X_SIZE + j) * 3 + 54] >> 6) % 2;
			//temp += (((ARR_NAME[(i * X_SIZE + j) * 3 + 54] >> 5) % 2) << 5);
			temp += (((ARR_NAME[(i * X_SIZE + j) * 3 + 54 + 1] >> 7) % 2) << 4);
			temp += (((ARR_NAME[(i * X_SIZE + j) * 3 + 54 + 1] >> 6) % 2) << 3);
			temp += (((ARR_NAME[(i * X_SIZE + j) * 3 + 54 + 1] >> 5) % 2) << 2);
			temp += (((ARR_NAME[(i * X_SIZE + j) * 3 + 54 + 2] >> 7) % 2) << 7);
			temp += (((ARR_NAME[(i * X_SIZE + j) * 3 + 54 + 2] >> 6) % 2) << 6);
			temp += (((ARR_NAME[(i * X_SIZE + j) * 3 + 54 + 2] >> 5) % 2) << 5);

			fwrite(&temp, sizeof(temp), 1, fp); // addiu $1, $0, ____
			cnt++;
			//fwrite(&sb, sizeof(sb), 1, fp);
			//fwrite(&addiuAddr, sizeof(addiuAddr), 1, fp);
		}
		for (int j = X_SIZE; j < 800; j++) {
			unsigned char temp = 0;
			fwrite(&temp, sizeof(temp), 1, fp);
			cnt++;
		}
	}
	for (int i = Y_SIZE; i < 600; i++) for (int j = 0; j < 800; j++) {
		unsigned char temp = 0;
		fwrite(&temp, sizeof(temp), 1, fp);
		cnt++;
	}

	// unsigned int jr = 0000 0011 1110 0000 0000 0000 0000 1000;
	// 1000 0000 0000 0000 0000 1110 0011 0000
	//unsigned int jr = 0x3e00008;

	//// unsigned int nop = 0000 0000 0000 0000 0000 0000 0000 0000;
	//unsigned int nop = 0;

	//fwrite(&jr, sizeof(jr), 1, fp);
	//fwrite(&nop, sizeof(nop), 1, fp);

	fclose(fp);
	std::cout << "cnt = " << cnt << std::endl;

	return 0;
}
