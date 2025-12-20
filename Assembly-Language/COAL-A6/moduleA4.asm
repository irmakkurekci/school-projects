.586
.model flat, C
.code



solution_for_grade_6 PROC PUBLIC 
    mov esi, [esp+4]    

    test esi, esi        
    jz null_input 
    
  
    xor ecx, ecx         
    xor edx, edx        
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
        mov eax, ecx       
        ret

null_input:
    mov eax, 0           
    ret
solution_for_grade_6 ENDP


solution_for_grade_9 PROC PUBLIC
    ; Load parameters from the stack
    mov esi, [esp+4]    
    mov edi, [esp+8]    

    ; Check for null pointers
    test esi, esi
    jz null_output      
    test edi, edi
    jz null_output     

    ; Clear registers
    xor ecx, ecx      
    xor eax, eax        

next_char:
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
    jmp count_repeats  

output_char:
    mov al, bl        
    stosb             

    cmp ecx, 1          
    je next_char        

    add cl, '0'        
    mov al, cl         
    stosb               

    ; Reset for the next character
    mov ecx, 1         
    mov bl, al          
    jmp next_char       

output_last_char:
    mov al, bl         
    stosb              
    cmp ecx, 1          
    je end_string       

    add cl, '0'        
    mov al, cl
    stosb              

end_string:
    mov al, 0           
    stosb               

    ret                

null_output:
    mov byte ptr [edi], 0  
    ret
solution_for_grade_9 ENDP


END
