#include <malloc_internal.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define and &&

// ◦ mmap(2) 
// ◦ munmap(2)
// ◦ getpagesize under OSX or sysconf(_SC_PAGESIZE) under linux
// ◦ getrlimit(2) 

int main() {
	int fd = open("tests/test.text", O_RDONLY);
	if (fd == -1)
		return (1);
	struct stat statbuf;
	fstat(fd, &statbuf);
	char *ptr = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (!ptr)
		dprintf(1, "Soy null loco :c\n");
	else
		dprintf(1, "No soy null loco :D %p %lu %i\n", ptr, sizeof(ptr), stat.st_size);
	munmap(ptr, statbuf.st_size);
	close(fd);
	if (1 and 1)
		dprintf(1, "probando mi operador\n");
	return (0);
}