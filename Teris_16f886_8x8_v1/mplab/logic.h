/*
This file contains main logic processing of the game.
Author: Danh Hoang (htvdanh@gmail.com, HCMC, VietNam)    
Date: Sep 16th, 2016
*/
enum
{
	ALIGN_OK,
	ALIGN_LEFT_OVER_BOUNDARY,
	ALIGN_RIGHT_OVER_BOUNDARY
};
MATRIX4x4* lg_get_MATRIX4x4(uint8_t index, uint8_t sub_index)
{
	return &g_matrix4x4[g_char_info[index].start_index + sub_index];
}
void lg_clear_matrix(void) 
{
	MEMSET(&g_matrix8x8, 0, sizeof(MATRIX8x8));
	hal_print_Screen();
}
uint8_t lg_is_row_full(const MATRIX8x8* matrix, uint8_t row)
{
	if(matrix->row[row] == (uint8_t)0xFF)
	{
		dbg_print1(DEBUG_DISABLE, "row = %X", matrix->row[row]);
		dbg_print1(DEBUG_DISABLE, "row(%d) is full", row);
		dbg_print_MATRIX8x8(DEBUG_DISABLE, "Row is full", matrix);
		return 1;
	}
	return 0;
}
void lg_delete_matrix_row(MATRIX8x8* matrix, uint8_t row)
{
	for(int8_t i = MATRIX8x8_ROW_MAX - 1; i >= 0; i--)
	{
		if(i <= row)
		{
			if(i > 0)
			{
				matrix->row[i] = matrix->row[i - 1];
			}
			else
			{
				matrix->row[i] = (uint8_t)0x0;
			}
		}
	}
}
uint8_t lg_delete_matrix(MATRIX8x8* matrix)
{
	uint8_t count = 0;
	int8_t row = MATRIX8x8_ROW_MAX - 1;
	while(row >= 0)
	{
#if !WINDOW_BASE
		Seed++;
#endif
		if(lg_is_row_full(matrix, row) == 1)
		{
			dbg_print_MATRIX8x8(DEBUG_DISABLE, "Before delete MATRIX8x8", &g_matrix8x8);
			lg_delete_matrix_row(matrix, row);
			dbg_print_MATRIX8x8(DEBUG_DISABLE, "After delete MATRIX8x8", &g_matrix8x8);
			count++;
		}
		else
		{
			row--;
		}
	}
	dbg_print1(DEBUG_DISABLE, "delete_matrix count = %d", count);
	return count;
}
uint8_t lg_get_num_removed_rows(MATRIX8x8* matrix)
{
	uint8_t count = 0;
	for(int8_t row = 0; row < MATRIX8x8_ROW_MAX; row++)
	{
		if(lg_is_row_full(matrix, row) == 1)
		{
			count++;
		}
	}
	dbg_print1(DEBUG_DISABLE, "num full rows = %d", count);
	return count;
}

uint8_t lg_is_row_empty(const MATRIX8x8* matrix, uint8_t row)
{
	if(matrix->row == 0x0)
	{
		return 1;
	}
	return 0;
}
uint8_t lg_hit_land(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, const MATRIX8x8* matrix8x8)
{
	dbg_print_line(DEBUG_DISABLE, "==============hit_land============");

	for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
	{
		for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
		{
			if(get_matrix_bit((uint8_t*)matrix4x4->row, row, col) == 1)
			{
				if((y + row) >= (MATRIX8x8_ROW_MAX - 1))
				{
					dbg_print2(DEBUG_DISABLE, "hit1 row = %d, col = %d", row, col);
					return 1;
				}

				if(get_matrix_bit((uint8_t*)matrix8x8->row, y + row + 1, x + col) == 1)
				{
					dbg_print2(DEBUG_DISABLE, "hit2 row = %d, col = %d", row, col);
					return 1;
				}
			}
		}
	}
	dbg_print_line(DEBUG_DISABLE, "not hit");
	return 0;
} 
uint8_t lg_is_valid(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, const MATRIX8x8* matrix8x8)
{
	dbg_print_line(DEBUG_DISABLE, "==============is_valid============");
	for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
	{
		for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
		{
			if(get_matrix_bit((uint8_t*)matrix4x4->row, row, col) == 1)
			{
				if(get_matrix_bit((uint8_t*)matrix8x8->row, y + row, x + col) == 1)
				{
					dbg_print_line(DEBUG_DISABLE, "not valid1");
					dbg_print2(DEBUG_DISABLE, "row = %d, col = %d", row, col);
					return 0;
				}

				if(( x + col < 0) || (x + col >= MATRIX8x8_COLUMN_MAX))
				{
					dbg_print_line(DEBUG_DISABLE, "not valid2");
					dbg_print2(DEBUG_DISABLE, "row = %d, col = %d", row, col);
					return 0;
				}
				if((y + row) > (MATRIX8x8_ROW_MAX - 1))
				{
					dbg_print_line(DEBUG_DISABLE, "not valid3");
					dbg_print2(DEBUG_DISABLE, "row = %d, col = %d", row, col);
					return 0;
				}
			}
		}
	}
	dbg_print_line(DEBUG_DISABLE, "valid");
	return 1;
}
uint8_t lg_is_left_boundary(int8_t x, const MATRIX4x4* matrix4x4, const MATRIX8x8* matrix8x8)
{
	for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
	{
		for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
		{
			if(get_matrix_bit((uint8_t*)matrix4x4->row, row, col) == 1)
			{
				if( x + col < 0)
				{
					dbg_print_line(DEBUG_DISABLE, "ALIGN_LEFT_OVER_BOUNDARY");
					return ALIGN_LEFT_OVER_BOUNDARY;
				}
			}
		}
	}
	return ALIGN_OK;
}     
uint8_t lg_is_right_boundary(int8_t x, const MATRIX4x4* matrix4x4, const MATRIX8x8* matrix8x8)
{
	for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
	{
		for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
		{
			if(get_matrix_bit((uint8_t*)matrix4x4->row, row, col) == 1)
			{
				if(x + col > MATRIX8x8_COLUMN_MAX - 1)
				{
					dbg_print_line(DEBUG_DISABLE, "ALIGN_RIGHT_OVER_BOUNDARY");
					return ALIGN_RIGHT_OVER_BOUNDARY;
				}
			}
		}
	}
	return ALIGN_OK;
}     
uint8_t lg_fall_off(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, const MATRIX8x8* matrix8x8)
{
	while(1)
	{
		for(int8_t row = MATRIX4x4_ROW_MAX - 1; row >= 0; row--)
		{
			for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
			{
#if !WINDOW_BASE
				Seed++;
#endif
				if(get_matrix_bit((uint8_t*)matrix4x4->row, row, col) == 1)
				{
					if(get_matrix_bit((uint8_t*)matrix8x8->row, y + row + 1, x + col) == 1)
					{
						dbg_print_line(DEBUG_DISABLE, "fall_off1");
						dbg_print2(DEBUG_DISABLE, "x = %d, y = %d", x, y);
						return y;
					}
					if((y + row) >= (MATRIX8x8_ROW_MAX - 1))
					{
						dbg_print_line(DEBUG_DISABLE, "fall_off2");
						dbg_print2(DEBUG_DISABLE, "x = %d, y = %d", x, y);
						return y;
					}
				}
			}
		}
		y++;
	}
} 
void lg_clear(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, MATRIX8x8* matrix8x8)
{
	for(uint8_t row = 0; row < MATRIX4x4_ROW_MAX; row++)
	{
		for(uint8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
		{
			if(get_matrix_bit((uint8_t*)matrix4x4->row, row, col) == 1)
			{
				set_matrix_bit((uint8_t*)matrix8x8->row, y + row, x + col, 0);
			}
		}
	}
}     
void lg_merge(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, MATRIX8x8* matrix8x8)
{
	dbg_print_MATRIX4x4(DEBUG_DISABLE, "Before merge MATRIX8x8", x, y, matrix4x4);
	dbg_print_MATRIX8x8(DEBUG_DISABLE, "Before merge MATRIX8x8", matrix8x8);

	for(uint8_t row = 0; row < MATRIX4x4_ROW_MAX; row++)
	{
		for(uint8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
		{
			if(get_matrix_bit((uint8_t*)matrix4x4->row, row, col) == 1)
			{
				set_matrix_bit((uint8_t*)matrix8x8->row, y + row, x + col, 1);
			}
		}
	}
	dbg_print_MATRIX8x8(DEBUG_DISABLE, "After merge MATRIX8x8", matrix8x8);
}     
void lg_merge1(int8_t x, int8_t y, const MATRIX4x4* matrix4x4, const MATRIX8x8* matrix8x8_in, MATRIX8x8* matrix8x8_out)
{
#ifdef WINDOW_BASE
	size_t len;
#else
	register size_t len;
#endif    
	len = sizeof(MATRIX8x8);
	memcpy(matrix8x8_out, matrix8x8_in, len);

	for(uint8_t row = 0; row < MATRIX4x4_ROW_MAX; row++)
	{
		for(uint8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
		{
			if(get_matrix_bit((uint8_t*)matrix4x4->row, row, col) == 1)
			{
				set_matrix_bit((uint8_t*)matrix8x8_out->row, y + row, x + col, 1);
			}
		}
	}
}     
uint16_t lg_get_num_of_orphan(const MATRIX8x8* matrix)
{
	uint16_t risk = 0;
	uint8_t full = 0xFF;
	for(uint8_t col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
	{
		full = 0xFF;
		for(int8_t row = MATRIX8x8_ROW_MAX - 1; row >= 0; row--)
		{
			if(full == 0xFF)
			{
				full = get_matrix_bit((uint8_t*)matrix->row, row, col);
			}
			else
			{
				if(get_matrix_bit((uint8_t*)matrix->row, row, col) == 1)
				{
					if(full == 0)
					{
						risk++;
					}
				}
				full = get_matrix_bit((uint8_t*)matrix->row, row, col);
			}
		}
	}
	dbg_print1(DEBUG_DISABLE, "risk = %d", risk);

	return risk;
}
uint16_t lg_get_weight(const MATRIX8x8* matrix)
{
	uint8_t start;
	uint16_t risk = 0;
	uint8_t pre = 0xFF;
	for(uint8_t col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
	{
		pre = 0xFF;
		start = 0;
		for(int8_t row = MATRIX8x8_ROW_MAX - 1; row >= 0; row--)
		{
			if(pre == 0xFF)
			{
				pre = get_matrix_bit((uint8_t*)matrix->row, row, col);
			}
			else
			{
				if(pre != get_matrix_bit((uint8_t*)matrix->row, row, col))
				{
					pre = get_matrix_bit((uint8_t*)matrix->row, row, col);
					if(pre == 0)
					{
						start = 0;
					}
					else
					{
						start = 1;
					}
				}
				if(start == 1)
				{
					risk++;
				}
			}
		}
	}
	dbg_print1(DEBUG_DISABLE, "risk = %d", risk);

	return risk;
}

uint8_t lg_char_info_index_rand()
{
	return (uint8_t)(rand()%CHARACTER_MAX);
}
int8_t lg_left_most(int8_t x, const MATRIX4x4* matrix4x4, const MATRIX8x8* matrix8x8)
{
	while(1)
	{
#if !WINDOW_BASE
		Seed++;
#endif
		if(lg_is_left_boundary(x, matrix4x4, matrix8x8) == ALIGN_LEFT_OVER_BOUNDARY)
		{
			dbg_print1(DEBUG_DISABLE, "left_most = %d", x + 1);
			return x + 1;
		}
		x--;
	}
}    
int8_t lg_right_most(int8_t x, const MATRIX4x4* matrix4x4, const MATRIX8x8* matrix8x8)
{
	while(1)
	{
#if !WINDOW_BASE
		Seed++;
#endif
		if(lg_is_right_boundary(x, matrix4x4, matrix8x8) == ALIGN_RIGHT_OVER_BOUNDARY)
		{
			dbg_print1(DEBUG_DISABLE, "right_most = %d", x - 1);
			return x - 1;
		}
		x++;
	}
}    
uint8_t lg_get_height(MATRIX8x8* matrix)
{
	for(int8_t row = MATRIX8x8_ROW_MAX - 1; row >= 0; row--)
	{
		if(lg_is_row_empty(matrix, row) == 1)
		{
			dbg_print1(DEBUG_DISABLE, "lg_get_height height = %d", MATRIX8x8_ROW_MAX - row - 1);
			return (uint8_t)(MATRIX8x8_ROW_MAX - row - 1);
		}
	}
	return MATRIX8x8_ROW_MAX;
}
uint8_t lg_get_height_after_merge(int8_t y, MATRIX4x4* matrix)
{
	dbg_print_line(DEBUG_DISABLE, "lg_get_height_after_merge");
	for(int8_t row = 0; row < MATRIX4x4_ROW_MAX; row++)
	{
		for(int8_t col = 0; col < MATRIX4x4_COLUMN_MAX; col++)
		{
			if(get_matrix_bit((uint8_t*)matrix->row, row, col) == 1)
			{
				dbg_print1(DEBUG_DISABLE, "y = %d", y);
				dbg_print1(DEBUG_DISABLE, "row = %d", row);
				dbg_print1(DEBUG_DISABLE, "height = %d", MATRIX8x8_ROW_MAX - y - row);
				return (uint8_t)(MATRIX8x8_ROW_MAX - y - row);
			}
		}
	}
}
uint8_t lg_get_holes_after_merge(MATRIX8x8* matrix)
{
	int8_t start = -1;
	int8_t stop = -1;
	uint8_t num_hole = 0;
	for(int8_t col = 0; col < MATRIX8x8_COLUMN_MAX; col++)
	{
		start = stop = -1;
		for(int8_t row = 0; row < MATRIX8x8_ROW_MAX; row++)
		{
			if(col == 0)
			{
				if((get_matrix_bit((uint8_t*)matrix->row, row, col) == 0) && (get_matrix_bit((uint8_t*)matrix->row, row, col + 1) == 1))
				{
					if(start == -1)
					{
						start = row;
					}
				}
			}
			else if(col == MATRIX8x8_COLUMN_MAX - 1)
			{
				if((get_matrix_bit((uint8_t*)matrix->row, row, col) == 0) && (get_matrix_bit((uint8_t*)matrix->row, row, col - 1) == 1))
				{
					if(start == -1)
					{
						start = row;
					}
				}
			}
			else
			{
				if((get_matrix_bit((uint8_t*)matrix->row, row, col) == 0) && (get_matrix_bit((uint8_t*)matrix->row, row, col - 1) == 1) && (get_matrix_bit((uint8_t*)matrix->row, row, col + 1) == 1))
				{
					if(start == -1)
					{
						start = row;
					}
				}
			}
			if(start >= 0)
			{
				if(row == MATRIX8x8_ROW_MAX - 1)
				{
					if(stop == -1)
					{
						stop = MATRIX8x8_ROW_MAX;
					}
				}
				else if(get_matrix_bit((uint8_t*)matrix->row, row + 1, col) == 1)
				{
					if(stop == -1)
					{
						stop = row + 1;
					}
				}
			}

		}
		if((start >= 0) && (stop >= 0) && (stop - start >= 3))
		{
			dbg_print1(DEBUG_DISABLE, "col = %d", col);
			dbg_print1(DEBUG_DISABLE, "start = %d", start);
			dbg_print1(DEBUG_DISABLE, "stop = %d", stop);
			num_hole++;
		}
	}
	dbg_print1(DEBUG_DISABLE, "num_hole = %d", num_hole);
	return num_hole;
}
MATRIX4x4* temp_cur_matrix4x4;
MATRIX8x8 temp_matrix8x8;
uint8_t lg_find_best_solution()
{
	dbg_print_line(DEBUG_DISABLE, "===find_best_solution===");

	uint8_t res = 0;
	int8_t left_most_index, right_most_index;

	int8_t temp_pre_x = 0xF, tem_pre_sub_index = 0xF;
	int16_t temp_pre_risk = -30000;
	int8_t temp_y;
	int16_t temp_risk;
	uint16_t temp_high;

	for(uint8_t tem_sub_index = 0; tem_sub_index < g_char_info[g_char_info_index].num; tem_sub_index++)
	{
		temp_cur_matrix4x4 = &g_matrix4x4[g_char_info[g_char_info_index].start_index + tem_sub_index];
		left_most_index = lg_left_most(cur_x, temp_cur_matrix4x4, &g_matrix8x8);
		right_most_index = lg_right_most(cur_x, temp_cur_matrix4x4, &g_matrix8x8);

		for(int8_t temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
		{
			temp_y = lg_fall_off(temp_x, cur_y, temp_cur_matrix4x4, &g_matrix8x8);

			dbg_print_MATRIX4x4(DEBUG_DISABLE, "After fall off", temp_x, temp_y, temp_cur_matrix4x4);
			dbg_print_Screen(DEBUG_DISABLE, "After fall off");

			if(lg_is_valid(temp_x, temp_y, temp_cur_matrix4x4, &g_matrix8x8) == 0)
			{
				continue;
			}
			res = 1;
			lg_merge1(temp_x, temp_y, temp_cur_matrix4x4, &g_matrix8x8, &temp_matrix8x8);
			temp_high = lg_get_height_after_merge(temp_y, temp_cur_matrix4x4);
			if((lg_get_height(&g_matrix8x8) <= MATRIX8x8_ROW_MAX/2 + 1)
					&& (temp_high <= MATRIX8x8_ROW_MAX/2 + 1))
			{
				temp_risk = (((int16_t)lg_get_num_removed_rows(&temp_matrix8x8)) << 10)
                				   - lg_get_num_of_orphan(&temp_matrix8x8)*4
								   - temp_high*3
								   - lg_get_holes_after_merge(&temp_matrix8x8)*2
								   - lg_get_weight(&temp_matrix8x8);
			}
			else
			{
				temp_risk = (((int16_t)lg_get_num_removed_rows(&temp_matrix8x8)) << 10)
                				   - lg_get_num_of_orphan(&temp_matrix8x8)*2
								   - temp_high*5
								   - lg_get_holes_after_merge(&temp_matrix8x8)*3
								   - lg_get_weight(&temp_matrix8x8);
			}
			dbg_print_MATRIX8x8(DEBUG_DISABLE, "Valid instance", &temp_matrix8x8);
			dbg_print_line(DEBUG_DISABLE, "Start evaluation");
			dbg_print1(DEBUG_DISABLE, "temp_risk = %d", temp_risk);
			if(temp_risk > temp_pre_risk)
			{
				dbg_print2(DEBUG_DISABLE, "risk: (%d) > (%d)", temp_risk, temp_pre_risk);
				temp_pre_risk = temp_risk;
				tem_pre_sub_index = tem_sub_index;
				temp_pre_x = temp_x;
			}

#ifdef WINDOW_BASE
			dbg_print3(DEBUG_DISABLE, "sub_index = %d, temp_pre_x = %d, temp_pre_risk = %d",
					tem_pre_sub_index, temp_pre_x, temp_pre_risk);
			//			system("PAUSE");
#else
			dbg_print_line(DEBUG_DISABLE, "Loop");
			dbg_print1(DEBUG_DISABLE, "sub_index = %d", tem_pre_sub_index);
			dbg_print1(DEBUG_DISABLE, "temp_pre_x = %d", temp_pre_x);
			dbg_print1(DEBUG_DISABLE, "temp_pre_risk = %d", temp_pre_risk);
#endif
		}
	}
	if(res == 1)
	{
		g_char_info_sub_index = tem_pre_sub_index;
		cur_x = temp_pre_x;
		dbg_print_cur_MATRIX4x4(DEBUG_DISABLE, "Chosen", cur_x, cur_y);
#ifdef WINDOW_BASE
		dbg_print3(DEBUG_DISABLE, "chosen sub_index = %d, temp_pre_x = %d, temp_pre_risk = %d",
				tem_pre_sub_index, temp_pre_x, temp_pre_risk);
#else
		dbg_print_line(DEBUG_DISABLE, "Chosen");
		dbg_print1(DEBUG_DISABLE, "sub_index = %d", tem_pre_sub_index);
		dbg_print1(DEBUG_DISABLE, "temp_pre_x = %d", temp_pre_x);
		dbg_print1(DEBUG_DISABLE, "temp_pre_risk = %d", temp_pre_risk);
#endif
	}
	else
	{
		dbg_print_line(DEBUG_DISABLE, "GAME OVER!!!");
	}
	return res;
}
