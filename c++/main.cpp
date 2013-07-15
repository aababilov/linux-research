#include <cstdio>
using namespace std;

/*
template<class T>
class tc_t {
public:
	static T inst;
	static T get() {return inst;}
};

typedef tc_t<int> tc_int;

template<class T>
T tc_t<T>::inst;

typedef tc_t<long> tc_long;

template<>
long tc_t<long>::inst =-40;


void test_template()
{
	printf("%d\n", tc_int::inst);
	tc_int::inst = 0;
	printf("%d\n", tc_int::get());

	printf("%d\n", tc_long::inst);
	tc_long::inst = 5;
	printf("%d\n", tc_long::get());

}
*/

class base_t;

void g_func(base_t *ptr);

class base_t {
public:
	virtual void virf() = 0;
	virtual ~base_t() { printf("~base\n");g_func(this); }
};


class der_t: public base_t {
public:
	void virf() {printf("der\n"); }
	virtual ~der_t() { printf("~der\n"); g_func(this); }
};

void test_abstr()
{
	der_t obj;
//	base_t bobj;
	//obj.virf();
//	g_func(&obj);
}

int main()
{
	test_abstr();
}

void g_func(base_t *ptr)
{
	ptr->virf();
	der_t *p = (der_t*)ptr;
	p->virf();
}
