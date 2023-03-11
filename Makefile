all: dirs run files main 

dirs: src/dirs.c include/fs.h
		gcc -c src/dirs.c -o build/dirs.o `pkg-config fuse --cflags --libs` -I ./src

files: src/files.c include/fs.h
		gcc -c src/files.c -o build/files.o `pkg-config fuse --cflags --libs` -I ./src

run: src/main.c include/fs.h
		gcc -c src/main.c -o build/main.o `pkg-config fuse --cflags --libs` -I ./src

main: build/dirs.o build/main.o build/files.o include/fs.h
		gcc -o bin/fs build/dirs.o build/main.o build/files.o `pkg-config fuse --cflags --libs` -I ./src
