#include <stdio.h>

double thelist[]={ 3.141, 6.02, 42.0, 0.7 };

#define lambda(lambda$_ret, lambda$_args, lambda$_body) \
({ \
	 lambda$_ret lambda$__anon$ lambda$_args \
	 lambda$_body \
	 &lambda$__anon$; \
})

double average_apply(double (*fn)(double inp)) {
	int i = 0, n = sizeof(thelist) / sizeof(thelist[0]);
	double avg = 0.0;
	for(i = 0; i < n; i++) {
		avg += fn(thelist[i]);
		printf("Running sum = %f\n", avg);
	}

	return avg / n;
}

int main(int argc, char *argv[]) {
	printf("%f\n", average_apply(lambda(double, (double x), { return 2 * x; })));
	printf("%f\n", average_apply(lambda(double, (double x), { return x / 3.0; })));

	return 0;
}
