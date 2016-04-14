#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#define TRUE 1
#define FALSE 0
#define MAX 256
//ambos são ficheiros regulares;
//o ambos têm o mesmo nome;
//o ambos têm as mesmas permissões de acesso;
//o ambos têm o mesmo conteúdo.


int compareFileContent(char *filePath1, char *filePath2)
{
	FILE *file1, *file2;

	//used to compare files character by character
	int ch1, ch2;

	file1 = fopen(filePath1, "r");

	if(file1 == NULL)
	{
		perror("Opening file1 to compare");
		exit(6);
	}

	file2 = fopen(filePath2, "r");

	if(file2 == NULL)
	{
		perror("Opening file2 to compare");
		exit(6);
	}


	//Compares char by char until the end of one file
	do{
		ch1 = getc(file1);
		ch2 = getc(file2);
	}while((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2));

	fclose(file1);
	fclose(file2);

	if(ch1 == ch2) //if the characters remain the same, the loop ran through the entire two files, so they are identical
		return 1; //If they are identical, return 1 for true

	//If they are not identical, return 0 for false
	return 0;
}

int compareFiles(char *fileInfo1, char *fileInfo2)
{
	char *ch1, *ch2;

	//Reads first word, i.e., fileName

	char* token1 = strtok(fileInfo1, " ");
	char* token2 = strtok(fileInfo2, " ");

	char fileName1[MAX];
	char fileName2[MAX];

	strcat(fileName1, token1);
	strcat(fileName2, token2);

	//compares files' names. On different file names, return 0 for false
	//NOTE: strcmp returns 0 if the strings are equal!

	if(strcmp(fileName1, fileName2))
		return 0;


	char at1[MAX];
	char at2[MAX];

	//Reads second word, i.e., last access time

	token1 = strtok(NULL, " ");
	token2 = strtok(NULL, " ");

	strcat(at1, token1);
	strcat(at2, token2);

	//compares files' last access time

	if(strcmp(at1, at2))
		return 0;


	char size1[MAX];
	char size2[MAX];

	//Reads third word, i.e., file size

	token1 = strtok(NULL, " ");
	token2 = strtok(NULL, " ");

	strcat(size1, token1);
	strcat(size2, token2);

	//compares files' size

	if(strcmp(size1, size2))
		return 0;



	char m1[MAX];
	char m2[MAX];

	//Reads forth word, i.e., mode

	token1 = strtok(NULL, " ");
	token2 = strtok(NULL, " ");

	strcat(m1, token1);
	strcat(m2, token2);

	//compares files' size

	if(strcmp(m1, m2))
		return 0;

	char path1[MAX];
	char path2[MAX];

	token1 = strtok(NULL, " ");
	token2 = strtok(NULL, " ");

	strcat(path1, token1);
	strcat(path2, token2);


	return compareFileContent(path1, path2);

}



int createProcess(char *fileName, char *files)
{
  int pid = fork();
  if(pid == 0)
  {
    execlp("listdir", "listdir", fileName, files, NULL);
    perror("execlp");
    exit(4);
  }
  return pid;
}




int main(int argc, char *argv[]) {

es
  if (argc != 2) {
    fprintf(stderr, "Invalid Arguments");
    exit(1);
  }

  char files[] = "\"To Save\" File";

  if(createProcess(argv[1], files) > 0)
  {
    wait(); // a completar
    //compareFiles(files);
  }

  return 0;
}
