#include<iostream>
#include<math.h>
using namespace std;

void sbox(bool * x , bool * y)
{
	uint8_t xh = 0, yh = 0;
	bool xy[8] = {0};
	uint8_t sbox[0x10][0x10] =
	{
		//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F

		0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,		//0
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,		//1
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,		//2
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,		//3
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,		//4
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,		//5
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,		//6
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,		//7
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,		//8
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,		//9
		0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,		//A
		0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,		//B
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,		//C
		0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,		//D
		0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,		//E
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16		//F 
	};

	xh = x[0]*8 + x[1]*4 + x[2]*2 + x[3]*1;
	yh = y[0]*8 + y[1]*4 + y[2]*2 + y[3]*1;

	for(int i = 1; i <= 8 ; i++){ xy[8-i] = (bool)( (sbox[xh][yh]/(int)pow(2, i-1))%2 ); }
		
	//WORK IN PROGRESS -- SUCCESS
	//if(xh == 4 && yh == 0)
	//{
		//cout << endl;
		//for(int k =0 ; k < 8 ; k++)
			//cout << xy[k];
		//cout << endl;
	//}
	
	x[0] = xy[0];
	x[1] = xy[1];
	x[2] = xy[2];
	x[3] = xy[3];

	y[0] = xy[4];
	y[1] = xy[5];
	y[2] = xy[6];
	y[3] = xy[7];
}

void sboxInv(bool * x , bool * y)
{
	uint8_t xh = 0, yh = 0;
	bool xy[8] = {0};
	uint8_t sboxInv[0x10][0x10] =
		//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F

	{ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb		//0
	, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb		//1
	, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e		//2
	, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25		//3
	, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92		//4
	, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84		//5
	, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06		//6
	, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b		//7
	, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73		//8
	, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e		//9
	, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b		//A
	, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4		//B
	, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f		//C
	, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef		//D
	, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61		//E
	, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d		//F 
	};

	xh = x[0]*8 + x[1]*4 + x[2]*2 + x[3]*1;
	yh = y[0]*8 + y[1]*4 + y[2]*2 + y[3]*1;

	for(int i = 1; i <= 8 ; i++){ xy[8-i] = (bool)( (sboxInv[xh][yh]/(int)pow(2, i-1))%2 ); }

	x[0] = xy[0];
	x[1] = xy[1];
	x[2] = xy[2];
	x[3] = xy[3];

	y[0] = xy[4];
	y[1] = xy[5];
	y[2] = xy[6];
	y[3] = xy[7];
}

void subBytes(bool state[4][4][8])
{
	bool x[4] = {0};
	bool y[4] = {0};

	for(int i = 0; i < 16 ; i++)
	{
		x[0] = state[i/4][i%4][0]; x[1] = state[i/4][i%4][1]; x[2] = state[i/4][i%4][2]; x[3] = state[i/4][i%4][3];
		y[0] = state[i/4][i%4][4]; y[1] = state[i/4][i%4][5]; y[2] = state[i/4][i%4][6]; y[3] = state[i/4][i%4][7];

		sbox(x , y);

		state[i/4][i%4][0] = x[0]; state[i/4][i%4][1] = x[1]; state[i/4][i%4][2] = x[2]; state[i/4][i%4][3] = x[3];
		state[i/4][i%4][4] = y[0]; state[i/4][i%4][5] = y[1]; state[i/4][i%4][6] = y[2]; state[i/4][i%4][7] = y[3];
	}
}

void subBytesInv(bool state[4][4][8])
{
	bool x[4] = {0};
	bool y[4] = {0};

	for(int i = 0; i < 16 ; i++)
	{
		x[0] = state[i/4][i%4][0]; x[1] = state[i/4][i%4][1]; x[2] = state[i/4][i%4][2]; x[3] = state[i/4][i%4][3];
		y[0] = state[i/4][i%4][4]; y[1] = state[i/4][i%4][5]; y[2] = state[i/4][i%4][6]; y[3] = state[i/4][i%4][7];

		sboxInv(x , y);

		state[i/4][i%4][0] = x[0]; state[i/4][i%4][1] = x[1]; state[i/4][i%4][2] = x[2]; state[i/4][i%4][3] = x[3];
		state[i/4][i%4][4] = y[0]; state[i/4][i%4][5] = y[1]; state[i/4][i%4][6] = y[2]; state[i/4][i%4][7] = y[3];
	}
}

void shiftRows(bool state[4][4][8])
{
	bool temp[4][4][8] = {0};
	for(int i =0 ; i < 128 ; i ++)
				temp[i/32][(i%32)/8][i%8] = state[i/32][(i%32)/8][i%8];

	for(int l = 0; l < 8 ; l++)
	{
		state[0][1][l] = temp[1][1][l]; // shift first box of temp up
		state[1][1][l] = temp[2][1][l];
		state[2][1][l] = temp[3][1][l];
		state[3][1][l] = temp[0][1][l];

		state[0][2][l] = temp[2][2][l];
		state[1][2][l] = temp[3][2][l];
		state[2][2][l] = temp[0][2][l];
		state[3][2][l] = temp[1][2][l];

		state[0][3][l] = temp[3][3][l];
		state[1][3][l] = temp[0][3][l];
		state[2][3][l] = temp[1][3][l];
		state[3][3][l] = temp[2][3][l];
	}
}

void shiftRowsInv(bool state[4][4][8])
{
	bool temp[4][4][8] = {0};
	for(int i =0 ; i < 128 ; i ++)
				temp[i/32][(i%32)/8][i%8] = state[i/32][(i%32)/8][i%8];
	
	for(int r = 0; r < 8 ; r++)
	{
		state[0][1][r] = temp[3][1][r]; // shift first box of temp down
		state[1][1][r] = temp[0][1][r];
		state[2][1][r] = temp[1][1][r];
		state[3][1][r] = temp[2][1][r];

		state[0][2][r] = temp[2][2][r];
		state[1][2][r] = temp[3][2][r];
		state[2][2][r] = temp[0][2][r];
		state[3][2][r] = temp[1][2][r];

		state[0][3][r] = temp[1][3][r];
		state[1][3][r] = temp[2][3][r];
		state[2][3][r] = temp[3][3][r];
		state[3][3][r] = temp[0][3][r];
	}
}

uint8_t gfmul(uint8_t a, uint8_t b)		// multiplication in rijndael field
{
	uint8_t p = 0; /* the product of the multiplication */
	while (b) {
		if (b & 1) /* if b is odd, then add the corresponding a to p (final product = sum of all a's corresponding to odd b's) */
			p ^= a; /* since we're in GF(2^m), addition is an XOR */

		if (a & 0x80) /* GF modulo: if a >= 128, then it will overflow when shifted left, so reduce */
			a = (a << 1) ^ 0x11b; /* XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) – you can change it but it must be irreducible */
		else
			a <<= 1; /* equivalent to a*2 */
		b >>= 1; /* equivalent to b // 2 */
	}
	return p;
}

void mixCols(bool state[4][4][8])
{
	uint8_t  state2[4][4] = { 0 };
	uint8_t mixcolumnMatrix[4][4] = { { 2, 3, 1, 1 },
	{ 1, 2, 3, 1 },
	{ 1, 1, 2, 3 },
	{ 3, 1, 1, 2 } };
	uint8_t temp[4][4] = { 0 };

	for(int i = 0; i < 16 ; i ++)
	{
		state2[i/4][i%4] = state[i/4][i%4][0]*128 + state[i/4][i%4][1]*64 + state[i/4][i%4][2]*32 + state[i/4][i%4][3]*16 + 
							state[i/4][i%4][4]*8 + state[i/4][i%4][5]*4 + state[i/4][i%4][6]*2 + state[i/4][i%4][7]*1;
	}

	for (int column = 0; column < 4; column++)
	{
		for (int i = 0; i < 4; ++i)
		{
			temp[column][i] = gfmul(state2[column][0], mixcolumnMatrix[i][0]) ^ gfmul(state2[column][1], mixcolumnMatrix[i][1]) ^ gfmul(state2[column][2], mixcolumnMatrix[i][2]) ^ gfmul(state2[column][3], mixcolumnMatrix[i][3]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			state2[i][j] = temp[i][j];
		}
	}

	for(int i = 0; i < 16 ; i ++)
	{
		for(int j = 1; j <= 8 ; j++){ state[i/4][i%4][8-j] = (bool)( (state2[i/4][i%4]/(int)pow(2, j-1))%2 ); }
	}
}

void mixColsInv(bool state[4][4][8])
{
	uint8_t  state2[4][4] = { 0 };
	uint8_t a = 0, b = 0, c = 0, d = 0;

	for(int i = 0; i < 16 ; i ++)
	{
		state2[i/4][i%4] = state[i/4][i%4][0]*128 + state[i/4][i%4][1]*64 + state[i/4][i%4][2]*32 + state[i/4][i%4][3]*16 + 
							state[i/4][i%4][4]*8 + state[i/4][i%4][5]*4 + state[i/4][i%4][6]*2 + state[i/4][i%4][7]*1;
	}

	for (int i = 0; i < 4; i++)
	{
		a = state2[i][0];
		b = state2[i][1];
		c = state2[i][2];
		d = state2[i][3];
		state2[i][0] = gfmul(a, 0x0e) ^ gfmul(b, 0x0b) ^ gfmul(c, 0x0d) ^ gfmul(d, 0x09);
		state2[i][1] = gfmul(a, 0x09) ^ gfmul(b, 0x0e) ^ gfmul(c, 0x0b) ^ gfmul(d, 0x0d);
		state2[i][2] = gfmul(a, 0x0d) ^ gfmul(b, 0x09) ^ gfmul(c, 0x0e) ^ gfmul(d, 0x0b);
		state2[i][3] = gfmul(a, 0x0b) ^ gfmul(b, 0x0d) ^ gfmul(c, 0x09) ^ gfmul(d, 0x0e);
	}

	for(int i = 0; i < 16 ; i ++)
	{
		for(int j = 1; j <= 8 ; j++){ state[i/4][i%4][8-j] = (bool)( (state2[i/4][i%4]/(int)pow(2, j-1))%2 ); }
	}
}

void keyPerRound(bool * keyEx, bool key16[4][4][8] , int whichKey)
{
	for(int g = 0; g < 128 ; g++)
	{
		key16[g/32][(g%32)/8][g%8] = *(keyEx + g + whichKey*128 );
	}
}

void keyExpand(bool * key, bool * keyEx, int rounds)
{
	bool word1[32] = {0};
	bool word2[32] = {0};
	bool word3[32] = {0};
	bool word4[32] = {0};
	bool temp[8] = {0};
	bool x[4] = {0};
	bool y[4] = {0};
	uint8_t RC = 0;
	bool RCB[8] = {0};

	for(int i = 0 ; i < 128 ; i++)
		{*(keyEx + i) = key[i];} // verified
	for(int i = 0 ; i < 32 ; i++)
	{
		word1[i] = key[i];
		word2[i] = key[i + 32];
		word3[i] = key[i + 64];
		word4[i] = key[i + 96];
	}

	for(int s = 1; s <= rounds; s++)
	{
		// G function :-
		for(int i =0 ; i <8 ; i++)
		{
			temp[i] = word1[i];

			word4[i   ] = word4[i+8 ];
			word4[i+8 ] = word4[i+16];
			word4[i+16] = word4[i+24];
			word4[i+24] = word4[i   ];
		}

		for(int t = 0 ; t < 4 ; t ++)
		{
			for(int i = 0 ; i < 4 ; i ++)
			{
				x[i] = word4[i + t*8];
				y[i] = word4[i + 4 + t*8];
			}

			sbox(x, y);

			for(int i = 0 ; i < 4 ; i ++)
			{
				word4[i] = x[i + t*8];
				word4[i+4] = y[i + t*8];
			}
		}

		switch(s)
		{
			case 1:
				RC = 0x01;
			break;
			case 2:
				RC = 0x02;
			break;
			case 3:
				RC = 0x04;
			break;
			case 4:
				RC = 0x08;
			break;
			case 5:
				RC = 0x10;
			break;
			case 6:
				RC = 0x20;
			break;
			case 7:
				RC = 0x40;
			break;
			case 8:
				RC = 0x80;
			break;
			case 9:
				RC = 0x1B;
			break;
			case 10:
				RC = 0x36;
			break;
			case 11:
				RC = 0x6C;
			break;
			case 12:
				RC = 0xD8;
			break;
			case 13:
				RC = 0xAB;
			break;
			case 14:
				RC = 0x4D;
			break;
			case 15:
				RC = 0x9A;
			break;
		}
		for(int q = 1; q <= 8 ; q++){ RCB[8-q] = (bool)( (RC/(int)pow(2, q-1))%2 ); }
		for(int t = 0 ; t < 8 ; t ++)
		{
			word4[t] = word4[t] ^ RCB[t];
		}

		for(int u = 0; u < 32 ; u++)
		{
			word1[u] = word1[u] ^ word4[u];
			word2[u] = word2[u] ^ word1[u];
			word3[u] = word3[u] ^ word2[u];
			word4[u] = word4[u] ^ word3[u];
		}

		for(int i =0 ; i < 32 ; i ++)
			{
				*(keyEx + i + s*128) = word1[i];
				*(keyEx + i + 32 + s*128) = word2[i];
				*(keyEx + i + 64 + s*128) = word3[i];
				*(keyEx + i + 96 + s*128) = word4[i];
			}
	}
}

void addkey(bool state[4][4][8], bool key16[4][4][8])
{
	for(int i =0 ; i < 128 ; i ++)
				state[i/32][(i%32)/8][i%8] = state[i/32][(i%32)/8][i%8] ^ key16[i/32][(i%32)/8][i%8];
}

void RoundE(bool state[4][4][8])
{
	subBytes(state);
	shiftRows(state);
	mixCols(state);
}

void RoundD(bool state[4][4][8])
{
	mixColsInv(state);
	shiftRowsInv(state);
	subBytesInv(state);
}

void lastRoundE(bool state[4][4][8])
{
	subBytes(state);
	shiftRows(state);
}

void firstRoundD(bool state[4][4][8])
{
	shiftRowsInv(state);
	subBytesInv(state);
}

void aesE(bool * stream128, bool * key, int rounds)
{
	bool state[4][4][8] = {0};
	bool keyEx[(rounds+1)*(4)*(4)*(8)] = {0};
	bool key16[4][4][8] = {0};

	for(int i = 0 ; i < 128 ; i++)
	{
		state[i/32][(i%32)/8][i%8] = stream128[i];
	}

	keyExpand(key , keyEx, rounds);
	
	keyPerRound(keyEx, key16, 0);
	addkey(state, key16);
	for(int i = 1; i <= rounds-1 ; i++)
	{
		RoundE(state);
		keyPerRound(keyEx, key16, i);
		addkey(state, key16);
	}
	lastRoundE(state);
	keyPerRound(keyEx, key16, rounds);
	addkey(state, key16);

	for(int i = 0 ; i < 128 ; i++)
	{
		stream128[i] = state[i/32][(i%32)/8][i%8];
	}
}

void aesD(bool * stream128, bool * key, int rounds)
{
	bool state[4][4][8] = {0};
	bool keyEx[(rounds+1)*(4)*(4)*(8)] = {0};
	bool key16[4][4][8] = {0};

	for(int i = 0 ; i < 128 ; i++)
	{
		state[i/32][(i%32)/8][i%8] = stream128[i];
	}

	keyExpand(key , keyEx, rounds);

	keyPerRound(keyEx, key16, rounds);
	addkey(state, key16);
	firstRoundD(state);
	keyPerRound(keyEx, key16, rounds-1);
	addkey( state, key16);
	for(int i = rounds-2; i >=0 ; i--)
	{
		RoundD(state);
		keyPerRound(keyEx, key16, i);
		addkey( state, key16);
	}

	for(int i = 0 ; i < 128 ; i++)
	{
		stream128[i] = state[i/32][(i%32)/8][i%8];
	}
}

int main()
{
	bool stream128[128] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
							0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
							0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,
							0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,
							0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,
							0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,
							0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
							0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0};

	bool key[256] = {	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
							0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
							0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,
							0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,
							0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,
							0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,
							0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
							0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
						 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
							0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
							0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,
							0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,
							0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,
							0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,
							0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
							0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0};
	int rounds = sizeof(key);
	

	aesE(stream128, key, rounds);
	aesD(stream128, key, rounds);

	cout << endl;
	for(int i = 0 ; i < 128 ; i++) // output
	{
		if(i%16 == 0)
			cout << endl;
		cout << stream128[i] << " ";
	}
	cout << endl;
}