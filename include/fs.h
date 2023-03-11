#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

extern char dir_list[256][256];
extern int curr_dir_idx;
extern char files_list[256][256];
extern int curr_file_idx;
extern char files_content[256][256];
extern int curr_file_content_idx;
extern void add_dir( const char *dir_name );
extern int is_dir( const char *path );
extern void add_file( const char *filename );
extern int is_file( const char *path );
extern int get_file_index( const char *path );
extern void write_to_file( const char *path, const char *new_content );
