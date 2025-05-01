#ifndef Z_TREE_HPP
#define Z_TREE_HPP

#include <stdbool.h>
#include <stdint.h>
#include "Vector.h"


#define Z_TREE(dtype, dname)                                                                                     \
                                                                                                                 \
Z_VECTOR(struct dname##_node_*, dname##_node_vector)                                                             \
                                                                                                                 \
typedef struct dname##_node_ {                                                                                   \
    dtype data;                                                                                                  \
    struct dname##_node_ * parent;                                                                               \
    dname##_node_vector * children;                                                                              \
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
    node->children = dname##_node_vector_create();                                                               \
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
        dname##_node_vector_push_back(parent->children, (dname##_node*) node);                                   \
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
        dname##_node_vector_push_back(parent->children, (dname##_node*) node);                                   \
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
    if (!node) return;                                                                                           \
    dname##_node_vector_iterator it = dname##_node_vector_iterator_begin(node->children);                        \
    while (dname##_node_vector_iterator_has_next(&it)) {                                                         \
        dname##_destroy_node((dname##_node *) *dname##_node_vector_iterator_next(&it));                          \
    }                                                                                                            \
    dname##_node_vector_destroy(node->children);                                                                 \
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
        dname##_node_vector * parent_children = node->parent->children;                                          \
        dname##_node_vector_iterator it = dname##_node_vector_iterator_begin(parent_children);                   \
        size_t index = 0;                                                                                        \
        while (dname##_node_vector_iterator_has_next(&it)) {                                                     \
            dname##_node * parent_child_node = (dname##_node *) *dname##_node_vector_iterator_next(&it);         \
            if (node == parent_child_node) {                                                                     \
                dname##_node_vector_pop(parent_children, index);                                                 \
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
    dname##_node_vector_iterator it = dname##_node_vector_iterator_begin(node->children);                        \
    while (dname##_node_vector_iterator_has_next(&it)) {                                                         \
        dname##_node * child_node = (dname##_node *) *dname##_node_vector_iterator_next(&it);                    \
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
static void dname##_node_children_print(dname##_node * node, void (*func)(dtype), size_t lvl) {                  \
    dname##_node_vector_iterator it = dname##_node_vector_iterator_begin(node->children);                        \
    while (dname##_node_vector_iterator_has_next(&it)) {                                                         \
        for(size_t i = 0; i < lvl; ++i) {                                                                        \
            printf("-> ");                                                                                       \
        }                                                                                                        \
        dname##_node * child_node = (dname##_node *) *dname##_node_vector_iterator_next(&it);                    \
        dtype value = child_node->data;                                                                          \
        func(value);                                                                                             \
        printf("\n");                                                                                            \
        dname##_node_children_print(child_node, func, lvl + 1);                                                  \
    }                                                                                                            \
}                                                                                                                \
                                                                                                                 \
/*Print all tree values with depth formating*/                                                                   \
/*Support int, float, char*/                                                                                     \
static inline void dname##_print(dname* tree, void (*func)(dtype)) {                                             \
    func(tree->root_node->data);                                                                                 \
    printf("\n");                                                                                                \
    dname##_node_children_print(tree->root_node, func, 1);                                                       \
}                                                                                                                \

#endif // Z_TREE_HPP