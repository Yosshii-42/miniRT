#include "parser.h"

void    parser(char *filename)
{
    int     fd;
    char    *line;
    t_env   *env;
    t_lit   *lit;
    t_obj   *obj;

    open_file(filename, &fd);
    env = (t_env *)safe_malloc(1, sizeof(t_env));
    lit = NULL;
    obj = NULL;
    init_env(env, lit);
    set_get_env(SET, env);
    set_get_lit(SET, lit);
    set_get_obj(SET, obj);
    printf("** after init env **\n");
    print_env_data();
    while (1)
    {
        line = NULL;
        line = get_next_line(fd);
        if (line)
            make_information(line);
        else
            break ;
        free(line);
    }
    env->lit = lit;
    print_lit_data();
    print_obj_data();
}

void    make_information(char *line)
{
    char    **split;

    split = ft_split(line, SPACE);
    if (!split[0])
    {
        free(split[0]);
        free(split);
        return ;
    }
    if (check_first_element(split[0]) == ENV)
    {
        make_env_data(split);
        printf("\n** after read line **\n");
        print_env_data();
    }
    else if (check_first_element(split[0]) == LIT)
        make_lit_data(split);
    else if (check_first_element(split[0]) == OBJ)
        make_obj_data(split);
    else
        print_error_and_exit("parser", "couldn't find identifier");
    free_split(split);
}

void    set_array(char *str, double arr[3], int select)
{
    char    **number;

    check_comma(str);
    number = ft_split(str, ",");
    if (count_split(number) != 3)
        print_error_and_exit("set array", "argument count should be 3");
    arr[0] = ft_atof(number[0]);
    arr[1] = ft_atof(number[1]);
    arr[2] = ft_atof(number[2]);
    free_split(number);
    if (select == VECTOR || select == RGB)
        check_array_num(arr, select);
}

void    set_struct_xyz(t_xyz *xyz, double arr[3])
{
    xyz->x = arr[0];
    xyz->y = arr[1];
    xyz->z = arr[2];
}
