#ifndef JMATRIX_H
#define JMATRIX_H

#include "JIncludes.h"

template <class T>
class JMatrix {
private:
	int nr,nc;
	T** v;
public:
	JMatrix();
	JMatrix(int r,int c);
	JMatrix(int r,int c,const T &a);
	JMatrix(int r,int c,const T* a);
	JMatrix(const JMatrix &a);
	JMatrix & operator=(const JMatrix &a);
	typedef T value_type;
	inline T* operator[](const int i);
	inline const T* operator[](const int i) const;
	//TODO: move to a typedef of JMatrix<double>
	//inline JMatrix<T> & operator*=(const T &a);
	//inline JMatrix<T> & operator/=(const T &a);
	//inline JMatrix<T> & operator+=(const T &a);
	//inline JMatrix<T> & operator-=(const T &a);
	inline int nrows() const;
	inline int ncols() const;
	void resize(int r,int c);
	void assign(int r,int c,const T &a);
	~JMatrix();

	T* dataPointer();
};

/****************************************************************************************/
//ctors, dtors, copy


template <class T>
JMatrix<T>::JMatrix(): nr(0), nc(0), v(NULL) {}

template <class T>
JMatrix<T>::JMatrix(int r, int c): nr(r), nc(c), v(nr > 0 ? new T*[nr] : NULL) {
	int i,nel = nr*nc;
	if (v) v[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) v[i] = v[i-1] + nc; 
}

template <class T>
JMatrix<T>::JMatrix(int r, int c, const T &a): nr(r), nc(c), v(nr > 0 ? new T*[nr] : NULL) {
	int i,j,nel = nr*nc;
	if (v) v[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) v[i] = v[i-1] + nc;
	for (i = 0; i < nr; i++) for (j = 0; j < nc; j++) memcpy(v[i][j],&a,sizeof(T));//v[i][j] = a;
}

template <class T>
JMatrix<T>::JMatrix(int r, int c, const T* a): nr(r), nc(c), v(nr > 0 ? new T*[nr] : NULL) {
	int i,j,nel = nr*nc;
	if (v) v[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) v[i] = v[i-1] + nc;
	//for (i = 0; i < nr; i++) for (j = 0; j < nc; j++) v[i][j] = *a++;
	if (v) memcpy(v[0],a,sizeof(T) * nel);
}

template <class T>
JMatrix<T>::JMatrix(const JMatrix<T> &a): nr(a.nr), nc(a.nc), v(nr > 0 ? new T*[nr] : NULL) {
	int i,j,nel = nr*nc;
	if (v) v[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) v[i] = v[i-1] + nc;
	//for (i = 0; i < nr; i++) for (j = 0; j < nc; j++) v[i][j] = a[i][j];
	if (v) memcpy(v[0],a.v[0],sizeof(T) * nel);
}

template <class T>
JMatrix<T> & JMatrix<T>::operator=(const JMatrix &a) {
	if (this != &a) {
		int i,j,nel;
		if (nr != a.nr || nc != a.nc) {
			if (v != NULL) {
				delete[] (v[0]);
				delete[] (v);
			}
			nr = a.nr;
			nc = a.nc;
			v = nr > 0 ? new T*[nr] : NULL;
			nel = nr*nc;
			if (v) v[0] = nel > 0 ? new T[nel] : NULL;
			for (i = 1; i < nr; i++) v[i] = v[i-1] + nc;
		}
		//for (i = 0; i < nr; i++) for (j = 0; j < nc; j++) v[i][j] = a[i][j];
		if (v) memcpy(v[0],a.v[0],sizeof(T) * nel);
	}
	return *this;
}

template <class T>
JMatrix<T>::~JMatrix() {
	if (v != NULL) {
		delete[] v[0];
		delete[] v;
	}
}



/****************************************************************************************/
//matrix related operator overloads




template <class T>
inline T* JMatrix<T>::operator[](const int i) {
#ifdef CHECKBOUND
	if (i < 0 || i >= nr) throw("JMatrix subscript out of bounds");
#endif
	return v[i];
}

template <class T>
inline const T* JMatrix<T>::operator[](const int i) const {
#ifdef CHECKBOUND
	if (i < 0 || i >= nr) throw("JMatrix subscript out of bounds");
#endif
	return v[i];
}
/*
template <class T>
inline JMatrix<T> & JMatrix<T>::operator*=(const T &a) {
	int i,j;
	for (i = 0; i < nr; i++) for (j = 0; j < nc; j++) v[i][j]*= a;
	return *this;
}

template <class T>
inline JMatrix<T> & operator*(JMatrix<T> mat, const T &a) {
	return mat*= a;
}

template <class T>
inline JMatrix<T> & operator*(const T &a, JMatrix<T> mat) {
	return mat * a;
}

template <class T>
inline JMatrix<T> & JMatrix<T>::operator/=(const T &a) {
	int i,j;
	for (i = 0; i < nr; i++) for (j = 0; j < nc; j++) v[i][j]/= a;
	return *this;
}

template <class T>
inline JMatrix<T> & operator/(JMatrix<T> mat, const T &a) {
	return mat/= a;
}

template <class T>
inline JMatrix<T> & operator/(const T &a, JMatrix<T> mat) {
	return mat / a;
}

template <class T>
inline JMatrix<T> & JMatrix<T>::operator+=(const T &a) {
	int i,j;
	for (i = 0; i < nr; i++) for (j = 0; j < nc; j++) v[i][j]+= a;
	return *this;
}

template <class T>
inline JMatrix<T> & operator+(JMatrix<T> mat, const T &a) {
	return mat+= a;
}

template <class T>
inline JMatrix<T> & operator+(const T &a, JMatrix<T> mat) {
	return mat + a;
}

template <class T>
inline JMatrix<T> & JMatrix<T>::operator-=(const T &a) {
	int i,j;
	for (i = 0; i < nr; i++) for (j = 0; j < nc; j++) v[i][j]-= a;
	return *this;
}

template <class T>
inline JMatrix<T> & operator-(JMatrix<T> mat, const T &a) {
	return mat-= a;
}

template <class T>
inline JMatrix<T> & operator-(const T &a, JMatrix<T> mat) {
	return mat - a;
}
*/





/****************************************************************************************/
//utils


template <class T>
inline int JMatrix<T>::nrows() const { return nr; }

template <class T>
inline int JMatrix<T>::ncols() const { return nc; }

template <class T>
void JMatrix<T>::resize(int r, int c) {
	int i,nel;
	if (nr != r || nc != c) {
		if (v != NULL) {
			delete[] v[0];
			delete[] v;
		}
		nr = r;
		nc = c;
		v = nr > 0 ? new T*[nr] : NULL;
		nel = nr*nc;
		if (v) v[0] = nel > 0 ? new T[nel] : NULL;
		for (i = 1; i < nr; i++) v[i] = v[i-1] + nc;
	}
}

template <class T>
void JMatrix<T>::assign(int r, int c, const T &a) {
	int i,j,nel;
	if (nr != r || nc != c) {
		if (v != NULL) {
			delete[] v[0];
			delete[] v;
		}
		nr = r;
		nc = c;
		v = nr > 0 ? new T*[nr] : NULL;
		nel = nr*nc;
		if (v) v[0] = nel > 0 ? new T[nel] : NULL;
		for (i = 1; i < nr; i++) v[i] = v[i-1] + nc;
	}
	for (i = 0; i < nr; i++) for (j = 0; j < nc; j++) memcpy(v[i][j],&a,sizeof(T));//v[i][j] = a;
}

template <class T>
T* JMatrix<T>::dataPointer() {
	return v[0];
}










#endif //JMATRIX_H
