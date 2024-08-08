.text 0x00430000

#  int colors[8];
#  sprite sprites[20];
#  char sprite[49];
#=============================================================
# void draw_sprite(X, Y, sprite_id){
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
draw_sprite:


    jr   $ra
#=============================================================

#=============================================================
# void draw_animated_sprite(animated_sprite*)
draw_animated_sprite:

	jr    $ra
#=============================================================

#=============================================================
# void apply_movement(animated_sprite*)
apply_movement:

	jr    $ra
#=============================================================

#=============================================================
# void set_move_animated_sprite(animated_sprite* sp, int vx, int vy)
set_move_animated_sprite:

	jr   $ra
#=============================================================

#=============================================================   
# void stop_animated_sprite(animated_sprite* sp)
stop_animated_sprite:

	jr   $ra
#=============================================================

#=============================================================
# char get_grid_element(row-y, column-x, grid_table* )
get_grid_element:

	jr  $ra
#=============================================================

#=============================================================
# draw_grid(width, height, grid_table* )
draw_grid:

	jr   $ra
#=============================================================

# struct mov_vector {
#    int valid;
#    int mov_x;
#    int mov_y;
# }
#=============================================================
# process_input(mov_vector *)
process_input:

	jr   $ra
#=============================================================

#=============================================================   
# void try_change_movement(animated_sprite* sp, mov_vector* mv)
try_change_movement:
	
	jr   $ra
#=============================================================

#=============================================================
# bool check_movement(animated_sprite*)
check_movement:

	jr   $ra
#=============================================================

