#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// minishellのpwd関数（引数なし）
int pwd(void);

// 標準出力をキャプチャ（引数なしの関数用）
static char *capture_stdout_no_args(int (*func)(void)) {
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(1);
	}

	int saved_stdout = dup(STDOUT_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	func(); // minishellのpwd関数を呼び出し
	fflush(stdout);

	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	char *buffer = malloc(4096);
	if (!buffer)
		exit(1);

	ssize_t n = read(pipefd[0], buffer, 4095);
	if (n < 0) n = 0;
	buffer[n] = '\0';
	close(pipefd[0]);

	return buffer;
}

// bashのpwd出力を取得
static char *capture_builtin_pwd(void) {
	FILE *fp = popen("pwd", "r");
	if (!fp) {
		perror("popen");
		exit(1);
	}

	char *buffer = malloc(4096);
	if (!buffer)
		exit(1);

	size_t total = fread(buffer, 1, 4095, fp);
	buffer[total] = '\0';
	pclose(fp);
	return buffer;
}

int main(void) {
	char *custom_out = capture_stdout_no_args(pwd);
	char *builtin_out = capture_builtin_pwd();

	// 改行を削除
	custom_out[strcspn(custom_out, "\n")] = '\0';
	builtin_out[strcspn(builtin_out, "\n")] = '\0';

	if (strcmp(custom_out, builtin_out) != 0) {
		fprintf(stderr, "NG: pwd command\n");
		fprintf(stderr, "  Custom : [%s]\n", custom_out);
		fprintf(stderr, "  Builtin: [%s]\n", builtin_out);
		free(custom_out);
		free(builtin_out);
		return 1;
	}

	printf("OK: pwd command passed (Output: %s)\n", custom_out);

	free(custom_out);
	free(builtin_out);
	return 0;
}
