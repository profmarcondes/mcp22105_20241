.data
data_c: .word 0
data_d: .word 0

.text
main:
	li $a0, 3
	li $a1, 5
	jal sumOfSquares
	sw $v0, data_c
	
	li $a0, 10
	li $a1, 15
	jal sumOfSquares
	sw $v0, data_d
	
	lw $t0, data_c
	add $t0, $t0, $v0
	
	li $v0, 10
	syscall
	
.text 0x00401000
sumOfSquares:
	mul $t0, $a0, $a0
	mul $t1, $a1, $a1
	add $v0, $t0, $t1
	jr  $ra
	
	
#  unsigned int fatorial ( unsigned int n ) {
#       unsigned int res = 1;
#		if( n != 0 ) {
#          res = n * fatorial(n-1);
#       }
#		return res;
#  }
#  res -> $v0, n -> $a0
#  
fatorial:


	li $v0, 1 # unsigned int res = 1;
	beqz $a0, fatorial_if0_end
		addi $a0, $a0, -1
		jal fatorial
		mul $v0, $a0, $v0
	fatorial_if0_end:
	jr $ra
	
	
	
	









	
	
