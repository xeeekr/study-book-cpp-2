#include <iostream>

namespace p3_1_2 {
	template <typename TPara>
	void f1(TPara p) {
		std::cout << p << " : " << typeid(p).name() << std::endl;
	}

	void run1() {
		std::cout << "========== " << "3.1.2.1" << std::endl;

		int i = 0;
		int &j = i;
		const int &k = i;

		f1(3);
		f1(i);
		f1(j);
		f1(k);

		std::unique_ptr<int> up;
		//f1(up);	// ERROR
		f1(std::move(up));
	}

	template <typename TPara>
	void f2(const TPara &p) {
		std::cout << p << " : " << typeid(p).name() << std::endl;
	}

	template <typename TPara>
	void f3(TPara &p) {
		std::cout << p << " : " << typeid(p).name() << std::endl;
	}

	template <typename TPara>
	void f3_2(TPara &p) {
		std::cout << p << " : " << typeid(p).name() << std::endl;
		p = 4;
	}

	void run2() {
		std::cout << "========== " << "3.1.2.2" << std::endl;
		int i = 0;
		int &j = i;
		const int &k = i;

		f3(i);
		f3(j);
		f3(k);

		f3_2(i);
		// f3_2(k);	// ERROR
	}

	template <typename TPara>
	void f4(TPara &&p) {
		std::cout << p << " : " << typeid(p).name() << std::endl;
	}

	void run3() {
		std::cout << "========== " << "3.1.2.3" << std::endl;

		int i = 0;
		std::unique_ptr<int> up;

		f4(3);
		f4(std::move(i));
		f4(std::move(up));
	}

	template <typename TPara>
	void f5(TPara &&p) {
		std::cout << p << " : " << typeid(p).name() << std::endl;
		f4(std::forward<TPara>(p));
	}

	void run4() {
		std::cout << "========== " << "3.1.2.4" << std::endl;
		int i = 0;
		std::unique_ptr<int> up;

		f5(3);
		f5(std::move(i));
		f5(std::move(up));
	}

	template <typename T>
	void rvalue_only1(T&& arg) {
		std::cout << arg << " : " << typeid(arg).name() << std::endl;
	}
	template <typename T>
	void rvalue_only1(T&) = delete;

	template <typename T>
	void rvalue_only2(T&& arg) {
		static_assert(std::is_rvalue_reference<decltype(arg)>::value, "This function is only allowed for rvalues!");
		std::cout << arg << " : " << typeid(arg).name() << std::endl;
	}

	void run5() {
		std::cout << "========== " << "3.1.2.5" << std::endl;
		int i = 0;
		int &j = i;
		const int &k = i;

		rvalue_only1(3);
		//rvalue_only1(i);	// ERROR
		//rvalue_only1(j);	// ERROR
		//rvalue_only1(k);	// ERROR

		std::unique_ptr<int> up;
		//rvalue_only1(up);	// ERROR
		rvalue_only1(std::move(up));

		rvalue_only2(3);
		//rvalue_only2(i);	// ERROR
		//rvalue_only2(j);	// ERROR
		//rvalue_only2(k);	// ERROR
		//rvalue_only2(up);	// ERROR
		rvalue_only2(std::move(up));
	}
}

namespace p3_1_7 {
	auto max(auto a, auto b) {
		std::cout << a << " : " << typeid(a).name() << std::endl;
		std::cout << b << " : " << typeid(b).name() << std::endl;
		return a > b ? a : b;
	}
	void run() {
		std::cout << "========== " << "3.1.7" << std::endl;
		int a = 1;
		int b = 2;
		unsigned c = 3;
		float d = 1.0;
		double e = 2.0;

		auto r1 = max(a, b);
		std::cout << typeid(r1).name() << std::endl;
		auto r2 = max(a, c);
		std::cout << typeid(r2).name() << std::endl;
		auto r3 = max(a, d);
		std::cout << typeid(r3).name() << std::endl;
		auto r4 = max(a, e);
		std::cout << typeid(r4).name() << std::endl;
	}
}


int main() {
	p3_1_2::run1();
	p3_1_2::run2();
	p3_1_2::run3();
	p3_1_2::run4();
	p3_1_2::run5();

	p3_1_7::run();
	return EXIT_SUCCESS;
}
