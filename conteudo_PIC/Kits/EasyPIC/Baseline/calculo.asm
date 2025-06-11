
_soma:

;calculo.c,9 :: 		unsigned char soma(char _b, char _c)
;calculo.c,12 :: 		return _b+_c;
	MOVF        FARG_soma__c+0, 0 
	ADDWF       FARG_soma__b+0, 0 
	MOVWF       R0 
;calculo.c,13 :: 		}
L_end_soma:
	RETURN      0
; end of _soma
