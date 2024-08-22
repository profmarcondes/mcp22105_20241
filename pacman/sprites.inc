.text 0x00430000

#  int colors[8];
#  sprite sprites[20];
#  char sprite[49];
#=============================================================
# void draw_sprite(sprite_id, X, Y){
#       char * ptr_sprite =  sprites[sprite_id];
#       for(int i = 0; i < 49; i++){ 
#			color = colors[*ptr_sprite];
#           sX = i % 7 ;
#			sY = i / 7 ;
#           sX = X + sX;
#           sY = Y + sY;
#        	set_pixel(sX, sY, color)
#           ptr_sprite++;
#       }
# }

# old_stack      40($sp)
#########################
#  empty, 36($sp)
# -----------------------
#  $ra, 32($sp)
# -----------------------
#  $s4, 28($sp)
# -----------------------
#  $s3, 24($sp)
# -----------------------
#  $s2, 20($sp)
# -----------------------
#  $s1, 16($sp)
# -----------------------
#  $s0, 12($sp)
# -----------------------
#  $a2, 8($sp)
# -----------------------
#  $a1, 4($sp)
# -----------------------
#  $a0, 0($sp)
#########################
draw_sprite:
	addiu $sp, $sp -40
	sw $ra, 32($sp)
 	sw $s4, 28($sp)
	sw $s3, 24($sp)
	sw $s2, 20($sp)
	sw $s1, 16($sp)
	sw $s0, 12($sp)


	# char * ptr_sprite =  sprites[sprite_id]; ## $s0
	la  $s0, sprites
	mul $t0, $a0, 49    ## calculo offset
	add $s0, $s0, $t0   ## $s0 <- sprites[sprite_id];
	
	move $s1, $a1  # X - $s1
	move $s2, $a2  # Y - $s2
	
	la   $s3, colors # &colors - s3
	
	li  $s4, 0 ## $s1 - i
	draw_sprite_L0:
		bge $s4, 49, draw_sprite_L0_end
			lb  $t0, 0($s0)    ## $t0 = *ptr_sprite;
			sll $t0, $t0, 2   ## t0 * 4
			add $t0, $t0, $s3 ### t0 = &color[*ptr_sprite]
			lw  $a2, 0($t0)   ### a2 = color[*ptr_sprite]
			
			li  $t0, 7
			div $s4, $t0
			mfhi $a0 # sX = i % 7
			mflo $a1 # sY = i / 7 ;
			add $a0, $s1, $a0 # sX = X + sX;
			add $a1, $s2, $a1 # sY = Y + sY;

			# set_pixel(sX, sY, color)
			jal set_pixel
			
			addi $s0, $s0, 1 # ptr_sprite++;
			
		addi $s4, $s4, 1 # i ++
		j draw_sprite_L0
	draw_sprite_L0_end:
	
	lw $ra, 32($sp)
 	lw $s4, 28($sp)
	lw $s3, 24($sp)
	lw $s2, 20($sp)
	lw $s1, 16($sp)
	lw $s0, 12($sp)
	addiu $sp, $sp 40
    jr   $ra
#=============================================================


# old_stack      16($sp)
#########################
#  $ra, 12($sp)
# -----------------------
#  $a2, 8($sp)
# -----------------------
#  $a1, 4($sp)
# -----------------------
#  $a0, 0($sp)
#=============================================================
# void draw_animated_sprite(animated_sprite*)
draw_animated_sprite:
	addiu $sp, $sp, -16
	sw    $ra, 12($sp)

	lw  $a1, 4($a0) 
	lw  $a2, 8($a0)
	lw  $a0, 0($a0)
	jal draw_sprite

	lw    $ra, 12($sp)
	addiu $sp, $sp, 16
	jr    $ra
#=============================================================

# struct animated_sprite {
# 	int ID;      ## 0
# 	int pos_X;   ## 4
#	int pos_Y;   ## 8
#	int mov_X;   ## 12
#	int mov_Y;   ## 16
# }
#=============================================================
# void apply_movement(animated_sprite* ptr)
apply_movement:
	lw 	$t0, 4($a0)    ## t0 <- ptr.pos_X
	lw  $t1, 12($a0)   ## t1 <- ptr.mov_X
	add $t0, $t0, $t1  ## pos_X += mov_X
	sw  $t0, 4($a0)    ## ptr.pos_X <- t0
	
	lw 	$t0, 8($a0)    ## t0 <- ptr.pos_Y
	lw  $t1, 16($a0)   ## t1 <- ptr.mov_Y
	add $t0, $t0, $t1  ## pos_Y += mov_Y
	sw  $t0, 8($a0)    ## ptr.pos_Y <- t0
	
	jr    $ra
#=============================================================

#=============================================================
# void set_move_animated_sprite(animated_sprite* sp, int vx, int vy)
set_move_animated_sprite:
	sw   $a1, 12($a0)
	sw   $a2, 16($a0)
	jr   $ra
#=============================================================

#=============================================================   
# void stop_animated_sprite(animated_sprite* sp)
stop_animated_sprite:
	sw   $zero, 12($a0)
	sw   $zero, 16($a0)
	jr   $ra
#=============================================================

#=============================================================
# char get_grid_element(column_x, row_y, grid_table*)
get_grid_element:

	jr  $ra
#=============================================================

#=============================================================
# draw_grid(width, height, grid_table*)
draw_grid:

	jr   $ra
#=============================================================

# struct mov_vector {
#    int valid;
#    int mov_x;
#    int mov_y;
# }
#########################
# old_stack ($a0)  8($sp)
#########################
#  < empty >       4($sp)
# -----------------------
#  $ra             0($sp)
#=============================================================
# process_input(mov_vector *)
process_input:
	addiu $sp, $sp, -8
	sw $ra, 0($sp)     # save return address ($ra)
	sw $a0, 8($sp)     # save process_input parameter ($a0)

	jal get_nonblocking_char
	beq $v0, -1, process_input_exit
	
	bne $v0, ' ', process_input_a
	li $t0, 0 # mov_x
	li $t1, 0 # mov_y
	j 	process_input_end
	
process_input_a:
	bne $v0, 'a', process_input_s
	li $t0, -1 # mov_x
	li $t1, 0 # mov_y
	j 	process_input_end
	
process_input_s:
	bne $v0, 's', process_input_w
	li $t0, 0 # mov_x
	li $t1, 1 # mov_y
	j 	process_input_end
	
process_input_w:
	bne $v0, 'w', process_input_d
	li $t0, 0 # mov_x
	li $t1, -1 # mov_y
	j 	process_input_end
		
process_input_d:
	bne $v0, 'd', process_input_exit
	li $t0, 1 # mov_x
	li $t1, 0 # mov_y	
	
process_input_end:
	lw $a0, 8($sp) # restauro valor do $a0
	sw $t0, 4($a0) # seta mov_x
	sw $t1, 8($a0) # seta mov_y
	li $t0, 1
	sw $t0, 0($a0) # seta valid
	
process_input_exit:
	lw $ra, 0($sp)
	addiu $sp, $sp, 8
	jr   $ra
#=============================================================

#########################
# old_stack ($a1)  20($sp)
# ------------------------
# old_stack ($a0)  16($sp)
#########################
#  $ra             12($sp)
# -----------------------
#  $a2             8($sp)
# -----------------------
#  $a1             4($sp)
# -----------------------
#  $a0             0($sp)
#=============================================================   
# void try_change_movement(animated_sprite* sp, mov_vector* mv)
try_change_movement:
	lw $t0, 0($a1) # valid 
	beqz $t0, try_change_movement_end
	
	addiu $sp, $sp, -16
	sw    $ra, 12($sp)
	
	sw $zero, 0($a1) # zero valid
	
	lw $t0, 4($a1)
	lw $t1, 8($a1)

	# call set_move_animated_sprite(animated_sprite* sp, int vx, int vy)
	move $a1, $t0
	move $a2, $t1
	jal  set_move_animated_sprite

	lw    $ra, 12($sp)
	addiu $sp, $sp, 16

try_change_movement_end:	
	jr   $ra
#=============================================================

#=============================================================
# bool check_movement(animated_sprite*)
check_movement:

	jr   $ra
#=============================================================

