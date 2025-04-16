/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-16 05:30:03 by yonuma            #+#    #+#             */
/*   Updated: 2025-04-16 05:30:03 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int echo(int argc, char *argv[]); // minishellのecho関数

static char *capture_stdout_with_read(int (*func)(int, char **), int argc, char *argv[]) {
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(1);
	}

	int saved_stdout = dup(STDOUT_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	func(argc, argv); // minishellのecho呼び出し
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

static char *capture_builtin_echo(char *args[]) {
	char command[1024] = "bash -c 'builtin echo";
	for (int i = 0; args[i] != NULL; i++) {
		strcat(command, " ");
		strcat(command, args[i]);
	}
	strcat(command, "'");

	FILE *fp = popen(command, "r");
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
	struct {
		const char *name;
		char *args[6];
		int argc;
	} test_cases[] = {
		{"No option", {"Hello", "World", NULL}, 2},
		{"With -n", {"-n", "Hello", "World", NULL}, 3},
		{"With -n and no newline", {"-n", "Hello", "World", NULL}, 3},
		{"With -n and empty string", {"-n", "", NULL}, 2},
		{"With only -n", {"-n", NULL}, 1},
		{"With only -n and empty string", {"-n", "", NULL}, 2},
		{"With multiple -n", {"-n", "-n", "Hello", "World", NULL}, 4},
		{"With multiple -n and no newline", {"-n", "-n", "Hello", "World", NULL}, 4},
		{"With special characters", {"Hello", "$USER", "`echo test`", NULL}, 3},
		{"With empty arguments", {NULL}, 0},
		{"No arguments", {NULL}, 0},
	};

	size_t total_tests = sizeof(test_cases) / sizeof(test_cases[0]);
	size_t failed = 0;

	for (size_t i = 0; i < total_tests; i++) {
		char *custom_out = capture_stdout_with_read(echo, test_cases[i].argc, test_cases[i].args);
		char *builtin_out = capture_builtin_echo(test_cases[i].args);

		if (strcmp(custom_out, builtin_out) != 0) {
			fprintf(stderr, "NG: %s\n", test_cases[i].name);
			fprintf(stderr, "  Custom : [%s]\n", custom_out);
			fprintf(stderr, "  Builtin: [%s]\n", builtin_out);
			failed++;
		}

		free(custom_out);
		free(builtin_out);
	}

	return (failed == 0 ? 0 : 1);
}
