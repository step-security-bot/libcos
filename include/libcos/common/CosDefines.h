//
// Created by david on 12/06/23.
//

#ifndef LIBCOS_COS_DEFINES_H
#define LIBCOS_COS_DEFINES_H

#if defined(__cplusplus)
#define COS_DECLS_BEGIN extern "C" {
#define COS_DECLS_END }
#else
#define COS_DECLS_BEGIN
#define COS_DECLS_END
#endif

/**
 * @def COS_INLINE
 *
 * @brief Marks a function as inline.
 */
#if defined(_MSC_VER)
#define COS_STATIC_INLINE static __inline
#else
#define COS_STATIC_INLINE static inline
#endif

#if defined(__has_attribute)
#define COS_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#define COS_HAS_ATTRIBUTE(x) 0
#endif

#if defined(__has_builtin)
#define COS_HAS_BUILTIN(x) __has_builtin(x)
#else
#define COS_HAS_BUILTIN(x) 0
#endif

#if defined(__has_extension)
#define COS_HAS_EXTENSION(x) __has_extension(x)
#else
#define COS_HAS_EXTENSION(x) 0
#endif

#if defined(__GNUC__) && !defined(__clang__)

#define COS_GCC_VERSION_AT_LEAST(major, minor, patchlevel) \
    ((__GNUC__ > (major)) ||                               \
     ((__GNUC__ == (major)) && COS_GCC_VERSION_AT_LEAST_MINOR_(minor, patchlevel)))

#if (___GNUC__ >= 2) && defined(__GNUC_MINOR__)
#define COS_GCC_VERSION_AT_LEAST_MINOR_(minor, patchlevel) \
    ((__GNUC_MINOR__ > (minor)) ||                         \
     ((__GNUC_MINOR__ == (minor)) && COS_GCC_VERSION_AT_LEAST_PATCHLEVEL_(patchlevel)))
#else
#define COS_GCC_VERSION_AT_LEAST_MINOR_(minor, patchlevel) (1)
#endif

#if (___GNUC__ >= 3) && defined(__GNUC_PATCHLEVEL__)
#define COS_GCC_VERSION_AT_LEAST_PATCHLEVEL_(patchlevel) \
    (__GNUC_PATCHLEVEL__ >= (patchlevel))
#else
#define COS_GCC_VERSION_AT_LEAST_PATCHLEVEL_(patchlevel) (1)
#endif

#else

#define COS_GCC_VERSION_AT_LEAST(major, minor, patchlevel) (0)

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
 * @def COS_ATTR_UNUSED
 *
 * @brief Marks a variable as unused.
 */
#if COS_HAS_ATTRIBUTE(unused)
#define COS_ATTR_UNUSED __attribute__((unused))
#else
#define COS_ATTR_UNUSED
#endif

/**
 * @def COS_ATTR_PURE
 *
 * @brief Marks a function as returning a value that depends only on its arguments.
 */
#if COS_HAS_ATTRIBUTE(pure)
#define COS_ATTR_PURE __attribute__((pure))
#else
#define COS_ATTR_PURE
#endif

/**
 * @def COS_ATTR_MALLOC
 *
 * @brief Marks a function as returning a pointer to memory that should be freed.
 */
#if COS_HAS_ATTRIBUTE(malloc)
#define COS_ATTR_MALLOC __attribute__((malloc))

#if COS_GCC_VERSION_AT_LEAST(11, 1, 0)
#define COS_ATTR_MALLOC_DEALLOC(deallocator) __attribute__((malloc(deallocator)))
#define COS_ATTR_MALLOC_DEALLOC_INDEX(deallocator, ptr_index) __attribute__((malloc(deallocator, ptr_index)))
#else
#define COS_ATTR_MALLOC_DEALLOC(deallocator)
#define COS_ATTR_MALLOC_DEALLOC_INDEX(deallocator, ptr_index)
#endif

#else
#define COS_ATTR_MALLOC
#define COS_ATTR_MALLOC_DEALLOC(deallocator)
#define COS_ATTR_MALLOC_DEALLOC_INDEX(deallocator, ptr_index)
#endif

#define COS_MALLOC_LIKE COS_ATTR_MALLOC

#define COS_DEALLOC_FUNC(...) COS_GET_DEALLOC_FUNC_MACRO_(__VA_ARGS__,                   \
                                                          COS_ATTR_MALLOC_DEALLOC_INDEX, \
                                                          COS_ATTR_MALLOC_DEALLOC)(__VA_ARGS__)

#define COS_GET_DEALLOC_FUNC_MACRO_(_1, _2, NAME, ...) NAME

/**
 * @def COS_ATTR_ALLOC_SIZE(size_index)
 * @def COS_ATTR_ALLOC_SIZES(size_index1, size_index2)
 *
 * @brief Marks a function as returning a pointer to memory that should be freed,
 * and specifies the size of the allocated memory.
 */
#if COS_HAS_ATTRIBUTE(alloc_size)
#define COS_ATTR_ALLOC_SIZE(size_index) __attribute__((alloc_size(size_index)))
#define COS_ATTR_ALLOC_SIZES(size_index1, size_index2) __attribute__((alloc_size(size_index1, size_index2)))
#else
#define COS_ATTR_ALLOC_SIZE(size_index)
#define COS_ATTR_ALLOC_SIZES(size_index1, size_index2)
#endif

#if COS_HAS_ATTRIBUTE(access)
#define COS_ATTR_ACCESS(access_mode, ref_index) __attribute__((access(access_mode, ref_index)))
#define COS_ATTR_ACCESS_SIZE(access_mode, ref_index, size_index) __attribute__((access(access_mode, ref_index, size_index)))
#else
#define COS_ATTR_ACCESS(access_mode, ref_index)
#define COS_ATTR_ACCESS_SIZE(access_mode, ref_index, size_index)
#endif

#define COS_ATTR_ACCESS_READ_ONLY(ref_index) COS_ATTR_ACCESS(read_only, ref_index)
#define COS_ATTR_ACCESS_READWRITE(ref_index) COS_ATTR_ACCESS(read_write, ref_index)
#define COS_ATTR_ACCESS_WRITE_ONLY(ref_index) COS_ATTR_ACCESS(write_only, ref_index)
#define COS_ATTR_ACCESS_NONE(ref_index) COS_ATTR_ACCESS(none, ref_index)

#define COS_ATTR_ACCESS_READONLY_SIZE(ref_index, size_index) COS_ATTR_ACCESS_SIZE(read_only, ref_index, size_index)
#define COS_ATTR_ACCESS_READ_WRITE_SIZE(ref_index, size_index) COS_ATTR_ACCESS_SIZE(read_write, ref_index, size_index)
#define COS_ATTR_ACCESS_WRITE_ONLY_SIZE(ref_index, size_index) COS_ATTR_ACCESS_SIZE(write_only, ref_index, size_index)

#if COS_HAS_ATTRIBUTE(fallthrough)
#define COS_ATTR_FALLTHROUGH __attribute__((fallthrough))
#else
#define COS_ATTR_FALLTHROUGH
#endif

#if COS_HAS_ATTRIBUTE(diagnose_if)
#define COS_ATTR_DIAGNOSE_IF(condition, message, type) __attribute__((diagnose_if(condition, message, type)))
#else
#define COS_ATTR_DIAGNOSE_IF(condition, message, type)
#endif

#define COS_ATTR_DIAGNOSE_WARNING(condition, message) COS_ATTR_DIAGNOSE_IF(condition, message, "warning")
#define COS_ATTR_DIAGNOSE_ERROR(condition, message) COS_ATTR_DIAGNOSE_IF(condition, message, "error")

#define COS_PRECONDITION(condition) COS_ATTR_DIAGNOSE_WARNING(!(condition), "Precondition not satisfied: " #condition)

#if COS_HAS_BUILTIN(__builtin_expect)
#define COS_LIKELY(x) __builtin_expect(!!(x), 1)
#define COS_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define COS_LIKELY(x) (x)
#define COS_UNLIKELY(x) (x)
#endif

#if COS_HAS_EXTENSION(nullability)
#define COS_Nullable _Nullable
#define COS_Nonnull _Nonnull

#define COS_nonnull_cast(x) ((__typeof__(*(x)) *)(x))
#else
#define COS_Nullable /* nothing */
#define COS_Nonnull  /* nothing */

#define COS_nonnull_cast(x) (x)
#endif

#if COS_HAS_EXTENSION(assume_nonnull)
#define COS_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define COS_ASSUME_NONNULL_END _Pragma("clang assume_nonnull end")
#else
#define COS_ASSUME_NONNULL_BEGIN
#define COS_ASSUME_NONNULL_END
#endif

#endif /* LIBCOS_COS_DEFINES_H */
