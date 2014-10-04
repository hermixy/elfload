/* Copyright © 2014, Owen Shepherd
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include "elfload.h"

#if defined(__i386__)

#define R_386_NONE     0
#define R_386_RELATIVE 8

el_status el_applyrel(el_ctx *ctx, Elf_Rel *rel)
{
    uint32_t *p = (uint32_t*) (rel->r_offset + ctx->base_load_vaddr);
    uint32_t type = ELF_R_TYPE(rel->r_info);
    uint32_t sym  = ELF_R_SYM(rel->r_info);

    switch (type) {
        case R_386_NONE: break;
        case R_386_RELATIVE:
            EL_DEBUG("Applying R_386_RELATIVE reloc @%p\n", p);
            *p += ctx->base_load_vaddr;
            break;
        default:
            EL_DEBUG("Bad relocation %u\n", type);
            return EL_BADREL;
    }

    return EL_OK;
}

#endif