// Copyright 2010-2014 RethinkDB, all rights reserved.
#ifndef BTREE_LEAF_STRUCTURE_HPP_
#define BTREE_LEAF_STRUCTURE_HPP_

#include <stdint.h>

#include "buffer_cache/types.hpp"

// The leaf node begins with the following struct layout.  (This is the old leaf node
// layout, which is getting migrated to main_leaf_node_t or something else, depending
// on which btree it's in.)
struct leaf_node_t {
    // The magic value: It tells us whether this is in the original format (described
    // here) or some other.
    block_magic_t magic;

    // The size of pair_offsets.
    uint16_t num_pairs;

    // The total size (in bytes) of the live entries and their 2-byte
    // pair offsets in pair_offsets.  (Does not include the size of
    // the live entries' timestamps.)
    uint16_t live_size;

    // The frontmost offset.
    uint16_t frontmost;

    // The first offset whose entry is not accompanied by a timestamp.
    uint16_t tstamp_cutpoint;

    // The pair offsets.
    uint16_t pair_offsets[];

} __attribute__ ((__packed__));


// Leaf nodes for the main b-tree.
struct main_leaf_node_t {
    // The magic value, telling that it's of the main_leaf_node_t struct layout, and
    // not some other.
    block_magic_t magic;

    // The size of pair_offsets;
    uint16_t num_pairs;

    uint16_t live_size;

    uint16_t frontmost;

    uint16_t tstamp_cutpoint;

    uint16_t deletions_cutpoint;

    uint16_t pair_offsets[];

} __attribute__ ((__packed__));



#endif  // BTREE_LEAF_STRUCTURE_HPP_