// #include <malloc_internal.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>


/* Contents, described in more detail in "description of public routines" below.

  Standard (ANSI/SVID/...)  functions:
    malloc(size_t n);
    calloc(size_t n_elements, size_t element_size);
    free(void* p);
    realloc(void* p, size_t n);
    memalign(size_t alignment, size_t n);
    valloc(size_t n);
    mallinfo()
    mallopt(int parameter_number, int parameter_value)

  Additional functions:
    independent_calloc(size_t n_elements, size_t size, void* chunks[]);
    independent_comalloc(size_t n_elements, size_t sizes[], void* chunks[]);
    pvalloc(size_t n);
    malloc_trim(size_t pad);
    malloc_usable_size(void* p);
    malloc_stats();
*/

// ◦ mmap(2) 
// ◦ munmap(2)
// ◦ getpagesize under OSX or sysconf(_SC_PAGESIZE) under linux
// ◦ getrlimit(2) 
/*
	Main de ejemplo con mmap asociado a un archivo esto permite su lectura sin nececidad
	de usar malloc y read evitaando tantos llamados al sistema y tratando su contenido
	como un puntero
*/

/*int main() {
	int fd = open("tests/test.text", O_RDONLY);
	if (fd == -1)
		return (1);
	struct stat statbuf;
	fstat(fd, &statbuf);
	char *ptr = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
		return (dprintf(1, "Estoy jodido loco :c\n"), close(fd), 1);
	if (!ptr)
		dprintf(1, "Soy null loco :c\n");
	else
		dprintf(1, "No soy null loco :D %p %lu %li %s\n", ptr, sizeof(ptr), statbuf.st_size, ptr);
	munmap(ptr, statbuf.st_size);
		dprintf(1, "getpagesize %i", getpagesize());
	close(fd);
	return (0);
}
*/

/*
	En este main se realiza una prueba de mmap sin depender de un archivo y escribimos sobre el para
	cambiar su valor
*/
/*int	main(void) {

	size_t	system_size = getpagesize();

	char	*ptr = mmap(NULL, system_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (dprintf(2, "Error al inicializar el mmao\n"), EXIT_FAILURE);
	// snprintf(ptr, system_size, "Hola desde mmap sin archivo!");
	for (size_t iter = 0; iter < system_size; iter++)
		ptr[iter] = '0';
	dprintf(1, "[PTR] -> %s size the pointer %lu\n", ptr, strlen(ptr));
	if (munmap(ptr, system_size) == ERROR)
		return dprintf(2, "Error en limpiar la memoria\ns");
	return (EXIT_SUCCESS);
}*/

/*
	En este main se puede ver la informacion de cuantos mapeos hace y si usa el heap no
	#include <malloc.h>
*/
// int main() {
//     void *p1 = malloc(100);       // probablemente en el heap
//     void *p2 = malloc(200000);    // probablemente en mmap
//     malloc_stats();               // imprime info interna
// 	static int a;
// 	// int a = 0;
// 	dprintf(1, "%lu\n", sizeof(a));
//     free(p1);
//     free(p2);
// }
void print_bits(unsigned int num) {
    for (int i = sizeof(unsigned int) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

// int main(void) {
// 	printf("alignof(char) %lu\n", __alignof__(char));
// 	printf("alignof(long double) %lu\n", __alignof__(long double));
// 	printf("MALLOC_ALIGNMENT %lu\n", MALLOC_ALIGNMENT);
// 	printf("--->%lu\n", SYSTEM_SIZE);

// 	char	*ptr = MEMORY_PAGE;
// 	if (ptr == MAP_FAILED)
// 		return (dprintf(2, "Error al inicializar el mmao\n"), EXIT_FAILURE);
// 	for (size_t iter = 0; iter < SYSTEM_SIZE; iter++)
// 		ptr[iter] = '0';
// 	dprintf(1, "[PTR] -> %s size the pointer %lu\n", ptr, strlen(ptr));
// 	if (munmap(ptr, SYSTEM_SIZE) == ERROR)
// 		return dprintf(2, "Error en limpiar la memoria\ns");

// 	size_t foo = 10;

// 	foo |= INUSE_FLAG;
// 	printf("| foo %lu\n", foo);
// 	print_bits(foo);
// 	foo &= ~INUSE_FLAG;
// 	printf("& foo %lu\n", foo);
// 	print_bits(foo);
// 	print_bits(INUSE_FLAG);
// 	dprintf(1, "foo=%lu  comparator or (%ld)\n", foo, (foo | (size_t)11));
// 	return (0);
// }

// #include <stdlib.h>
#include <limits.h>

typedef struct s_test t_test;

struct s_test
{
	int	a;
	unsigned long b;
	char	*c;
	t_test	*next;
};


/******************************************************************************/
/*                            COLORS                                          */
/******************************************************************************/

#define END	"\033[m"
#define RED	"\033[1;31m"
#define GREEN	"\033[1;32m"
#define YELLOW	"\033[1;33m"
#define BLUE	"\033[1;34m"
#define TUR	"\033[1;35m"
#define CYAN	"\033[1;36m"
#define ORANGE	"\033[38;5;208m"
#define PURPLE	"\033[38;5;128m"

/* error messages */
#define FT_LS "\033[1;31mft_ls: \033[m"
#define ERR_MALLOC "%serror trying to allocate memory `%s'\n"
#define ERR_INVALID "%sinvalid option -- '%s'\n"
#define ERR_OPEN "%scannot open directory '%s':%s\n"
#define WARNING_POINTER "%sWarning%s: func: %s pointer %s are null\n"

int	main(void) {
	char *ptr = malloc(sizeof(t_test *) * 4);
	size_t assigned = sizeof(sizeof(t_test *) * 4);
	if (!ptr) {
		dprintf(1, "Estoy malito :c\n");
		return 1;
	}
	dprintf(1, "%s[ASSIGNED SIZE]%s size = %lu\n", BLUE, END, sizeof(ptr));
	dprintf(1, "%s[SIZE]%s size = %lu\n", BLUE, END, assigned);
	dprintf(1, "%s[SIZE]%s memory size malloc = %lu\n", BLUE, END, sizeof(ptr));
	if (sizeof(ptr) == assigned)
		dprintf(1, "%s[TEST]%s memory size %sOK%s\n", BLUE, END, GREEN, END);
	else
		dprintf(1, "%s[ERROR]%s memory size %sKO%s\n", RED, END, RED, END);
	dprintf(1, "%s[REFERENCE]%s number pointer = %p\n", BLUE, END, ptr);
	free(ptr);
}
