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

short solution_for_grade_7(short x, short y, short z)
{
    // Selected variant: Variant 1, Expression: 5XY – 4(Z – Y)

    short result;
    __asm
    {
        mov ax, x           // ax = x
        imul ax, y           // ax = xy
        imul ax, 5          // ax = 5 * (xy)


        mov bx, z           // bx = z
        sub bx, y          // bx = z - y
        imul bx, 4          // bx = 4 * (z - y)

        sub ax, bx          // ax = 5XY – 4(Z – Y)

        // Save result
        mov[result], ax     // result = ax
    }


    

    return result;
}

short solution_for_grade_9(short x, short y, short z)
{
    // Selected variant: Variant 1, Expression: 5XY – 4(Z – Y)

    short result;
    short denominator; // We will store (3Y - 2Z) in this variable

    __asm
    {
        mov ax, x           // ax = x
        imul ax, y           // ax = xy
        imul ax, 5          // ax = 5 * (xy)


        mov bx, z           // bx = z
        sub bx, y          // bx = z - y
        imul bx, 4          // bx = 4 * (z - y)


        sub ax, bx          // ax = 5XY – 4(Z – Y)


        mov bx, y           // bx = y
        imul bx, 3          // bx = 3 * y

        mov cx, z           // cx = z
        imul cx, 2          // cx = 2 * z

        sub bx, cx          // bx = 3y - 2z
        mov[denominator], bx // Save denominator for checking later


        cmp bx, 0
        je division_by_zero  // Jump if denominator is zero

        //  (5XY – 4(Z – Y)) / (3Y - 2Z)
        cwd                 // Sign extend AX into DX:AX for division
        idiv bx             // ax = (5XY – 4(Z – Y)) / (3Y - 2Z)

        // Store result
        mov[result], ax     // result = ax
        jmp done

        division_by_zero :
        mov result, 0

            done :
    }
    
    
   
    return result;
}



int main()
{
    short x = 420;  // Test values for X
    short y = -50; // Test values for Y
    short z = 122;  // Test values for Z

    short result1 = solution_for_grade_7(x, y, z);
    short result2 = solution_for_grade_9(x, y, z);

    printf("solution_for_grade_7(%d, %d, %d) = %d\n", x, y, z, result1);
    printf("solution_for_grade_9(%d, %d, %d) = %d\n", x, y, z, result2);

    assert(result1 == ((5 * (x * y) - 4 * (z - y)) / (3 * y - 2 * z)));
    assert(result2 == (5 * (x * y) - 4 * (z - y)));
    return 0;
}
