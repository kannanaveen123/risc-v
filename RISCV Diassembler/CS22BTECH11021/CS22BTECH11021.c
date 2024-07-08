#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20
char func7[8] = "", rs2[6] = "", rs1[6] = "", rd[6] = "", func3[4] = "", imm_6_11[7] = "";
int reg1 = 0, reg2 = 0, dreg = 0, immed = 0, size_B = 0, address_B[MAX], size_J = 0, address_J[MAX];
int decimal(char *binary)
{
    int ans = 0, i = 0, a = 2048;
    int b = 1;
    if (strlen(binary) == 5)
    {
        a = 16;
        b = 0;
    }
    else if (strlen(binary) == 6)
    {
        a = 32;
    }
    else if (strlen(binary) == 20)
    {
        a = 524288;
        b = 0;
    }
    while (binary[i] != '\0')
    {
        ans = ans + (binary[i] - '0') * a;
        a = a / 2;
        i++;
    }

    if ((ans > 2047) && b == 1)
    {
        ans = ans - 4096;
    }
    return ans;
}
void convert(char *binary_digits)
{
    for (int i = 0; i < 32; i++)
    {
        if (i <= 6)
        {
            func7[i] = binary_digits[i];
        }
        else if (i >= 7 && i <= 11)
        {
            rs2[i - 7] = binary_digits[i];
        }
        else if (i >= 12 && i <= 16)
        {
            rs1[i - 12] = binary_digits[i];
        }
        else if (i >= 17 && i <= 19)
        {
            func3[i - 17] = binary_digits[i];
        }
        else if (i >= 20 && i <= 24)
        {
            rd[i - 20] = binary_digits[i];
        }
    }
    char imm[13] = "";
    strcat(imm, func7);
    strcat(imm, rs2);
    for (int i = 0; i < 6; i++)
    {
        imm_6_11[i] = imm[i];
    }
    reg1 = decimal(rs1);
    reg2 = decimal(rs2);
    dreg = decimal(rd);
    immed = decimal(imm);
}
void R_TYPE()
{
    if (strcmp(func7, "0000000") == 0 && strcmp(func3, "000") == 0)
    {
        printf("add x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
    else if (strcmp(func7, "0100000") == 0 && strcmp(func3, "000") == 0)
    {
        printf("sub x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
    else if (strcmp(func7, "0000000") == 0 && strcmp(func3, "100") == 0)
    {
        printf("xor x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
    else if (strcmp(func7, "0000000") == 0 && strcmp(func3, "110") == 0)
    {
        printf("or x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
    else if (strcmp(func7, "0000000") == 0 && strcmp(func3, "111") == 0)
    {
        printf("and x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
    else if (strcmp(func7, "0000000") == 0 && strcmp(func3, "001") == 0)
    {
        printf("sll x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
    else if (strcmp(func7, "0000000") == 0 && strcmp(func3, "101") == 0)
    {
        printf("srl x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
    else if (strcmp(func7, "0100000") == 0 && strcmp(func3, "101") == 0)
    {
        printf("sra x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
    else if (strcmp(func7, "0000000") == 0 && strcmp(func3, "010") == 0)
    {
        printf("slt x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
    else if (strcmp(func7, "0000000") == 0 && strcmp(func3, "011") == 0)
    {
        printf("sltu x%d,x%d,x%d\n", dreg, reg1, reg2);
    }
}
void I_TYPE(char *opcode)
{
    // if (label_index != -1)
    // {
    //     printf("L%d :", label_index + 1);
    // }
    if (strcmp(opcode, "0000011") == 0)
    {
        if (strcmp(func3, "000") == 0)
        {
            printf("lb x%d,%d(x%d)\n", dreg, immed, reg1);
        }
        else if (strcmp(func3, "001") == 0)
        {
            printf("lh x%d,%d(x%d)\n", dreg, immed, reg1);
        }
        else if (strcmp(func3, "010") == 0)
        {
            printf("lw x%d,%d(x%d)\n", dreg, immed, reg1);
        }
        else if (strcmp(func3, "011") == 0)
        {
            printf("ld x%d,%d(x%d)\n", dreg, immed, reg1);
        }
        else if (strcmp(func3, "100") == 0)
        {
            printf("lbu x%d,%d(x%d)\n", dreg, immed, reg1);
        }
        else if (strcmp(func3, "101") == 0)
        {
            printf("lhu x%d,%d(x%d)\n", dreg, immed, reg1);
        }
        else if (strcmp(func3, "110") == 0)
        {
            printf("lwu x%d,%d(x%d)\n", dreg, immed, reg1);
        }
    }
    else if (strcmp(opcode, "1100111") == 0)
    {
        printf("jalr x%d,x%d,%d\n", dreg, reg1, immed);
    }
    else
    {
        int immed1 = decimal(imm_6_11) * 64;
        if (strcmp(func3, "000") == 0)
        {
            printf("addi x%d,x%d,%d\n", dreg, reg1, immed);
        }
        else if (strcmp(func3, "100") == 0)
        {
            printf("xori x%d,x%d,%d\n", dreg, reg1, immed);
        }
        else if (strcmp(func3, "110") == 0)
        {
            printf("ori x%d,x%d,%d\n", dreg, reg1, immed);
        }
        else if (strcmp(func3, "111") == 0)
        {
            printf("andi x%d,x%d,%d\n", dreg, reg1, immed);
        }
        else if (strcmp(func3, "001") == 0 && strcmp(imm_6_11, "000000") == 0)
        {
            printf("slli x%d,x%d,%d\n", dreg, reg1, immed - immed1);
        }
        else if (strcmp(func3, "101") == 0 && strcmp(imm_6_11, "000000") == 0)
        {
            printf("srli x%d,x%d,%d\n", dreg, reg1, immed - immed1);
        }
        else if (strcmp(func3, "101") == 0 && strcmp(imm_6_11, "010000") == 0)
        {
            printf("srai x%d,x%d,%d\n", dreg, reg1, immed - immed1);
        }
        else if (strcmp(func3, "010") == 0)
        {
            printf("slti x%d,x%d,%d\n", dreg, reg1, immed);
        }
        else if (strcmp(func3, "011") == 0)
        {
            printf("sltiu x%d,x%d,%d\n", dreg, reg1, immed);
        }
    }
}
void S_TYPE()
{
    char imm_11_5[8], imm_4_0[6];
    char imm[13] = "";
    strcpy(imm_11_5, func7);
    strcpy(imm_4_0, rd);
    strcat(imm, func7);
    strcat(imm, rd);
    immed = decimal(imm);
    if (strcmp(func3, "000") == 0)
    {
        printf("sb x%d,%d(x%d)\n", reg2, immed, reg1);
    }
    else if (strcmp(func3, "001") == 0)
    {
        printf("sh x%d,%d(x%d)\n", reg2, immed, reg1);
    }
    else if (strcmp(func3, "010") == 0)
    {
        printf("sw x%d,%d(x%d)\n", reg2, immed, reg1);
    }
    else if (strcmp(func3, "011") == 0)
    {
        printf("sd x%d,%d(x%d)\n", reg2, immed, reg1);
    }
}
void B_TYPE(char *binary_digits, int k)
{
    char imm[15] = "";
    imm[0] = '0';
    int b = 0;
    imm[1] = binary_digits[24];
    for (int i = 1; i < 7; i++)
    {
        imm[i + 1] = binary_digits[i];
        if (7 + i < 11)
        {
            imm[7 + i] = binary_digits[19 + i];
        }
    }
    int var = decimal(imm) * 2;
    int a = -1;
    int f = 0;
    while (f < size_B)
    {
        if (address_B[f] == k + var / 4)
        {

            break;
        }
        f++;
    }
    if ((k + var / 4) < 20)
    {
        a = 0;
        if (f == size_B)
        {
            address_B[size_B] = k + var / 4;
            size_B++;
        }
    }
    if (strcmp(func3, "000") == 0)
    {
        if (a == -1)
            printf("beq x%d,x%d,%d\n", reg1, reg2, var);
        else if (f == size_B)
            printf("beq x%d,x%d,L%d\n", reg1, reg2, size_B);
        else
            printf("beq x%d,x%d,L%d\n", reg1, reg2, f + 1);
    }
    else if (strcmp(func3, "001") == 0)
    {
        if (a == -1)
            printf("bne x%d,x%d,%d\n", reg1, reg2, var);
        else if (f == size_B)
            printf("bne x%d,x%d,L%d\n", reg1, reg2, size_B);
        else
            printf("bne x%d,x%d,L%d\n", reg1, reg2, f + 1);
    }
    else if (strcmp(func3, "100") == 0)
    {
        if (a == -1)
            printf("blt x%d,x%d,%d\n", reg1, reg2, var);
        else if (f == size_B)
            printf("blt x%d,x%d,L%d\n", reg1, reg2, size_B);
        else
            printf("blt x%d,x%d,L%d\n", reg1, reg2, f + 1);
    }
    else if (strcmp(func3, "101") == 0)
    {
        if (a == -1)
            printf("bge x%d,x%d,%d\n", reg1, reg2, var);
        else if (f == size_B)
            printf("bge x%d,x%d,L%d\n", reg1, reg2, size_B);
        else
            printf("bge x%d,x%d,L%d\n", reg1, reg2, f + 1);
    }
    else if (strcmp(func3, "110") == 0)
    {
        if (a == -1)
            printf("bltu x%d,x%d,%d\n", reg1, reg2, var);
        else if (f == size_B)
            printf("bltu x%d,x%d,L%d\n", reg1, reg2, size_B);
        else
            printf("bltu x%d,x%d,L%d\n", reg1, reg2, f + 1);
    }
    else if (strcmp(func3, "111") == 0)
    {
        if (a == -1)
            printf("bgeu x%d,x%d,%d\n", reg1, reg2, var);
        else if (f == size_B)
            printf("bgeu x%d,x%d,L%d\n", reg1, reg2, size_B);
        else
            printf("bgeu x%d,x%d,L%d\n", reg1, reg2, f + 1);
    }
}
void J_TYPE(char *binary_digits, int k)
{
    char imm[21] = "";
    imm[0] = binary_digits[0];
    for (int i = 0; i < 10; i++)
    {
        imm[10 + i] = binary_digits[i + 1];
    }
    imm[9] = binary_digits[11];
    for (int i = 0; i < 8; i++)
    {
        imm[1 + i] = binary_digits[12 + i];
    }
    int var = decimal(imm) * 2;
    int a = -1;
    int f = 0;
    while (f < size_J)
    {
        if (address_J[f] == k + var / 4)
        {
            break;
        }
        f++;
    }
    if ((k + var / 4) < 20)
    {
        a = 0;
        if (f == size_J)
        {
            address_J[size_J] = k + var / 4;
            size_J++;
        }
    }
    if (a == -1)
    {
        printf("jal x%d %d\n", dreg, var);
    }
    else if (f == size_J)
    {
        printf("jal x%d L%d\n", dreg, size_J);
    }
    else
    {
        printf("jal x%d L%d\n", dreg, f + 1);
    }
}

void U_TYPE(char *hex_digit)
{
    char imm_u[22] = "";
    strcat(imm_u, func7);
    strcat(imm_u, rs2);
    strcat(imm_u, rs1);
    strcat(imm_u, func3);
    int a = decimal(imm_u);
    printf("lui x%d, 0x%X\n", dreg, a);
}
int main()
{
    char hex_digit[20][9];

    for (int i = 0; i < 20; i++)
    {
        scanf("%s", hex_digit[i]);
    }
    char binary_digits[20][33] = {""};
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (hex_digit[i][j] == '0')
            {
                strcat(binary_digits[i], "0000");
            }
            if (hex_digit[i][j] == '1')
            {
                strcat(binary_digits[i], "0001");
            }
            if (hex_digit[i][j] == '2')
            {
                strcat(binary_digits[i], "0010");
            }
            if (hex_digit[i][j] == '3')
            {
                strcat(binary_digits[i], "0011");
            }
            if (hex_digit[i][j] == '4')
            {
                strcat(binary_digits[i], "0100");
            }
            if (hex_digit[i][j] == '5')
            {
                strcat(binary_digits[i], "0101");
            }
            if (hex_digit[i][j] == '6')
            {
                strcat(binary_digits[i], "0110");
            }
            if (hex_digit[i][j] == '7')
            {
                strcat(binary_digits[i], "0111");
            }
            if (hex_digit[i][j] == '8')
            {
                strcat(binary_digits[i], "1000");
            }
            if (hex_digit[i][j] == '9')
            {
                strcat(binary_digits[i], "1001");
            }
            if (hex_digit[i][j] == 'a')
            {
                strcat(binary_digits[i], "1010");
            }
            if (hex_digit[i][j] == 'b')
            {
                strcat(binary_digits[i], "1011");
            }
            if (hex_digit[i][j] == 'c')
            {
                strcat(binary_digits[i], "1100");
            }
            if (hex_digit[i][j] == 'd')
            {
                strcat(binary_digits[i], "1101");
            }
            if (hex_digit[i][j] == 'e')
            {
                strcat(binary_digits[i], "1110");
            }
            if (hex_digit[i][j] == 'f')
            {
                strcat(binary_digits[i], "1111");
            }
        }
    }
    for (int k = 0; k < 20; k++)
    {
        char opcode[8];
        for (int i = 25; i < 32; i++)
        {
            opcode[i - 25] = binary_digits[k][i];
        }
        convert(binary_digits[k]);
        int m = 0;
        while (m < k)
        {
            if (address_B[m] == k)
            {
                printf("\n");
                printf("L%d :", m + 1);
                break;
            }
            m++;
        }
        if (strcmp(opcode, "0110011") == 0)
        {
            R_TYPE();
        }
        else if (strcmp(opcode, "0010011") == 0 || strcmp(opcode, "0000011") == 0 || strcmp(opcode, "1100111") == 0)
        {
            I_TYPE(opcode);
        }
        else if (strcmp(opcode, "0100011") == 0)
        {
            S_TYPE();
        }
        else if (strcmp(opcode, "1100011") == 0)
        {
            B_TYPE(binary_digits[k], k);
        }
        else if (strcmp(opcode, "1101111") == 0)
        {
            J_TYPE(binary_digits[k], k);
        }
        else if (strcmp(opcode, "0110111") == 0)
        {
            U_TYPE(hex_digit[k]);
        }
    }
}
