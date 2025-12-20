#ifdef __cplusplus
#include <cstdio>
#include <cassert>
#else
#include <stdio.h>
#include <assert.h>
#endif


void solution_for_grade_7(const int arr[], size_t arr_rows, size_t arr_cols, int result[])
{
    if (!arr || !result || arr_rows == 0 || arr_cols == 0)
    {
        if (result)
        {
            for (size_t i = 0; i < arr_rows; ++i)
                result[i] = -1;
        }
        return;
    }

    __asm
    {
        xor esi, esi
        xor edi, edi
        mov ecx, arr_rows

        row_loop :
        push ecx
            mov ebx, arr
            xor eax, eax
            mov ecx, arr_cols

            col_loop :
        mov edx, esi
            imul edx, arr_cols
            add edx, ecx
            sub edx, 1
            imul edx, 4
            add edx, ebx
            mov edx, [edx]
            test edx, 1
            jnz skip
            inc eax

            skip :
        loop col_loop

            mov ebx, result
            mov[ebx + edi * 4], eax
            inc esi
            inc edi
            pop ecx
            loop row_loop
    }
}






void solution_for_grade_9(const int arr[], size_t arr_rows, size_t arr_cols, int result[])
{
    if (!arr || !result || arr_rows == 0 || arr_cols == 0)
    {
        if (result)
        {
            for (size_t i = 0; i < arr_rows; ++i)
                result[i] = -1;
        }
        return;
    }

    __asm
    {
        xor esi, esi
        xor edi, edi
        mov ecx, arr_rows

        row_loop :
        push ecx
            mov ebx, arr
            mov eax, 0x80000000  
            mov ecx, arr_cols

            col_loop :
        mov edx, esi
            imul edx, arr_cols
            add edx, ecx
            sub edx, 1
            imul edx, 4
            add edx, ebx
            mov edx, [edx]
            cmp edx, 0
            jge skip
            cmp edx, eax
            jle skip
            mov eax, edx

            skip :
        loop col_loop

            mov ebx, result
            cmp eax, 0x80000000
            jne store_max
            mov eax, -1

            store_max:
        mov[ebx + edi * 4], eax
            inc esi
            inc edi
            pop ecx
            loop row_loop
    }
}


const size_t ROWS = 2;
const size_t COLS = 4;


int main()
{
    const int input1[ROWS][COLS] = { { 0, -1500, 2500, 70000 }, { 3500, 4500, -5500, -80000 } };
    int result1[ROWS]{};

    solution_for_grade_7((const int*)input1, ROWS, COLS, result1);

    const int expected1[ROWS]{ 4, 4 };
    

    for (auto i{ 0U }; i < ROWS; i++)
    {
        printf("%d ", result1[i]);
        assert(result1[i] == expected1[i]);
    }
    puts("");

    //Null pointer for input array
    solution_for_grade_7(nullptr, ROWS, COLS, result1);
    for (auto i{ 0U }; i < ROWS; i++)
    {
        printf("%d ", result1[i]);
        assert(result1[i] == -1);
    }
    puts("");
    //Zero columns
    solution_for_grade_7((const int*)input1, 0, COLS, result1);
    for (auto i{ 0U }; i < ROWS; i++)
    {
        printf("%d ", result1[i]);
        assert(result1[i] == -1);
    }
    puts("");
    //Zero rows 
    solution_for_grade_7((const int*)input1, ROWS, 0, result1);
    for (auto i{ 0U }; i < ROWS; i++)
    {
        printf("%d ", result1[i]);
        assert(result1[i] == -1);
    }

    puts("");
    const int input2[ROWS][COLS] = { { 0, -1500, 2500, 70000 }, { 3500, -4500, -5500, -80000 } };
    int result2[ROWS]{};

    solution_for_grade_9((const int*)input2, ROWS, COLS, result2);

    const int expected2[ROWS]{ -1500, -4500 };

    for (size_t i = 0; i < ROWS; i++)
    {
        printf("%d ", result2[i]);
        assert(result2[i] == expected2[i]);
    }
    puts("");

    //Null input array
    solution_for_grade_9(nullptr, ROWS, COLS, result2);
    for (size_t i = 0; i < ROWS; i++)
    {
        assert(result2[i] == -1);
    }
    puts("");
    //Zero rows
    solution_for_grade_9((const int*)input2, 0, COLS, result2);
    for (size_t i = 0; i < ROWS; i++)
    {
        assert(result2[i] == -1);
    }
    puts("");
    //Zero columns
    solution_for_grade_9((const int*)input2, ROWS, 0, result2);
    for (size_t i = 0; i < ROWS; i++)
    {
        assert(result2[i] == -1);
    }

    return 0;
}
