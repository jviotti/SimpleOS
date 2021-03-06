/* Copyright (c) 2018, Juan Cruz Viotti
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *     # derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "port.h"

byte_t port_byte_in(const port_t port)
{
  byte_t result;

  // This is GCC's inline assembly extension, which uses GAS assembly
  // See: https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax
  // The instruction that we want for this ask is "in <port>, <destination>".
  // In GAS, % is used to denote registers, but notice we have to escape % in C.
  //
  // "=a" (result): put the "al" register in variable "result"
  // "d" (port): load "dx" with "port"
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));

  return result;
}

void port_byte_out(const port_t port, const byte_t value)
{
  __asm__("out %%al, %%dx" : : "a" (value), "d" (port));
}

word_t port_word_in(const port_t port)
{
  word_t result;
  __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void port_word_out(const port_t port, const word_t value)
{
  __asm__("out %%ax, %%dx" : : "a" (value), "d" (port));
}
