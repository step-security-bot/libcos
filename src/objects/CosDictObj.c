/*
 * Copyright (c) 2023 OpenCOS.
 */

#include "libcos/objects/CosDictObj.h"

#include "common/Assert.h"
#include "libcos/common/CosDict.h"
#include "libcos/objects/CosObj.h"

#include <stdlib.h>

COS_ASSUME_NONNULL_BEGIN

struct CosDictObj {
    CosObjType type;

    CosDict *value;
};

CosDictObj *
cos_dict_obj_alloc(CosDict * COS_Nullable dict)
{
    CosDictObj * const dict_obj = calloc(1, sizeof(CosDictObj));
    if (!dict_obj) {
        goto failure;
    }

    dict_obj->type = CosObjType_Dict;

    if (dict) {
        dict_obj->value = (CosDict *)dict;
    }
    else {
        CosDict * const new_dict = cos_dict_alloc(&cos_dict_obj_key_callbacks,
                                                  &cos_dict_obj_value_callbacks,
                                                  0);
        if (!new_dict) {
            goto failure;
        }
        dict_obj->value = new_dict;
    }
    COS_ASSERT(dict_obj->value != NULL, "Expected a dictionary value");

    return dict_obj;

failure:
    if (dict_obj) {
        free(dict_obj);
    }
    return NULL;
}

void
cos_dict_obj_free(CosDictObj *dict_obj)
{
    if (!dict_obj) {
        return;
    }

    cos_dict_free(dict_obj->value);
    free(dict_obj);
}

bool
cos_dict_obj_set(CosDictObj *dict_obj,
                 CosNameObj *key,
                 CosObj *value,
                 CosError * COS_Nullable error)
{
    COS_PARAMETER_ASSERT(dict_obj != NULL);
    COS_PARAMETER_ASSERT(key != NULL);
    COS_PARAMETER_ASSERT(value != NULL);
    if (!dict_obj || !key || !value) {
        return false;
    }

    return cos_dict_set(dict_obj->value, key, value, error);
}

COS_ASSUME_NONNULL_END
