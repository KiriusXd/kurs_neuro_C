#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <gpiod.h>

#define LED_GPIO 17  // Укажите правильный номер GPIO для светодиода
#define GPIO_CHIP "/dev/gpiomem4"

static int running = 1;

void handle_sigint(int signum) {
    running = 0;
}

int main(void) {
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int ret;

    // Обработка сигнала Ctrl+C для выхода
    signal(SIGINT, handle_sigint);

    // Открываем GPIO-чип
    chip = gpiod_chip_open(GPIO_CHIP);
    if (!chip) {
        perror("Ошибка: не удалось открыть чип GPIO");
        exit(EXIT_FAILURE);
    }

    // Получаем линию GPIO
    line = gpiod_chip_get_line_offset(chip, LED_GPIO);
    if (!line) {
        perror("Ошибка: не удалось получить линию GPIO");
        gpiod_chip_close(chip);
        exit(EXIT_FAILURE);
    }

    // Запрашиваем линию на вывод
    ret = gpiod_line_request_output(line, "led_toggle", 0);
    if (ret < 0) {
        perror("Ошибка: не удалось запросить GPIO на вывод");
        gpiod_chip_close(chip);
        exit(EXIT_FAILURE);
    }

    printf("Светодиод мигает на GPIO %d. Нажмите Ctrl+C для выхода.\n", LED_GPIO);

    // Мигание светодиодом
    while (running) {
        ret = gpiod_line_set_value(line, 1);
        if (ret < 0) {
            perror("Ошибка: не удалось установить GPIO в HIGH");
            break;
        }
        sleep(1);

        ret = gpiod_line_set_value(line, 0);
        if (ret < 0) {
            perror("Ошибка: не удалось установить GPIO в LOW");
            break;
        }
        sleep(1);
    }

    // Освобождаем ресурсы
    gpiod_line_release(line);
    gpiod_chip_close(chip);

    printf("Выход из программы.\n");
    return 0;
}
//gcc -Wall -o led gpiod.c -lgpiod
//
//