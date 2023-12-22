//
// Created by david on 17/12/23.
//

#include "libcos/io/CosFileInputStream.h"
#include "parse/CosTokenizer.h"
#include "syntax/CosSyntax.h"

#include <libcos/io/CosInputStream.h>

#include <stdlib.h>

int
main(int argc, char *argv[])
{
    // Get the current working directory.

    CosFileInputStream * const input_stream = cos_file_input_stream_open("/home/david/Projects/C/libcos/tests/data/Hello-world.pdf",
                                                                     "r",
                                                                     NULL);
    if (!input_stream) {
        goto failure;
    }

    CosTokenizer * const tokenizer = cos_tokenizer_alloc((CosInputStream *)input_stream);
    if (!tokenizer) {
        goto failure;
    }

    const CosToken *token = NULL;
    while ((token = cos_tokenizer_next_token(tokenizer)) != NULL) {
        if (token->type == CosToken_Type_EOF) {
            break;
        }

        switch (token->type) {
            case CosToken_Type_Unknown: {
                CosString *string = NULL;
                if (cos_token_value_get_string(&(token->value),
                                               &string)) {
                    printf("Unknown: %s\n",
                           string->data);
                }
                else {
                    printf("Unknown\n");
                }
            } break;

            case CosToken_Type_Boolean: {
                bool value = false;
                if (cos_token_value_get_boolean(&(token->value),
                                                &value)) {
                    printf("Boolean: %s\n",
                           value ? "true" : "false");
                }
            } break;
            case CosToken_Type_Literal_String: {
                CosString *string = NULL;
                if (cos_token_value_get_string(&(token->value),
                                               &string)) {
                    printf("Literal String: %s\n",
                           string->data);
                }
            } break;
            case CosToken_Type_Hex_String: {
                CosData *data = NULL;
                if (cos_token_value_get_data(&(token->value),
                                             &data)) {
                    printf("Hex String: %s\n",
                           data->bytes);
                }
            } break;
            case CosToken_Type_Name: {
                CosString *string = NULL;
                if (cos_token_value_get_string(&(token->value),
                                               &string)) {
                    printf("Name: %s\n",
                           string->data);
                }
            } break;
            case CosToken_Type_Integer: {
                int value = 0;
                if (cos_token_value_get_integer_number(&(token->value),
                                                       &value)) {
                    printf("Integer: %d\n",
                           value);
                }
            } break;
            case CosToken_Type_Real: {
                double value = 0.0;
                if (cos_token_value_get_real_number(&(token->value),
                                                    &value)) {
                    printf("Real: %f\n",
                           value);
                }
            } break;
            case CosToken_Type_Stream: {
                printf("Stream\n");
            } break;
            case CosToken_Type_Null: {
                printf("Null\n");
            } break;
            case CosToken_Type_EndOfLine: {
                printf("End of Line\n");
            } break;
            case CosToken_Type_ArrayStart: {
                printf("Array Start\n");
            } break;
            case CosToken_Type_ArrayEnd: {
                printf("Array End\n");
            } break;
            case CosToken_Type_DictionaryStart: {
                printf("Dictionary Start\n");
            } break;
            case CosToken_Type_DictionaryEnd: {
                printf("Dictionary End\n");
            } break;
            case CosToken_Type_Keyword: {
                CosKeywordType value = CosKeywordType_Unknown;
                if (cos_token_value_get_keyword(&(token->value),
                                                &value)) {
                    printf("Keyword: %s\n",
                           cos_keyword_type_to_string(value));
                }
            } break;
            case CosToken_Type_EOF: {
                printf("EOF\n");
            } break;
        }
    }

    cos_tokenizer_free(tokenizer);
    cos_input_stream_close((CosInputStream *)input_stream);

    return EXIT_SUCCESS;

failure:
    return EXIT_FAILURE;
}
