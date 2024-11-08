#!/usr/bin/env perl

use strict;
use warnings;
use v5.40;
use Data::Dumper "Dumper";

my $pascal = do {
    use Regexp::Grammars;
    qr{

    <nocontext:>

    # Распознать число
    <number>

    # Правило для числа
    <rule: number>
        <[d]>+ <fraction>? <exponent>? <float>?

    # Правило для десятичной дроби
    <rule: fraction>
        \. <int>

    # Правило для целого числа
    <rule: int>
        <[d]>+

    # Правило для целого числа с опциональным знаком
    <rule: integer>
        [+-]? <int>

    # Правило для экспоненты
    <rule: exponent>
        e <integer>

    # Правила для чисел с плавающей точкой.
    <rule: frexp>
        <[d]>+ <exponent>

    <rule: float>
        \. <frexp>

    # Токен цифры
    <token: d>
        [0-9]

    }xms;
};

# Читаем вход и проверяем на принадлежность языку
# с помощью конечного детерминированного автомата.
while (my $input = <>) {
    chomp $input;
    # Если слово принадлежит языку, выводим на печать парсер...
    if ($input =~ $pascal) {
        say Dumper \%/;
    # ...в противном случае сообщаем о неудаче.
    } else {
        say "Последовательность не является числом в Pascal.";
    }
}
