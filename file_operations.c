#include "cinema_db.h"

void save_to_file(const char* filename, FilmArray* array) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Ошибка: не удалось открыть файл для записи!\n");
        return;
    }
    
    fwrite(&array->size, sizeof(int), 1, file);
    fwrite(array->films, sizeof(Film), array->size, file);
    
    fclose(file);
    printf("Данные успешно сохранены в файл '%s'\n", filename);
}

FilmArray* load_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Файл '%s' не найден. Создана новая база данных.\n", filename);
        return create_film_array(10);
    }
    
    int size;
    fread(&size, sizeof(int), 1, file);
    
    FilmArray* array = create_film_array(size > 10 ? size : 10);
    if (!array) {
        fclose(file);
        return NULL;
    }
    
    array->size = size;
    fread(array->films, sizeof(Film), size, file);
    
    fclose(file);
    printf("Загружено %d фильмов из файла '%s'\n", size, filename);
    
    return array;
}