
_main:

;MyProject.c,40 :: 		void main() {           // a função main é void (não retorna valor) pois é a...
;MyProject.c,48 :: 		PORTB = soma(10,20);     // PORTB = 30;
	MOVLW       10
	MOVWF       FARG_soma__b+0 
	MOVLW       20
	MOVWF       FARG_soma__c+0 
	CALL        _soma+0, 0
	MOVF        R0, 0 
	MOVWF       PORTB+0 
;MyProject.c,59 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
