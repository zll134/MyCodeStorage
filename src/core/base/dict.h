/* ********************************
 * Author:       Zhanglele
 * Description:  hash表管理模块
 * create time:  2023.05.21
 ********************************/
#ifndef DICT_H
#define DICT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct tag_dict_entry {
    void *key;
    void *val;
    struct tag_dict_entry *next;
} dict_entry_t;

typedef struct {
    dict_entry_t **table;
    uint32_t size;
    uint32_t sizemask;
    uint32_t used;
} dict_htable_t;

typedef struct {
    void *priv_data;
    uint32_t (*hash_func)(const void *key);
    void *(*key_dup)(const void *key);
    void *(*val_dup)(const void *val);
    void (*free)(const void *data);
    bool (*key_match)(const void *key1, const void *key2);
} dict_config_t;

typedef struct {
    dict_htable_t ht[2];  /* 设置两个哈希表用于渐进式rehash */
    dict_config_t config; /* 哈希表配置 */
    int rehash_idx;       /* 记录正在rehash的哈希表编号, -1表示未重哈希 */
} dict_t;

/* 创建哈希表对象 */
dict_t *dict_create(dict_config_t *config);

/* 释放哈希表对象 */
void dict_destroy(dict_t *dict);

/* 改变哈希表的长度。
 * @warning: 如果正在进行rehash，该操作会失败
 * */
int dict_resize(dict_t *dict, uint32_t size);

/* 向哈希表中添加键值对 */
int dict_add(dict_t *dict, void *key, void *value);

/* 删除哈希表中的键 */
int dict_delete(dict_t *dict, void *key);

#endif