
#ifdef __cplusplus
#include <cstdio>
#include <cstring>
#include <cassert>
#else
#include <stdio.h>
#include <string.h>
#include <assert.h>
#endif

int solution_for_grade_6(const char* input)
{
   
    if (input == nullptr) {
        return 0; 
    }

    int result = 0;

    __asm
    {
        mov esi, input      
        xor eax, eax        
        mov ecx, 0        
        mov bl, 0           

        count_loop:
        lodsb              
            test al, al         
            jz end_count      

            cmp al, ' '         
            jz outside_word     

            cmp bl, 1           
            je count_loop       

           
            inc ecx             
            mov bl, 1           
            jmp count_loop      

            outside_word :
        mov bl, 0          
            jmp count_loop      

            end_count :
        mov result, ecx    
    }

    return result;
}



void solution_for_grade_9(const char* input, char* output)
{
    if (input == nullptr || output == nullptr) {
        return; 
    }

    __asm
    {
        mov esi, input      
        mov edi, output   
        xor ecx, ecx    
        xor eax, eax      

        next_char :
        lodsb               
            test al, al        
            jz end_string      

            mov bl, al          
            mov ecx, 1          

            count_repeats:
        lodsb              
            test al, al         
            jz output_last_char 

            cmp al, bl          
            jne output_char     

            inc ecx             
            cmp ecx, 9          
            je output_char      
            jmp count_repeats  

            output_char :
        mov al, bl          
            stosb               
            cmp ecx, 1          
            jle next_char       

            add cl, '0'         
            mov al, cl          
            stosb               
            jmp next_char       

            output_last_char :
        mov al, bl          
            stosb               
            cmp ecx, 1          
            jle end_string     

            add cl, '0'         
            mov al, cl          
            stosb               

            end_string :
        mov al, 0          
            stosb
    }
}

int main()
{
    int n_result = 0;

    
    n_result = solution_for_grade_6("A BC. D");
    assert(n_result == 3);  

    n_result = solution_for_grade_6("A BC.    D ");
    assert(n_result == 3);  

    
    n_result = solution_for_grade_6("Word");
    assert(n_result == 1); 

    
    n_result = solution_for_grade_6("");
    assert(n_result == 0);  

   
    n_result = solution_for_grade_6(nullptr);
    assert(n_result == 0); 


    char s_result[256] = "";

   
    solution_for_grade_9("ABBBCCCC", s_result);
    assert(strcmp(s_result, "AB3C4"));

   
    solution_for_grade_9("ABCDE", s_result);
    assert(strcmp(s_result, "ABCDE")); 

   
    solution_for_grade_9("AABBCCDDEE", s_result);
    assert(strcmp(s_result, "A2B2C2D2E2")); 

    
    solution_for_grade_9("AAABBC", s_result);
    assert(strcmp(s_result, "A3B2C")); 

   
    solution_for_grade_9("", s_result);
    assert(strcmp(s_result, "") == 0); 


    return 0;
}