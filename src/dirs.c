#include "../include/fs.h"

void add_dir( const char *dir_name )
{
	/*
	*	incrementing directory index
	*	adding the name to dir_list as soon as a directory is created in the filesystem
	*/
	curr_dir_idx++;
	strcpy( dir_list[ curr_dir_idx ], dir_name );
}

int is_dir( const char *path )
{
	path++; // Eliminating "/" in the path

	/*
	*	Used to determine the directory bit when running commands that check for the
	*	directory bit in Unix/Linux
	*
	*/
	
	for ( int curr_idx = 0; curr_idx <= curr_dir_idx; curr_idx++ )
		if ( strcmp( path, dir_list[ curr_idx ] ) == 0 )
			return 1;
	
	return 0;
}