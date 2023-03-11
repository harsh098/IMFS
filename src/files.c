#include "../include/fs.h"


/**
 * This section deals with operations on files whose directory bit is set to 0
 */

void add_file( const char *filename )
{

	/**
	 * Increment the current_file_idx and add the name to files_list
	*/
	curr_file_idx++;
	strcpy( files_list[ curr_file_idx ], filename );
	/**
	 * The "" empty string is written to the files_content array
	 * Drawbacks:-
	 * 	Appending the file is limited to 256 bytes as the size is fixed
	*/
	curr_file_content_idx++;
	strcpy( files_content[ curr_file_content_idx ], "" );
}

int is_file( const char *path )
{
	path++; // Eliminating "/" in the path
	
	/**
	 * Similar to dirs.c is_dir function
	 * determines if the file being read is a directory or a regular file
	*/
	for ( int curr_idx = 0; curr_idx <= curr_file_idx; curr_idx++ )
		if ( strcmp( path, files_list[ curr_idx ] ) == 0 )
			return 1;
	
	return 0;
}

int get_file_index( const char *path )
{
	path++; // Eliminating "/" in the path

	
	
	for ( int curr_idx = 0; curr_idx <= curr_file_idx; curr_idx++ )
		if ( strcmp( path, files_list[ curr_idx ] ) == 0 )
			return curr_idx;
	
	return -1;
}

void write_to_file( const char *path, const char *new_content )
{
	int file_idx = get_file_index( path );
	
	if ( file_idx == -1 ) // No such file
		return;
		
	strcpy( files_content[ file_idx ], new_content ); 
}
