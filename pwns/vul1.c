//gcc vul1.c -m64 -fno-stack-protector -z execstack -no-pie -o vul1 -Wl,--dynamic-linker=/lib64/ld-linux-x86-64.so.2
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	char buf[256];
	strcpy(buf,argv[1]);
	printf("Input:%s\n",buf);
	return 0;
}
