#include "header.h"

int main(void) 
{

    Student avshalom;
    Student avshalomData;
    
    Human avshalomHuman;
    Real avshalomReal;
    
    StudentGrades avshalomGrades;
    
    avshalomHuman.psychology = 99.9;
    avshalomHuman.sociology = 99.8;
    avshalomHuman.philosophy = 99.7;
    avshalomHuman.anthropology = 99.6;
    
    avshalomReal.physics = 99.5;
    avshalomReal.math = 99.4;
    avshalomReal.chemistry = 99.3;
    avshalomReal.biology = 99.2;
    
    avshalomGrades.humanGrades = avshalomHuman;
    avshalomGrades.raelGrades = avshalomReal;
    avshalomGrades.sport = 100;    
    
    avshalom.studentGrades = avshalomGrades;
    strcpy(avshalom.firstName , "Avshalom");
    strcpy(avshalom.lastName , "Ariel");    
    

    if (SaveStudent(&avshalom, "Avshalom.bin")) 
    {
        printf("Student saved\n");
    } 
    else 
    {
        perror("Failed to save student.\n");
        return 1;
    }


    if (LoadStruct(&avshalomData, "Avshalom.bin")) 
    {
        printf("First name: %s\nLast name: %s\n", avshalomData.firstName, avshalomData.lastName);
        printf("sport grade:%f\n",avshalomData.studentGrades.sport);
        
        printf("psychology grade:%f\n",avshalomData.studentGrades.humanGrades.psychology);
        printf("sociology grade:%f\n",avshalomData.studentGrades.humanGrades.sociology);
        printf("philosophy grade:%f\n",avshalomData.studentGrades.humanGrades.philosophy);
        printf("anthropology grade:%f\n",avshalomData.studentGrades.humanGrades.anthropology);
        
        printf("physics grade:%f\n",avshalomData.studentGrades.raelGrades.physics);
        printf("math grade:%f\n",avshalomData.studentGrades.raelGrades.math);
        printf("chemistry grade:%f\n",avshalomData.studentGrades.raelGrades.chemistry);
        printf("biology grade:%f\n",avshalomData.studentGrades.raelGrades.biology);
        
    } 
    else 
    {
        perror("Failed to load student.\n");
        return 1;
    }

    return 0;
}


















