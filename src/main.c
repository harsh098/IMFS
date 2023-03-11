
 
#include "../include/fs.h"


char dir_list[ 256 ][ 256 ];
int curr_dir_idx = -1;
char files_list[ 256 ][ 256 ];
int curr_file_idx = -1;
char files_content[ 256 ][ 256 ];
int curr_file_content_idx = -1;


static int do_getattr( const char *path, struct stat *st )
{
	/*
		 * st_mode specifies if file in question is a directory,
		 * regular file or other;
		 *
		 * st_nlink specifies number of hardlinks
		 *
		 * st_size is size of file in bytes
		 *
		 * S_IFDIR macro indicates file is a directory 
		 * we do a bitwise or to set default permission bits
		 * 	-rwx-r-x-r-x = 0755 (Why directory bit 0? because 0|1 = 1)
		 * no of hardlinks is set to 2 by default for directories
		 * 
		 * S_IFREG is used to indicate regular files
		 * we do a bitwise or to set permission bits as
		 * 	-rw-r--r-- = 0644
		 * no of hardlinks set to 1 by default for regular files
		 *
		 * st_size = 1024 bytes for files is set here
		 */
	st->st_uid = getuid(); // The owner of the file/directory is the user who mounted the filesystem
	st->st_gid = getgid(); // The group of the file/directory is the same as the group of the user who mounted the filesystem
	st->st_atime = time( NULL ); // The last "a"ccess of the file/directory is right now
	st->st_mtime = time( NULL ); // The last "m"odification of the file/directory is right now
	
	if ( strcmp( path, "/" ) == 0 || is_dir( path ) == 1 )
	{
		st->st_mode = S_IFDIR | 0755;
		st->st_nlink = 2; 	}
	else if ( is_file( path ) == 1 )
	{
		st->st_mode = S_IFREG | 0644;
		st->st_nlink = 1;
		st->st_size = 1024;
	}
	else
	{
		return -ENOENT;
	}
	
	return 0;
}

static int do_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi )
{
	/*
	 * We define the files available in the location in the do_readdir function it has five parameters:-
	 * path = path of the directory in question;
	 * buffer =  contains the names of files/directories which are available inside the directory in question.
	 * filler is the function sent by fuse we could use it to fill the buffer with available files in path , the function returns 0 on success
	 *
	 * */
	filler( buffer, ".", NULL, 0 ); // Current Directory
	filler( buffer, "..", NULL, 0 ); // Parent Directory
	
	if ( strcmp( path, "/" ) == 0 ) // If the user is trying to show the files/directories of the root directory show the following
	{
		for ( int curr_idx = 0; curr_idx <= curr_dir_idx; curr_idx++ )
			filler( buffer, dir_list[ curr_idx ], NULL, 0 );
	
		for ( int curr_idx = 0; curr_idx <= curr_file_idx; curr_idx++ )
			filler( buffer, files_list[ curr_idx ], NULL, 0 );
	}
	
	return 0;
}

static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi )
{
	printf("Reading %s at offset: %ld\n", path, offset);
	int file_idx = get_file_index( path );
	
	if ( file_idx == -1 )
		return -1;
	
	char *content = files_content[ file_idx ];
	
	memcpy( buffer, content + offset, size );
		
	return strlen( content ) - offset;
}

static int do_mkdir( const char *path, mode_t mode )
{
	path++;
	add_dir( path );
	
	return 0;
}

static int do_mknod( const char *path, mode_t mode, dev_t rdev )
{
	path++;
	add_file( path );
	
	return 0;
}

static int do_write( const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *info )
{
	write_to_file( path, buffer );
	printf("Writing to %s at offset: %ld\n", path, offset);
	return size;
}

//This struct outlines fuse_operations.
static struct fuse_operations operations = {
    .getattr	= do_getattr,
    .readdir	= do_readdir,
    .read		= do_read,
    .mkdir		= do_mkdir,
    .mknod		= do_mknod,
    .write		= do_write,
};

int main( int argc, char *argv[] )
{
	return fuse_main( argc, argv, &operations, NULL );
}
