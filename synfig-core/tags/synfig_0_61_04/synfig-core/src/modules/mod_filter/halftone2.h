/* === S Y N F I G ========================================================= */
/*!	\file halftone2.h
**	\brief Template Header
**
**	$Id: halftone2.h,v 1.1.1.1 2005/01/04 01:23:10 darco Exp $
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
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

/* === S T A R T =========================================================== */

#ifndef __SYNFIG_HALFTONE2_H
#define __SYNFIG_HALFTONE2_H

/* === H E A D E R S ======================================================= */

#include <synfig/vector.h>
#include <synfig/valuenode.h>
#include <synfig/layer_composite.h>
#include <synfig/time.h>
#include <synfig/angle.h>
#include "halftone.h"

/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */

class Halftone2 : public synfig::Layer_Composite
{
	SYNFIG_LAYER_MODULE_EXT

private:

	Halftone halftone;
	synfig::Color	color_dark;
	synfig::Color	color_light;

	synfig::Color color_func(const synfig::Point &x, float supersample,const synfig::Color &under_color)const;

	float calc_supersample(const synfig::Point &x, float pw,float ph)const;

	//float halftone_func(synfig::Point x)const;

public:
	Halftone2();
	
	virtual bool set_param(const synfig::String &param, const synfig::ValueBase &value);
	virtual synfig::ValueBase get_param(const synfig::String &param)const;
	virtual synfig::Color get_color(synfig::Context context, const synfig::Point &pos)const;
	virtual bool accelerated_render(synfig::Context context,synfig::Surface *surface,int quality, const synfig::RendDesc &renddesc, synfig::ProgressCallback *cb)const;
	synfig::Layer::Handle hit_check(synfig::Context context, const synfig::Point &point)const;	

	virtual Vocab get_param_vocab()const;
};

/* === E N D =============================================================== */

#endif
