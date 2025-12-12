#include "cinema_db.h"

FilmArray* create_film_array(int initial_capacity) {
    FilmArray* array = (FilmArray*)malloc(sizeof(FilmArray));
    if (!array) return NULL;
    
    array->films = (Film*)malloc(sizeof(Film) * initial_capacity);
    if (!array->films) {
        free(array);
        return NULL;
    }
    
    array->size = 0;
    array->capacity = initial_capacity;
    return array;
}

void destroy_film_array(FilmArray* array) {
    if (array) {
        free(array->films);
        free(array);
    }
}

void add_film(FilmArray* array, Film film) {
    if (array->size >= array->capacity) {
        int new_capacity = array->capacity * 2;
        Film* new_films = (Film*)realloc(array->films, sizeof(Film) * new_capacity);
        if (!new_films) {
            printf("Ошибка: не удалось расширить массив!\n");
            return;
        }
        array->films = new_films;
        array->capacity = new_capacity;
    }
    
    array->films[array->size] = film;
    array->size++;
}

void remove_film_by_id(FilmArray* array, int id) {
    for (int i = 0; i < array->size; i++) {
        if (array->films[i].id == id) {
            for (int j = i; j < array->size - 1; j++) {
                array->films[j] = array->films[j + 1];
            }
            array->size--;
            printf("Фильм с ID %d удален.\n", id);
            return;
        }
    }
    printf("Фильм с ID %d не найден.\n", id);
}

Film* find_film_by_id(FilmArray* array, int id) {
    for (int i = 0; i < array->size; i++) {
        if (array->films[i].id == id) {
            return &array->films[i];
        }
    }
    return NULL;
}

void print_all_films(FilmArray* array) {
    if (array->size == 0) {
        printf("База данных пуста.\n");
        return;
    }
    
    printf("\n=== Список всех фильмов ===\n");
    printf("ID  | Название                     | Жанр         | Длит. | Рейтинг | Год\n");
    printf("----|------------------------------|--------------|-------|---------|-----\n");
    
    for (int i = 0; i < array->size; i++) {
        Film film = array->films[i];
        printf("%-3d | %-28s | %-12s | %-5d | %-7.1f | %-4d\n",
               film.id, film.title, film.genre, film.duration, film.rating, film.year);
    }
    printf("Всего фильмов: %d\n", array->size);
}

void search_films(FilmArray* array) {
    if (array->size == 0) {
        printf("База данных пуста.\n");
        return;
    }
    
    printf("\n=== Поиск фильмов ===\n");
    printf("1. По жанру\n");
    printf("2. По рейтингу (выше указанного)\n");
    printf("3. По году выпуска\n");
    printf("Выберите критерий поиска: ");
    
    int choice;
    scanf("%d", &choice);
    clear_input_buffer();
    
    printf("\nРезультаты поиска:\n");
    printf("ID  | Название                     | Жанр         | Длит. | Рейтинг | Год\n");
    printf("----|------------------------------|--------------|-------|---------|-----\n");
    
    int found = 0;
    
    switch (choice) {
        case 1: {
            char genre[50];
            printf("Введите жанр для поиска: ");
            fgets(genre, sizeof(genre), stdin);
            genre[strcspn(genre, "\n")] = '\0';
            
            for (int i = 0; i < array->size; i++) {
                if (strstr(array->films[i].genre, genre) != NULL) {
                    Film film = array->films[i];
                    printf("%-3d | %-28s | %-12s | %-5d | %-7.1f | %-4d\n",
                           film.id, film.title, film.genre, film.duration, film.rating, film.year);
                    found++;
                }
            }
            break;
        }
        case 2: {
            float min_rating;
            printf("Введите минимальный рейтинг: ");
            scanf("%f", &min_rating);
            
            for (int i = 0; i < array->size; i++) {
                if (array->films[i].rating >= min_rating) {
                    Film film = array->films[i];
                    printf("%-3d | %-28s | %-12s | %-5d | %-7.1f | %-4d\n",
                           film.id, film.title, film.genre, film.duration, film.rating, film.year);
                    found++;
                }
            }
            break;
        }
        case 3: {
            int year;
            printf("Введите год выпуска: ");
            scanf("%d", &year);
            
            for (int i = 0; i < array->size; i++) {
                if (array->films[i].year == year) {
                    Film film = array->films[i];
                    printf("%-3d | %-28s | %-12s | %-5d | %-7.1f | %-4d\n",
                           film.id, film.title, film.genre, film.duration, film.rating, film.year);
                    found++;
                }
            }
            break;
        }
        default:
            printf("Неверный выбор.\n");
            return;
    }
    
    printf("\nНайдено фильмов: %d\n", found);
}

Film create_new_film(int next_id) {
    Film film;
    film.id = next_id;
    
    printf("Введите название фильма: ");
    fgets(film.title, sizeof(film.title), stdin);
    film.title[strcspn(film.title, "\n")] = '\0';
    
    printf("Введите жанр: ");
    fgets(film.genre, sizeof(film.genre), stdin);
    film.genre[strcspn(film.genre, "\n")] = '\0';
    
    printf("Введите длительность (в минутах): ");
    scanf("%d", &film.duration);
    
    printf("Введите рейтинг (0.0-10.0): ");
    scanf("%f", &film.rating);
    
    printf("Введите год выпуска: ");
    scanf("%d", &film.year);
    
    clear_input_buffer();
    
    return film;
}

void edit_film(Film* film) {
    printf("\nРедактирование фильма (ID: %d)\n", film->id);
    printf("Оставьте поле пустым (нажмите Enter), чтобы не изменять его.\n");
    
    char input[100];
    
    printf("Текущее название: %s\n", film->title);
    printf("Новое название: ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1) {
        input[strcspn(input, "\n")] = '\0';
        strcpy(film->title, input);
    }
    
    printf("Текущий жанр: %s\n", film->genre);
    printf("Новый жанр: ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1) {
        input[strcspn(input, "\n")] = '\0';
        strcpy(film->genre, input);
    }
    
    printf("Текущая длительность: %d\n", film->duration);
    printf("Новая длительность (введите 0 чтобы не менять): ");
    fgets(input, sizeof(input), stdin);
    if (atoi(input) != 0) {
        film->duration = atoi(input);
    }
    
    printf("Текущий рейтинг: %.1f\n", film->rating);
    printf("Новый рейтинг (введите 0 чтобы не менять): ");
    fgets(input, sizeof(input), stdin);
    if (atof(input) != 0) {
        film->rating = atof(input);
    }
    
    printf("Текущий год: %d\n", film->year);
    printf("Новый год (введите 0 чтобы не менять): ");
    fgets(input, sizeof(input), stdin);
    if (atoi(input) != 0) {
        film->year = atoi(input);
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_menu() {
    printf("\n=== Управление базой данных кинотеатра ===\n");
    printf("1. Вывести все фильмы\n");
    printf("2. Найти фильмы\n");
    printf("3. Добавить новый фильм\n");
    printf("4. Удалить фильм\n");
    printf("5. Редактировать фильм\n");
    printf("6. Сохранить изменения в файл\n");
    printf("0. Выйти из программы\n");
    printf("Выберите действие: ");
}