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

#define Z_TREE(dtype)                                                                                            \
                                                                                                                 \
Z_VECTOR(uintptr_t)                                                                                              \
                                                                                                                 \
typedef struct dtype##_tree_node_ {                                                                              \
    dtype data;                                                                                                  \
    struct dtype##_tree_node_ * parent;                                                                          \
    uintptr_t_vector * children;                                                                                 \
} dtype##_tree_node;                                                                                             \
                                                                                                                 \
typedef struct dtype##_tree_ {                                                                                   \
    dtype##_tree_node * root_node;                                                                               \
} dtype##_tree;                                                                                                  \
                                                                                                                 \
/*Create Node with value and parent (Default must be NULL)*/                                                     \
static inline dtype##_tree_node * dtype##_tree_create_node(dtype value) {                                        \
    dtype##_tree_node * node = (dtype##_tree_node *) malloc(sizeof(dtype##_tree_node));                          \
    node->data = value;                                                                                          \
    node->parent = NULL;                                                                                         \
    node->children = uintptr_t_vector_create();                                                                  \
    return node;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
/*Create empty Tree*/                                                                                            \
static inline dtype##_tree * dtype##_tree_create_empty() {                                                       \
    dtype##_tree * tree = (dtype##_tree *) malloc(sizeof(dtype##_tree));                                         \
    tree->root_node = NULL;                                                                                      \
    return tree;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
/*Create Tree from root value*/                                                                                  \
static inline dtype##_tree * dtype##_tree_create_from_value(dtype root_value) {                                  \
    dtype##_tree * tree = (dtype##_tree *) malloc(sizeof(dtype##_tree));                                         \
    tree->root_node = dtype##_tree_create_node(root_value);                                                      \
    return tree;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
/*Create Tree from node*/                                                                                        \
static inline dtype##_tree * dtype##_tree_create_from_node(dtype##_tree_node * node) {                           \
    dtype##_tree * tree = (dtype##_tree *) malloc(sizeof(dtype##_tree));                                         \
    tree->root_node = node;                                                                                      \
    return tree;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
static inline bool dtype##_tree_is_empty(dtype##_tree * tree) {                                                  \
    return tree->root_node == NULL;                                                                              \
}                                                                                                                \
                                                                                                                 \
static bool dtype##_tree_insert_node(dtype##_tree * tree, dtype##_tree_node * parent, dtype##_tree_node * node) {       \
    if (dtype##_tree_is_empty(tree)) {                                                                           \
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
static bool dtype##_tree_insert_value(dtype##_tree * tree, dtype##_tree_node * parent, dtype value) {            \
    if (parent && !dtype##_tree_is_empty(tree)) {                                                                \
        dtype##_tree_node * node = dtype##_tree_create_node(value);                                              \
        node->parent = parent;                                                                                   \
        uintptr_t_vector_push_back(parent->children, (uintptr_t) node);                                          \
        return true;                                                                                             \
    }                                                                                                            \
    if (!dtype##_tree_is_empty(tree)) {                                                                          \
        tree->root_node->data = value;                                                                           \
        return true;                                                                                             \
    }                                                                                                            \
    return false;                                                                                                \
}                                                                                                                \
                                                                                                                 \
/*Destroy Node and all Child-Nodes recursive*/                                                                   \
/*Does not remove children from the parent children list*/                                                       \
static void dtype##_tree_destroy_node(dtype##_tree_node * node) {                                                \
    uintptr_t_vector_iterator it = uintptr_t_vector_iterator_begin(node->children);                              \
    while (uintptr_t_vector_iterator_has_next(&it)) {                                                            \
        dtype##_tree_destroy_node((dtype##_tree_node *) *uintptr_t_vector_iterator_next(&it));                   \
    }                                                                                                            \
    uintptr_t_vector_destroy(node->children);                                                                    \
    free(node);                                                                                                  \
}                                                                                                                \
                                                                                                                 \
/*Destroy Tree and all Child-Nodes recursive (uses dtype##_tree_destroy_node)*/                                  \
static inline void dtype##_tree_destroy(dtype##_tree * tree) {                                                   \
    dtype##_tree_destroy_node(tree->root_node);                                                                  \
    free(tree);                                                                                                  \
}                                                                                                                \
                                                                                                                 \
static inline void dtype##_tree_delete_node(dtype##_tree_node * node) {                                          \
    dtype##_tree_node * parent_node = node->parent;                                                              \
    if (node->parent) {                                                                                          \
        uintptr_t_vector * parent_children = node->parent->children;                                             \
        uintptr_t_vector_iterator it = uintptr_t_vector_iterator_begin(parent_children);                         \
        size_t index = 0;                                                                                        \
        while (uintptr_t_vector_iterator_has_next(&it)) {                                                        \
            dtype##_tree_node * parent_child_node = (dtype##_tree_node *) *uintptr_t_vector_iterator_next(&it);  \
            if (node == parent_child_node) {                                                                     \
                uintptr_t_vector_pop(parent_children, index);                                                    \
                break;                                                                                           \
            }                                                                                                    \
            ++index;                                                                                             \
        }                                                                                                        \
    }                                                                                                            \
    dtype##_tree_destroy_node(node);                                                                             \
}                                                                                                                \
                                                                                                                 \
/*Find Node with value between children*/                                                                        \
static dtype##_tree_node * dtype##_tree_find_in_childs(dtype##_tree_node * node, dtype value) {                  \
    uintptr_t_vector_iterator it = uintptr_t_vector_iterator_begin(node->children);                              \
    while (uintptr_t_vector_iterator_has_next(&it)) {                                                            \
        dtype##_tree_node * child_node = (dtype##_tree_node *) *uintptr_t_vector_iterator_next(&it);             \
        if (child_node->data == value) {                                                                         \
            return child_node;                                                                                   \
        }                                                                                                        \
        dtype##_tree_node * found_among_children = dtype##_tree_find_in_childs(child_node, value);               \
        if (found_among_children) {                                                                              \
            return found_among_children;                                                                         \
        }                                                                                                        \
    }                                                                                                            \
    return NULL;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
/*Find Node with value*/                                                                                         \
static inline dtype##_tree_node * dtype##_tree_find(dtype##_tree * tree, dtype value) {                          \
    if (tree->root_node->data == value) {                                                                        \
        return tree->root_node;                                                                                  \
    }                                                                                                            \
    return dtype##_tree_find_in_childs(tree->root_node, value);                                                  \
}                                                                                                                \
                                                                                                                 \
/*Print node */                                                                                                  \
static void dtype##_node_children_print(dtype##_tree_node * node, size_t lvl) {                                  \
    uintptr_t_vector_iterator it = uintptr_t_vector_iterator_begin(node->children);                              \
    while (uintptr_t_vector_iterator_has_next(&it)) {                                                            \
        for(size_t i = 0; i < lvl; ++i) {                                                                        \
            printf("-> ");                                                                                       \
        }                                                                                                        \
        dtype##_tree_node * child_node = (dtype##_tree_node *) *uintptr_t_vector_iterator_next(&it);             \
        dtype value = child_node->data;                                                                          \
        PRINT_VALUE(dtype, value);                                                                               \
        printf("\n");                                                                                            \
        dtype##_node_children_print(child_node, lvl + 1);                                                        \
    }                                                                                                            \
}                                                                                                                \
                                                                                                                 \
/*Print all tree values with depth formating*/                                                                   \
/*Support int, float, char*/                                                                                     \
static inline void dtype##_tree_print(dtype##_tree * tree) {                                                     \
    PRINT_VALUE(dtype, tree->root_node->data);                                                                   \
    printf("\n");                                                                                                \
    dtype##_node_children_print(tree->root_node, 1);                                                             \
}                                                                                                                \

#endif // Z_TREE_HPP