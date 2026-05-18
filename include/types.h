#ifndef LIBFT_TYPES_H
# define LIBFT_TYPES_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

/*
** =========================================================
** Primitive type aliases
**
** Motivation: explicit-width types across the entire library.
** All modules MUST use these instead of raw int/long/etc.
** =========================================================
*/

/* Unsigned integers */
typedef uint8_t     t_u8;
typedef uint16_t    t_u16;
typedef uint32_t    t_u32;
typedef uint64_t    t_u64;

/* Signed integers */
typedef int8_t      t_i8;
typedef int16_t     t_i16;
typedef int32_t     t_i32;
typedef int64_t     t_i64;

/* Floating point */
typedef float       t_f32;
typedef double      t_f64;

/* Architecture-sized integers */
typedef size_t      t_usize;   /* unsigned: sizes, counts, indices  */
typedef ptrdiff_t   t_isize;   /* signed:   differences, error codes */

/* Pointer-sized integers */
typedef uintptr_t   t_uptr;
typedef intptr_t    t_iptr;

/* Boolean */
typedef bool        t_bool;

/* Raw byte type — explicit for memory manipulation */
typedef unsigned char t_byte;

#endif /* LIBFT_TYPES_H */
