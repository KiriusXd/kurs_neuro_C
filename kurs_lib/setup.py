from setuptools import setup, Extension

module = Extension(
    'gpio', # отвечает за то что пишется в import
    sources=['gpio_module.c'],
    libraries=['gpiod'],  # Указываем линковку с libgpiod
)

setup(
    name='gpio_c', # имя пакета
    version='1.0', # версия
    description='GPIO модуль для Raspberry Pi на С', # описание
    ext_modules=[module],
)