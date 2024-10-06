/*
 * MIT License
 *
 * Copyright (c) 2024 Julian Kahlert
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <errno.h>
#include <math.h>

#include "./lcg.h"

int lcg_init(struct lcg *lcg, struct lcg_cfg *cfg)
{
	if (!lcg)
		return -EINVAL;

	/* like ZX81 */
        if (cfg) {
		lcg->a = cfg->a ? cfg->a : 75;
		lcg->c = cfg->c ? cfg->c : 74;
		lcg->m = cfg->m ? cfg->m : (1 << 16) + 1;
		lcg->seed = cfg->seed ? cfg->seed : 1337;
	} else {
		lcg->a = 75;
		lcg->c = 74;
		lcg->m = (1 << 16) + 1;
		lcg->seed = 1337;
	}

	lcg->current = lcg->seed;
}

uint32_t lcg_next(struct lcg *lcg)
{
	if (!lcg)
		return 0;

	lcg->current = (lcg->a * lcg->current + lcg->c) % lcg->m;
	return lcg->current;
}

#ifndef LIB_ELEMENTAL_ARCH_HAS_NO_FLOAT
float lcg_next_real(struct lcg *lcg)
{
	if (!lcg)
		return NAN;

	return (float)lcg_next(lcg) / lcg->m;
}

float lcg_next_gaussian(struct lcg *lcg, float u, float o)
{
	if (!lcg)
		return NAN;

	float x1 = lcg_next_real(lcg);
	float x2 = lcg_next_real(lcg);

	/* Box-Muller transform for Gaussian distribution */
	float z0 = sqrt(-2.0 * log(x1)) * cos(2.0 * M_PI * x2);

	/* Scale and shift */
	return z0 * o + u;
}
#endif
