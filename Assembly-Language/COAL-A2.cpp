//#include "stdafx.h" // might be required for the older versions of Visual Studio
#ifdef __cplusplus
#include <cstdio>
#include <cassert>
#else
#include <stdio.h>
#include <assert.h>
#endif

// C++ built-in data types mapping to assembler data types:
//   char  data type is signed  8-bit integer (DB in assembler)
//   short data type is signed 16-bit integer (DW in assembler)
//   int   data type is signed 32-bit integer (DD in assembler)

// You must use integer data type for input values.

// Update the given template code appropriately.

int solution_for_grade_5(int x, int y, int z)
{


    int result;
    int denominator;

    __asm
    {


        mov eax, x
        imul eax, y
        imul eax, 5

        mov ebx, z
        sub ebx, y
        imul ebx, 4

        sub eax, ebx


        push eax

        mov ebx, y
        imul ebx, 3

        mov ecx, z
        imul ecx, 2

        sub ebx, ecx
        mov[denominator], ebx


        cmp ebx, 0
        je division_by_zero


        pop eax
        cdq
        idiv ebx


        mov[result], eax
        jmp done


        division_by_zero :
        mov eax, 0
            mov[result], eax

            done :
    }




    return result;
}


int solution_for_grade_7(int x, int y, int z)
{


    int result;
    __asm
    {

        mov eax, y
        sub eax, 1
        mov ebx, eax

        imul eax, eax
        imul eax, ebx


        mov ebx, z
        cmp ebx, 0
        je division_by_zero

        cdq
        idiv ebx


        mov ebx, x
        sub ebx, eax


        mov result, ebx
        jmp done

        division_by_zero :
        mov result, 0

            done :
    }
    return result;
}

int solution_for_grade_9(int x, int y, int z)
{
    int result;
    int D;
    int E;


    __asm
    {

        mov eax, y
        sub eax, 1
        mov ebx, eax

        imul eax, eax
        imul eax, ebx


        mov ebx, z
        cmp ebx, 0
        je division_by_zero

        cdq
        idiv ebx


        mov ebx, x
        sub ebx, eax
        mov D, ebx



        mov eax, x
        imul eax, y
        imul eax, 5

        mov ebx, z
        sub ebx, y
        imul ebx, 4

        sub eax, ebx
        mov E, eax



        cmp D, 0
        jg positive_D
        jl negative_D


        mov eax, -1
        mov result, eax
        jmp done

        positive_D :

        mov eax, E
            imul eax, D
            mov result, eax
            jmp done

            negative_D :

        mov eax, E
            mov ebx, D
            cdq
            idiv ebx
            mov result, eax
            jmp done

            division_by_zero :

        mov D, 0
            mov eax, -1
            mov result, eax

            done :
    }

    return result;
}

int main()
{
    // Note the 32-bit signed int value range is –2’147’483’648 .. 2’147’483’647
    int f = 320000;
    int s = -250000;
    int t = 122000;
    int r = 0;

    r = solution_for_grade_5(f, s, t);
    printf("solution_for_grade_5(%d, %d, %d) = %d\n", f, s, t, r);
    int expected_result = ((5 * f * s) - (4 * t - 4 * s)) / (3 * s - 2 * t);
    assert(r == expected_result);
    r = solution_for_grade_7(f, s, t);
    printf("solution_for_grade_7(%d, %d, %d) = %d\n", f, s, t, r);
    //X - ((Y - 1) ^ 3 / Z)
    int expected_result2 = f - (((s - 1) * (s - 1) * (s - 1))) / t;
    assert(r == expected_result2);
    r = solution_for_grade_9(f, s, t);
    printf("solution_for_grade_9(%d, %d, %d) = %d\n", f, s, t, r);
    int expected_result3 = ((5 * f * s) - (4 * t - 4 * s)) * (f - (((s - 1) * (s - 1) * (s - 1))) / t);
    assert(r == expected_result3);

    return 0;
}
