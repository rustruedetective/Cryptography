#include<iostream>
#include<math.h>
#define BS 64 // at end

using namespace std;

void IP(bool * input) // Initial Permutation
{
	int ip[BS] = {58, 50, 42, 34, 26, 18, 10,  2,
			 	  60, 52, 44, 36, 28, 20, 12,  4,
				  62, 54, 46, 38, 30, 22, 14,  6,
				  64, 56, 48, 40, 32, 24, 16,  8,
				  57, 49, 41, 33, 25, 17,  9,  1,
				  59, 51, 43, 35, 27, 19, 11,  3,
				  61, 53, 45, 37, 29, 21, 13,  5,
				  63, 55, 47, 39, 31, 23, 15,  7};
	bool tempx[BS] = {0};

	for(int i = 0; i < BS ; i++){ tempx[i] = input[ip[i]-1]; }
	for(int i = 0; i < BS ; i++){ input[i] = tempx[i]; }
}

void IPInv(bool * input) // Final Permutation
{
	int ipinv[BS] = {40,  8, 48, 16, 56, 24, 64, 32,
					 39,  7, 47, 15, 55, 23, 63, 31,
					 38,  6, 46, 14, 54, 22, 62, 30,
					 37,  5, 45, 13, 53, 21, 61, 29,
					 36,  4, 44, 12, 52, 20, 60, 28,
					 35,  3, 43, 11, 51, 19, 59, 27,
					 34,  2, 42, 10, 50, 18, 58, 26,
					 33,  1, 41,  9, 49, 17, 57, 25};
	bool tempx[BS] = {0};

	for(int i = 0; i < BS ; i++){ tempx[i] = input[ipinv[i]-1]; }
	for(int i = 0; i < BS ; i++){ input[i] = tempx[i]; }
}

void KEYPC_1(const bool * key64, bool * key56)
{
	int pc_1[56] = {57, 49, 41, 33, 25, 17,  9,  1,
					58, 50, 42, 34, 26, 18, 10,  2,
					59, 51, 43, 35, 27, 19, 11,  3,
					60, 52, 44, 36, 63, 55, 47, 39,
					31, 23, 15,  7, 62, 54, 46, 38,
					30, 22, 14,  6, 61, 53, 45, 37,
					29, 21, 13,  5, 28, 20, 12,  4};


	for(int i = 0 ; i < 56 ; i++){ key56[i] = key64[pc_1[i]-1]; }
}

void KEYPC_2(bool * key56, bool * key48)
{
	int pc_2[48] = {14, 17, 11, 24,  1,  5,  3, 28,
					 15,  6, 21, 10, 23, 19, 12,  4,
					 26,  8, 16,  7, 27, 20, 13,  2,
					 41, 52, 31, 37, 47, 55, 30, 40,
					 51, 45, 33, 48, 44, 49, 39, 56,
					 34, 53, 46, 42, 50, 36, 29, 32};


	for(int i = 0 ; i < 48 ; i++){ key48[i] = key56[pc_2[i]-1]; }
}

void KeySchedE(bool * internkey, bool * key48, int index)
{
	if(index == 1 || index == 2 || index == 9 || index ==16)
	{
		bool tempkrotate = internkey[0], tempkrotate2 = internkey[28];
		for(int i = 0; i < 28; i++)
		{
			internkey[i] = internkey[i+1];
			internkey[i + 28] = internkey[i + 28 + 1];
		}
		internkey[27] = tempkrotate; internkey[55] = tempkrotate2;
	}
	else
	{
		bool tempkrotate11 = internkey[0], tempkrotate12 = internkey[1], tempkrotate21 = internkey[28], tempkrotate22 = internkey[29];
		for(int i = 0; i < 28; i++)
		{
			internkey[i] = internkey[i+2];
			internkey[i + 28] = internkey[i + 28 + 2];
		}
		internkey[26] = tempkrotate11; internkey[27] = tempkrotate12; internkey[54] = tempkrotate21; internkey[55] = tempkrotate22;
	}

	KEYPC_2(internkey, key48);
}

void KeySchedD(bool * internkey, bool * key48, int index)
{
	if(index == 1)
	{
		// do no rotation
	}
	else if(index == 2 || index == 9 || index == 16)
	{
		bool tempkrotate = internkey[27],  tempkrotate2 = internkey[55];
		for(int i = 27; i >= 0; i--)
		{
			internkey[i] = internkey[i-1];
			internkey[i + 28] = internkey[i + 28 - 1];
		}
		internkey[0] = tempkrotate; internkey[28] = tempkrotate2;
	}
	else
	{
		bool tempkrotate11 = internkey[26],tempkrotate12= internkey[27],tempkrotate21 = internkey[54],  tempkrotate22= internkey[55];
		for(int i = 27; i >= 0; i--)
		{
			internkey[i] = internkey[i-2];
			internkey[i + 28] = internkey[i + 28 - 2];
		}
		internkey[0] = tempkrotate11; internkey[1] = tempkrotate12; internkey[28] = tempkrotate21; internkey[29] = tempkrotate22;
	}

	KEYPC_2(internkey, key48);
}

void EXPBOX(bool * right, bool * right48)
{
	int expbox[48] = {32,  1,  2,  3,  4,  5,
					    4,  5,  6,  7,  8,  9,
					    8,  9, 10, 11, 12, 13,
					   12, 13, 14, 15, 16, 17,
					   16, 17, 18, 19, 20, 21,
					   20, 21, 22, 23, 24, 25,
					   24, 25, 26, 27, 28, 29,
					   28, 29, 31, 31, 32,  1};


	for(int i = 0; i < 48 ; i++){ right48[i] = right[expbox[i]-1]; }
}

void PERBOX(bool * right)
{
	int perbox[32] = {16,  7, 20, 21, 29, 12, 28, 17,
					   1, 15, 23, 26,  5, 18, 31, 10,
					   2,  8, 24, 14, 32, 27,  3,  9,
					  19, 13, 30,  6, 22, 11,  4, 25};
	bool tempright[32] = {0};


	for(int i = 0; i < 32 ; i++){ tempright[i] = right[perbox[i]-1]; }
	for(int i = 0; i < 32 ; i++){ right[i] = tempright[i]; }
}

void sbox(bool * sboxin, bool * sboxout, int index)
{
	int s[8][4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
						0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
						4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
						15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
					{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
					  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
					  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
					  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
					{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
					 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
					 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
					 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
					{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
					 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
					 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
					 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
					{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
					 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
					 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
					 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
					{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
					 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
					 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
					 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
					{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
					 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
					 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
					 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
					{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
					 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
					 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
					 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};
	int sboxoutint = s[index][sboxin[0]*2 + sboxin[5]*1][sboxin[1]*8 + sboxin[2]*4 + sboxin[3]*2 + sboxin[4]*1];


	for(int i = 1; i <= 4 ; i++){ sboxout[4-i] = (bool)( (sboxoutint/(int)pow(2, i-1))%2 ); }
}

f_function(bool * right , const bool * key48)
{
	bool right48[48] = {0};
	bool sboxin[6] = {0};
	bool sboxout[4] = {0};

	EXPBOX(right, right48);
	
	for(int i = 0; i < 48 ; i++){ right48[i] = key48[i] ^ right48[i]; }
	for(int i = 0; i < 8 ; i++)
		{ for(int j = 0; j < 6 ; j++){ sboxin[j] = right48[j + i*6]; }
		  sbox(sboxin, sboxout, i);
		  for(int j = 0; j < 4 ; j++){ right[j + i*4] = sboxout[j]; } }

	PERBOX(right);
}

void Round(bool * left, bool * right, const bool * key48)
{
	//AREA CLOSED WORKING
	//for(int i = 0; i < 32; i++)
	//{
		//right[i] = !right[i];
		//left[i] = !left[i];
	//}

	bool templeft[32] = {0};
	for(int i = 0; i < 32; i++){ templeft[i] = right[i]; }

	//AREA CLOSED WORKING
	//for(int i = 0; i < 32; i++){ right[i] = left[i];; }

	f_function(right , key48);
	for(int i = 0; i < 32; i++){ right[i] = left[i] ^ right[i]; }

	for(int i = 0; i < 32; i++){ left[i] = templeft[i]; }
}

void RoundEnginesE(bool * input,  bool * key56)
{
	//AREA CLOSED WORKING
	//for(int i = 0; i < BS; i++)
	//{
		//input[i] = key[i] ^ input[i];
	//}

	bool right[32] = {0};
	bool left[32] = {0};
	bool key48[48] = {0};

	for(int i = 0; i < 64 ; i++){ left[i] = input[i]; right[i] = input[i+32]; }

	for(int i = 1; i <= 16; i++)
	{
		KeySchedE(key56, key48, i);
		Round(left, right, key48);
	}

	for(int i = 0; i < BS/2 ; i++){ input[i] = right[i]; input[i+32] = left[i]; }
}

void RoundEnginesD(bool * input,  bool * key56)
{
	//AREA CLOSED WORKING
	//for(int i = 0; i < BS; i++)
	//{
		//input[i] = key[i] ^ input[i];
	//}

	bool right[32] = {0};
	bool left[32] = {0};
	bool key48[48] = {0};

	for(int i = 0; i < 64 ; i++){ left[i] = input[i]; right[i] = input[i+32]; }

	for(int i = 1; i <= 16 ; i++)
	{
		KeySchedD(key56, key48, i);
		Round(left, right, key48);
	}

	for(int i = 0; i < BS/2 ; i++){ input[i] = right[i]; input[i+32] = left[i]; }
}

void desE(bool * input, const bool * key64) // DES Encryption
{
	bool key56[56] ={0};

	//ALGORITHM
	IP(input);
	KEYPC_1(key64, key56);
	RoundEnginesE(input, key56);
	IPInv(input);
}

void desD(bool * input, const bool * key64) // DES Decryption
{
	bool key56[56] ={0};
	
	//ALGORITHM
	IP(input);
	KEYPC_1(key64, key56);
	RoundEnginesD(input, key56);	
	IPInv(input);
}

int main()
{
	bool input[64] = {0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,
				  0,0,0,1,1,0,0,0,
				  0,0,0,1,1,0,0,0,
				  0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0};
	bool key64[64] = {1,0,0,0,0,0,0,0,
				  1,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,1};

	desE(input, key64);
	desD(input, key64);

	cout << endl;
	for(int i = 0 ; i < BS ; i++) // output
	{
		if(i%8 == 0)
			cout << endl;
		cout << input[i] << " ";
	}
	cout << endl;
}