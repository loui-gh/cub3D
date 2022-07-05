#include "../incl/raycast.h"

/* find start of map */
/* DA RULEZ
1st + last line only 1s
lines start and end with 1
0 cannot be preceded or followed by space (needs to b surrounded)
arr[i][j]
if char == 0, arr[i - 1][j] != ' ' && arr[i + 1][j]
only valid characters (1, 0, (N,S,W or E), space)

*/

// void	create_map_array(t_vars *vars, char *map_path)
// {
// 	ssize_t		rc;
// 	int			fd;

// 	vars->buf = ft_calloc(sizeof(char), 1000);
// 	fd = open(map_path, O_RDONLY);
// 	//if (fd == -1) print error msg
// 	rc = read(fd, vars->buf, 1000);
// 	if (rc < 1)
// 	{
// 		ft_free(vars);
// 		close(fd);
// 		exit(EXIT_FAILURE);
// 	}
// 	vars->map->ptr_map = ft_split(vars->buf, '\n');
// 	if (vars->map->ptr_map == NULL)
// 	{
// 		ft_free(vars);
// 		exit(EXIT_FAILURE);
// 	}
// 	check_p_c_e(vars);
// 	set_x_y(vars);
// 	check_element(vars);
// 	check_rectangle(vars);
// 	check_walls(vars);
// 	close(fd);
// }