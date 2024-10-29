#ifndef HEADER
#define HEADER

#include <stdio.h> /*printf, FILE**/
#include <string.h>/*strcpy*/


typedef struct Human
{
	float psychology;
	float sociology;
	float philosophy;
	float anthropology;
} Human;


typedef struct Real
{
	float physics;
	float math;
	float chemistry;
	float biology;
} Real;


typedef struct StudentGrades
{
	Human humanGrades;
	Real raelGrades;
	float sport;

} StudentGrades;


typedef struct Student
{
	StudentGrades studentGrades;
	char firstName[20];
	char lastName[20]; 
} Student;


int SaveStudent(const Student* student, const char* filename);
int LoadStruct(Student* student, const char* filename);


#endif









