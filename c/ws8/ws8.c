
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "ws8.h" 


#define MAX_LENGTH 300 

void Print(int num)
{
	printf("%d", num);
}



struct str_two_funcs 
{
  char* str;
  int (*Compare)(char*);
  enum results(*Invoke)(char*);
};




int loggit(void)
{
	char key;
	char str[300];
	char file_name[MAX_LENGTH];
	int i; 
	FILE *ptrfile;
	struct str_two_funcs choice_arr[3];

    printf("Enter a file name, make sure its in the right format: \n");
    
    fgets(file_name, MAX_LENGTH, stdin); 
	
    printf("You file name is: %s\n", file_name); 
	
	ptrfile = fopen(file_name , "a");
	
	if ((ptrfile = fopen(file_name, "r")) == NULL)
	{
       printf("Error! opening file");
       exit(1);
   }
	
	printf("enter contenct of thr file\n");

	key ='a';
	
	
	choice_arr[0].Compare = Cmp_rmv;
	choice_arr[1].Compare = Cmp_cnt;
	choice_arr[2].Compare = Cmp_ext;
	
	choice_arr[0].str = "-remove";
	choice_arr[1].str = "-count";
	choice_arr[2].str = "-exit";
	
	choice_arr[0].Invoke = Invoke_rmv;
	choice_arr[1].Invoke = Invoke_cnt;
	choice_arr[2].Invoke = Invoke_ext;
	
	
	while(key != 27)
	{
		key = 'a';		
		memset(str, 0, sizeof(str));
		
		while(key != '\n' && key != 27)
		{
			scanf("%c", &key);
			strncat(str, &key, 1);
		}

		if (*str == '-')
		{
			for(i = 0; i < 3; ++i)
			{
				if(choice_arr[i].Compare(str) == 0)
				{
					choice_arr[i].Invoke(file_name);
					key = 27;
					printf("inside condition");
				} 
				printf("in - loop\n");
			}
		}
		
		
		fprintf(ptrfile, "%s", str);
		
	}

	fclose(ptrfile);
		
    printf("finished\n");

    return 0;
}



int Cmp_rmv (char* str)
{
	int result;
	char* str1;
	
	str1 = "-remove";
	result = strcmp(str, str1);
	
	return result;
}

int Cmp_cnt (char* str)
{
	int result;
	char* str1;
	
	str1 = "-count";
	
	result = strcmp(str, str1);
	
	return result;
}

int Cmp_ext (char* str)
{
	int result;
	char* str1;
	
	str1 = "-exit";
	
	result = strcmp(str, str1);
	
	return result;
}


enum results Invoke_rmv(char* fname)
{
	enum results result = RESULT;
	int rem;
	
	rem = remove(fname);
	if (rem == 0)
	{
        printf("Deleted successfully");
    }
    else
    {
        printf("Unable to delete the file");
	}
	printf("removed the file\n");
	return result;
}


enum results Invoke_cnt(char* fname)
{
	enum results result = RESULT;
	int ch=0;
  	int lines=0;

	FILE *fp = fopen(fname,"r");
	
	while(!feof(fp))
	{
  		ch = fgetc(fp);
  		if(ch == '\n')
  		{
    		lines++;
    	}
    	return result;
    }
	printf("the number of lines is %d \n", lines);	
	
	printf("count the file\n");
	return result;  
}


enum results Invoke_ext(char* fname)
{
	enum results result = RESULT;
	FILE *fp = fopen(fname,"r");
	fclose(fp);
	printf("exit the file\n");

	return result;
	
}


/*



int loggit(void)
{
	char key;
	char str[300];
	char file_name[MAX_LENGTH];
	int i; 
	FILE *ptrfile;
	struct str_two_funcs choice_arr[3];

    printf("Enter a file name, make sure its in the right format: \n");
    
    fgets(file_name, MAX_LENGTH, stdin); 
	
    printf("You file name is: %s\n", file_name); 
	
	ptrfile = fopen(file_name , "a");
	
	if ((ptrfile = fopen(file_name, "r")) == NULL)
	{
       printf("Error! opening file");
       exit(1);
   }
	
	printf("enter contenct of thr file\n");

	key ='a';
	
	
	choice_arr[0].Compare = Cmp_rmv;
	choice_arr[1].Compare = Cmp_cnt;
	choice_arr[2].Compare = Cmp_ext;
	
	choice_arr[0].str = "-remove";
	choice_arr[1].str = "-count";
	choice_arr[2].str = "-exit";
	
	choice_arr[0].Invoke = Invk_rmv;
	choice_arr[1].Invoke = Invk_cnt;
	choice_arr[2].Invoke = Invk_ext;
	
	
	while(key != 27)
	{
		key = 'a';		
		memset(str, 0, sizeof(str));
		
		while(key != '\n' && key != 27)
		{
			scanf("%c", &key);
			strncat(str, &key, 1);
			
		}

		if (*str == '-')
		{
			for(i = 0; i < 3; ++i)
			{
				if(!choice_arr[i].Compare)
				{
					choice_arr[i].Invoke(file_name);
					
				} 
			}
		}
		
		
		
		fprintf(ptrfile, "%s", str);
		
	}
	fscanf(ptrfile, "%s", str);
	fclose(ptrfile);
		
    printf("finished\n");

    return 0;
}



int Cmp_rmv (char* str)
{
	int result;
	if (strlen(str) == strlen("-remove"))
	{
		result = strcmp(str, "-remove");
	}
	
	return result;
}

int Cmp_cnt (char* str)
{
	int result;
	if (strlen(str) == strlen("-count"))
	{
		result = strcmp(str, "-count");
	}
	
	return result;
}

int Cmp_ext (char* str)
{
	int result;
	if (strlen(str) == strlen("-exit"))
	{
		result = strcmp(str, "-exit");
	}
	
	return result;
}


int Invk_rmv(char* pfile)
{

	int rem;
	
	rem = remove(pfile);
	if (rem == 0)
	{
        printf("Deleted successfully");
    }
    else
    {
        printf("Unable to delete the file");
	}
	
	return 0;
}


int Invk_cnt(char* fname)
{
	int ch=0;
  	int lines=0;

	FILE *fp = fopen(fname,"r");
	
	while(!feof(fp))
	{
  		ch = fgetc(fp);
  		if(ch == '\n')
  		{
    	lines++;
    	}
    }
	printf("the number of lines is %d \n", lines);	
	
	return 0;  
}


int Invk_ext(char* fname)
{

	FILE *fp = fopen(fname,"r");
	fclose(fp);
	printf("exit the file");
	
	return 0;
	
}

*/


/*






int loggit(void)
{
	char key;
	char str[300];
	char file_name[MAX_LENGTH];
	int i; 
	FILE *ptrfile;
	struct str_two_funcs choice_arr[3];
	int lines;
	
	choice_arr[0].Compare = Cmp_rmv;
	choice_arr[1].Compare = Cmp_cnt;
	choice_arr[2].Compare = Cmp_ext;
	
	choice_arr[0].str = "-remove";
	choice_arr[1].str = "-count";
	choice_arr[2].str = "-exit";
	
	choice_arr[0].Invoke = Invoke_rmv;
	choice_arr[1].Invoke = Invoke_cnt;
	choice_arr[2].Invoke = Invoke_ext;

    printf("Enter a file name, make sure its in the right format: \n");
    
    fgets(file_name, MAX_LENGTH, stdin); 
	
    printf("You file name is: %s\n", file_name); 
	
	ptrfile = fopen(file_name , "a");
	
	if ((ptrfile = fopen(file_name, "a")) == NULL)
	{
       printf("Error! opening file");
       exit(1);
    }
	
	printf("enter contenct of thr file\n");

	key ='a';	
	lines = 0;
	
	while(key != 27)
	{
		key = 'a';		
		memset(str, 0, sizeof(str));
		
		
		while(key != '\n' && key != 27)
		{
			scanf("%c", &key);
			strncat(str, &key, 1);
		}

		++lines;	
		
		if (*str == '-')
		{
			for(i = 0; i < 3; ++i)
			{
				if(choice_arr[i].Compare(str) == 0)
				{
					choice_arr[i].Invoke(file_name);
					key = 27;
					if (i == 1)
					{
						printf("number of lines is %d\n", (lines-1));
					}
				} 
			}
			fputs(str, ptrfile);
		}
		else if (*str == '<')
		{
			fclose(ptrfile);
			Invoke_app(file_name, str);
			fopen(file_name, "a");
		}
		else
		{
			fputs(str, ptrfile);
		}		
	}
	fscanf(ptrfile, "%s", str);
	fclose(ptrfile);
		
    printf("finished\n");

    return 0;
}



int Cmp_rmv (char* str)
{
	int result;
	char* str1;
	
	str1 = "-remove";
	result = strncmp(str1, str, 7);
	
	return result;
}

int Cmp_cnt (char* str)
{
	int result;
	char* str1;
	
	str1 = "-count";
	
	result = strncmp(str1, str, 6);
	
	return result;
}

int Cmp_ext (char* str)
{
	int result;
	char* str1;
	
	str1 = "-exit";
	
	result = strncmp(str1, str, 5);
	
	return result;
}


enum results Invoke_rmv(char* fname)
{
	enum results result = RESULT;
	int rem;
	
	rem = remove(fname);
	if (rem == 0)
	{
        printf("Deleted successfully");
    }
    else
    {
        printf("Unable to delete the file");
	}

	return result;
}


enum results Invoke_cnt(char* fname)
{
	enum results result = RESULT;
	int lines; 
	FILE *fp = fopen(fname,"r");
	char c;
	
	c = 'a';
	lines = 0;
	
	while(c != EOF)
	{
        c = getc(fp);

        if (c == '\n')
        { 
            lines = lines + 1;
        }
 	}
    fclose(fp);
    
	printf("the number of lines is %d \n", lines);
	
	return result;  
}


enum results Invoke_ext(char* fname)
{
	enum results result = RESULT;
	FILE *fp = fopen(fname,"r");
	fclose(fp);
	printf("exit the file succesfuly\n");

	return result;
	
}


enum results Invoke_app(char* filename, char *str)
{
	enum results result = RESULT;
	FILE *file; 
	size_t str_len;
	long fileSize;
	char *fileContent;
	
	file = fopen(filename, "r+");
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return result;
    }


    str_len = strlen(str);


    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);


    fileContent = (char *)malloc(fileSize + 1);
    if (fileContent == NULL) 
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return result;
    }

    rewind(file);
    fread(fileContent, 1, fileSize, file);


    rewind(file);


    fwrite(str, 1, str_len, file);


    fwrite(fileContent, 1, fileSize, file);


    fileContent[fileSize] = '\0';


    free(fileContent);


    fclose(file);
}




















*/
