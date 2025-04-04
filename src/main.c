#include "parser.h"
#include "ui.h"
#include "raytracing.h"
#include "calc.h"

bool check_filename(char *filename)
{
    while (*filename != '.')
        filename++;
    if (ft_memcmp(filename, ".rt", 4))
        return (false);
    return (true);
}

int main(int argc, char **argv)
{
    int     part;
    t_env   *env;
    t_obj   *obj;

    if (argc != 2 || check_filename(argv[1]) == false)
        print_error_and_exit("main", "*.rt file required");
    part = MANDATORY;
    parser(argv[1], part);
    env = set_get_env(GET, NULL);
    obj = set_get_obj(GET, NULL);
    // minirt(env, data);
    // minirt();
	init_window(obj, env);
    //free_lit(env->lit);
    //free(env);
    //free_obj(obj);
    calc_test();
    printf("end\n");
    return (0);
}