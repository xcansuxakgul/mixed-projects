#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
	double x;
	double y;
	double z;
} Vector;

void print_vector(const Vector v);
Vector sum(const Vector v1, const Vector v2);
Vector diff(const Vector v1, const Vector v2);
double dot_product(const Vector v1, const Vector v2);
Vector cross_product(const Vector v1, const Vector v2);
double norm(const Vector v);
int is_unitvector(const Vector v);
Vector unit(const Vector v);
Vector multiplyby_scalar(const Vector v1, const double c);
double angle(const Vector v1, const Vector v2);
double distance(const Vector v1, const Vector v2);
int are_linearly_independent(const Vector v1, const Vector v2, const Vector v3);
int are_orthogonal(const Vector v1, const Vector v2, const Vector v3);
int are_orthonormal(const Vector v1, const Vector v2, const Vector v3);
Vector projection(const Vector v1, const Vector v2);
Vector orthogonal_projection(const Vector v1, const Vector v2);
int convert_2_orthogonal_basis(Vector *v1, Vector *v2, Vector *v3);
char* vector2str(const Vector v);

 
int main () 
{
	Vector v1 = {1, 2, 2}, v2 = {-1, 0, 2}, v3 = {0, 0, 1};
	double k = 2;
    printf("v1 = ");
    print_vector(v1);
    printf("v2 = ");
    print_vector(v2);
    printf("v3 = ");
    print_vector(v3);
	 
    printf("v1 + v2 = ");
	print_vector(sum(v1, v2));
	
	printf("v1 - v2 = ");
	print_vector(diff(v1, v2));
	
	printf("k * v1  = ");
	print_vector(multiplyby_scalar(v1, k));
	
	printf("v1 . v2 = %.2lf\n", dot_product(v1, v2));
	
	printf("v1 x v2 = ");
	print_vector(cross_product(v1, v2));
	
	printf("| v1 |  = %.2lf\n", norm(v1));
	
	if(is_unitvector(v1))
		printf("v1 is a unit vector.\n");
	else
		printf("v1 is not unit vector.\n");
	
	printf("unit( v1 ) = ");
	print_vector(unit(v1));
	
  	printf("angle(v1, v2) = %.2lf\n", angle(v1, v2));
	
	printf("distance(v1, v2) = %.2lf\n", distance(v1, v2));
		
	if(are_linearly_independent(v1, v2, v3))
		printf("Vectors are linearly independent.\n");
	else
		printf("Vectors are not linearly independent.\n");
	
	if(are_orthogonal(v1, v2, v3))
		printf("Vectors are orthogonal.\n");
	else
		printf("Vectors are not orthogonal.\n");
		
	if(are_orthonormal(v1, v2, v3))
		printf("Vectors are orthonormal.\n");
	else
		printf("Vectors are not orthonormal.\n");	
		
	printf("Projection of v1 onto v2 is = ");
	print_vector(projection(v1, v2));
	
	printf("Orthogonal projection of v1 onto v2 is = ");
	print_vector(orthogonal_projection(v1, v2));
	
	
	if(convert_2_orthogonal_basis(&v1, &v2, &v3)){
		printf("Orthogonalization of vectors:\n");
		printf("v1 = ");
	    print_vector(v1);
	    printf("v2 = ");
	    print_vector(v2);
	    printf("v3 = ");
	    print_vector(v3);
	}		
    
    puts(vector2str(v1));
    
    return 0; 
}

void print_vector(const Vector v){
	printf("(%.2f, %.2f, %.2f)\n", v.x, v.y,v.z);
}
Vector sum(const Vector v1, const Vector v2){
	Vector sm;
	sm.x = v1.x + v2.x;
	sm.y = v1.y + v2.y;
	sm.z = v1.z + v2.z;
	return sm;
}
Vector diff(const Vector v1, const Vector v2){
	Vector dif;
	dif.x = v1.x - v2.x;
	dif.y = v1.y - v2.y;
	dif.z = v1.z - v2.z;
	return dif;
}
Vector multiplyby_scalar(const Vector v1, const double c){
	Vector mult;
	mult.x = v1.x * c;
	mult.y = v1.y * c;
	mult.z = v1.z * c;
	return mult;
}
double dot_product(const Vector v1, const Vector v2){
	return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
Vector cross_product(const Vector v1, const Vector v2){
	Vector cross;
	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return cross;
}
double norm(const Vector v){
	return sqrt(dot_product(v, v));
}
int is_unitvector(const Vector v){ /* BAK BURAYA*/
	if(norm(v)==1.00)return 1;
	else return 0;
}
Vector unit(const Vector v){
	return multiplyby_scalar(v,1 / norm(v));
}
double angle(const Vector v1, const Vector v2){
	return acos(dot_product(v1, v2)/norm(v1)*norm(v2));
}
double distance(const Vector v1, const Vector v2){
	return norm(diff(v1,v2));
}
int are_linearly_independent(const Vector v1, const Vector v2, const Vector v3){
	return(v1.x*(v2.y*v3.z - v3.y *v2.z)-v2.x*(v1.y*v3.z-v3.y*v1.z)+v3.x*(v1.y*v2.z-v2.y*v1.z));
}
int are_orthogonal(const Vector v1, const Vector v2, const Vector v3){
	int res1,res2,res3;
	res1 = dot_product(v1,v2);
	res2 = dot_product(v1,v3);
	res3 = dot_product(v2,v3);
	if(res1==0 && res2==0 && res3==0) return 1;
	else return 0;
}
int are_orthonormal(const Vector v1, const Vector v2, const Vector v3){
	int res,unt1,unt2,unt3;
	res = are_orthogonal(v1,v2,v3);
	unt1 = is_unitvector(v1);
	unt2 = is_unitvector(v2);
	unt3 = is_unitvector(v3);
	if(res == 1 && unt1 == 1 && unt2 == 1 && unt3 == 1) return 1;
	else return 0;
}
Vector projection(const Vector v1, const Vector v2){
	return multiplyby_scalar(v2,dot_product(v1,v2) / pow(norm(v2),2));
}
Vector orthogonal_projection(const Vector v1, const Vector v2){
	return diff(v1,projection(v1,v2));
}
int convert_2_orthogonal_basis(Vector *v1, Vector *v2, Vector *v3){
	if(are_linearly_independent(*v1,*v2,*v3)){
		Vector teta1,teta2,teta3;
		teta1= *v1; 
		teta2=diff(*v2,projection(*v2,teta1));
		teta3 = diff(diff(*v3,projection(*v3,teta1)),projection(*v3,teta2));
		*v1 = teta1;
		*v2 = teta2;
		*v3 = teta3;
		return 1;
	}return 0;
}
char* vector2str(const Vector v){
	char *str ;
	str = (char *)malloc(sizeof(int)*10);
	sprintf(str,"(%.2f,%.2f,%.2f)",v.x,v.y,v.z);
	return str;
}