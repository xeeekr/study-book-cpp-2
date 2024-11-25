#include <iostream>

namespace ch3_07_0 {
	double fin_diff(double f(double), double x, double h) {
		return (f(x + h) - f(x)) / h;
	}

	double sin_plus_cos(double x) {
		return sin(x) + cos(x);
	}

	struct sc_f {
		double operator() (double x) const {
			return sin(x) + cos(x);
		}
	};

	class psc_f {
	public:
		psc_f(double alpha) : alpha{alpha} {}

		double operator() (double x) const {
			return sin(alpha * x) + cos(x);
		}

	private:
		double alpha;
	};

	void run() {
		std::cout << fin_diff(sin_plus_cos, 1., 0.001) << std::endl;
		std::cout << fin_diff(sin_plus_cos, 0., 0.001) << std::endl;

		sc_f sc_o;
		std::cout << "sc_f(1.) : " << sc_o(1.) << std::endl;

		psc_f psc_o{1.0};
		std::cout << "psc_f(1.0) : " << psc_o(1.) << std::endl;
	}
}

namespace ch3_07_1 {
	template <typename F, typename T>
	T inline fin_diff(F f, const T& x, const T& h) {
		return (f(x + h) - f(x)) / h;
	}

	void run() {
		ch3_07_0::psc_f psc_o{1.0};

		std::cout << fin_diff(psc_o, 1., 0.001) << std::endl;
		std::cout << fin_diff(ch3_07_0::psc_f{2.0}, 1., 0.001) << std::endl;
		std::cout << fin_diff(ch3_07_0::sin_plus_cos, 0., 0.001) << std::endl;
	}
}

namespace ch3_07_2 {
	template <typename F, typename T>
	class derivative {
	public:
		derivative(const F& f, const T&h) : f{f}, h{h} {}

		T operator() (const T& x) const {
			return (f(x + h) - f(x)) / h;
		}

	private:
		const F& f;
		T h;
	};

	void run() {
		using d_psc_f = derivative<ch3_07_0::psc_f, double>;

		ch3_07_0::psc_f	psc_o{1.0};
		d_psc_f d_psc_o{psc_o, 0.001};

		std::cout << "der. of sin(x) + cos(x) at 0 is " << d_psc_o(0.0) << std::endl;

		using dd_psc_f = derivative<d_psc_f, double>;

		dd_psc_f dd_psc_o{d_psc_o, 0.001};
		std::cout << "2nd der. of sin(x) + cos(x) at 0 is " << dd_psc_o(0.0) << std::endl;
	}

	template <typename F, typename T>
	class second_derivative {
	public:
		second_derivative(const F& f, const T& h) : h{h}, fp{f, h} {}

		T operator() (const T& x) const {
			return (fp(x + h) - fp(x)) / h;
		}

	private:
		T h;
		derivative<F, T> fp;
	};

	void run2() {
		second_derivative<ch3_07_0::psc_f, double> dd_psc_o{ch3_07_0::psc_f{1.0}, 0.001};

		std::cout << "2nd der. of sin(x) + cos(x) at 0 is " << dd_psc_o(0.0) << std::endl;
	}
}

namespace ch3_07_3 {
	template <unsigned N, typename F, typename T>
	class nth_derivative {
		using prev_derivative = nth_derivative<N - 1, F, T>;

	public:
		nth_derivative(const F& f, const T& h) : h{h}, fp{f, h} {}

		T operator() (const T& x) const {
			return (fp(x + h) - fp(x)) / h;
		}

	private:
		T h;
		prev_derivative fp;
	};

	template <typename F, typename T>
	class nth_derivative<1, F, T> {
	public:
		nth_derivative(const F& f, const T& h) : f{f}, h{h} {}

		T operator() (const T& x) const {
			return (f(x + h) - f(x)) / h;
		}

	private:
		const F& f;
		T h;
	};

	void run() {
		nth_derivative<22, ch3_07_0::psc_f, double> d22_psc_o{ch3_07_0::psc_f{1.0}, 0.00001};

		std::cout << "22nd der. of sin(x) + cos(x) at 0 is " << d22_psc_o(0.0) << std::endl;
	}

	template <unsigned N, typename F, typename T>
	nth_derivative<N, F, T> derive(const F& f, const T& h) {
		return nth_derivative<N, F, T>{f, h};
	}

	void run2() {
		auto d7_psc_o = derive<7>(ch3_07_0::psc_f{1.0}, 0.00001);

		std::cout << "7nd der. of sin(x) + cos(x) at 0 is " << d7_psc_o(0.0) << std::endl;
	}
}



int main() {
	ch3_07_0::run();
	ch3_07_1::run();
	ch3_07_2::run();
	ch3_07_2::run2();
	ch3_07_3::run();
	ch3_07_3::run2();

	return EXIT_SUCCESS;
}
