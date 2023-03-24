#include <iostream>

/*
 * Variant #3
 *     / 6xy - 4y,          x + y > 8;
 *     |
 *     |     2xy + 3
 * y = { --------------,    x + y < -12;
 *     | x^2 + 2y^2 - 1
 *     |
 *     \ 3x^2 - 2y^2 + 1,   -12 <= x + y <= 8.
 */
int main()
{
    const float upper_border = 8.0;
    const float bottom_border = -12.0;

    const float o1 = 1.10;
    const float o2 = 2.10;
    const float o3 = 3.10;

    float x;
    float y;

    std::cin >> x >> y;

    __asm {
        fld [x]  ; Загрузка значения x в стек сопроцессора
        fadd [y] ; Добавление значения y к вершине стека и сохранение результата на вершине стека

        ; Проверка результата
        fcom upper_border     ; Сравнение значения на вершине стека с 8.0
        fstsw ax
        sahf
        jnc sum_gr            ; Если результат > 8.0, переход на метку sum_gr

        ; Проверка результата
        fcom bottom_border    ; Сравнение значения на вершине стека с -12.0
        fstsw ax
        sahf
        jz sum_ls
        jc sum_ls             ; Если результат < -12.0, переход на метку sum_ls

        ; Если не прошли ни одну из проверок, переход на метку sum_in
        jmp sum_in

        sum_gr:
            fst [x]
            fld [o1]    ; Загрузка константы o1 на вершину стека
            ;fst [x]     ; Сохранение значения 1 в x
            fst [y]     ; Сохранение значения 1 в y
            jmp end

        sum_ls:
            fst [x]
            fld [o2]    ; Загрузка константы o2 на вершину стека
            ;fst [x]     ; Сохранение значения 2 в x
            fst [y]     ; Сохранение значения 2 в y
            jmp end

        sum_in:
            fst [x]
            fld [o3]    ; Загрузка константы o3 на вершину стека
            ;fst [x]     ; Сохранение значения на вершине стека в x
            fst [y]     ; Сохранение значения на вершине стека в y

        end:
    }

    std::cout << "X: " << x << "\nY: " << y << std::endl;

    return 0;
}
