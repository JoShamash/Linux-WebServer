#include "../header.h"

int main(){
	int stack_data = 0;
	char* heap_data = malloc(1024);
	strcpy(heap_data, "hello");
	static int static_data = 0;	

	if(fork()){
		while(1){
			sleep(2);
			printf("I am father, pid = %d\n", getpid());
			printf("stack_data(%p): %d\n", &stack_data, stack_data++);			
			strcat(heap_data, "a");
			printf("heap_data(%p): %s\n", heap_data, heap_data);
			printf("static_data(%p): %d\n", &static_data, static_data++);
			printf("----------------------\n");
		}
	}else{
		while(1){
			sleep(3);
			printf("I am son, pid = %d\n", getpid());
			printf("stack_data(%p): %d\n", &stack_data, stack_data--);			
			strcat(heap_data, "b");
			printf("heap_data(%p): %s\n", heap_data, heap_data);
			printf("static_data(%p): %d\n", &static_data, static_data--);
			printf("----------------------\n");
		}
	}
	return 0;
}
