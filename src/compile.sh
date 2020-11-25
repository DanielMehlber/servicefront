emcc -Oz --closure 1 -s MALLOC="emmalloc" -s ASSERTIONS=0 -DNDEBUG example-clientlet.c
