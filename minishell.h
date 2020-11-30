#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define BUFFER_SIZE 100
# include <assert.h>
# include <errno.h>

typedef struct	s_env
{
	char	**envp;
}				t_env;

int		ft_gnl(int fd, char **line);
char	**ft_split(char const *line, char sep);
char	**ft_strip(char const *line, char **envp);
char	*ft_get_env(t_env *e, char *name);
void	ft_del_env(t_env *e, char *name);
void	ft_set_env(t_env *e, char *name, char *ctnt);
char	*ft_strjoin(char const *left, char const *right);
int		ft_echo(char **argv);
int		ft_cd(char **argv, t_env *e);
#endif
