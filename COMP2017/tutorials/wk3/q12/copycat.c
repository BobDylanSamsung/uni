#include <stdio.h>
#include <errno.h>
#define BUF_SZ 100

void print_file(FILE* file){
	char buf[BUF_SZ];

	while(fgets(buf, BUF_SZ, file)){
		printf("%s", buf);
	}

}

int main(int argc, char** argv){

	FILE* infile;

	if (1 == argc){
		infile = stdin;
		print_file(infile);
	}
	else{
		for(int i = 1; i < argc; i++){
			infile = fopen(argv[i], "r");
			print_file(infile);
			fclose(infile);
		}
	}


}