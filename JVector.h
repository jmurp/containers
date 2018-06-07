#ifndef JVECTOR_H
#define JVECTOR_H

#include "JIncludes.h"

//JVector class definition
template <class T>
class JVector {
private:
	int ne;
	T* v;
public:
	JVector();
	explicit JVector(int n);
	JVector(int n, const T &a);
	JVector(int n, const T* a);
	JVector(const JVector &a);
	JVector & operator=(const JVector &a);
	typedef T value_type;
	inline T & operator[](const int i);
	inline const T & operator[](const int i) const;
	//TODO: move these to a typedef of JVector<double>
	//inline JVector<T> & operator*=(const T &a);
	//inline JVector<T> & operator+=(const T &a);
	//inline JVector<T> & operator-=(const T &a);
	//inline JVector<T> & operator/=(const T &a);
	inline int size() const;
	void resize(int n);
	void assign(int n, const T &a);
	void set(int n, const T &a);
	~JVector();

	T* dataPointer();
};


/****************************************************************************************/
//ctors, dtors, copy assignment



template <class T>
JVector<T>::JVector(): ne(0), v(NULL) {}

template <class T>
JVector<T>::JVector(int n): ne(n), v(ne > 0 ? new T[ne] : NULL) {}

template <class T>
JVector<T>::JVector(int n, const T &a): ne(n), v(ne > 0 ? new T[ne] : NULL) {
	for (int i = 0; i < ne; i++) memcpy(v[i],&a,sizeof(T));//v[i] = a;
}

template <class T>
JVector<T>::JVector(int n, const T* a): ne(n), v(ne > 0 ? new T[ne] : NULL) {
	//for (int i = 0; i < ne; i++) v[i] = *a++;
	if (v) memcpy(v,a,sizeof(T) * ne);
}

template <class T>
JVector<T>::JVector(const JVector &a): ne(a.ne), v(ne > 0 ? new T[ne] : NULL) {
	//for (int i = 0; i < ne; i++) v[i] = a[i];
	if (v) memcpy(v,a.v,sizeof(T) * ne);
}

template <class T>
JVector<T> & JVector<T>::operator=(const JVector<T> &a) {
	if (this != &a) {
		if (ne != a.ne) {
			if (v != NULL) delete[] v;
			ne = a.ne;
			v = ne > 0 ? new T[ne] : NULL;
		}
		//for (int i = 0; i < ne; i++) v[i] = a[i];
		if (v) memcpy(v,a.v,sizeof(T) * ne);
	}
	return *this;
}

template <class T>
JVector<T>::~JVector<T>() {
	if (v != NULL) delete[] v;
}

/****************************************************************************************/
//vector related operator overloads


template <class T>
inline T & JVector<T>::operator[](const int i) {
#ifdef CHECKBOUND
	if (i < 0 || i >= ne) throw("JVector subscript out of bounds");
#endif
	return v[i];
}

template <class T>
inline const T & JVector<T>::operator[](const int i) const {
#ifdef CHECKBOUND
	if (i < 0 || i >= ne) throw("JVector subscript out of bounds");
#endif
	return v[i];
}

/*
template <class T>
inline JVector<T> & JVector<T>::operator*=(const T &a) {
	for (int i = 0; i < ne; i++) v[i]*= a;
	return *this;
}

template <class T>
inline JVector<T> operator*(JVector<T> vec,const T &a) {
	return vec*=a;
}

template <class T>
inline JVector<T> operator*(const T &a,JVector<T> vec) {
	return vec * a;
}


template <class T>
inline JVector<T> & JVector<T>::operator+=(const T &a) {
	for (int i = 0; i < ne; i++) v[i]+= a;
	return *this;
}

template <class T>
inline JVector<T> operator+(JVector<T> vec,const T &a) {
	return vec+=a;
}

template <class T>
inline JVector<T> operator+(const T &a,JVector<T> vec) {
	return vec + a;
}


template <class T>
inline JVector<T> & JVector<T>::operator-=(const T &a) {
	for (int i = 0; i < ne; i++) v[i]-= a;
	return *this;
}

template <class T>
inline JVector<T> operator-(JVector<T> vec,const T &a) {
	return vec-=a;
}

template <class T>
inline JVector<T> operator-(const T &a,JVector<T> vec) {
	return vec - a;
}


template <class T>
inline JVector<T> & JVector<T>::operator/=(const T &a) {
	for (int i = 0; i < ne; i++) v[i]/= a;
	return *this;
}

template <class T>
inline JVector<T> operator/(JVector<T> vec,const T &a) {
	return vec/=a;
}

template <class T>
inline JVector<T> operator/(const T &a,JVector<T> vec) {
	return vec / a;
}
*/

/****************************************************************************************/
//util methods



template <class T>
inline int JVector<T>::size() const { return ne; }

template <class T>
void JVector<T>::resize(int n) {
	if (ne != n) {
		if (v != NULL) delete[] v;
		ne = n;
		v = ne > 0 ? new T[ne] : NULL;
	}
}

template <class T>
void JVector<T>::assign(int n, const T &a) {
	if (ne != n) {
		if (v != NULL) delete[] v;
		ne = n;
		v = ne > 0 ? new T[ne] : NULL;
	}
	for (int i = 0; i < ne; i++) {//v[i] = a;
		memcpy(v[i],&a,sizeof(T));
	}
}

template <class T>
void JVector<T>::set(int i, const T &a) {
#ifdef CHECKBOUND
	if (i < 0 || i >= ne) throw("JVector subscript out of bounds");
#endif
	//v[i] = a;
	memcpy(v[i],&a,sizeof(T));
}

template <class T>
T* JVector<T>::dataPointer() {
	return v;
}


#endif //JVECTOR_H
