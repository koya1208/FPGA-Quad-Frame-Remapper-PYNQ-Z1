#include "xquad_frame_remapper.h"

XQuad_frame_remapper_Config XQuad_frame_remapper_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,quad-frame-remapper-1.0", /* compatible */
		0x40000000 /* reg */
	},
	 {
		 NULL
	}
};