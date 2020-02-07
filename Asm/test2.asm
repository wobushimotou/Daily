DATA SEGMENT
     INFOR1 DB 0AH,0DH,"Are you readlly want exit? $"
     INFOR2 DB 0AH,0DH,"Thank you for your using! $"
     INFOR3 DB 0AH,0DH,"Let's continue! $"
     INFOR4 DB 0AH,0DH,"You press an error key! $"
DATA ENDS
CODE SEGMENT
    ASSUME CS:CODE,DS:DATA
START:
    MOV AX,DATA
    MOV DS,AX
    LEA DX,INFOR1
    MOV AH,09H
    INT 21H

    MOV AH,01H
    INT 21H

    CMP AL,'y'
    JE FIRST

    CMP AL,'Y'
    JE FIRST

    CMP AL,'n'
    JE SECOND
    
    CMP AL,'N'
    JE SECOND
    
    LEA DX,INFOR4
    MOV AH,09H
    INT 21H
    JMP PEND
FIRST:
    LEA DX,INFOR2
    MOV AH,09H
    INT 21H
    JMP PEND
SECOND:
    LEA DX,INFOR3
    MOV AH,09H
    INT 21H
    JMP PEND
PEND:
    MOV AH,4CH
    INT 21H
CODE ENDS
    END START

