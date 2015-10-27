/* === S Y N F I G ========================================================= */
/*!	\file synfig/rendering/common/optimizer/optimizersurfacecreate.cpp
**	\brief OptimizerSurfaceCreate
**
**	$Id$
**
**	\legal
**	......... ... 2015 Ivan Mahonin
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/
/* ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#ifndef WIN32
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

#include "optimizersurfacecreate.h"

#include "../task/tasksurfacecreate.h"
#include "../task/tasksurfaceconvert.h"

#endif

using namespace synfig;
using namespace rendering;

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

void
OptimizerSurfaceCreate::insert_task(
	std::set<Surface::Handle> &created_surfaces,
	const RunParams& params,
	Task::List::iterator &i,
	const Task::Handle &task ) const
{
	if ( task
	  && task->target_surface
	  && !task->target_surface->is_created()
	  && !created_surfaces.count(task->target_surface) )
	{
		created_surfaces.insert(task->target_surface);
		TaskSurfaceCreate::Handle surface_create = new TaskSurfaceCreate();
		surface_create->target_surface = task->target_surface;
		surface_create->target_rect = RectInt(0, 0, task->target_surface->get_width(), task->target_surface->get_height());
		i = params.list.insert(i, surface_create);
		++i;
		apply(params);
	}
}

void
OptimizerSurfaceCreate::run(const RunParams& params) const
{
	std::set<Surface::Handle> created_surfaces;
	for(Task::List::iterator i = params.list.begin(); i != params.list.end();)
	{
		if (*i)
		{
			if (TaskSurfaceCreate::Handle::cast_dynamic(*i))
			{
				if (created_surfaces.count((*i)->target_surface))
					{ i = params.list.erase(i); continue; }
				created_surfaces.insert((*i)->target_surface);
			}
			else
			if (TaskSurfaceConvert::Handle::cast_dynamic(*i))
			{
				created_surfaces.insert((*i)->target_surface);
			}
			else
			{
				for(std::vector<Task::Handle>::const_iterator j = (*i)->sub_tasks.begin(); j != (*i)->sub_tasks.end(); ++j)
					insert_task(created_surfaces, params, i, *j);
				insert_task(created_surfaces, params, i, *i);
			}
		}
		++i;
	}
}

/* === E N T R Y P O I N T ================================================= */