/*
 * Copyright (c) 2024 OpenCOS.
 */

#ifndef LIBCOS_COS_TOKEN_H
#define LIBCOS_COS_TOKEN_H

#include "libcos/common/CosData.h"
#include "libcos/common/CosDefines.h"
#include "libcos/common/CosString.h"
#include "parse/tokenizer/CosTokenValue.h"

#include <stdbool.h>

COS_DECLS_BEGIN
COS_ASSUME_NONNULL_BEGIN

typedef struct CosToken CosToken;

typedef enum CosToken_Type {
    CosToken_Type_Unknown,

    CosToken_Type_Literal_String,
    CosToken_Type_Hex_String,
    CosToken_Type_Name,
    CosToken_Type_Integer,
    CosToken_Type_Real,

    CosToken_Type_ArrayStart,
    CosToken_Type_ArrayEnd,
    CosToken_Type_DictionaryStart,
    CosToken_Type_DictionaryEnd,

    CosToken_Type_Keyword,

    CosToken_Type_EOF,
} CosToken_Type;

typedef struct CosTokenValue CosTokenValue;

struct CosToken {
    /**
     * @brief The type of the token.
     */
    CosToken_Type type;

    /**
     * @brief The value of the token.
     *
     * This is only valid for certain token types.
     */
    CosTokenValue * COS_Nullable value;
};

COS_ASSUME_NONNULL_END
COS_DECLS_END

#endif /* LIBCOS_COS_TOKEN_H */
