//수정판

#include <stdio.h>

int plainBlock[64] = { 0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,1,1,0 };

int InitialPermutationTable[64] =  // 초기 치환표
{ 58,50,42,34,26,18,10,2,
  60,52,44,36,28,20,12,4,
  62,54,46,38,30,22,14,6,
  64,56,48,40,32,24,16,8,
  57,49,41,33,25,17, 9,1,
  59,51,43,35,27,19,11,3,
  61,53,45,37,29,21,13,5,
  63,55,47,39,31,23,15,7 };

int FinalPermutationTable[64] =         // 최종 치환표
{ 40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25 };

int ExpansionPermutationTable[48] =             // 확장 P-박스 표
{ 32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1 };

int StraightPermutationTable[32] =                    // 단순 치환표
{ 16,  7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26,  5, 18, 31, 10,
    2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25 };

int ParityDropTable[56] =                            // 패리티 제거 표
{ 57,49,41,33,25,17,9,1,
58,50,42,34,26,18,10,2,
59,51,43,35,27,19,11,3,
60,52,44,36,63,55,47,39,
31,23,15,7,62,54,46,38,
30,22,14,6,61,53,45,37,
29,21,13,5,28,20,12,4 };

int KeyCompressionTable[48] =                         // 키 감축 표
{
   14, 17, 11, 24,  1,  5,
   3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};

int ShiftTable[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

int SubstitutionTables[8][4][16] = {           // S-박스
    
    {
        { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
        { 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
        { 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
        { 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
    },

    {
        { 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
        { 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
        { 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
        { 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
    },
    
    {
        { 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
        { 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
        { 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
        { 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
    },
   
    {
        { 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
        { 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
        { 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
        { 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
    },
    
    {
        { 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
        { 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
        { 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
        { 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
    },
    
    {
        { 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
        { 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
        { 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
        { 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
    },
    
    {
        { 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
        { 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
        { 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
        { 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
    },
   
    {
        { 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
        { 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
        { 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
        { 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
    }
};




int inBlock[64];
int leftBlock[32];
int rightBlock[32];
int outBlock[32];
int n;
int a[];
int b[];

int Roundkey[64] = { 1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,1,1,1,0,0,1,1,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1 };
// AABB09182736CCDD   1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,1,1,1,0,0,1,1,0,1,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0
// 1010101010111011000010010001100000100111001101101101000000000000

int row;
int col;
int value;
int T[32];
int cipherBlock[64];

void permute(int n1, int n2, int a[], int b[], int Table[]);
void split(int n1, int n2, int inBlock[], int leftBlock[32], int rightBlock[32]); // split 함수 통과하고나면 64bit inBlock이 leftBlock에 32bit, rightBlock에 32bit씩
void combine(int n1, int n2, int leftBlock[], int rightBlock[], int outBlock[]); // 합쳐준다
void mixer(int leftBlock[48], int rightBlock[48], int roundkey[48]);
void copy(int n, int a[], int b[]);
void exclusiveOr(int n, int T1[], int roundkey[], int T2[]);
void function(int inBlock[32], int RoundKey[32], int outBlock[32]);
void substitute(int inBlock[32], int outBlock[48], int SubstitutionTables[8][4][16]); // s박스 통과시키는 부분
void swapper(int leftBlock[32], int rigthBlock[32]);
void ShiftLeft(int block[28], int numOfShifts);
void Key_Generator(int keyWithParities[64], int RoundKeys[16][48], int ShiftTable[16]);
void Cipher(int plainblock[64], int RoundKeys[16][48], int cipherBlock[64]);

int main()
{
    int Roundkeys[16][48];
   
    Key_Generator(Roundkey, Roundkeys, ShiftTable);
    
    printf("\n=============== 평문 =================\n");
    for (int i = 0; i < 64; i++)
    {
        printf("%d", plainBlock[i]);
    }
    printf("\n==============InitialPermutationTable에 permute =============\n");
    permute(64, 64, plainBlock, inBlock, InitialPermutationTable);


    for (int i = 0; i < 64; i++)
    {
        printf("%d", inBlock[i]);
    }


    
    split(64, 32, inBlock, leftBlock, rightBlock);
    printf("\n==============split left Block==============\n"); // inBlock을 leftBlock과 rightBlock에 split
    for (int i = 0; i < 32; i++)
    {
        printf("%d", leftBlock[i]);
    }
    printf("\n==============split right Block==============\n");
    for (int i = 0; i < 32; i++)
    {
        printf("%d", rightBlock[i]);
    }                               // 까지 성공
    printf("\n\n");
    for (int round = 0; round < 16; round++)
    {
        
        printf("\n================= Round %d =================\n",round+1);
        mixer(leftBlock, rightBlock, Roundkeys[round]);
        printf("============ Mixer lefttblock ==============\n");
        for (int i = 0; i < 32; i++)
        {
            printf("%d", leftBlock[i]);
        }
        printf("\n============= Mixer rightblock =============\n");
        for (int i = 0; i < 32; i++)
        {
            printf("%d", rightBlock[i]);
        }



        swapper(leftBlock, rightBlock);
        printf("\n=========== Swapper leftBlock ==============\n");
        for (int i = 0; i < 32; i++)
        {
            printf("%d", leftBlock[i]);
        }

        printf("\n============ Swapper rightBlock ============\n");
        for (int i = 0; i < 32; i++)
        {
            printf("%d", rightBlock[i]);
        }
        printf("\n================ Round key =================\n");
        
            for (int j = 0; j < 48; j++)
            {
                printf("%d", Roundkeys[round][j]);

            }
            printf("\n\n");
        }
    printf("\n============================ CIPER TEXT =============================\n");
    Cipher(plainBlock, Roundkeys, cipherBlock);
    for (int i = 0; i < 64; i++) {
        printf("%d", cipherBlock[i]);
    }
    printf("\n=====================================================================\n\n");
    return 0;

}

/*printf("\n\n==============InitialPermutationTable에 permute =============\n\n");
permute(plainBlock, inBlock, InitialPermutationTable); -> permute(64,64,plainBlock,inBlock,i~~~)


permute(56, 48, preRoundKey, RoundKeys[i], KeyCompressionTable); */
// 테이블이 48,
void permute(int n1, int n2, int a[], int b[], int Table[]) // plainblcok이 intitialPermutationTable에 섞이고 inBlock으로 들어감
{
    a[n1];
    b[n2];
    for (int i = 0; i < n2; i++)
    {
        b[i] = a[Table[i] - 1];
    }
}

//  split(64,32,inBlock, leftBlock, rightBlock);
void split(int n1,int n2,int inBlock[], int leftBlock[32], int rightBlock[32])
{
    for (int i = 0; i < n2; i++) // 32
    {
        leftBlock[i] = inBlock[i];
    }
    for (int i = n2; i < n1; i++) // 64
    {
        rightBlock[i - n2] = inBlock[i];
    }
}
void combine(int n1, int n2, int leftBlock[], int rightBlock[], int outBlock[])
{
    for (int i = 0; i < n1; i++)
    {
        outBlock[i] = leftBlock[i];
    }
    for (int i = n1; i < n2; i++)
    {
        outBlock[i] = rightBlock[i-n1];
    }
    // combine(28, 56, leftKey, rightKey, preRoundKey);  
}

void mixer(int leftBlock[48], int rightBlock[48], int roundkey[48])
{
    int T1[48];
    int T2[48];
    int T3[48];
    copy(32, rightBlock, T1);                // rightBlock을 T1에 넣음
    function(T1, roundkey, T2);              // T1을 rounkey에 넣어서 결과를 T2에 넣음 , f함수 돌려서 xor로 보냄
    exclusiveOr(32, leftBlock, T2, T3);      //leftBlock을 t2와 xor시켜서 결과를 T3에 넣음
    copy(32,T3, leftBlock);                 // T3를 다시 rightBlock에 넣음 X 의사코드 오류 leftblock에 줘야됨 
}

void copy(int n, int a[], int b[])
{
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
}
void function(int inBlock[32], int RoundKey[48], int outBlock[32]) {
    int T1[48];
    int T2[48];
    int T3[32];
    permute(32,48,inBlock, T1, ExpansionPermutationTable);
    exclusiveOr(48, T1, RoundKey, T2);
    substitute(T2, T3, SubstitutionTables);  // s 박스통과시키는부분
    permute(32,32,T3, outBlock, StraightPermutationTable);
}

void exclusiveOr(int n, int T1[], int roundkey[], int T2[])
{
    for (int i = 0; i < n; i++)
    {
        T2[i] = T1[i] ^ roundkey[i];
    }                                    
}

void substitute(int inBlock[32], int outBlock[48], int SubstitutionTables[8][4][16]) // s박스 통과시키는 부분
{
   
    for (int i = 0; i < 8; i++)
    {
        row = 2 * inBlock[i * 6 + 0] + inBlock[i * 6 + 5];
        col = 8 * inBlock[i * 6 + 1] + 4 * inBlock[i * 6 + 2] + 2 * inBlock[i * 6 + 3] + inBlock[i * 6 + 4];  

        // 처음꺼 마지막꺼 중간에꺼 4개 10진수로 바꿔주는역할 
        
        value = SubstitutionTables[i][row][col];                      //해당i번째 박스에 row col값을 value로 뽑아냄

        outBlock[i * 4 + 0] = value / 8;
        value = value % 8;
        outBlock[i * 4 + 1] = value / 4;
        value = value % 4;
        outBlock[i * 4 + 2] = value / 2;
        value = value % 2;
        outBlock[i * 4 + 3] = value;                            // 도움
         
                //비트로 바꿔주는 연산
    }
}
void swapper(int leftBlock[32], int rightBlock[32])
{
    copy(32, leftBlock, T);
    copy(32, rightBlock, leftBlock);
    copy(32, T, rightBlock);
}


void Key_Generator(int keyWithParities[64], int RoundKeys[16][48], int ShiftTable[16])
{
    int cipherKey[56]; /// 56
    int leftKey[28];
    int rightKey[28];
    int preRoundKey[56];
    

    permute(64,56,keyWithParities, cipherKey, ParityDropTable);  // parity 제거
    split(56,28,cipherKey, leftKey, rightKey);
    for (int i = 0; i < 16; i++)
    {
        ShiftLeft(leftKey, ShiftTable[i]);
        ShiftLeft(rightKey, ShiftTable[i]);
        combine(28, 56, leftKey, rightKey, preRoundKey);                 // 작성중 combine 함수 끝나고 다시옴
        permute(56, 48, preRoundKey, RoundKeys[i], KeyCompressionTable);
    }
}

void ShiftLeft(int block[28], int numOfShifts)
{
    
    int T;
    for (int i = 0; i < numOfShifts; i++)
    {
        T = block[0];                          // 첫번째를 t에다가 빼놓음
        for (int j = 1; j < 28; j++)
        {
            block[j-1] = block[j];
        }
        block[27] = T;
    }
}
void Cipher(int plainblock[64], int RoundKeys[16][48], int cipherBlock[64])
{
    permute(64, 64, plainBlock, inBlock, InitialPermutationTable);
    split(64, 32, inBlock, leftBlock, rightBlock);
    for (int i = 0; i < 16; i++)
    {
        mixer(leftBlock, rightBlock, RoundKeys[i]);
        if (i != 15) swapper(leftBlock, rightBlock);
    }
    combine(32, 64, leftBlock, rightBlock, outBlock);
    permute(64, 64, outBlock, cipherBlock, FinalPermutationTable);
}
/* void Cipher(int plainBlock[64], int RoundKeys[16][48], int cipherBlock[64]) {
    int inBlock[64], leftBlock[32], rightBlock[32], outBlock[64];
    permute(64, 64, plainBlock, inBlock, InitialPermutationTable);
    split(64, 32, inBlock, leftBlock, rightBlock);
    for (int round = 0; round < 16; round++) {
        mixer(leftBlock, rightBlock, RoundKeys[round]);
        if (round != 15) {
            swapper(leftBlock, rightBlock);
        }
    }
    combine(32, 64, leftBlock, rightBlock, outBlock);
    permute(64, 64, outBlock, cipherBlock, FinalPermutationTable);*/