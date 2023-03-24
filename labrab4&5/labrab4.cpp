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
    const int upper_border = 8;
    const int bottom_border = -12;

    const int one = 1;
    const int two = 2;
    const int three = 3;
    const int four = 4;
    const int six = 6;

    int a;

    int x, y;

    std::cout << "Enter X and Y:\n";
    std::cin >> x >> y;

    __asm {
        fild x     ; Загрузка значения x в стек сопроцессора
        fimul y    ; Умножение st(0) и y, сохраняем на вершине стека сопроцессора

        ; Проверка результата
        ficom upper_border    ; Сравнение значения на вершине стека с 8.0
        fstsw ax
        sahf
        jnc sum_gr            ; Если результат > 8.0, переход на метку sum_gr

        ; Проверка результата
        ficom bottom_border   ; Сравнение значения на вершине стека с -12.0
        fstsw ax
        sahf
        jz sum_ls
        jc sum_ls             ; Если результат < -12.0, переход на метку sum_ls

        ; Если не прошли ни одну из проверок, переход на метку sum_in
        jmp sum_in

        sum_gr:
            ; 4xy + 4x
            
            ; x * y
            fild y      ; Загрузка значения y в стек сопроцессора
            fimul x     ; Умножение st(0) и x, сохраняем на вершине стека сопроцессора

            ; 4 * xy
            fimul four  ; Умножение st(0) и 4, сохраняем на вершине стека сопроцессора

            fistp a     ; Сохраняем 4xy в a

            ; 4 * x
            fild x      ; Загрузка значения x в стек сопроцессора
            fimul four  ; Умножение st(0) и 4, сохраняем на вершине стека сопроцессора

            ; 4xy + 4x
            fiadd a     ; Сложение st(0) (4x) и a (4xy), сохраняем на вершине стека сопроцессора

            ; Вывод
            fistp y

            jmp end

        sum_ls:
            ;     2xy + 3
            ; --------------
            ; x^2 + 2y^2 - 1

            ; x^2 + 2y^2 - 1
            ; x*x
            fild x      ; Загрузка значения x в стек сопроцессора
            fimul x     ; Умножаем на x
            
            fistp a     ; Сохраняем x*x в a

            ; 2yy
            fild y      ; Загрузка значения y в стек сопроцессора
            fimul y     ; Умножаем на y
            fimul two   ; Умножаем на 2

            ; xx + 2yy
            fiadd a     ; Добавляем a к содержимому стека

            ; xx+2yy - 1
            fisub one   ; Отнимаем 1 из стека

            fistp a     ; Сохраняем xx+2yy-1 в a

            ; 2xy+3
            fild x      ; Загрузка значения x в стек сопроцессора
            fimul y     ; Умножение на y
            fimul two   ; Умножение на 2
            fiadd three ; Сложение на 3

            ; <Основная дробь>
            fidiv a     ; Делим содержимое стека на a

            ; Вывод
            fistp y

            jmp end

        sum_in:
            ; 3x^2 - 2y^2 + 1
               
            ; y * y
            fild y      ; Загрузка значения y в стек сопроцессора
            fimul y     ; Умножаем на y вершину стека сопроцессора
            ; 2 * y*y
            fimul two   ; Умножаем на 2 вершину стека сопроцессора

            fistp a     ; Сохраняем 2yy в a

            ; x * x
            fild x      ; Загрузка значения x в стек сопроцессора
            fimul x     ; Умножаем на x вершину стека сопроцессора
            ; 3 * x*x
            fimul three ; Умножаем на 3 вершину стека сопроцессора

            ; 3x^2 - 2y^2
            fisub a     ; Вычитаем из вершины стека значение a

            fistp a     ; Сохраняем 3x^2-2y^2 в a

            ; 3x^2-2y^2 + 1
            fld1        ; Загрузка значения 1 в вершину стека сопроцессора
            fiadd a     ; Сложение st(0) и a, сохраняем на вершине стека сопроцессора

            ; Вывод
            fistp y

        end:
    }

    std::cout << "\nY: " << y << std::endl;

    return 0;
}
