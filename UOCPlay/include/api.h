#ifndef __UOCPLAY_API__H
#define __UOCPLAY_API__H
#include <stdbool.h>
#include "error.h"
#include "csv.h"
#include "person.h"
#include "subscription.h"
#include "film.h"
#include "show.h"
#include "watchstack.h"

#define FILE_READ_BUFFER_SIZE 2048

// Type that stores all the application data
typedef struct _ApiData {
    /////////////////////////////////
	// Ex1 PR1 3a
	/////////////////////////////////
    // People
    tPeople people;	
	// Subscriptions
    tSubscriptions subscriptions;
    // Catalog of films
    tFilmCatalog films;
   /////////////////////////////////
	// Ex1 PR2 3a
	/////////////////////////////////
    // Catalog of shows
    tShowCatalog shows;  
    /////////////////////////////////
} tApiData;

// Get the API version information
const char* api_version();

// Load data from a CSV file. If reset is true, remove previous data
tApiError api_loadData(tApiData* data, const char* filename, bool reset);

// Initialize the data structure
tApiError api_initData(tApiData* data);

// Add a person into the data if it does not exist
tApiError api_addPerson(tApiData* data, tCSVEntry entry);

// Add a subscription if it does not exist
tApiError api_addSubscription(tApiData* data, tCSVEntry entry);

// Add a film if it does not exist
tApiError api_addFilm(tApiData* data, tCSVEntry entry);

// Add a film to a subscription's watchlist from a CSV entry, avoiding duplicates
tApiError api_addToWatchlist(tApiData* data, int subscriptionId, tCSVEntry entry);
    
// Get the number of people registered on the application
int api_peopleCount(tApiData data);

// Get the number of subscriptions registered on the application
int api_subscriptionsCount(tApiData data);

// Get the number of films registered on the application
int api_filmsCount(tApiData data);

// Get the number of free films registered on the application
int api_freeFilmsCount(tApiData data);

// Get the number of shows registered on the application
int api_showsCount(tApiData data);

// Find a show by its name
tShow* api_findShow(tApiData data, const char* name);


// Free all used memory
tApiError api_freeData(tApiData* data);

// Add a new entry
tApiError api_addDataEntry(tApiData* data, tCSVEntry entry);

// Get subscription data
tApiError api_getSubscription(tApiData data, int id, tCSVEntry *entry);

// Get film data
tApiError api_getFilm(tApiData data, const char* name, tCSVEntry *entry);

// Get free films data
tApiError api_getFreeFilms(tApiData data, tCSVData *freeFilms);

// Get films data by genre
tApiError api_getFilmsByGenre(tApiData data, tCSVData *films, int genre);

// Get longest film
tApiError api_getLongestFilm(tApiData data, tCSVEntry *entry);

// Get longest free film
tApiError api_getLongestFreeFilm(tApiData data, tCSVEntry *entry);

// Get popular film
tApiError api_getPopularFilm(tApiData data, tCSVEntry *entry);

// Sort catalog by year, oldest to newest
tApiError api_sortCatalogByYear(tApiData *data);

// Sort catalog by rating, higehst to lowest
tApiError api_sortCatalogByRating(tApiData *data);

// Get longest film
tApiError api_getOldestFilm(tApiData data, tCSVEntry *entry, bool free);

// updateVipLevel of each person
tApiError api_updateVipLevel(tApiData *data);

// Sort people by VIP level, higehst to lowest
tApiError api_sortPeopleByVipLevel(tApiData *data);

// Sort people by document, lowest to highest
tApiError api_sortPeopleByDocument(tApiData *data);

// Get subscription data for the specified document
tApiError api_getSubscriptionsByDocument(tApiData data, char *name, tCSVData *csvData);

#endif // __UOCPLAY_API__H
