/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:25:00 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/20 18:50:12 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include <float.h>

#define BVH4_MAX_CHILDREN 4

static void bvh4_init_node(t_aabb_bvh *node)
{
    int i;

    node->min.x = FLT_MAX;
    node->min.y = FLT_MAX;
    node->min.z = FLT_MAX;
    node->max.x = -FLT_MAX;
    node->max.y = -FLT_MAX;
    node->max.z = -FLT_MAX;
    i = 0;
    while (i < 8)
    {
        node->children[i] = -1;
        ++i;
    }
    node->child_count = 0;
    node->depth = 0;
    node->skip = -1;
    node->bvh_ary_type = BVH4;
}

static void bvh4_expand_aabb(t_aabb_bvh *node, const t_aabb_bvh *child)
{
    if (child->min.x < node->min.x)
        node->min.x = child->min.x;
    if (child->min.y < node->min.y)
        node->min.y = child->min.y;
    if (child->min.z < node->min.z)
        node->min.z = child->min.z;
    if (child->max.x > node->max.x)
        node->max.x = child->max.x;
    if (child->max.y > node->max.y)
        node->max.y = child->max.y;
    if (child->max.z > node->max.z)
        node->max.z = child->max.z;
}

static int bvh4_collapse_node(const t_aabb_bvh *bvh2, int bvh2_size,
                              t_aabb_bvh *out, int *out_count, int bvh2_index)
{
    t_aabb_bvh node;
    int children_bvh2[BVH4_MAX_CHILDREN];
    int child2_count;
    int node_index;
    int i;
    const t_aabb_bvh *cur;
    int left;
    int right;
    int my_depth;

    if (bvh2_index < 0 || bvh2_index >= bvh2_size)
        return (-1);

    my_depth = bvh2[bvh2_index].depth;

    bvh4_init_node(&node);
    node.depth = my_depth;

    /* leaf: single object (depth == 0 in your BVH2) */
    if (my_depth == 0)
    {
        node.min = bvh2[bvh2_index].min;
        node.max = bvh2[bvh2_index].max;
        node.children[0] = -1 - bvh2[bvh2_index].object;
        node.child_count = 1;
        node_index = (*out_count)++;
        out[node_index] = node;
        return (node_index);
    }

    /* collect up to 4 real BVH2 children for this wide node */
    child2_count = 0;
    left = bvh2_index + 1;
    right = bvh2[bvh2_index].next;

    /* a real child must have depth == my_depth - 1 */
    if (left >= 0 && left < bvh2_size &&
        bvh2[left].depth == my_depth - 1 &&
        child2_count < BVH4_MAX_CHILDREN)
        children_bvh2[child2_count++] = left;

    if (right >= 0 && right < bvh2_size &&
        bvh2[right].depth == my_depth - 1 &&
        child2_count < BVH4_MAX_CHILDREN)
        children_bvh2[child2_count++] = right;

    if (child2_count == 0)
    {
        /* No valid children with smaller depth: treat as degenerate leaf */
        node.min = bvh2[bvh2_index].min;
        node.max = bvh2[bvh2_index].max;
        node.children[0] = -1 - bvh2[bvh2_index].object;
        node.child_count = 1;
        node_index = (*out_count)++;
        out[node_index] = node;
        return (node_index);
    }

    /* build parent AABB and count children */
    i = 0;
    while (i < child2_count)
    {
        cur = &bvh2[children_bvh2[i]];
        if (node.child_count == 0)
        {
            node.min = cur->min;
            node.max = cur->max;
        }
        else
            bvh4_expand_aabb(&node, cur);
        ++node.child_count;
        ++i;
    }

    node_index = (*out_count)++;
    out[node_index] = node;

    /* build children recursively or as encoded leaves */
    i = 0;
    while (i < node.child_count)
    {
        cur = &bvh2[children_bvh2[i]];
        if (cur->depth == 0)
            out[node_index].children[i] = -1 - cur->object;
        else
        {
            out[node_index].children[i] = bvh4_collapse_node(bvh2, bvh2_size,
                                                             out, out_count,
                                                             children_bvh2[i]);
            if (out[node_index].children[i] < 0)
                return (-1);
        }
        ++i;
    }

    return (node_index);
}


void print_bvh2(const t_aabb_bvh *bvh2, int size, const char *name)
{
    int i;

    printf("==== %s (BVH2) ====\n", name);
    for (i = 0; i < size; ++i)
    {
        const t_aabb_bvh *n = &bvh2[i];
        printf("#%d: depth=%d next=%d skip=%d type=%d ",
               i, n->depth, n->next, n->skip, n->bvh_ary_type);
        if (n->depth == 0)
            printf("leaf object=%d\n", n->object);
        else
            printf("internal\n");
    }
    printf("============\n");
}


void print_bvh4(const t_aabb_bvh *bvh4, int size, const char *name)
{
    int i, j;

    printf("==== %s (BVH4) ====\n", name);
    for (i = 0; i < size; ++i)
    {
        const t_aabb_bvh *n = &bvh4[i];
        printf("#%d: depth=%d child_count=%d skip=%d type=%d\n",
               i, n->depth, n->child_count, n->skip, n->bvh_ary_type);
        for (j = 0; j < n->child_count; ++j)
        {
            int c = n->children[j];
            if (c >= 0)
                printf("    child[%d] -> node %d\n", j, c);
            else
                printf("    child[%d] -> leaf object %d\n",
                       j, -1 - c);
        }
    }
    printf("============\n");
}

int create_bvh4_from_bvh2(const t_aabb_bvh *bvh2, int bvh2_size,
                          t_aabb_bvh *out_bvh4, int out_capacity,
                          int *out_size)
{
    int node_count;
    int root_index;

	print_bvh2(bvh2, bvh2_size, "triangle_bvh2");
    if (!bvh2 || bvh2_size <= 0 || !out_bvh4 || out_capacity <= 0)
    {
        if (out_size)
            *out_size = 0;
        return 0;
    }
    node_count = 0;

	root_index = bvh4_collapse_node(bvh2, bvh2_size, out_bvh4, &node_count, 0);
    if (root_index < 0)
        return -1;
    if (node_count > out_capacity)
        return -1;
    if (out_size)
        *out_size = node_count;
    print_bvh4(out_bvh4, *out_size, "triangle_bvh4");
    return 0;
}


