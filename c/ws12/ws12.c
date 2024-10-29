#include "header.h"


int SaveStudent(const Student *student, const char *filename) 
{
    FILE *file = fopen(filename, "wb");
    
    if (!file) 
    {
        perror("Error opening file for writing");
        return 0;
    }
    
    if (1 != fwrite(student, sizeof(Student), 1, file)) 
    {
        perror("Error writing to file");
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}


int LoadStruct(Student *student, const char *filename) 
{
    FILE *file = fopen(filename, "rb");
    
    if (!file) 
    {
        perror("Error opening file for reading");
        return 0;
    }
    
    if (1 != fread(student, sizeof(Student), 1, file)) 
    {
        perror("Error reading from file");
        fclose(file);
        return 0;
    }
    
    fclose(file);
    return 1;
}

