
#include "shell.h"

/**
 * main - le progrmame principalepour le compiler
 * @argc: argument counter1
 * @argv: argument  vector2
 * @env:   env variables
 */
int main(int argc, char **argv, char **env)
{
    char *prpt = "$ ";
    char *c_lin = NULL;
    char **args = NULL;
    int i = 0, status = 0, arg_num = 0;
    static int exit_stat, tall;
    size_t len = 0;
    ssize_t read = 0;
    (void)argc, (void)**argv;

    while (1)
    {
        if (isatty(STDIN_FILENO) == 1)
            write(STDOUT_FILENO, prpt, 3);

        read = _getline(&c_lin, &len, stdin);
        ++tall;
        if (char_special(c_lin, read, &exit_stat) == 127)
            continue;

        no_nul(c_lin);

        args = _parser(c_lin);

        for (i = 0; args[i]; i++)
            arg_num++;

        built_ins(c_lin, args, env, &exit_stat);

        status = my_path(args[0], args, env, &exit_stat);

        exec_env(status, args, &exit_stat, &tall);

        fflush(stdin);
    }

    free(c_lin);
    return (0);
}

