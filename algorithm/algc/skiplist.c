#include <stdlib.h>
#include <limits.h>

#define NULLitem INT_MAX
typedef int Item;
typedef int Key;

static bool less(Key k1, Key k2) {
    return k1 < k2;
}

static bool eq(Key k1, Key k2) {
    return k1 == k2;
}

static Key getKey(Item item) {
    return item;
}

typedef struct STnode* Link;

struct STnode {
    Item item;
    Link* next; // the link array
    int sz;     // size of link array
};

static Link head, z;
static int N;   // number of items in the list
static int lgN; // number of levels
static int lgNmax = 32; // max number of levels

static Link NewNode(Item item, int k) {
    Link x = (Link)malloc(sizeof(STnode));
    x->next = (Link*)malloc(k * sizeof(Link));
    x->item = item;
    x->sz = k;
    for (int i = 0; i < k; i++) {
        x->next[i] = z;
    }
    return x;
}

void STinit() {
    N = 0;
    lgN = 0;
    z = NewNode(NULLitem, 0);
    head = NewNode(NULLitem, lgNmax+1);
}

int randX() {
    int i, j, t = rand();
    for (i = 1, j = 2; i < lgNmax; i++, j *= 2) {
        if (t > RAND_MAX / j) {
            break;
        }
    }
    if (i > lgN) {
        lgN = i;
    }
    return i;
}

/**
 * insert x on k level. t is the header.
 */
static void insertR(Link t, Link x, int k) {
    Key v = getKey(x->item);
    if (less(v, getKey(t->next[k]->item))) {
        //
        // need to insert on this level, insert it
        //
        if (k < x->sz) {
            x->next[k] = t->next[k];
            t->next[k] = x; 
        }

        if (k == 0) {
            return;
        }

        //
        // continue to insert to next level, from top to bottom(0).
        //
        insertR(t, x, k-1);
        return;
    }
    insertR(t->next[k], x, k);
}

void STinsert(Item item) {
    insertR(head, NewNode(item, randX()), lgN);
    N++;
}

/**
 * search
 */
static Item searchR(Link t, Key v, int k) {
    if (t == z) {
        return NULLitem;
    }

    if (eq(v, getKey(t->item))) {
        return t->item;
    }

    if (less(v, getKey(t->next[k]->item))) {
        if (k == 0) {
            // reach the last level
            return NULLitem;
        } else {
            return searchR(t, v, k - 1);
        }
    }
    return searchR(t->next[k], v, k);
}

Item STsearch(Key v) {
    return searchR(head, v, lgN);
}


/**
 * delete
 */
static void deleteR(Link t, Key v, int k) {
    Link x = t->next[k];
    if (!less(getKey(x->item), v)) {
        //
        // unlink at each level we find a link
        //
        if (eq(v, getKey(x->item))) {
            t->next[k] = x->next[k];
        }

        //
        // free it when we reach the bottom level
        //
        if (k == 0) {
            free(x);
            return;
        }
        deleteR(t, v, k-1);
        return;
    }

    deleteR(t->next[k], v, k);
}

void STdelete(Key v) {
    deleteR(head, v, lgN);
    N--;
}

