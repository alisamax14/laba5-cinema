#ifndef CINEMA_DB_H
#define CINEMA_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    char title[100];
    char genre[50];
    int duration;
    float rating;
    int year;
} Film;

typedef struct {
    Film* films;
    int size;
    int capacity;
} FilmArray;

FilmArray* create_film_array(int initial_capacity);
void destroy_film_array(FilmArray* array);
void add_film(FilmArray* array, Film film);
void remove_film_by_id(FilmArray* array, int id);
Film* find_film_by_id(FilmArray* array, int id);

void print_all_films(FilmArray* array);
void search_films(FilmArray* array);
Film create_new_film(int next_id);
void edit_film(Film* film);

void save_to_file(const char* filename, FilmArray* array);
FilmArray* load_from_file(const char* filename);

void clear_input_buffer();
void print_menu();

#endif