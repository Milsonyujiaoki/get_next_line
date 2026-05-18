#include <string.h>

void *ft_bzero(void *ptr, size_t count) {
	//Declarar variáveis
	//instanciar variáveis
	//percorrer o ponteiro
	//transformar o byte em zero
    unsigned char *p;

    p = (unsigned char *)ptr;

    while(count--){
    	*p = 0;
    	p++;
    }
    return NULL;
}
