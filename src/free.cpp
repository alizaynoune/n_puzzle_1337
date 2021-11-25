#include "n_puzzle.hpp"

/* free all data */
void       ft_free(Data *data){
    /* close file descriptor */
    if (data->fd)
        fclose(data->fd);
    /* free list of lines */
    if (data->file){
        t_file *tmp;
        while (data->file){
            tmp = data->file;
            data->file = data->file->next;
            free(tmp->line);
            free(tmp);
        }
    }
    /* free map start */
    if (data->map_start){
        for (int i = 0; i < data->size; i++)
            free(data->map_start[i]);
        free(data->map_start);
    }
    /* free map goal */
    if (data->map_goal){
        for (int i = 0; i < data->size; i++)
            free(data->map_goal[i]);
        free(data->map_goal);
    }
}