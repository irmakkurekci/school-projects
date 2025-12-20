#include <string.h>
#include <cassert>
#include <stdio.h>
#include <iostream>
extern "C" int solution_for_grade_6(const char* input);
extern "C" void solution_for_grade_9(const char* input, char* output);
extern "C" void solution_for_grade_7(const int arr[], size_t arr_rows, size_t arr_cols, int result[]);
extern "C" void solution_for_grade_9_2(const int arr[], size_t arr_rows, size_t arr_cols, int result[]);

int main() {
    int n_result;

    n_result = solution_for_grade_6("A BC. D");
    printf("Result A4 Solution 6: %d\n", n_result);
    assert(n_result == 3);  // Should count 3 words

    n_result = solution_for_grade_6("Word");
    printf("Result A4 Solution 6: %d\n", n_result);
    assert(n_result == 1);  // Should count 1 word

    n_result = solution_for_grade_6("");
    printf("Result A4 Solution 6: %d\n", n_result);
    assert(n_result == 0);  // Should count 0 words

    n_result = solution_for_grade_6(nullptr);
    printf("Result A4 Solution 6: %d\n", n_result);
    assert(n_result == 0);  // Should count 0 words

    const char* input = "AAA";
    char output[100]; // Allocate enough space for the output

    solution_for_grade_9(input, output);

    std::cout << "Result A4 Solution 9: " << output << std::endl;


    const int input1[2][4] = { { 0, -1500, 2500, 70000 }, { 3500, 4500, -5500, -80000 } };
    int result1[2];

    solution_for_grade_7((const int*)input1, 2, 4, result1);
    printf("Result A5 Solution 7: ");
    for (int i = 0; i < 2; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");

    const int input2[2][4] = { { 0, -1500, 2500, 70000 }, { 3500, -4500, -5500, -80000 } };
    int result2[2];

    solution_for_grade_9_2((const int*)input2, 2, 4, result2);

    printf("Result A5 Solution 9: ");
    for (int i = 0; i < 2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");
    return 0;
}

