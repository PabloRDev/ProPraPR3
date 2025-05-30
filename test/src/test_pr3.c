#include "test_pr3.h"
#include "api.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// Run all tests for PR3

bool run_pr3(tTestSuite *test_suite, const char *input) {
    bool ok = true;
    tTestSection *section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR3", "Tests for PR3 exercices");

    section = testSuite_getSection(test_suite, "PR3");
    assert(section != NULL);

    ok = run_pr3_ex1(section, input);
    ok = run_pr3_ex2(section, input) && ok;
    ok = run_pr3_ex3(section, input) && ok;
    ok = run_pr3_ex4(section, input) && ok;

    return ok;
}

bool run_pr3_ex1(tTestSection *test_section, const char *input) {
    tApiError error;
    tTime duration;
    tDate release;
    tFilm film1, film2, film3, film4, film5;
    tFilm *filmp1;
    tFilmCatalog catalog, emptyCatalog;

    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    // film1
    duration.hour = 2;
    duration.minutes = 49;
    release.day = 7;
    release.month = 11;
    release.year = 2014;
    film_init(&film1, "Interstellar", duration, 4, release, 4.8f, false);

    // film2
    duration.hour = 2;
    duration.minutes = 0;
    release.day = 15;
    release.month = 5;
    release.year = 2015;
    film_init(&film2, "Mad Max: Fury Road", duration, 0, release, 4.5f, false);

    // film3
    duration.hour = 3;
    duration.minutes = 9;
    release.day = 10;
    release.month = 12;
    release.year = 1999;
    film_init(&film3, "The Green Mile", duration, 2, release, 4.8f, true);

    // film4
    duration.hour = 1;
    duration.minutes = 57;
    release.day = 15;
    release.month = 12;
    release.year = 2006;
    film_init(&film4, "The Pursuit of Happyness", duration, 2, release, 4.4f, true);

    // film5
    duration.hour = 3;
    duration.minutes = 9;
    release.day = 10;
    release.month = 12;
    release.year = 1999;
    film_init(&film5, "The Green Arrow", duration, 2, release, 4.8f, false);


    // Initialize the catalog
    error = film_catalog_init(&emptyCatalog);
    error = film_catalog_init(&catalog);
    if (error != E_SUCCESS) {
        failed = true;
        passed = false;
        fail_all = true;
    }

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 1 - Empty catalog
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_1", "Find longest film [Empty list]");
    if (!fail_all) {
        filmp1 = filmList_longestFind(emptyCatalog.filmList);

        if (filmp1 != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_1", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 2 - Find longest film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_2", "Find longest film");
    if (!fail_all) {
        film_catalog_add(&catalog, film1);
        film_catalog_add(&catalog, film2);
        film_catalog_add(&catalog, film3);
        film_catalog_add(&catalog, film4);

        filmp1 = filmList_longestFind(catalog.filmList);

        if (filmp1 == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmp1->name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_2", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 3 - Find longest film2
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_3", "Find longest film 2");
    if (!fail_all) {
        film_catalog_add(&catalog, film5);

        filmp1 = filmList_longestFind(catalog.filmList);

        if (filmp1 == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmp1->name, film5.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_3", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 4 - Find longest film3
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_4", "Find longest free film [empty List]");
    if (!fail_all) {
        filmp1 = freeFilmList_longestFind(emptyCatalog.freeFilmList);

        if (filmp1 != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_4", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 5 - Find longest free film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_5", "Find longest free film");
    if (!fail_all) {
        filmp1 = freeFilmList_longestFind(catalog.freeFilmList);

        if (filmp1 == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmp1->name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_5", !failed);


    /////////////////////////////////////////////////
    // PR3 EX1 TEST 6 - Sort films by date
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_6", "Sort films by date [empty list]");
    if (!fail_all) {
        error = filmList_SortByYear_Bubble(&emptyCatalog.filmList);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (emptyCatalog.filmList.first != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_6", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 7 - Sort films by date
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_7", "Sort films by date");
    if (!fail_all) {
        error = filmList_SortByYear_Bubble(&catalog.filmList);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->elem.name, film5.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->elem.name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->elem.name, film4.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->next->elem.name, film1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->next->next->elem.name, film2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_7", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 8 - Sort free films by date
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_8", "Sort free films by date [empty list]");
    if (!fail_all) {
        error = freeFilmList_SortByYear_Bubble(&emptyCatalog.freeFilmList);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (emptyCatalog.freeFilmList.first != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_8", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 9 - Sort free films by date
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_9", "Sort free films by date");
    if (!fail_all) {
        error = freeFilmList_SortByYear_Bubble(&catalog.freeFilmList);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.freeFilmList.first->elem->name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.freeFilmList.first->next->elem->name, film4.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_9", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 10 - Sort Catalog film list by date
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_10", "Sort catalog by date [empty catalog]");
    if (!fail_all) {
        error = filmCatalog_SortByYear(&emptyCatalog);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!emptyCatalog.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_10", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 11 - Sort Catalog film list by date
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_11", "Sort catalog by date ");
    if (!fail_all) {
        film_catalog_free(&catalog);
        film_catalog_add(&catalog, film1);
        film_catalog_add(&catalog, film2);
        film_catalog_add(&catalog, film3);
        film_catalog_add(&catalog, film4);
        film_catalog_add(&catalog, film5);

        error = filmCatalog_SortByYear(&catalog);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!emptyCatalog.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->elem.name, film5.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->elem.name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->elem.name, film4.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->next->elem.name, film1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->next->next->elem.name, film2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.freeFilmList.first->elem->name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.freeFilmList.first->next->elem->name, film4.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_11", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 12 - Check sortedByDate
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_12", "Check sortedByDate [before sorting]");
    if (!fail_all) {
        film_catalog_free(&catalog);
        film_catalog_add(&catalog, film1);
        film_catalog_add(&catalog, film2);

        if (catalog.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_12", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 13 - Check sortedByDate
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_13", "Check sortedByDate [after sorting]");
    if (!fail_all) {
        error = filmCatalog_SortByYear(&catalog);

        if (!catalog.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_13", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 14 - Check sortedByDate
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_14", "Check sortedByDate [after adding films]");
    if (!fail_all) {
        film_catalog_add(&catalog, film3);
        film_catalog_add(&catalog, film4);
        film_catalog_add(&catalog, film5);

        if (catalog.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_14", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 15 - Sort Catalog film list by date
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_15", "Sort catalog by date x2");
    if (!fail_all) {
        error = filmCatalog_SortByYear(&catalog);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!emptyCatalog.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->elem.name, film5.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->elem.name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->elem.name, film4.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->next->elem.name, film1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->next->next->elem.name, film2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.freeFilmList.first->elem->name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.freeFilmList.first->next->elem->name, film4.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_15", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 16 - Find oldest film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_16", "Find oldest film [empty catalog]");
    if (!fail_all) {
        filmp1 = filmCatalog_OldestFind(emptyCatalog, false);

        if (filmp1 != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_16", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 17 - Find oldest free film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_17", "Find oldest free film [empty catalog]");
    if (!fail_all) {
        filmp1 = filmCatalog_OldestFind(emptyCatalog, true);

        if (filmp1 != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_17", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 18 - Find oldest film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_18", "Find oldest film [sorted Catalog]");
    if (!fail_all) {
        filmp1 = filmCatalog_OldestFind(catalog, false);

        if (filmp1 == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmp1->name, film5.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_18", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 19 - Find oldest film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_19", "Find oldest free film [sorted Catalog]");
    if (!fail_all) {
        filmp1 = filmCatalog_OldestFind(catalog, true);

        if (filmp1 == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmp1->name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_19", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 20 - Find oldest film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_20", "Find oldest film");
    if (!fail_all) {
        film_catalog_free(&catalog);
        film_catalog_add(&catalog, film1);
        film_catalog_add(&catalog, film2);
        film_catalog_add(&catalog, film3);
        film_catalog_add(&catalog, film4);
        film_catalog_add(&catalog, film5);

        filmp1 = filmCatalog_OldestFind(catalog, false);

        if (filmp1 == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmp1->name, film5.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (catalog.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_20", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 21 - Find oldest film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_21", "Find oldest free film");
    if (!fail_all) {
        filmp1 = filmCatalog_OldestFind(catalog, true);

        if (filmp1 == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmp1->name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (catalog.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_21", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 22 - Sort by rating
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_22", "Sort catalog by rating [empty catalog]");
    if (!fail_all) {
        error = filmCatalog_SortByRating(&emptyCatalog);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_22", !failed);

    /////////////////////////////////////////////////
    // PR3 EX1 TEST 23 - Sort by rating
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX1_23", "Sort catalog by rating");
    if (!fail_all) {
        error = filmCatalog_SortByRating(&catalog);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (catalog.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->elem.name, film1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->elem.name, film5.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->elem.name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->next->elem.name, film2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.filmList.first->next->next->next->next->elem.name, film4.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.freeFilmList.first->elem->name, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(catalog.freeFilmList.first->next->elem->name, film2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX1_23", !failed);

    film_catalog_free(&catalog);
    film_free(&film1);
    film_free(&film2);
    film_free(&film3);
    film_free(&film4);
    film_free(&film5);


    return passed;
}


bool run_pr3_ex2(tTestSection *test_section, const char *input) {
    tApiError error;
    tSubscriptions emptySubscriptions, subscriptions;
    tPerson person1, person2, person3, person1Duplicated;
    tPeople emptyPeople, people;
    tSubscription subscription1, subscription2, subscription3, subscription4, subscription5;
    bool initPerson1 = false;
    bool initPerson2 = false;
    bool initPerson3 = false;
    bool initPerson1Duplicated = false;
    tCSVEntry entryPerson1, entryPerson2, entryPerson3, entryPerson1Duplicated, entrySubscription1, entrySubscription2,
            entrySubscription3, entrySubscription4, entrySubscription5;

    int vipLevel, auxPos;


    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    csv_initEntry(&entryPerson1);
    csv_parseEntry(&entryPerson1,
                   "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954",
                   "PERSON");
    csv_initEntry(&entryPerson1Duplicated);
    csv_parseEntry(&entryPerson1Duplicated,
                   "11111111A;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954",
                   "PERSON");
    csv_initEntry(&entryPerson2);
    csv_parseEntry(&entryPerson2,
                   "33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867",
                   "PERSON");
    csv_initEntry(&entryPerson3);
    csv_parseEntry(&entryPerson3,
                   "47051307Z;James;Bond;707070707;bond.jamesbond@example.com;Downing street, 10;07077;12/01/1952",
                   "PERSON");

    subscriptions_init(&emptySubscriptions);
    subscriptions_init(&subscriptions);
    people_init(&emptyPeople);
    people_init(&people);

    csv_initEntry(&entrySubscription1);
    csv_initEntry(&entrySubscription2);
    csv_initEntry(&entrySubscription3);
    csv_initEntry(&entrySubscription4);
    csv_initEntry(&entrySubscription5);

    csv_parseEntry(&entrySubscription1, "1;98765432J;01/01/2025;31/12/2025;Free;0;1", "SUBSCRIPTION");
    csv_parseEntry(&entrySubscription2, "2;33365111X;01/05/2025;30/04/2026;Standard;29.95;3", "SUBSCRIPTION");
    csv_parseEntry(&entrySubscription3, "3;98765432J;01/01/2026;30/06/2026;Standard;29.95;3", "SUBSCRIPTION");
    csv_parseEntry(&entrySubscription4, "4;98765432J;01/07/2026;31/06/2027;Standard;29.95;3", "SUBSCRIPTION");
    csv_parseEntry(&entrySubscription5, "5;47051307Z;01/01/2023;31/12/2028;Premium;39.95;3", "SUBSCRIPTION");

    subscription_parse(&subscription1, entrySubscription1);
    subscription_parse(&subscription2, entrySubscription2);
    subscription_parse(&subscription3, entrySubscription3);
    subscription_parse(&subscription4, entrySubscription4);
    subscription_parse(&subscription5, entrySubscription5);


    /////////////////////////////////////////////////
    // PR3 EX2 TEST 1 - Initiazlize Vip Level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_1", "Initiazlize Vip Level");
    if (!fail_all) {
        person_parse(&person1, entryPerson1);
        initPerson1 = true;

        if (person1.vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_1", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 2 - Copy Vip level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_2", "Copy Vip Level");
    if (!fail_all) {
        person_cpy(&person2, person1);
        initPerson2 = true;
        person1.vipLevel = 1;
        person_cpy(&person3, person1);
        initPerson3 = true;

        if (person2.vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (person3.vipLevel != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_2", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 3 - Calculate VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_3", "Calculate VIP level [empty subscriptions]");
    if (!fail_all) {
        vipLevel = calculate_vipLevel(&emptySubscriptions, person1.document);

        if (vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_3", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 4 - Calculate VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_4", "Calculate VIP level [non existing document]");
    if (!fail_all) {
        person_free(&person2);
        person_free(&person3);
        person_parse(&person2, entryPerson2);
        person_parse(&person3, entryPerson3);
        people_add(&people, person1);
        people_add(&people, person2);
        people_add(&people, person3);

        subscriptions_add(&subscriptions, people, subscription1);
        subscriptions_add(&subscriptions, people, subscription2);
        subscriptions_add(&subscriptions, people, subscription3);
        subscriptions_add(&subscriptions, people, subscription4);
        subscriptions_add(&subscriptions, people, subscription5);

        vipLevel = calculate_vipLevel(&subscriptions, "asdf");

        if (vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_4", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 5 - Calculate VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_5", "Calculate VIP level [person 1]");
    if (!fail_all) {
        vipLevel = calculate_vipLevel(&subscriptions, person1.document);

        if (vipLevel != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_5", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 6 - Calculate VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_6", "Calculate VIP level [person 2]");
    if (!fail_all) {
        vipLevel = calculate_vipLevel(&subscriptions, person2.document);

        if (vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_6", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 7 - Calculate VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_7", "Calculate VIP level [person 3]");
    if (!fail_all) {
        vipLevel = calculate_vipLevel(&subscriptions, person3.document);

        if (vipLevel == 5) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_7", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 8 - Update VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_8", "Update VIP level [empty subscriptions]");
    if (!fail_all) {
        error = update_vipLevel(&emptySubscriptions, &emptyPeople);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_8", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 9 - Update VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_9", "Update VIP level [empty subscriptions x2]");
    if (!fail_all) {
        error = update_vipLevel(&emptySubscriptions, &people);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[0].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[1].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[2].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_9", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 10 - Update VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_10", "Update VIP level");
    if (!fail_all) {
        error = update_vipLevel(&subscriptions, &people);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[0].vipLevel != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[1].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[2].vipLevel != 5) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_10", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 11 - Sort People by VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_11", "Sort People by VIP level [empty people]");
    if (!fail_all) {
        error = people_sortByVipLevel_QickSort(&emptyPeople);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_11", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 12 - Sort People by VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_12", "Sort People by VIP level");
    if (!fail_all) {
        error = people_sortByVipLevel_QickSort(&people);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[0].vipLevel != 5 || strcmp(people.elems[0].name, person3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[1].vipLevel != 1 || strcmp(people.elems[1].name, person1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[2].vipLevel != 0 || strcmp(people.elems[2].name, person2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_12", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 13 - Sort People by VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_13", "Sort People by VIP level [same VIP levels]");
    if (!fail_all) {
        update_vipLevel(&emptySubscriptions, &people);
        error = people_sortByVipLevel_QickSort(&people);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[0].vipLevel != 0 || strcmp(people.elems[0].name, person2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[1].vipLevel != 0 || strcmp(people.elems[1].name, person3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (people.elems[2].vipLevel != 0 || strcmp(people.elems[2].name, person1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_13", !failed);

    ////////////////////////////////////////////////
    // PR3 EX2 TEST 14 - Sort People by Document
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_14", "Sort People by Document [empty people]");
    if (!fail_all) {
        error = people_sortByDocument_QickSort(&emptyPeople);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_14", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 15 - Sort People by Document
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_15", "Sort People by Document");
    if (!fail_all) {
        error = people_sortByDocument_QickSort(&people);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(people.elems[0].name, person2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(people.elems[1].name, person3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(people.elems[2].name, person1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_15", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 16 - Sort People by Document
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_16", "Sort People by Document x2");
    if (!fail_all) {
        update_vipLevel(&subscriptions, &people);
        people_sortByVipLevel_QickSort(&people);

        error = people_sortByDocument_QickSort(&people);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(people.elems[0].name, person2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(people.elems[1].name, person3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(people.elems[2].name, person1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_16", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 17- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_17", "Find People by Email [empty people]");
    if (!fail_all) {
        auxPos = people_findByEmail(emptyPeople, person1.email);

        if (auxPos != -1) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_17", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 18- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_18", "Find People by Email [example@example.com]");
    if (!fail_all) {
        auxPos = people_findByEmail(people, "example@example.com");

        if (auxPos != -1) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_18", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 19- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_19", "Find People by Email [hendrik.lorentz@example.com]");
    if (!fail_all) {
        auxPos = people_findByEmail(people, person1.email);

        if (auxPos != 2) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_19", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 20- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_20", "Find People by Email [marie.curie@example.com]");
    if (!fail_all) {
        auxPos = people_findByEmail(people, person2.email);

        if (auxPos != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_20", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 21- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_21", "Find People by Email [bond.jamesbond@example.com]");
    if (!fail_all) {
        auxPos = people_findByEmail(people, person3.email);

        if (auxPos != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_21", !failed);


    /////////////////////////////////////////////////
    // PR3 EX2 TEST 22- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_22", "Find People by Email [hendrik.lorentz@example.com] x2");
    if (!fail_all) {
        update_vipLevel(&emptySubscriptions, &people);
        people_sortByVipLevel_QickSort(&people);

        auxPos = people_findByEmail(people, person1.email);

        if (auxPos != 2) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_22", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 23- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_23", "Find People by Email [marie.curie@example.com] x2");
    if (!fail_all) {
        auxPos = people_findByEmail(people, person2.email);

        if (auxPos != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_23", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 24- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_24", "Find People by Email [bond.jamesbond@example.com] x2");
    if (!fail_all) {
        auxPos = people_findByEmail(people, person3.email);

        if (auxPos != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_24", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 25- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_25", "Find People by Email [duplicated]");
    if (!fail_all) {
        person_parse(&person1Duplicated, entryPerson1Duplicated);
        initPerson1Duplicated = true;
        people_add(&people, person1Duplicated);
        auxPos = people_findByEmail(people, person1.email);

        if (auxPos != -1) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_25", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 26- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_26", "Find People by Email [marie.curie@example.com] x3");
    if (!fail_all) {
        auxPos = people_findByEmail(people, person2.email);

        if (auxPos != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_26", !failed);

    /////////////////////////////////////////////////
    // PR3 EX2 TEST 27- Find People by Email
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX2_27", "Find People by Email [bond.jamesbond@example.com] x3");
    if (!fail_all) {
        auxPos = people_findByEmail(people, person3.email);

        if (auxPos != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX2_27", !failed);


    csv_freeEntry(&entryPerson1);
    csv_freeEntry(&entryPerson2);
    csv_freeEntry(&entryPerson3);
    csv_freeEntry(&entryPerson1Duplicated);
    csv_freeEntry(&entrySubscription1);
    csv_freeEntry(&entrySubscription2);
    csv_freeEntry(&entrySubscription3);
    csv_freeEntry(&entrySubscription4);
    csv_freeEntry(&entrySubscription5);
    if (initPerson1)
        person_free(&person1);
    if (initPerson2)
        person_free(&person2);
    if (initPerson3)
        person_free(&person3);
    if (initPerson1Duplicated)
        person_free(&person1Duplicated);

    subscriptions_free(&emptySubscriptions);
    subscriptions_free(&subscriptions);
    people_free(&emptyPeople);
    people_free(&people);
    return passed;
}

bool run_pr3_ex3(tTestSection *test_section, const char *input) {
    tApiError error;
    tTime duration;
    tDate release;
    tFilm film1, film2, film3, film4, film5;
    tPerson person1, person2, person3;
    char *filmName = NULL;
    tFilmCatalog catalog, emptyCatalog;
    tSubscriptions emptySubscriptions, subscriptions, *pSubscriptions;
    tSubscription subscription1, subscription2, subscription3, subscription4, subscription5, *pSubscription;
    tCSVEntry entryPerson1, entryPerson2, entryPerson3, entrySubscription1, entrySubscription2, entrySubscription3,
            entrySubscription4, entrySubscription5;
    tPeople emptyPeople, people;

    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    // film1
    duration.hour = 2;
    duration.minutes = 49;
    release.day = 7;
    release.month = 11;
    release.year = 2014;
    film_init(&film1, "Interstellar", duration, 4, release, 4.8f, false);

    // film2
    duration.hour = 2;
    duration.minutes = 0;
    release.day = 15;
    release.month = 5;
    release.year = 2015;
    film_init(&film2, "Mad Max: Fury Road", duration, 0, release, 4.5f, false);

    // film3
    duration.hour = 3;
    duration.minutes = 9;
    release.day = 10;
    release.month = 12;
    release.year = 1999;
    film_init(&film3, "The Green Mile", duration, 2, release, 4.8f, true);

    // film4
    duration.hour = 1;
    duration.minutes = 57;
    release.day = 15;
    release.month = 12;
    release.year = 2006;
    film_init(&film4, "The Pursuit of Happyness", duration, 2, release, 4.4f, true);

    // film5
    duration.hour = 3;
    duration.minutes = 9;
    release.day = 10;
    release.month = 12;
    release.year = 1999;
    film_init(&film5, "The Green Arrow", duration, 2, release, 4.8f, false);


    // Initialize the catalog
    error = film_catalog_init(&emptyCatalog);
    error = film_catalog_init(&catalog);
    if (error != E_SUCCESS) {
        failed = true;
        passed = false;
        fail_all = true;
    }

    film_catalog_add(&catalog, film1);
    film_catalog_add(&catalog, film2);
    film_catalog_add(&catalog, film3);
    film_catalog_add(&catalog, film4);
    film_catalog_add(&catalog, film5);

    csv_initEntry(&entryPerson1);
    csv_parseEntry(&entryPerson1,
                   "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954",
                   "PERSON");
    csv_initEntry(&entryPerson2);
    csv_parseEntry(&entryPerson2,
                   "33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867",
                   "PERSON");
    csv_initEntry(&entryPerson3);
    csv_parseEntry(&entryPerson3,
                   "47051307Z;James;Bond;707070707;bond.jamesbond@example.com;Downing street, 10;07077;12/01/1952",
                   "PERSON");
    person_parse(&person1, entryPerson1);
    person_parse(&person2, entryPerson2);
    person_parse(&person3, entryPerson3);
    people_init(&emptyPeople);
    people_init(&people);
    people_add(&people, person1);
    people_add(&people, person2);
    people_add(&people, person3);


    csv_initEntry(&entrySubscription1);
    csv_initEntry(&entrySubscription2);
    csv_initEntry(&entrySubscription3);
    csv_initEntry(&entrySubscription4);
    csv_initEntry(&entrySubscription5);

    csv_parseEntry(&entrySubscription1, "1;98765432J;01/01/2025;31/12/2025;Free;0;1", "SUBSCRIPTION");
    csv_parseEntry(&entrySubscription2, "2;33365111X;01/05/2025;30/04/2026;Standard;29.95;3", "SUBSCRIPTION");
    csv_parseEntry(&entrySubscription3, "3;98765432J;01/01/2026;30/06/2026;Standard;29.95;3", "SUBSCRIPTION");
    csv_parseEntry(&entrySubscription4, "4;98765432J;01/07/2026;31/06/2027;Standard;29.95;3", "SUBSCRIPTION");
    csv_parseEntry(&entrySubscription5, "5;47051307Z;01/01/2023;31/12/2028;Premium;39.95;3", "SUBSCRIPTION");

    subscription_parse(&subscription1, entrySubscription1);
    subscription_parse(&subscription2, entrySubscription2);
    subscription_parse(&subscription3, entrySubscription3);
    subscription_parse(&subscription4, entrySubscription4);
    subscription_parse(&subscription5, entrySubscription5);

    subscriptions_init(&emptySubscriptions);
    subscriptions_init(&subscriptions);

    subscriptions_add(&subscriptions, people, subscription1);
    subscriptions_add(&subscriptions, people, subscription2);
    subscriptions_add(&subscriptions, people, subscription3);
    subscriptions_add(&subscriptions, people, subscription4);
    subscriptions_add(&subscriptions, people, subscription5);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 1 - Find popular film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_1", "Find popular film [Empty list]");
    if (!fail_all) {
        filmName = popularFilm_find(emptySubscriptions);

        if (filmName != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_1", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 2 - Find popular film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_2", "Find popular film [Empty watchlists]");
    if (!fail_all) {
        filmName = popularFilm_find(subscriptions);

        if (filmName != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_2", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 3 - Find popular film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_3", "Find popular film");
    if (!fail_all) {
        filmstack_push(&subscriptions.elems[0].watchlist, film1);
        filmstack_push(&subscriptions.elems[0].watchlist, film2);
        filmstack_push(&subscriptions.elems[0].watchlist, film3);

        filmName = popularFilm_find(subscriptions);

        if (filmName == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmName, film2.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        free(filmName);
    }
    end_test(test_section, "PR3_EX3_3", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 4 - Find popular film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_4", "Find popular film x2");
    if (!fail_all) {
        filmstack_push(&subscriptions.elems[2].watchlist, film3);
        filmstack_push(&subscriptions.elems[2].watchlist, film4);

        filmName = popularFilm_find(subscriptions);

        if (filmName == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmName, film3.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        free(filmName);
    }
    end_test(test_section, "PR3_EX3_4", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 5 - Find popular film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_5", "Find popular film x3");
    if (!fail_all) {
        filmstack_push(&subscriptions.elems[3].watchlist, film5);
        filmstack_push(&subscriptions.elems[3].watchlist, film1);

        filmName = popularFilm_find(subscriptions);

        if (filmName == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmName, film1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        free(filmName);
    }
    end_test(test_section, "PR3_EX3_5", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 6 - Find popular film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_6", "Find popular film x4");
    if (!fail_all) {
        filmstack_push(&subscriptions.elems[4].watchlist, film5);
        filmstack_push(&subscriptions.elems[4].watchlist, film4);
        filmstack_push(&subscriptions.elems[2].watchlist, film1);

        filmName = popularFilm_find(subscriptions);

        if (filmName == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(filmName, film1.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        free(filmName);
    }
    end_test(test_section, "PR3_EX3_6", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 7 - Find Subscriptions
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_7", "Find subscriptions [empty subscripion]");
    if (!fail_all) {
        pSubscriptions = subscriptions_findByDocument(emptySubscriptions, person1.document);

        if (pSubscriptions == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscriptions->count != 0 || pSubscriptions->elems != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        if (pSubscriptions != NULL) {
            subscriptions_free(pSubscriptions);
            free(pSubscriptions);
        }
    }
    end_test(test_section, "PR3_EX3_7", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 8 - Find Subscriptions
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_8", "Find subscriptions [98765432J]");
    if (!fail_all) {
        pSubscriptions = subscriptions_findByDocument(subscriptions, person1.document);

        if (pSubscriptions->count != 3 || pSubscriptions->elems == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[0].document, person1.document) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (date_cmp(subscription1.start_date, pSubscriptions->elems[0].start_date) != 0 || date_cmp(
                       subscription1.end_date, pSubscriptions->elems[0].end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscriptions->elems[0].watchlist.count != subscriptions.elems[0].watchlist.count) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[0].watchlist.top->elem.name,
                          subscriptions.elems[0].watchlist.top->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[0].watchlist.top->next->elem.name,
                          subscriptions.elems[0].watchlist.top->next->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[0].watchlist.top->next->next->elem.name,
                          subscriptions.elems[0].watchlist.top->next->next->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[1].document, person1.document) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (date_cmp(subscription3.start_date, pSubscriptions->elems[1].start_date) != 0 || date_cmp(
                       subscription3.end_date, pSubscriptions->elems[1].end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscriptions->elems[1].watchlist.count != subscriptions.elems[2].watchlist.count) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[1].watchlist.top->elem.name,
                          subscriptions.elems[2].watchlist.top->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[1].watchlist.top->next->elem.name,
                          subscriptions.elems[2].watchlist.top->next->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[1].watchlist.top->next->next->elem.name,
                          subscriptions.elems[2].watchlist.top->next->next->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[2].document, person1.document) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (date_cmp(subscription4.start_date, pSubscriptions->elems[2].start_date) != 0 || date_cmp(
                       subscription4.end_date, pSubscriptions->elems[2].end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscriptions->elems[2].watchlist.count != subscriptions.elems[3].watchlist.count) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[2].watchlist.top->elem.name,
                          subscriptions.elems[3].watchlist.top->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[2].watchlist.top->next->elem.name,
                          subscriptions.elems[3].watchlist.top->next->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        if (pSubscriptions != NULL) {
            subscriptions_free(pSubscriptions);
            free(pSubscriptions);
        }
    }
    end_test(test_section, "PR3_EX3_8", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 9 - Find Subscriptions
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_9", "Find subscriptions [33365111X]");
    if (!fail_all) {
        pSubscriptions = subscriptions_findByDocument(subscriptions, person2.document);

        if (pSubscriptions->count != 1 || pSubscriptions->elems == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[0].document, person2.document) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (date_cmp(subscription2.start_date, pSubscriptions->elems[0].start_date) != 0 || date_cmp(
                       subscription2.end_date, pSubscriptions->elems[0].end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscriptions->elems[0].watchlist.count != subscriptions.elems[1].watchlist.count) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        if (pSubscriptions != NULL) {
            subscriptions_free(pSubscriptions);
            free(pSubscriptions);
        }
    }
    end_test(test_section, "PR3_EX3_9", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 10 - Find Subscriptions
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_10", "Find subscriptions [47051307Z]");
    if (!fail_all) {
        pSubscriptions = subscriptions_findByDocument(subscriptions, person3.document);

        if (pSubscriptions->count != 1 || pSubscriptions->elems == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[0].document, person3.document) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (date_cmp(subscription5.start_date, pSubscriptions->elems[0].start_date) != 0 || date_cmp(
                       subscription5.end_date, pSubscriptions->elems[0].end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscriptions->elems[0].watchlist.count != subscriptions.elems[4].watchlist.count) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[0].watchlist.top->elem.name,
                          subscriptions.elems[4].watchlist.top->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(pSubscriptions->elems[0].watchlist.top->next->elem.name,
                          subscriptions.elems[4].watchlist.top->next->elem.name) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        if (pSubscriptions != NULL) {
            subscriptions_free(pSubscriptions);
            free(pSubscriptions);
        }
    }
    end_test(test_section, "PR3_EX3_10", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 11 - Find Subscriptions
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_11", "Find subscriptions [11111111A]");
    if (!fail_all) {
        pSubscriptions = subscriptions_findByDocument(subscriptions, "11111111A");

        if (pSubscriptions->count != 0 || pSubscriptions->elems != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        if (pSubscriptions != NULL) {
            subscriptions_free(pSubscriptions);
            free(pSubscriptions);
        }
    }
    end_test(test_section, "PR3_EX3_11", !failed);
    /////////////////////////////////////////////////
    // PR3 EX3 TEST 12 - Find Subscription Hash
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_12", "Find subscription Hash [empty subscription]");
    if (!fail_all) {
        pSubscription = subscriptions_findHash(emptySubscriptions, 1);

        if (pSubscription != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_12", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 13 - Find Subscription Hash
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_13", "Find subscription Hash");
    if (!fail_all) {
        pSubscription = subscriptions_findHash(subscriptions, 1);

        if (pSubscription == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscription != &subscriptions.elems[0]) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_13", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 14 - Find Subscription Hash
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_14", "Find subscription Hash x2");
    if (!fail_all) {
        pSubscription = subscriptions_findHash(subscriptions, 3);

        if (pSubscription == NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscription != &subscriptions.elems[2]) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_14", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 15 - Find Subscription Hash
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_15", "Find subscription Hash [non existing id]");
    if (!fail_all) {
        pSubscription = subscriptions_findHash(subscriptions, 300);

        if (pSubscription != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_15", !failed);


    /////////////////////////////////////////////////
    // PR3 EX3 TEST 16 - Find Subscriptions
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_16", "Find subscriptions [98765432J]x2");
    if (!fail_all) {
        pSubscriptions = subscriptions_findByDocument(subscriptions, person1.document);

        if (pSubscriptions->elems[0].id != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscriptions->elems[1].id != 2) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pSubscriptions->elems[2].id != 3) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        subscriptions_free(pSubscriptions);
        free(pSubscriptions);
    }
    end_test(test_section, "PR3_EX3_16", !failed);


    /////////////////////////////////////////////////
    // PR3 EX3 TEST 17 - Find Subscriptions
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_17", "Find subscriptions [33365111X]x2");
    if (!fail_all) {
        pSubscriptions = subscriptions_findByDocument(subscriptions, person2.document);

        if (pSubscriptions->elems[0].id != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        subscriptions_free(pSubscriptions);
        free(pSubscriptions);
    }
    end_test(test_section, "PR3_EX3_17", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 18 - Find Subscriptions
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_18", "Find subscriptions [47051307Z]x2");
    if (!fail_all) {
        pSubscriptions = subscriptions_findByDocument(subscriptions, person3.document);

        if (pSubscriptions->elems[0].id != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        subscriptions_free(pSubscriptions);
        free(pSubscriptions);
    }
    end_test(test_section, "PR3_EX3_18", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 19 - Delete subscription
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_19", "Delete Subscription [non-existing id]");
    if (!fail_all) {
        error = subscriptions_del(&subscriptions, 300);

        if (error != E_SUBSCRIPTION_NOT_FOUND) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_19", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 20 - Delete subscription
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_20", "Delete Subscription [1]");
    if (!fail_all) {
        error = subscriptions_del(&subscriptions, 1);

        if (error == E_SUBSCRIPTION_NOT_FOUND) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[0].id != 1 || strcmp(subscriptions.elems[0].document, person2.document) != 0 ||
                   date_cmp(subscriptions.elems[0].start_date, subscription2.start_date) != 0 || date_cmp(
                       subscriptions.elems[0].end_date, subscription2.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[1].id != 2 || strcmp(subscriptions.elems[1].document, person1.document) != 0 ||
                   date_cmp(subscriptions.elems[1].start_date, subscription3.start_date) != 0 || date_cmp(
                       subscriptions.elems[1].end_date, subscription3.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[2].id != 3 || strcmp(subscriptions.elems[2].document, person1.document) != 0 ||
                   date_cmp(subscriptions.elems[2].start_date, subscription4.start_date) != 0 || date_cmp(
                       subscriptions.elems[2].end_date, subscription4.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[3].id != 4 || strcmp(subscriptions.elems[3].document, person3.document) != 0 ||
                   date_cmp(subscriptions.elems[3].start_date, subscription5.start_date) != 0 || date_cmp(
                       subscriptions.elems[3].end_date, subscription5.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_20", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 21 - Delete subscription
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_21", "Delete Subscription [3]");
    if (!fail_all) {
        error = subscriptions_del(&subscriptions, 3);

        if (error == E_SUBSCRIPTION_NOT_FOUND) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[0].id != 1 || strcmp(subscriptions.elems[0].document, person2.document) != 0 ||
                   date_cmp(subscriptions.elems[0].start_date, subscription2.start_date) != 0 || date_cmp(
                       subscriptions.elems[0].end_date, subscription2.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[1].id != 2 || strcmp(subscriptions.elems[1].document, person1.document) != 0 ||
                   date_cmp(subscriptions.elems[1].start_date, subscription3.start_date) != 0 || date_cmp(
                       subscriptions.elems[1].end_date, subscription3.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[2].id != 3 || strcmp(subscriptions.elems[2].document, person3.document) != 0 ||
                   date_cmp(subscriptions.elems[2].start_date, subscription5.start_date) != 0 || date_cmp(
                       subscriptions.elems[2].end_date, subscription5.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_21", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 22 - Delete subscription
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_22", "Delete Subscription [3]x2");
    if (!fail_all) {
        error = subscriptions_del(&subscriptions, 3);

        if (error == E_SUBSCRIPTION_NOT_FOUND) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[0].id != 1 || strcmp(subscriptions.elems[0].document, person2.document) != 0 ||
                   date_cmp(subscriptions.elems[0].start_date, subscription2.start_date) != 0 || date_cmp(
                       subscriptions.elems[0].end_date, subscription2.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[1].id != 2 || strcmp(subscriptions.elems[1].document, person1.document) != 0 ||
                   date_cmp(subscriptions.elems[1].start_date, subscription3.start_date) != 0 || date_cmp(
                       subscriptions.elems[1].end_date, subscription3.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_22", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 23 - Delete subscription
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_23", "Delete Subscription [2]");
    if (!fail_all) {
        error = subscriptions_del(&subscriptions, 2);

        if (error == E_SUBSCRIPTION_NOT_FOUND) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[0].id != 1 || strcmp(subscriptions.elems[0].document, person2.document) != 0 ||
                   date_cmp(subscriptions.elems[0].start_date, subscription2.start_date) != 0 || date_cmp(
                       subscriptions.elems[0].end_date, subscription2.end_date) != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_23", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 24 - Delete subscription
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_24", "Delete Subscription [1]x2");
    if (!fail_all) {
        error = subscriptions_del(&subscriptions, 1);

        if (error == E_SUBSCRIPTION_NOT_FOUND || subscriptions.elems != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_24", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 25 - Add a subscription
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_25", "Add subscription");
    if (!fail_all) {
        error = subscriptions_add(&subscriptions, people, subscription2);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[0].id != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!subscription_equal(subscriptions.elems[0], subscription2)) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_25", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 26 - Add a subscription
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_26", "Add subscription x2");
    if (!fail_all) {
        error = subscriptions_add(&subscriptions, people, subscription1);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[0].id != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!subscription_equal(subscriptions.elems[0], subscription2)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[1].id != 2) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!subscription_equal(subscriptions.elems[1], subscription1)) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_26", !failed);

    /////////////////////////////////////////////////
    // PR3 EX3 TEST 27 - Add a subscription
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX3_27", "Add subscription x3");
    if (!fail_all) {
        error = subscriptions_add(&subscriptions, people, subscription4);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[0].id != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!subscription_equal(subscriptions.elems[0], subscription2)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[1].id != 2) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!subscription_equal(subscriptions.elems[1], subscription1)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (subscriptions.elems[2].id != 3) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!subscription_equal(subscriptions.elems[2], subscription4)) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX3_27", !failed);

    film_catalog_free(&catalog);
    film_free(&film1);
    film_free(&film2);
    film_free(&film3);
    film_free(&film4);
    film_free(&film5);

    csv_freeEntry(&entryPerson1);
    csv_freeEntry(&entryPerson2);
    csv_freeEntry(&entryPerson3);
    csv_freeEntry(&entrySubscription1);
    csv_freeEntry(&entrySubscription2);
    csv_freeEntry(&entrySubscription3);
    csv_freeEntry(&entrySubscription4);
    csv_freeEntry(&entrySubscription5);
    person_free(&person1);
    person_free(&person2);
    person_free(&person3);
    subscriptions_free(&emptySubscriptions);
    subscriptions_free(&subscriptions);
    people_free(&emptyPeople);
    people_free(&people);

    return passed;
}

bool run_pr3_ex4(tTestSection *test_section, const char *input) {
    tApiError error;
    tApiData emptyData, data;
    tCSVData csvData;
    tCSVEntry entry;
    tFilm film1, film2;
    tFilmListNode *pFilmListNode;
    tFreeFilmListNode *pFreeFilmListNode;

    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    // Inicialización de datos
    error = api_initData(&emptyData);
    error = api_initData(&data);
    if (error != E_SUCCESS) {
        passed = false;
        fail_all = true;
        failed = false;
    }
    error = api_loadData(&data, input, true);

    if (error != E_SUCCESS) {
        passed = false;
        fail_all = true;
        failed = false;
    }

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 1 - Api Add to WatchList
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_1", "Api Add to WatchList");
    if (!fail_all) {
        if (data.subscriptions.elems[0].watchlist.top == NULL || (data.subscriptions.elems[0].watchlist.count != 1)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[0].watchlist.top->elem.name, "Interstellar") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.subscriptions.elems[1].watchlist.top == NULL || (
                       data.subscriptions.elems[1].watchlist.count != 10)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[1].watchlist.top->elem.name, "A Quiet Place") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[1].watchlist.top->next->elem.name, "The Conjuring") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[1].watchlist.top->next->next->elem.name, "Halloween") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[1].watchlist.top->next->next->next->elem.name, "It Follows") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[1].watchlist.top->next->next->next->next->elem.name,
                          "The Babadook") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[1].watchlist.top->next->next->next->next->next->elem.name,
                          "Hereditary") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[1].watchlist.top->next->next->next->next->next->next->elem.name,
                          "The Exorcist") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.subscriptions.elems[1].watchlist.top->next->next->next->next->next->next->next->elem.name,
                       "Nomadland") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.subscriptions.elems[1].watchlist.top->next->next->next->next->next->next->next->next->elem.
                       name, "Dune: Part Two") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.subscriptions.elems[1].watchlist.top->next->next->next->next->next->next->next->next->next->
                       elem.name, "A Beautiful Mind") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.subscriptions.elems[2].watchlist.top == NULL || (
                       data.subscriptions.elems[2].watchlist.count != 1)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[2].watchlist.top->elem.name, "A Beautiful Mind") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.subscriptions.elems[3].watchlist.top == NULL || (
                       data.subscriptions.elems[3].watchlist.count != 1)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[3].watchlist.top->elem.name, "A Beautiful Mind") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.subscriptions.elems[4].watchlist.top == NULL || (
                       data.subscriptions.elems[4].watchlist.count != 2)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[4].watchlist.top->elem.name, "Nomadland") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[4].watchlist.top->next->elem.name, "Interstellar") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.subscriptions.elems[5].watchlist.top != NULL || (
                       data.subscriptions.elems[5].watchlist.count != 0)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.subscriptions.elems[13].watchlist.top == NULL || (
                       data.subscriptions.elems[13].watchlist.count != 1)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[13].watchlist.top->elem.name, "Hereditary") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.subscriptions.elems[28].watchlist.top == NULL || (
                       data.subscriptions.elems[28].watchlist.count != 1)) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.subscriptions.elems[28].watchlist.top->elem.name, "Hereditary") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.subscriptions.elems[29].watchlist.top != NULL || (
                       data.subscriptions.elems[29].watchlist.count != 0)) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_1", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 2 - Api Get Longest Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_2", "Api Get Longest Film [empty data]");
    if (!fail_all) {
        csv_initEntry(&entry);
        error = api_getLongestFilm(emptyData, &entry);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);
    }
    end_test(test_section, "PR3_EX4_2", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 3 - Api Get Longest Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_3", "Api Get Longest Film");
    if (!fail_all) {
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "The Godfather Part II;03:22;2;20/12/1974;4.9;0", "FILM");
        film_parse(&film1, entry);
        csv_freeEntry(&entry);
        csv_initEntry(&entry);
        error = api_getLongestFilm(data, &entry);
        film_parse(&film2, entry);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (entry.numFields != 6) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!film_equals(film1, film2)) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        csv_freeEntry(&entry);
        film_free(&film1);
        film_free(&film2);
    }
    end_test(test_section, "PR3_EX4_3", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 4 - Api Get Longest Free Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_4", "Api Get Longest Free Film [empty data]");
    if (!fail_all) {
        csv_initEntry(&entry);
        error = api_getLongestFreeFilm(emptyData, &entry);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);
    }
    end_test(test_section, "PR3_EX4_4", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 5 - Api Get Longest Free Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_5", "Api Get Longest Free Film");
    if (!fail_all) {
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "Schindler's List;03:15;2;15/12/1993;4.9;1", "FILM");
        film_parse(&film1, entry);
        csv_freeEntry(&entry);
        csv_initEntry(&entry);
        error = api_getLongestFreeFilm(data, &entry);
        film_parse(&film2, entry);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (entry.numFields != 6) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!film_equals(film1, film2)) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        csv_freeEntry(&entry);
        film_free(&film1);
        film_free(&film2);
    }
    end_test(test_section, "PR3_EX4_5", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 6 - Api Sort Catalog by Year
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_6", "Api Sort Catalog by Year [empty catalog]");
    if (!fail_all) {
        error = api_sortCatalogByYear(&emptyData);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_6", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 7 - Api Sort Catalog by Year
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_7", "Api Sort Catalog by Year");
    if (!fail_all) {
        error = api_sortCatalogByYear(&data);

        if (error != E_SUCCESS || !data.films.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->elem.name, "12 Angry Men") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->elem.name, "2001: A Space Odyssey") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->elem.name, "The Godfather") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->elem.name, "The Exorcist") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->elem.name, "The Godfather Part II") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->elem.name,
                          "Monty Python and the Holy Grail") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->next->elem.name,
                          "Star Wars: A New Hope") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->next->next->elem.name,
                          "Halloween") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->next->next->next->elem.name,
                          "The Empire Strikes Back") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->next->next->next->next->elem.name,
                          "The Shining") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.films.filmList.first->next->next->next->next->next->next->next->next->next->next->elem.name,
                       "Airplane!") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.films.filmList.first->next->next->next->next->next->next->next->next->next->next->next->elem
                       .name, "Raiders of the Lost Ark") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.films.filmList.first->next->next->next->next->next->next->next->next->next->next->next->next
                       ->elem.name, "Mad Max 2: The Road Warrior") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.films.filmList.first->next->next->next->next->next->next->next->next->next->next->next->next
                       ->next->elem.name, "The Thing") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        pFilmListNode = data.films.filmList.first;

        for (int i = 0; i < 30; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "Contact") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 20; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "The Pursuit of Happyness") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 20; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "The Grand Budapest Hotel") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 20; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "Hereditary") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "Dune: Part Two") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pFilmListNode->next != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        pFreeFilmListNode = data.films.freeFilmList.first;

        if (strcmp(pFreeFilmListNode->elem->name, "2001: A Space Odyssey") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "Ghostbusters") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "Se7en") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "Minority Report") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "Zombieland") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 18; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "Knives Out") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pFreeFilmListNode->next != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_7", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 8 - Api Get Oldest Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_8", "Api Get Oldest Film [empty data]");
    if (!fail_all) {
        csv_initEntry(&entry);
        error = api_getOldestFilm(emptyData, &entry, false);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);
    }
    end_test(test_section, "PR3_EX4_8", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 9 - Api Get Oldest Free Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_9", "Api Get Oldest Free Film [empty data]");
    if (!fail_all) {
        csv_initEntry(&entry);
        error = api_getOldestFilm(emptyData, &entry, true);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);
    }
    end_test(test_section, "PR3_EX4_9", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 10 - Api Get Oldest Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_10", "Api Get Oldest Film");
    if (!fail_all) {
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "12 Angry Men;01:36;2;10/04/1957;4.9;0", "FILM");
        film_parse(&film1, entry);
        csv_freeEntry(&entry);
        csv_initEntry(&entry);
        error = api_getOldestFilm(data, &entry, false);
        film_parse(&film2, entry);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (entry.numFields != 6) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!film_equals(film1, film2)) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        csv_freeEntry(&entry);
        film_free(&film1);
        film_free(&film2);
    }
    end_test(test_section, "PR3_EX4_10", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 11 - Api Get Oldest Free Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_11", "Api Get Oldest Free Film");
    if (!fail_all) {
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "2001: A Space Odyssey;02:29;4;02/04/1968;4.8;1", "FILM");
        film_parse(&film1, entry);
        csv_freeEntry(&entry);
        csv_initEntry(&entry);
        error = api_getOldestFilm(data, &entry, true);
        film_parse(&film2, entry);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (entry.numFields != 6) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!film_equals(film1, film2)) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        csv_freeEntry(&entry);
        film_free(&film1);
        film_free(&film2);
    }
    end_test(test_section, "PR3_EX4_11", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 12 - Api Sort Catalog by Rating
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_12", "Api Sort Catalog by Rating [empty catalog]");
    if (!fail_all) {
        error = api_sortCatalogByRating(&emptyData);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_12", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 13 - Api Sort Catalog by Rating
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_13", "Api Sort Catalog by Rating");
    if (!fail_all) {
        error = api_sortCatalogByRating(&data);

        if (error != E_SUCCESS || data.films.sortedByDate) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->elem.name, "12 Angry Men") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->elem.name, "Forrest Gump") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->elem.name, "Schindler's List") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->elem.name, "Terminator 2: Judgment Day") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->elem.name, "The Dark Knight") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->elem.name, "The Godfather") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->next->elem.name,
                          "The Godfather Part II") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->next->next->elem.name,
                          "The Matrix") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->next->next->next->elem.name,
                          "The Shawshank Redemption") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.films.filmList.first->next->next->next->next->next->next->next->next->next->elem.name,
                          "2001: A Space Odyssey") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.films.filmList.first->next->next->next->next->next->next->next->next->next->next->elem.name,
                       "Interstellar") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.films.filmList.first->next->next->next->next->next->next->next->next->next->next->next->elem
                       .name, "Monty Python and the Holy Grail") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.films.filmList.first->next->next->next->next->next->next->next->next->next->next->next->next
                       ->elem.name, "Parasite") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(
                       data.films.filmList.first->next->next->next->next->next->next->next->next->next->next->next->next
                       ->next->elem.name, "Raiders of the Lost Ark") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        pFilmListNode = data.films.filmList.first;

        for (int i = 0; i < 30; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "Jurassic Park") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 20; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "La La Land") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 20; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "The Revenant") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 20; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "Nomadland") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFilmListNode = pFilmListNode->next;
        }

        if (strcmp(pFilmListNode->elem.name, "The Blair Witch Project") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pFilmListNode->next != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        pFreeFilmListNode = data.films.freeFilmList.first;

        if (strcmp(pFreeFilmListNode->elem->name, "Schindler's List") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "The Green Arrow") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "Groundhog Day") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "The Thing") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 10; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "Airplane!") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        for (int i = 0; i < 18; i++) {
            pFreeFilmListNode = pFreeFilmListNode->next;
        }

        if (strcmp(pFreeFilmListNode->elem->name, "Superbad") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (pFreeFilmListNode->next != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_13", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 14 - Api Update VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_14", "Update VIP level [empty catalog]");
    if (!fail_all) {
        error = api_updateVipLevel(&emptyData);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_14", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 15 - Api Sort People by VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_15", "Api Update VIP level");
    if (!fail_all) {
        error = api_updateVipLevel(&data);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[0].vipLevel != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[1].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[2].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[3].vipLevel != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[4].vipLevel != 6) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[5].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[6].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[7].vipLevel != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[8].vipLevel != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[9].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[10].vipLevel != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[11].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[12].vipLevel != 1) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[13].vipLevel != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[14].vipLevel != 2) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_15", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 16 - Api Sort People by VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_16", "Sort People by VIP level [empty catalog]");
    if (!fail_all) {
        error = api_sortPeopleByVipLevel(&emptyData);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_16", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 17 - Api Sort People by VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_17", "Api Sort People by VIP level");
    if (!fail_all) {
        error = api_sortPeopleByVipLevel(&data);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[0].vipLevel != 6 || strcmp(data.people.elems[0].document, "47051307Z") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[1].vipLevel != 2 || strcmp(data.people.elems[1].document, "77788890J") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[2].vipLevel != 1 || strcmp(data.people.elems[2].document, "12345672C") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[3].vipLevel != 1 || strcmp(data.people.elems[3].document, "33344455F") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[4].vipLevel != 1 || strcmp(data.people.elems[4].document, "44455566C") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[5].vipLevel != 1 || strcmp(data.people.elems[5].document, "55566678H") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[6].vipLevel != 1 || strcmp(data.people.elems[6].document, "77788899D") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[7].vipLevel != 1 || strcmp(data.people.elems[7].document, "98765432J") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[8].vipLevel != 0 || strcmp(data.people.elems[8].document, "11122233B") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[9].vipLevel != 0 || strcmp(data.people.elems[9].document, "22233344E") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[10].vipLevel != 0 || strcmp(data.people.elems[10].document, "33365111X") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[11].vipLevel != 0 || strcmp(data.people.elems[11].document, "44455567G") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[12].vipLevel != 0 || strcmp(data.people.elems[12].document, "55565432Z") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[13].vipLevel != 0 || strcmp(data.people.elems[13].document, "66677789I") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (data.people.elems[14].vipLevel != 0 || strcmp(data.people.elems[14].document, "87654321A") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_17", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 18 - Api Sort People by Document
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_18", "Sort People by Document [empty catalog]");
    if (!fail_all) {
        error = api_sortPeopleByDocument(&emptyData);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_18", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 19 - Api Sort People by VIP level
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_19", "Api Sort People by VIP level");
    if (!fail_all) {
        error = api_sortPeopleByDocument(&data);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[0].document, "11122233B") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[1].document, "12345672C") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[2].document, "22233344E") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[3].document, "33344455F") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[4].document, "33365111X") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[5].document, "44455566C") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[6].document, "44455567G") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[7].document, "47051307Z") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[8].document, "55565432Z") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[9].document, "55566678H") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[10].document, "66677789I") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[11].document, "77788890J") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[12].document, "77788899D") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[13].document, "87654321A") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (strcmp(data.people.elems[14].document, "98765432J") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR3_EX4_19", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 20 - Api Get Popular Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_20", "Api Get Popular Film [empty data]");
    if (!fail_all) {
        csv_initEntry(&entry);
        error = api_getPopularFilm(emptyData, &entry);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);
    }
    end_test(test_section, "PR3_EX4_20", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 21 - Api Get Popular Film
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_21", "Api Get Popular Film");
    if (!fail_all) {
        csv_initEntry(&entry);
        csv_parseEntry(&entry, "Nomadland;01:48;2;19/02/2021;4.1;0", "FILM");
        film_parse(&film1, entry);
        csv_freeEntry(&entry);
        csv_initEntry(&entry);
        error = api_getPopularFilm(data, &entry);
        film_parse(&film2, entry);
        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (entry.numFields != 6) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (!film_equals(film1, film2)) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        csv_freeEntry(&entry);
        film_free(&film1);
        film_free(&film2);
    }
    end_test(test_section, "PR3_EX4_21", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 22 - Api Get Subscriptions by Document
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_22", "Api Get Subscriptions by Document [empty catalog]");
    if (!fail_all) {
        csv_init(&csvData);
        error = api_getSubscriptionsByDocument(emptyData, "98765432J", &csvData);

        if (error != E_SUCCESS) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_free(&csvData);
    }
    end_test(test_section, "PR3_EX4_22", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 23 - Api Get Subscriptions by Document
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_23", "Api Get Subscriptions by Document [98765432J]");
    if (!fail_all) {
        csv_init(&csvData);
        error = api_getSubscriptionsByDocument(data, "98765432J", &csvData);

        if (error != E_SUCCESS || csvData.count != 3) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        csv_initEntry(&entry);
        csv_parseEntry(&entry, "1;98765432J;01/01/2025;31/12/2025;Free;0;1", "SUBSCRIPTION");

        if (!csv_equalsEntry(csvData.entries[0], entry)) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);

        csv_initEntry(&entry);
        csv_parseEntry(&entry, "2;98765432J;01/01/2026;30/06/2026;Standard;29.95;3", "SUBSCRIPTION");

        if (!csv_equalsEntry(csvData.entries[1], entry)) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);

        csv_initEntry(&entry);
        csv_parseEntry(&entry, "3;98765432J;01/07/2026;31/06/2027;Standard;29.95;3", "SUBSCRIPTION");

        if (!csv_equalsEntry(csvData.entries[2], entry)) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);
        csv_free(&csvData);
    }
    end_test(test_section, "PR3_EX4_23", !failed);

    /////////////////////////////////////////////////
    // PR3 EX4 TEST 23 - Api Get Subscriptions by Document
    /////////////////////////////////////////////////
    start_test(test_section, "PR3_EX4_24", "Api Get Subscriptions by Document [33344455F]");
    if (!fail_all) {
        csv_init(&csvData);
        error = api_getSubscriptionsByDocument(data, "33344455F", &csvData);

        if (error != E_SUCCESS || csvData.count != 2) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        csv_initEntry(&entry);
        csv_parseEntry(&entry, "1;33344455F;01/07/2025;30/06/2026;Standard;29.95;3", "SUBSCRIPTION");

        if (!csv_equalsEntry(csvData.entries[0], entry)) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);

        csv_initEntry(&entry);
        csv_parseEntry(&entry, "2;33344455F;01/07/2026;30/06/2027;Premium;39.95;3", "SUBSCRIPTION");

        if (!csv_equalsEntry(csvData.entries[1], entry)) {
            failed = true;
            passed = false;
            fail_all = true;
        }
        csv_freeEntry(&entry);
        csv_free(&csvData);
    }
    end_test(test_section, "PR3_EX4_24", !failed);

    api_freeData(&emptyData);
    api_freeData(&data);

    return passed;
}
