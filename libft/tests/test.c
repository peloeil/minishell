#include "./test.h"

volatile sig_atomic_t received = 0;
volatile sig_atomic_t sig_libc = -1;
volatile sig_atomic_t sig_own = -1;

void signal_handler(int signum) {
	if (sig_libc == -1) {
		sig_libc = signum;
	} else {
		sig_own = signum;
	}
	received = 1;
}

void setup_handler(void) {
	struct sigaction sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGABRT, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);
}

void wait_signal(void) {
	while (!received) {
		pause();
	}
}

int same_status(void) {
	return sig_libc == sig_own;
}
