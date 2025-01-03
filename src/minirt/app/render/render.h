#ifndef RENDER_H
# define RENDER_H
# include "minirt/app/canvas/canvas.h"
# include "minirt/app/scene/scene.h"

# include <semaphore.h>
# include <pthread.h>
# include <stdint.h>

typedef enum e_task_type
{
	RAY_CAST,
	COMPUTE_CONST
}	t_task_type;

typedef struct s_task
{
	t_task_type		type;
	// compute constant (bounding box, ...)
	t_object		*object;
	// ray cast
	int				back_canvas;
	int32_t			ppr;
	t_ray			ray;
	int32_t			pixels[2];
	struct s_task	*next;
}	t_task;


typedef struct s_worker
{
	pthread_t		thid;
	struct s_render	*render;
}	t_worker;


typedef struct s_sync
{
	pthread_rwlock_t	scene_mut;
	pthread_mutex_t		canvas_mut[2];
	// keep track of active threads
	pthread_mutex_t		active_threads_mut;
	// use to check and add job in queue
	pthread_mutex_t		queue_mut;
	pthread_cond_t		finish_jobs_cond;
	// increment/decrement each time a task is added/removed
	sem_t				jobs_sem;
	int					nb_active_threads;
	int					nb_tasks_remain;
	int					pixel_rendered;
	volatile int		keep_alive;
	int					constant_calculated;
}	t_sync;

typedef struct s_render
{
	t_worker	*workers;
	t_sync		sync;
	t_scene		*scene;
	t_canvas	*canvas;
	struct s_menu *menu;
	t_task		*queue;
}	t_render;

#endif
