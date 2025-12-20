.586
.model flat, C
.code

solution_for_grade_7 PROC EXPORT arr: PTR DWORD, arr_rows: DWORD, arr_cols: DWORD, result: PTR DWORD
    ; Initialize registers
    xor esi, esi              
    xor edi, edi               
    mov ecx, arr_cols         

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
            ret
solution_for_grade_7 ENDP

solution_for_grade_9_2 PROC EXPORT arr: PTR DWORD, arr_rows: DWORD, arr_cols: DWORD, result: PTR DWORD
    ; Initialize registers
    xor esi, esi               
    xor edi, edi              
    mov ecx, arr_cols         

xor esi, esi
        xor edi, edi
        mov ecx, arr_rows

        row_loop :
        push ecx
            mov ebx, arr
            mov eax, 80000000h  
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
            cmp eax, 80000000h
            jne store_max
            mov eax, -1

            store_max:
        mov[ebx + edi * 4], eax
            inc esi
            inc edi
            pop ecx
            loop row_loop
            ret
solution_for_grade_9_2 ENDP

END
