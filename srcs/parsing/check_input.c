#include "../../includes/cub3d.h"


int is_valid_file(char *arg, bool cub)
{
    char *ext;

    if(!arg)
        return(1);
    ext = ft_strrchr(arg, '.');
    if(!ext)
        return(err_msg(arg, ERR_FILE_FORMAT, 1));
    if(cub == true && ft_strncmp(ext, ".cub", 5) == 0)
        return(0);
    if(cub == false && ft_strncmp(ext, ".xpm", 5) == 0)
        return(0);
    return(err_msg(arg, ERR_FILE_FORMAT, 1));
}

size_t max_line_width(t_game *game, int start)
{
    if(!cub)
        return(0);
    size_t max = 0;
    while(cub->file.file_content[start])
    {
        if (max < ft_strlen(cub->file.file_content[start]))
            max = ft_strlen(cub->file.file_content[start]);
        start++;
    }
    return(max);
}
