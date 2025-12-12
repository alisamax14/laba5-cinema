#include "cinema_db.h"

#define FILENAME "cinema_database.bin"

int main() {
    FilmArray* films = load_from_file(FILENAME);
    if (!films) {
        printf("Ошибка при создании базы данных!\n");
        return 1;
    }
    
    int choice;
    int next_id = films->size > 0 ? films->films[films->size - 1].id + 1 : 1;
    
    do {
        print_menu();
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                print_all_films(films);
                break;
                
            case 2:
                search_films(films);
                break;
                
            case 3: {
                Film new_film = create_new_film(next_id);
                add_film(films, new_film);
                next_id++;
                printf("Фильм успешно добавлен!\n");
                save_to_file(FILENAME, films);
                break;
            }
                
            case 4: {
                printf("Введите ID фильма для удаления: ");
                int id;
                scanf("%d", &id);
                clear_input_buffer();
                remove_film_by_id(films, id);
                save_to_file(FILENAME, films);
                break;
            }
                
            case 5: {
                printf("Введите ID фильма для редактирования: ");
                int id;
                scanf("%d", &id);
                clear_input_buffer();
                
                Film* film = find_film_by_id(films, id);
                if (film) {
                    edit_film(film);
                    printf("Фильм успешно отредактирован!\n");
                    save_to_file(FILENAME, films);
                } else {
                    printf("Фильм с ID %d не найден.\n", id);
                }
                break;
            }
                
            case 6:
                save_to_file(FILENAME, films);
                break;
                
            case 0:
                printf("Выход из программы...\n");
                break;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);
    
    save_to_file(FILENAME, films);
    destroy_film_array(films);
    
    return 0;
}