#########################################################
# B[8] = A [i-j]
#
#########################################################
## i -> s3, j -> s4, A -> s6, B -> s7
.data
A: .word 98, 45, 2, 6, 7, 8, 12, 34, 99
B: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

.text

li $s3, 5
li $s4, 1
la $s6, A
la $s7, B


sub $t0, $s3, $s4  ## t0 <- i - j 
sll $t0, $t0, 2    ## t0 <- (i-j) * 4 (offset)
add $t0, $t0, $s6  ## t0 <- &A[i-j]
lw $s0, 0($t0)     ## s0 <- A[i-j]

sw $s0, 32($s7)    ## B[8] <- s0