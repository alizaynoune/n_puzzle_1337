#include "n_puzzle.hpp"

/* free map */
void        free_map(t_map *map, int size){
    if (map){
        for (int i = 0; i < size; i++){
            if (map[i].pieces)
                free(map[i].pieces);
        }
        free(map);
    }
}


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
    /* free map */
    // if (data->map){
    //     // free_table(data->map, data->size);
    //     for (int i = 0; i < data->size; i++){
    //         if (data->map[i].pieces)
    //             free(data->map[i].pieces);
    //     }
    //     free(data->map);
    // }
    free_map(data->map, data->size);
    free_map(data->map_copy, data->size);
}