#include "ft_ls.h"

void	print_opt(t_opt *opt)
{
	printf("-------OPTIONS--------\n");
	printf("l is %u\n", opt->l);
	printf("a is %u\n", opt->a);
	printf("t is %u\n", opt->t);
	printf("r is %u\n", opt->r);
	printf("R is %u\n", opt->R);
	printf("\n");
}

void	dir_prt(t_dir *dir)
{
	t_dir	*tmp;

	tmp = dir;
	if (!tmp->sub)
	{
		printf("there is no sub!\n");
	}
	else
	{
		tmp = tmp->sub;
		while (tmp->next)
		{
			printf("%s ", tmp->name);
			tmp = tmp->next;
		}
		printf("\n");
	}
}