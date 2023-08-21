//
// Created by david on 12/06/23.
//

#ifndef LIBCOS_COS_DEFINES_H
#define LIBCOS_COS_DEFINES_H

#if defined(__has_attribute)
#define COS_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#define COS_HAS_ATTRIBUTE(x) 0
#endif

/**
 * @def COS_FORMAT_PRINTF(format_index, args_index)
 *
 * @brief Marks a function as printf-like.
 *
 * @param format_index The index of the format string argument.
 *
 * @param args_index The index of the first variadic argument.
 * For functions that do not take a variable number of arguments, this should be 0.
 *
 * @note The indices start at 1.
 */
#if COS_HAS_ATTRIBUTE(format)
#define COS_FORMAT_PRINTF(format_index, args_index) __attribute__((format(printf, format_index, args_index)))
#else
#define COS_FORMAT_PRINTF(format_index, args_index)
#endif

/**
 * @def COS_NORETURN
 *
 * @brief Marks a function as not returning.
 */
#if COS_HAS_ATTRIBUTE(noreturn)
#define COS_NORETURN __attribute__((noreturn))
#else
#define COS_NORETURN
#endif

/**
 * @def COS_NONSTRING
 *
 * @brief Marks a "string-like" variable as not being a NUL-terminated string.
 */
#if COS_HAS_ATTRIBUTE(nonstring)
#define COS_NONSTRING __attribute__((nonstring))
#else
#define COS_NONSTRING
#endif

/**
 * @def COS_WARN_UNUSED_RESULT
 *
 * @brief Marks a function as returning a value that should be used.
 */
#if COS_HAS_ATTRIBUTE(warn_unused_result)
#define COS_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#define COS_WARN_UNUSED_RESULT
#endif

/**
 * @def COS_MALLOC
 *
 * @brief Marks a function as returning a pointer to memory that should be freed.
 */
#if COS_HAS_ATTRIBUTE(malloc)
#define COS_MALLOC __attribute__((malloc))
#else
#define COS_MALLOC
#endif

#endif /* LIBCOS_COS_DEFINES_H */
