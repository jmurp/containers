#ifndef J3MATRIX_H
#define J3MATRIX_H

#include "JIncludes.h"

template <class T>
class J3Matrix {
private:
	int nn, mm, kk;
	T*** v;
public:
	J3Matrix();
	J3Matrix(int n,int m,int k);
	J3Matrix(int n,int m,int k,const T &a);
	J3Matrix(int n,int m,int k,const T *a);
	J3Matrix(const J3Matrix &a);
	J3Matrix & operator=(const J3Matrix &a);
	typedef T value_type;
	inline T** operator[](const int i);
	inline const T* const * operator[](const int i) const;
	//TODO: move to a typedef of J3Matrix<double>
	//inline J3Matrix<T> & operator*=(const T &a);
	//inline J3Matrix<T> & operator/=(const T &a);
	//inline J3Matrix<T> & operator+=(const T &a);
	//inline J3Matrix<T> & operator-=(const T &a);
	inline int dim1() const;
	inline int dim2() const;
	inline int dim3() const;
	void resize(int n,int m,int k);
	void assign(int n,int m,int k,const T &a);
	~J3Matrix();

	T* dataPointer();
};
/****************************************************************************************/
//ctors, dtors, copy



template <class T>
J3Matrix<T>::J3Matrix(): nn(0), mm(0), kk(0), v(NULL) {}

template <class T>
J3Matrix<T>::J3Matrix(int n,int m,int k): nn(n), mm(m), kk(k), v(nn > 0 ? new T**[nn] : NULL) {
	int i,j;
	if (v) v[0] = mm > 0 ? new T*[nn*mm] : NULL;
	if (v[0]) v[0][0] = kk > 0 ? new T[nn*mm*kk] : NULL;
	if (v[0][0]) {
		for (i = 1; i < mm; i++) v[0][i] = v[0][i-1] + kk;
		for (i = 1; i < nn; i++) {
			v[i] = v[i-1] + mm;
			v[i][0] = v[i-1][0] + mm*kk;
			for (j = 1; j < mm; j++) v[i][j] = v[i][j-1] + kk;
		}
	}
}

template <class T>
J3Matrix<T>::J3Matrix(int n, int m, int k, const T &a): nn(n), mm(m), kk(k), v(nn > 0 ? new T**[nn] : NULL) {
	int i,j,l;
	if (v) v[0] = mm > 0 ? new T*[nn*mm] : NULL;
	if (v[0]) v[0][0] = kk > 0 ? new T[nn*mm*kk] : NULL;
	if (v[0][0]) {
		for (i = 1; i < mm; i++) v[0][i] = v[0][i-1] + kk;
		for (i = 1; i < nn; i++) {
			v[i] = v[i-1] + mm;
			v[i][0] = v[i-1][0] + mm*kk;
			for (j = 1; j < mm; j++) v[i][j] = v[i][j-1] + kk;
		}
	}
	for (i = 0; i < nn; i++) for (j = 0; j < mm; j++) for (l = 0; l < kk; l++) memcpy(v[i][j][l],&a,sizeof(T));//v[i][j][l] = a;
}

template <class T>
J3Matrix<T>::J3Matrix(const J3Matrix<T> &a): nn(a.nn), mm(a.mm), kk(a.kk), v(nn > 0 ? new T**[nn] : NULL) {
	int i,j,l;
	if (v) v[0] = mm > 0 ? new T*[nn*mm] : NULL;
	if (v[0]) v[0][0] = kk > 0 ? new T[nn*mm*kk] : NULL;
	if (v[0][0]) {
		for (i = 1; i < mm; i++) v[0][i] = v[0][i-1] + kk;
		for (i = 1; i < nn; i++) {
			v[i] = v[i-1] + mm;
			v[i][0] = v[i-1][0] + mm*kk;
			for (j = 1; j < mm; j++) v[i][j] = v[i][j-1] + kk;
		}
	}
	//for (i = 0; i < nn; i++) for (j = 0; j < mm; j++) for (l = 0; l < kk; l++) v[i][j][l] = a[i][j][l];
	if (v[0][0]) memcpy(v[0][0],a.v[0][0],sizeof(T) * (nn*mm*kk));
}

template <class T>
J3Matrix<T>::J3Matrix(int n, int m, int k, const T *a): nn(n), mm(m), kk(k), v(nn > 0 ? new T**[nn] : NULL) {
	int i,j,l;
	if (v) v[0] = mm > 0 ? new T*[nn*mm] : NULL;
	if (v[0]) v[0][0] = kk > 0 ? new T[nn*mm*kk] : NULL;
	if (v[0][0]) {
		for (i = 1; i < mm; i++) v[0][i] = v[0][i-1] + kk;
		for (i = 1; i < nn; i++) {
			v[i] = v[i-1] + mm;
			v[i][0] = v[i-1][0] + mm*kk;
			for (j = 1; j < mm; j++) v[i][j] = v[i][j-1] + kk;
		}
	}
	//for (i = 0; i < nn; i++) for (j = 0; j < mm; j++) for (l = 0; l < kk; l++) v[i][j][l] = *a++;
	if (v[0][0]) memcpy(v[0][0],a,sizeof(T) * (nn*mm*kk));
}

template <class T>
J3Matrix<T> & J3Matrix<T>::operator=(const J3Matrix &a) {
	if (this != &a) {
		int i,j,k;
		if (nn != a.nn || mm != a.mm || kk != a.kk) {
			delete[] (v[0][0]);
			delete[] (v[0]);
			delete[] (v);
			nn = a.nn;
			mm = a.mm;
			kk = a.kk;
			v = nn > 0 ? new T**[nn] : NULL;
			if (v) v[0] = mm > 0 ? new T*[nn*mm] : NULL;
			if (v[0]) v[0][0] = kk > 0 ? new T[nn*mm*kk] : NULL;
			if (v[0][0]) {
				for (i = 1; i < mm; i++) v[0][i] = v[0][i-1] + kk;
				for (i = 1; i < nn; i++) {
					v[i] = v[i-1] + mm;
					v[i][0] = v[i-1][0] + mm*kk;
					for (j = 1; j < mm; j++) v[i][j] = v[i][j-1] + kk;
				}
			}
		}
		//for (i = 0; i < nn; i++) for (j = 0; j < mm; j++) for (k = 0; k < kk; k++) v[i][j][k] = a[i][j][k];
		if (v[0][0]) memcpy(v[0][0],a.v[0][0],sizeof(T) * (nn*mm*kk));
	}
	return *this;
}

template <class T>
inline T** J3Matrix<T>::operator[](const int i) {
#ifdef CHECKBOUND
	if (i < 0 || i >= nn) throw("J3Matrix subscript out of bounds");
#endif
	return v[i];
}

template <class T>
inline const T* const * J3Matrix<T>::operator[](const int i) const {
#ifdef CHECKBOUND
	if (i < 0 || i >= nn) throw("J3Matrix subscript out of bounds");
#endif
	return v[i];
}

template <class T>
J3Matrix<T>::~J3Matrix() {
	if (v != NULL) {
		delete[] (v[0][0]);
		delete[] (v[0]);
		delete[] (v);
	}
}



/****************************************************************************************/
//matrix related operator overloads
/*
template <class T>
inline J3Matrix<T> & J3Matrix<T>::operator*=(const T &a) {
	int i,j,k;
	for (i=0;i<nn;i++) for (j=0;j<mm;j++) for (k=0;k<kk;k++) v[i][j][k]*= a;
	return *this;
}

template <class T>
inline J3Matrix<T> & operator*(J3Matrix<T> m, const T &a) {
	return m*= a;
}

template <class T>
inline J3Matrix<T> & operator*(const T &a, J3Matrix<T> m) {
	return m * a;
}

template <class T>
inline J3Matrix<T> & J3Matrix<T>::operator/=(const T &a) {
	int i,j,k;
	for (i=0;i<nn;i++) for (j=0;j<mm;j++) for (k=0;k<kk;k++) v[i][j][k]/= a;
	return *this;
}

template <class T>
inline J3Matrix<T> & operator/(J3Matrix<T> m, const T &a) {
	return m/= a;
}

template <class T>
inline J3Matrix<T> & operator/(const T &a, J3Matrix<T> m) {
	return m / a;
}

template <class T>
inline J3Matrix<T> & J3Matrix<T>::operator+=(const T &a) {
	int i,j,k;
	for (i=0;i<nn;i++) for (j=0;j<mm;j++) for (k=0;k<kk;k++) v[i][j][k]+= a;
	return *this;
}

template <class T>
inline J3Matrix<T> & operator+(J3Matrix<T> m, const T &a) {
	return m+= a;
}

template <class T>
inline J3Matrix<T> & operator+(const T &a, J3Matrix<T> m) {
	return m + a;
}

template <class T>
inline J3Matrix<T> & J3Matrix<T>::operator-=(const T &a) {
	int i,j,k;
	for (i=0;i<nn;i++) for (j=0;j<mm;j++) for (k=0;k<kk;k++) v[i][j][k]-= a;
	return *this;
}

template <class T>
inline J3Matrix<T> & operator-(J3Matrix<T> m, const T &a) {
	return m-= a;
}

template <class T>
inline J3Matrix<T> & operator-(const T &a, J3Matrix<T> m) {
	return m - a;
}
*/




/****************************************************************************************/
//utils

template <class T>
inline int J3Matrix<T>::dim1() const { return nn; }

template <class T>
inline int J3Matrix<T>::dim2() const { return mm; }

template <class T>
inline int J3Matrix<T>::dim3() const { return kk; }

template <class T>
void J3Matrix<T>::resize(int n, int m, int k) {
	if (nn != n || mm != m || kk != k) {
		if (v != NULL) {
			delete[] (v[0][0]);
			delete[] (v[0]);
			delete[] (v);
		}
		nn = n;
		mm = m;
		kk = k;
		v = nn > 0 ? new T**[nn] : NULL;
		if (v) v[0] = mm > 0 ? new T*[nn*mm] : NULL;
		if (v[0]) v[0][0] = kk > 0 ? new T[nn*mm*kk] : NULL;
		int i,j,l;
		if (v[0][0]) {
			for (i=1;i<mm;i++) v[0][i] = v[0][i-1] + kk;
			for (i=1;i<nn;i++) {
				v[i] = v[i-1] + mm;
				v[i][0] = v[i-1][0] + mm*kk;
				for (j=1;j<mm;j++) v[i][j] = v[i][j-1] + kk;
			}
		}
	}
}

template <class T>
void J3Matrix<T>::assign(int n, int m, int k, const T &a) {
	int i,j,l;
	if (nn != n || mm != m || kk != k) {
		if (v != NULL) {
			delete[] (v[0][0]);
			delete[] (v[0]);
			delete[] (v);
		}
		nn = n;
		mm = m;
		kk = k;
		v = nn > 0 ? new T**[nn] : NULL;
		if (v) v[0] = mm > 0 ? new T*[nn*mm] : NULL;
		if (v[0]) v[0][0] = kk > 0 ? new T[nn*mm*kk] : NULL;
		if (v[0][0]) {
			for (i=1;i<mm;i++) v[0][i] = v[0][i-1] + kk;
			for (i=1;i<nn;i++) {
				v[i] = v[i-1] + mm;
				v[i][0] = v[i-1][0] + mm*kk;
				for (j=1;j<mm;j++) v[i][j] = v[i][j-1] + kk;
			}
		}
	}
	for (i=0;i<nn;i++) for (j=0;j<mm;j++) for(l=0;l<kk;l++) memcpy(v[i][j][l],&a,sizeof(T));//v[i][j][l] = a;
}

template <class T>
T* J3Matrix<T>::dataPointer() {
	return v[0][0];
}







#endif //J3MATRIX_H
