#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "film.h"
#include "watchstack.h"

// Initializes the stack
tApiError filmstack_init(tFilmstack* stack) {
    /////////////////////////////////
    // PR2_2c
    /////////////////////////////////

    assert(stack != NULL);
    stack->top = NULL;
    stack->count = 0;
    return E_SUCCESS;
}

// Returns true if the stack is empty
bool filmstack_isEmpty(tFilmstack stack) {
    /////////////////////////////////
    // PR2_2d
    /////////////////////////////////

    return stack.top == NULL;
}


// Adds a new film to the stack, unless it already exists
tApiError filmstack_push(tFilmstack* stack, tFilm film) {
    /////////////////////////////////
    // PR2_2e
    /////////////////////////////////
    assert(stack != NULL);

    // Check if the film already exists in the stack (by title)
    tFilmstackNode* current = stack->top;
    while (current != NULL) {
        if (film_equals(current->elem, film)) {
            // Film is already in the stack, do not add it
            return E_FILM_ALREADY_EXISTS;
        }
        current = current->next;
    }

    // Allocate memory for the new node
    tFilmstackNode* node = (tFilmstackNode*) malloc(sizeof(tFilmstackNode));
    if (node == NULL)
        return E_MEMORY_ERROR;

    // Copy the film to the new node
    film_cpy(&node->elem, film);

    // Insert the node at the top of the stack
    node->next = stack->top;
    stack->top = node;
    stack->count++;

    return E_SUCCESS;
}

// Returns the top film (without removing it)
tFilm* filmstack_top(tFilmstack stack) {
    /////////////////////////////////
    // PR2_2f
    /////////////////////////////////

    if (stack.top == NULL)
        return NULL;
    return &stack.top->elem;
}

// Removes the top film from the stack
tApiError filmstack_pop(tFilmstack* stack) {
    /////////////////////////////////
    // PR2_2g
    /////////////////////////////////

    assert(stack != NULL);
    if (stack->top == NULL)
        return E_STRUCTURE_EMPTY;

    tFilmstackNode* temp = stack->top;
    stack->top = stack->top->next;
    film_free(&temp->elem);
    free(temp);
    stack->count--;

    return E_SUCCESS;
}

// Frees the whole stack
void filmstack_free(tFilmstack* stack) {
    /////////////////////////////////
    // PR2_2f
    /////////////////////////////////

    assert(stack != NULL);
    while (!filmstack_isEmpty(*stack)) {
        filmstack_pop(stack);
    }
}