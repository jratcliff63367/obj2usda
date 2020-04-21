#pragma once

#include <stdint.h>

namespace exportusda
{

bool exportUSDA(uint32_t vcount,
				uint32_t tcount,
				const float *vertices,
				const uint32_t *indices,
				const char *fname);


}
