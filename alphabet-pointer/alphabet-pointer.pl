#! /usr/bin/perl
use v5.40;

# Hashmap для слов, где ключ --- слово в тексте,
# значение --- список строк, где оно встретилось.
my %word_positions;

# Считываем строки.
my $line_number = 0;
while (<>) {
    $line_number++;
    my $line = $_;
    # Для каждой строки заносим слова,
    # которые в ней встретились, в hashmap.
    while ($line =~ /(\b\w+\b)/g) {
        my $word = $1;
        push @{ $word_positions{lc $word} }, $line_number;
    }
}

# Сортируем ключи лексикографически и выводим номера строк.
for my $word (sort keys %word_positions) {
    say "$word ", join(' ', @{ $word_positions{$word} });
}
