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

export { lcg_next_gaussian, lcg_next_real, lcg_init, lcg_next };

const lcg_init = (args = {}) => {
  /* like ZX81 */
  args.a ||= 75;
  args.c ||= 74;
  args.m ||= 2 ** 16 + 1;
  args.seed ||= 1337;

  return {
    seed: args.seed,
    a: args.a,
    c: args.c,
    m: args.m,
    current: args.seed,
  };
};

const lcg_next = (lcg) => {
  lcg.current = (lcg.a * lcg.current + lcg.c) % lcg.m;
  return lcg.current;
};

const lcg_next_real = (lcg) => {
  const x = lcg_next(lcg) / lcg.m;
  return x;
};

const lcg_next_gaussian = (lcg, u, o) => {
  const x1 = lcg_next_real(lcg);
  const x2 = lcg_next_real(lcg);

  /* Use the Box-Muller transform to get two standard normal variables */
  const z0 = Math.sqrt(-2.0 * Math.log(x1)) * Math.cos(2.0 * Math.PI * x2);

  /* Transform the standard normal variable to the desired Gaussian distribution */
  return z0 * o + u;
};
