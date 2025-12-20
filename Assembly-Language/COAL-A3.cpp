#include <stdio.h>
#include <assert.h>

int solution_for_grade_7(int const* arr, size_t arr_size) {
    int result = 0;
    if (arr == NULL || arr_size == 0) 
        return 0;

    __asm {
        mov ESI, arr
        mov ECX, arr_size
        xor EAX, EAX   // Initialize result to 0
        test ECX, ECX
        jecxz Exit

        Cycle :
        mov EBX, [ESI]
            test EBX, 1    // Check if the number is odd
            jz Next        // If even, skip to the next
            add EAX, EBX   // Add odd value to result

            Next :
        add ESI, 4
            loop Cycle

            Exit :
        mov result, EAX
    }

    return result;
}


int solution_for_grade_9(int const* arr, size_t arr_size) {
    int min_even_index = -1;
    int min_even_value = 0x7FFFFFFF; // Set to largest possible integer

    if (arr == NULL || arr_size == 0) 
        return -1; 

    __asm {
        mov ESI, arr
        mov ECX, arr_size
        xor EAX, EAX       // Index tracker

        test ECX, ECX
        jecxz Exit

        FindMinEven :
        mov EBX, [ESI]
            test EBX, 1        // Check if the number is even
            jnz Skip           // Skip if odd

            cmp EBX, min_even_value
            jge Skip           // Skip if current even value is >= min_even_value

            mov min_even_value, EBX // Update min_even_value
            mov min_even_index, EAX // Store current index

            Skip :
        add ESI, 4
            inc EAX
            loop FindMinEven

            Exit :
    }

    return min_even_index;
}

int main()
{
    int test_result;

    // Testing solution_for_grade_7
    int test_arr1[] = { 900000, 998, 5022, -300, 4444, 5678, 54367, 70, -80001, 3 };
    test_result = solution_for_grade_7(test_arr1, sizeof(test_arr1) / sizeof(test_arr1[0]));
    assert(test_result == -25631);  // Sum of odd values
    printf("Grade 7 result1 = %d\n", test_result);

    int test_arr2[] = { -91, -11, 20, -33, 40, -55, 60, -71, 801, 0 };
    test_result = solution_for_grade_7(test_arr2, sizeof(test_arr2) / sizeof(test_arr2[0]));
    assert(test_result == 540);  // Sum of odd values
    printf("Grade 7 result2 = %d\n", test_result);

    // Testing solution_for_grade_9
    int test_arr3[] = { 900000, 998, -5022, -300, 4444, -5678, -54366, 70, -80000, 3 };
    test_result = solution_for_grade_9(test_arr3, sizeof(test_arr3) / sizeof(test_arr3[0]));
    assert(test_result == 8);  // Index of minimum even value
    printf("Grade 9 result1 = %d\n", test_result);

    int test_arr4[] = { -91, -11, 20, -33, 40, -55, 60, -71, 800, 0 };
    test_result = solution_for_grade_9(test_arr4, sizeof(test_arr4) / sizeof(test_arr4[0]));
    assert(test_result == 9);  // Index of minimum even value
    printf("Grade 9 result2 = %d\n", test_result);

    int test_arr5[] = { 10, 21, 31, 41, 51 }; 
    test_result = solution_for_grade_9(test_arr5, sizeof(test_arr5) / sizeof(test_arr5[0]));
    assert(test_result == 0);
    printf("Grade 9 result3 = %d\n", test_result);

    return 0;
}
