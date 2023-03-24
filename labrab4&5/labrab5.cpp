#include <iostream>

/*
 * Variant #3
 *     / 4xy + 4x,          xy > 8;
 *     |
 *     |     2xy + 3
 * y = { --------------,    xy < -12;
 *     | x^2 + 2y^2 - 1
 *     |
 *     \ 3x^2 - 2y^2 + 1,   -12 <= xy <= 8.
 */
int main()
{
    const float upper_border = 8.0;
    const float bottom_border = -12.0;

    const float one = 1.0;
    const float two = 2.0;
    const float three = 3.0;
    const float four = 4.0;
    const float six = 6.0;

    float a;

    float x, y;

    std::cout << "Enter X and Y:\n";
    std::cin >> x >> y;

    __asm {
        fld x   ; Загрузка значения x в стек сопроцессора
        fmul y  ; Умножение st(0) и y, сохраняем на вершине стека сопроцессора

        ; Проверка результата
        fcom upper_border   ; Сравнение значения на вершине стека с 8.0
        fstsw ax
        sahf
        jnc sum_gr          ; Если результат > 8.0, переход на метку sum_gr

        ; Проверка результата
        fcom bottom_border  ; Сравнение значения на вершине стека с - 12.0
        fstsw ax
        sahf
        jz sum_ls
        jc sum_ls           ; Если результат < -12.0, переход на метку sum_ls

        ; Если не прошли ни одну из проверок, переход на метку sum_in
        jmp sum_in

        sum_gr:
            ; 4xy + 4x

            ; x * y
            fld y       ; Загрузка значения y в стек сопроцессора
            fmul x      ; Умножение st(0) и x, сохраняем на вершине стека сопроцессора

            ; 4 * xy
            fmul four   ; Умножение st(0) и 4, сохраняем на вершине стека сопроцессора

            fstp a      ; Сохраняем 4xy в a

            ; 4 * x
            fld x       ; Загрузка значения x в стек сопроцессора
            fmul four   ; Умножение st(0) и 4, сохраняем на вершине стека сопроцессора

            ; 4xy + 4x
            fadd a      ; Сложение st(0) (4x) и a(4xy), сохраняем на вершине стека сопроцессора

            ; Вывод
            fstp y

            jmp end

        sum_ls:
            ;     2xy + 3
            ; --------------
            ; x ^ 2 + 2y ^ 2 - 1

            ; x ^ 2 + 2y ^ 2 - 1
            ; x * x
            fld x; Загрузка значения x в стек сопроцессора
            fmul x; Умножаем на x

            fstp a; Сохраняем x* x в a

            ; 2yy
            fld y; Загрузка значения y в стек сопроцессора
            fmul y      ; Умножаем на y
            fmul two    ; Умножаем на 2

            ; xx + 2yy
            fadd a      ; Добавляем a к содержимому стека

            ; xx + 2yy - 1
            fsub one    ; Отнимаем 1 из стека

            fstp a      ; Сохраняем xx + 2yy - 1 в a

            ; 2xy + 3
            fld x       ; Загрузка значения x в стек сопроцессора
            fmul y      ; Умножение на y
            fmul two    ; Умножение на 2
            fadd three  ; Сложение на 3

            ; <Основная дробь>
            fdiv a      ; Делим содержимое стека на a

            ; Вывод
            fstp y

            jmp end

        sum_in:
            ; 3x^2 - 2y^2 + 1

            ; y*y
            fld y       ; Загрузка значения y в стек сопроцессора
            fmul y      ; Умножаем на y вершину стека сопроцессора
            ; 2 * y * y
            fmul two    ; Умножаем на 2 вершину стека сопроцессора

            fstp a      ; Сохраняем 2yy в a

            ; x * x
            fld x       ; Загрузка значения x в стек сопроцессора
            fmul x      ; Умножаем на x вершину стека сопроцессора
            ; 3 * x * x
            fmul three  ; Умножаем на 3 вершину стека сопроцессора

            ; 3x ^ 2 - 2y ^ 2
            fsub a      ; Вычитаем из вершины стека значение a

            fstp a      ; Сохраняем 3x ^ 2 - 2y ^ 2 в a

            ; 3x ^ 2 - 2y ^ 2 + 1
            fld1        ; Загрузка значения 1 в вершину стека сопроцессора
            fadd a      ; Сложение st(0) и a, сохраняем на вершине стека сопроцессора

            ; Вывод
            fstp y

        end:
    }

    std::cout << "\nY: " << y << std::endl;

    return 0;
}