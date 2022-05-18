# Linear-Algebra-with-C
## The Definition of Functions

* void print_vector(const Vector v): 
  It prints the vector as shown in output.
  
* Vector sum(const Vector v1, const Vector v2):
  It returns the sum of two vectors.
  
* Vector sum(const Vector v1, const Vector v2):
  It returns the sum of two vectors.
  
* double dot_product(const Vector v1, const Vector v2):
  It returns the dot product of two vectors
  
* Vector cross_product(const Vector v1, const Vector v2):
  It returns the cross product of two vectors.

* double norm(const Vector v):
  It returns the norm (length) of a vector.
  
* int is_unitvector(const Vector v):
  It check whether a vector is unit vector or not.
  
* Vector unit(const Vector v):
  It returns the unit vector of a vector.

* Vector multiplyby_scalar(const Vector v1, const double c):
  It returns the vector that is the scalar multiplication of a vector by a constant.

* double angle(const Vector v1, const Vector v2):
  It returns the angle between two vectors.

* double distance(const Vector v1, const Vector v2):
  It returns the distance between two vectors. (|v1-v2|)

* int are_linearly_independent(const Vector v1, const Vector v2, const Vector v3):
  It check whether three vectors are linearly independent or not.
 
* int are_orthogonal(const Vector v1, const Vector v2, const Vector v3):
  It check whether three vectors are orthogonal or not.

* int are_orthonormal(const Vector v1, const Vector v2, const Vector v3):
  It check whether three vectors are orthonormal or not.

* Vector projection(const Vector v1, const Vector v2):
  It returns the projection vector of v1 onto the vector v2.

* Vector orthogonal_projection(const Vector v1, const Vector v2):
  It returns the orthogonal projection vector of v1 onto the vector v2.

* int convert_2_orthogonal_basis(Vector *v1, Vector *v2, Vector *v3):
  It converts three linearly independent vectors into an orthogonal basis by using the 

* Gram Schmidt Process:
  If vectors are not linearly independent, the function return 0, otherwise it returns 1.

* char* vector2str(const Vector v):
  It converts a vector into a string (such as “(2.00, 1.00, 0.00)”) and it returns the string.
