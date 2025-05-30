#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "subscription.h"

#include <math.h>

// Parse input from CSVEntry
void subscription_parse(tSubscription *data, tCSVEntry entry) {
    // Check input data
    assert(data != NULL);

    // Check entry fields
    assert(csv_numFields(entry) == NUM_FIELDS_SUBSCRIPTION);

    int pos = 0; // Allow to easy incremental position of the income data

    // Copy subscription's id data
    data->id = csv_getAsInteger(entry, pos);

    // Copy identity document data
    assert(strlen(entry.fields[++pos]) == MAX_DOCUMENT);
    csv_getAsString(entry, pos, data->document, MAX_DOCUMENT + 1);

    // Parse start date
    assert(strlen(entry.fields[++pos]) == DATE_LENGTH);
    date_parse(&(data->start_date), entry.fields[pos]);

    // Parse end date
    assert(strlen(entry.fields[++pos]) == DATE_LENGTH);
    date_parse(&(data->end_date), entry.fields[pos]);

    // Copy plan data
    csv_getAsString(entry, ++pos, data->plan, MAX_PLAN + 1);

    // Copy price data
    data->price = csv_getAsReal(entry, ++pos);

    // Copy number of devices data
    data->numDevices = csv_getAsInteger(entry, ++pos);

    // Init watchlist
    filmstack_init(&data->watchlist);

    // Check preconditions that needs the readed values
    assert(data->price >= 0);
    assert(data->numDevices >= 1);
}

// Copy the data from the source to destination (individual data)
void subscription_cpy(tSubscription *destination, tSubscription source) {
    // Copy subscription's id data
    destination->id = source.id;

    // Copy identity document data
    strncpy(destination->document, source.document, MAX_DOCUMENT + 1);

    // Copy start date
    date_cpy(&(destination->start_date), source.start_date);

    // Copy end date
    date_cpy(&(destination->end_date), source.end_date);

    // Copy plan data
    strncpy(destination->plan, source.plan, MAX_PLAN + 1);

    // Copy price data
    destination->price = source.price;

    // Copy number of devices data
    destination->numDevices = source.numDevices;

    filmstack_init(&destination->watchlist);

    if (source.watchlist.count > 0) {
        tFilmstackNode *pFimStackNodes[source.watchlist.count];
        tFilmstackNode *fimStackNode;
        fimStackNode = source.watchlist.top;
        int j = 0;
        while (fimStackNode != NULL) {
            pFimStackNodes[j] = fimStackNode;
            fimStackNode = fimStackNode->next;
            j++;
        }

        //adding the films to the watchlist in reverse order because filmstack_push is used
        for (j = source.watchlist.count - 1; j >= 0; j--) {
            filmstack_push(&destination->watchlist, pFimStackNodes[j]->elem);
        }
    }
}

// Get subscription data using a string
void subscription_get(tSubscription data, char *buffer) {
    // Print all data at same time
    sprintf(buffer, "%d;%s;%02d/%02d/%04d;%02d/%02d/%04d;%s;%g;%d",
            data.id,
            data.document,
            data.start_date.day, data.start_date.month, data.start_date.year,
            data.end_date.day, data.end_date.month, data.end_date.year,
            data.plan,
            data.price,
            data.numDevices);
}

// Initialize subscriptions data
tApiError subscriptions_init(tSubscriptions *data) {
    // Check input data
    assert(data != NULL);
    data->elems = NULL;
    data->count = 0;

    return E_SUCCESS;
}

// Return the number of subscriptions
int subscriptions_len(tSubscriptions data) {
    return data.count;
}

// Add a new subscription
tApiError subscriptions_add(tSubscriptions *data, tPeople people, tSubscription subscription) {
    // Check input data
    assert(data != NULL);

    // If subscription already exists, return an error
    for (int i = 0; i < data->count; i++) {
        if (subscription_equal(data->elems[i], subscription))
            return E_SUBSCRIPTION_DUPLICATED;
    }

    // If the person does not exist, return an error
    if (people_find(people, subscription.document) < 0)
        return E_PERSON_NOT_FOUND;

    // Copy the data to the new position
    if (data->elems == NULL) {
        data->elems = (tSubscription *) malloc(sizeof(tSubscription));
    } else {
        data->elems = (tSubscription *) realloc(data->elems, (data->count + 1) * sizeof(tSubscription));
    }
    assert(data->elems != NULL);
    subscription_cpy(&(data->elems[data->count]), subscription);

    /////////////////////////////////
    // Increase the number of elements
    data->count++;

    /////////////////////////////////
    // PR3_3f
    /////////////////////////////////

    return E_SUCCESS;
}

// Remove a subscription
tApiError subscriptions_del(tSubscriptions *data, int id) {
    int idx;
    int i;

    // Check if an entry with this data already exists
    idx = subscriptions_find(*data, id);

    // If the subscription does not exist, return an error
    if (idx < 0)
        return E_SUBSCRIPTION_NOT_FOUND;

    // Shift elements to remove selected
    for (i = idx; i < data->count - 1; i++) {
        //free watchlist
        filmstack_free(&data->elems[i].watchlist);
        // Copy element on position i+1 to position i
        subscription_cpy(&(data->elems[i]), data->elems[i + 1]);

        /////////////////////////////////
        // PR3_3e
        /////////////////////////////////
    }
    // Update the number of elements
    data->count--;

    if (data->count > 0) {
        filmstack_free(&data->elems[data->count].watchlist);
        data->elems = (tSubscription *) realloc(data->elems, data->count * sizeof(tSubscription));
        assert(data->elems != NULL);
    } else {
        subscriptions_free(data);
    }

    return E_SUCCESS;
}

// Get subscription data of position index using a string
void subscriptions_get(tSubscriptions data, int index, char *buffer) {
    assert(index >= 0 && index < data.count);
    subscription_get(data.elems[index], buffer);
}

// Returns the position of a subscription looking for id's subscription. -1 if it does not exist
int subscriptions_find(tSubscriptions data, int id) {
    int i = 0;
    while (i < data.count) {
        if (data.elems[i].id == id) {
            return i;
        }
        i++;
    }

    return -1;
}

// Print subscriptions data
void subscriptions_print(tSubscriptions data) {
    char buffer[1024];
    int i;
    for (i = 0; i < data.count; i++) {
        subscriptions_get(data, i, buffer);
        printf("%s\n", buffer);
    }
}

// Remove all elements
tApiError subscriptions_free(tSubscriptions *data) {
    if (data->elems != NULL) {
        /////////////////////////////////
        // PR2_2b
        /////////////////////////////////
        for (int i = 0; i < data->count; i++) {
            filmstack_free(&data->elems[i].watchlist);
        }
        /////////////////////////////////
        free(data->elems);
    }
    subscriptions_init(data);

    return E_SUCCESS;
}

// 2c - Calculate Vip Level of a person
int calculate_vipLevel(tSubscriptions *data, char *document) {
    assert(data != NULL);
    assert(document != NULL);

    float totalPrice = 0;

    for (int i = 0; i < data->count; i++) {
        if (strcmp(data->elems[i].document, document) == 0) {
            const tDate start = data->elems[i].start_date;
            const tDate end = data->elems[i].end_date;
            // Calculate months
            int months = (end.year - start.year) * 12 + (end.month - start.month);
            if (end.day >= start.day) {
                months += 1;
            }

            totalPrice += data->elems[i].price * (float) months;
        }
    }

    return (int) (totalPrice / 500.0);
}

// 2d - Update the vipLevel of each person
tApiError update_vipLevel(tSubscriptions *data, tPeople *people) {
    assert(data != NULL);
    assert(people != NULL);

    for (int i = 0; i < people->count; i++) {
        if (data->count == 0) {
            people->elems[i].vipLevel = 0;
        }

        people->elems[i].vipLevel = calculate_vipLevel(data, people->elems[i].document);
    }

    return E_SUCCESS;
}

// 3a - Return a pointer to the longest film of the list

// Summary:
// Scan all subscriptions and their film watchlist.
// Keep track of unique films and count how many times each appears.
// Update film info if it finds a newer release date for the same film.
// Then it finds the film with the highest count, breaking ties by choosing the newest film.
// Returns a dynamically allocated copy of the name of that film.
// Returns NULL if no films are found.
char *popularFilm_find(tSubscriptions data) {
    if (data.count == 0) return NULL;

    // Temporary storage (randomly set to 10 elems)
    tFilm uniqueFilms[10];
    int filmCounts[10];
    int uniqueCount = 0;

    // Subscriptions iteration to get the film stack
    for (int i = 0; i < data.count; i++) {
        const tFilmstack *stack = &data.elems[i].watchlist;
        tFilmstackNode *node = stack->top;

        // Film stack iteration
        while (node != NULL) {
            const tFilm current = node->elem;
            int found = 0; // Flag -> already counted

            // Check if the film already exists in uniqueFilms
            for (int j = 0; j < uniqueCount; j++) {
                if (film_equals(uniqueFilms[j], current)) {
                    filmCounts[j]++;
                    found = 1;

                    // Check if the current film's release date is newer than the stored one
                    if (date_cmp(current.release, uniqueFilms[j].release) > 0) {
                        // Update to keep the newest release info
                        uniqueFilms[j] = current;
                    }

                    break; // Film handled
                }
            }

            // Not found in uniqueFilms -> add it to uniqueFilms
            if (!found) {
                uniqueFilms[uniqueCount] = current;
                filmCounts[uniqueCount] = 1;
                uniqueCount++;
            }

            node = node->next;
        }
    }

    // After reviewing watchlist, no films
    if (uniqueCount == 0) return NULL;

    // Find most popular film -> If a .If two films have the same count, compare their release dates.The film with the newer release date wins the tie and becomes maxIndex.
    int maxIndex = 0;
    for (int i = 1; i < uniqueCount; i++) {
        if (filmCounts[i] > filmCounts[maxIndex]) {
            // A film has a higher count, it becomes the new maxIndex
            maxIndex = i;
        } else if (filmCounts[i] == filmCounts[maxIndex]) {
            // Same count -> compare release dates -> newer release date wins
            if (date_cmp(uniqueFilms[i].release, uniqueFilms[maxIndex].release) > 0) {
                maxIndex = i;
            }
        }
    }

    return strdup(uniqueFilms[maxIndex].name);
}

// 3b 3d - Return a pointer to the subscriptions of the client with the specified document
tSubscriptions *subscriptions_findByDocument(tSubscriptions data, char *document) {
    if (document == NULL) return NULL;

    // Allocate memory result
    tSubscriptions *result = malloc(sizeof(tSubscriptions));
    if (result == NULL) return NULL;

    result->elems = NULL;
    result->count = 0;

    // No subscriptions -> empty result
    if (data.count == 0) return result;

    result->elems = malloc(sizeof(tSubscription) * data.count);
    if (result->elems == NULL) {
        free(result);
        return NULL;
    }

    // Subscriptions iteration
    for (int i = 0; i < data.count; i++) {
        if (strcmp(data.elems[i].document, document) == 0) {
            tSubscription *src = &data.elems[i];
            tSubscription *dest = &result->elems[result->count];

            // Deep copy
            dest->id = result->count; // <-- Changed this line only
            strcpy(dest->document, src->document);
            dest->start_date = src->start_date;
            dest->end_date = src->end_date;
            strcpy(dest->plan, src->plan);
            dest->price = src->price;
            dest->numDevices = src->numDevices;

            dest->watchlist.top = NULL;
            dest->watchlist.count = 0;

            tFilmstackNode *temp[1000]; // Assuming randomly 1000 films
            int stackSize = 0;

            // Iterate over the original watchlist stack
            tFilmstackNode *node = src->watchlist.top;
            while (node != NULL && stackSize < 1000) {
                temp[stackSize++] = node;
                node = node->next;
            }

            // Copy the stack nodes in reverse order to preserve original order
            for (int j = stackSize - 1; j >= 0; j--) {
                tFilmstackNode *newNode = malloc(sizeof(tFilmstackNode));
                if (newNode == NULL) {
                    break;
                }

                if (temp[j]->elem.name != NULL) {
                    newNode->elem.name = malloc(strlen(temp[j]->elem.name) + 1);
                    if (newNode->elem.name != NULL) {
                        strcpy(newNode->elem.name, temp[j]->elem.name);
                    } else {
                        // malloc failure: set name to NULL
                        newNode->elem.name = NULL;
                    }
                } else {
                    newNode->elem.name = NULL;
                }

                newNode->elem.duration = temp[j]->elem.duration;
                newNode->elem.genre = temp[j]->elem.genre;
                newNode->elem.release = temp[j]->elem.release;
                newNode->elem.rating = temp[j]->elem.rating;
                newNode->elem.isFree = temp[j]->elem.isFree;

                // Insert the new node at the top
                newNode->next = dest->watchlist.top;
                dest->watchlist.top = newNode;

                dest->watchlist.count++;
            }

            result->count++;
        }
    }

    // No matching subscriptions found
    if (result->count == 0) {
        free(result->elems);
        result->elems = NULL;
    }

    return result;
}

// 3c - Return a pointer to the subscription with the specified id
tSubscription *subscriptions_findHash(tSubscriptions data, int id) {
    if (id < 1 || id > data.count) {
        return NULL;
    }

    return &data.elems[id - 1];
}

// Compare two subscription
bool subscription_equal(tSubscription subscription1, tSubscription subscription2) {
    if (strcmp(subscription1.document, subscription2.document) != 0)
        return false;

    if (date_cmp(subscription1.start_date, subscription2.start_date) != 0)
        return false;

    if (date_cmp(subscription1.end_date, subscription2.end_date) != 0)
        return false;

    if (strcmp(subscription1.plan, subscription2.plan) != 0)
        return false;

    if (subscription1.price != subscription2.price)
        return false;

    if (subscription1.numDevices != subscription2.numDevices)
        return false;

    return true;
}
