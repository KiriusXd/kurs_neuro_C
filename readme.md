Драйвер для работы с портами GPIO на Raspberry Pi 5

1. Обновить систему и установить необходимые библиотеки

sudo apt-get update
sudo apt-get install libgpiod-dev libgpiod2 

2. скомпилировать файл (в разработке)

Для тестов

gpiod.c сейчас включает выключает светодиод на 17 порту (указывается прямо в коде)
компиляция gpiod.c:
gcc -Wall -o led gpioid.c -lgpiod