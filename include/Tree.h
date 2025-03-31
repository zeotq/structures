#ifndef Z_TREE_HPP
#define Z_TREE_HPP

#include <stdbool.h>
#include <stdint.h>
#include "Vector.h"

#define PRINT_VALUE(dtype, value) do {                                                                           \
    if (__builtin_types_compatible_p(dtype, int32_t))                                                            \
        printf("%u", value);                                                                                     \
    else if (__builtin_types_compatible_p(dtype, uint32_t))                                                      \
        printf("%d", value);                                                                                     \
    else if (__builtin_types_compatible_p(dtype, double))                                                        \
        printf("%d", value);                                                                                     \
    else if (__builtin_types_compatible_p(dtype, char))                                                          \
        printf("%c", value);                                                                                     \
    else                                                                                                         \
        printf("ERROR: Use custom print function!");                                                             \
} while(0)

#define Z_TREE(dtype, dname)                                                                                     \
                                                                                                                 \
Z_VECTOR(uintptr_t, uintptr_t_vector)                                                                            \
                                                                                                                 \
typedef struct dname##_node_ {                                                                                   \
    dtype data;                                                                                                  \
    struct dname##_node_ * parent;                                                                               \
    uintptr_t_vector * children;                                                                                 \
} dname##_node;                                                                                                  \
                                                                                                                 \
typedef struct dname##_ {                                                                                        \
    dname##_node * root_node;                                                                                    \
} dname;                                                                                                         \
                                                                                                                 \
/*Create Node with value and parent (Default must be NULL)*/                                                     \
static inline dname##_node * dname##_create_node(dtype value) {                                                  \
    dname##_node * node = (dname##_node *) malloc(sizeof(dname##_node));                                         \
    node->data = value;                                                                                          \
    node->parent = NULL;                                                                                         \
    node->children = uintptr_t_vector_create();                                                                  \
    return node;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
/*Create empty Tree*/                                                                                            \
static inline dname* dname##_create_empty() {                                                                    \
    dname* tree = (dname*) malloc(sizeof(dname));                                                                \
    tree->root_node = NULL;                                                                                      \
    return tree;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
/*Create Tree from root value*/                                                                                  \
static inline dname* dname##_create_from_value(dtype root_value) {                                               \
    dname* tree = (dname*) malloc(sizeof(dname));                                                                \
    tree->root_node = dname##_create_node(root_value);                                                           \
    return tree;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
/*Create Tree from node*/                                                                                        \
static inline dname* dname##_create_from_node(dname##_node * node) {                                             \
    dname* tree = (dname*) malloc(sizeof(dname));                                                                \
    tree->root_node = node;                                                                                      \
    return tree;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
static inline bool dname##_is_empty(dname* tree) {                                                               \
    return tree->root_node == NULL;                                                                              \
}                                                                                                                \
                                                                                                                 \
static bool dname##_insert_node(dname* tree, dname##_node * parent, dname##_node * node) {                       \
    if (dname##_is_empty(tree)) {                                                                                \
        tree->root_node = node;                                                                                  \
        return true;                                                                                             \
    }                                                                                                            \
    if (parent) {                                                                                                \
        uintptr_t_vector_push_back(parent->children, (uintptr_t) node);                                          \
        node->parent = parent;                                                                                   \
        return true;                                                                                             \
    }                                                                                                            \
    return false;                                                                                                \
}                                                                                                                \
                                                                                                                 \
static bool dname##_insert_value(dname* tree, dname##_node * parent, dtype value) {                              \
    if (parent && !dname##_is_empty(tree)) {                                                                     \
        dname##_node * node = dname##_create_node(value);                                                        \
        node->parent = parent;                                                                                   \
        uintptr_t_vector_push_back(parent->children, (uintptr_t) node);                                          \
        return true;                                                                                             \
    }                                                                                                            \
    if (!dname##_is_empty(tree)) {                                                                               \
        tree->root_node->data = value;                                                                           \
        return true;                                                                                             \
    }                                                                                                            \
    return false;                                                                                                \
}                                                                                                                \
                                                                                                                 \
/*Destroy Node and all Child-Nodes recursive*/                                                                   \
/*Does not remove children from the parent children list*/                                                       \
static void dname##_destroy_node(dname##_node * node) {                                                          \
    uintptr_t_vector_iterator it = uintptr_t_vector_iterator_begin(node->children);                              \
    while (uintptr_t_vector_iterator_has_next(&it)) {                                                            \
        dname##_destroy_node((dname##_node *) *uintptr_t_vector_iterator_next(&it));                             \
    }                                                                                                            \
    uintptr_t_vector_destroy(node->children);                                                                    \
    free(node);                                                                                                  \
}                                                                                                                \
                                                                                                                 \
/*Destroy Tree and all Child-Nodes recursive (uses dname##_destroy_node)*/                                       \
static inline void dname##_destroy(dname* tree) {                                                                \
    dname##_destroy_node(tree->root_node);                                                                       \
    free(tree);                                                                                                  \
}                                                                                                                \
                                                                                                                 \
static inline void dname##_delete_node(dname* tree, dname##_node * node) {                                       \
    if (tree->root_node == node) {                                                                               \
        dname##_destroy_node(tree->root_node);                                                                   \
        tree->root_node = NULL;                                                                                  \
        return;                                                                                                  \
    }                                                                                                            \
    dname##_node * parent_node = node->parent;                                                                   \
    if (node->parent) {                                                                                          \
        uintptr_t_vector * parent_children = node->parent->children;                                             \
        uintptr_t_vector_iterator it = uintptr_t_vector_iterator_begin(parent_children);                         \
        size_t index = 0;                                                                                        \
        while (uintptr_t_vector_iterator_has_next(&it)) {                                                        \
            dname##_node * parent_child_node = (dname##_node *) *uintptr_t_vector_iterator_next(&it);            \
            if (node == parent_child_node) {                                                                     \
                uintptr_t_vector_pop(parent_children, index);                                                    \
                break;                                                                                           \
            }                                                                                                    \
            ++index;                                                                                             \
        }                                                                                                        \
    }                                                                                                            \
    dname##_destroy_node(node);                                                                                  \
}                                                                                                                \
                                                                                                                 \
/*Find Node with value between children*/                                                                        \
static dname##_node * dname##_find_in_childs(dname##_node * node, dtype value) {                                 \
    uintptr_t_vector_iterator it = uintptr_t_vector_iterator_begin(node->children);                              \
    while (uintptr_t_vector_iterator_has_next(&it)) {                                                            \
        dname##_node * child_node = (dname##_node *) *uintptr_t_vector_iterator_next(&it);                       \
        if (child_node->data == value) {                                                                         \
            return child_node;                                                                                   \
        }                                                                                                        \
        dname##_node * found_among_children = dname##_find_in_childs(child_node, value);                         \
        if (found_among_children) {                                                                              \
            return found_among_children;                                                                         \
        }                                                                                                        \
    }                                                                                                            \
    return NULL;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
/*Find Node with value*/                                                                                         \
static inline dname##_node * dname##_find(dname* tree, dtype value) {                                            \
    if (tree->root_node->data == value) {                                                                        \
        return tree->root_node;                                                                                  \
    }                                                                                                            \
    return dname##_find_in_childs(tree->root_node, value);                                                       \
}                                                                                                                \
                                                                                                                 \
/*Print node */                                                                                                  \
static void dname##_node_children_print(dname##_node * node, size_t lvl) {                                       \
    uintptr_t_vector_iterator it = uintptr_t_vector_iterator_begin(node->children);                              \
    while (uintptr_t_vector_iterator_has_next(&it)) {                                                            \
        for(size_t i = 0; i < lvl; ++i) {                                                                        \
            printf("-> ");                                                                                       \
        }                                                                                                        \
        dname##_node * child_node = (dname##_node *) *uintptr_t_vector_iterator_next(&it);                       \
        dtype value = child_node->data;                                                                          \
        PRINT_VALUE(dtype, value);                                                                               \
        printf("\n");                                                                                            \
        dname##_node_children_print(child_node, lvl + 1);                                                        \
    }                                                                                                            \
}                                                                                                                \
                                                                                                                 \
/*Print all tree values with depth formating*/                                                                   \
/*Support int, float, char*/                                                                                     \
static inline void dname##_print(dname* tree) {                                                                  \
    PRINT_VALUE(dtype, tree->root_node->data);                                                                   \
    printf("\n");                                                                                                \
    dname##_node_children_print(tree->root_node, 1);                                                             \
}                                                                                                                \

#endif // Z_TREE_HPP