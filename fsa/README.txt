Input: stdin
Output: stdout

Конечный автомат, распознающий числа в языке Паскаль.

<NUMBER> ::= d | d <FRACTION> | d <EXPONENT> | d <FLOAT> | d <NUMBER>
<FRACTION> ::= . <INT>
<INT> ::= d | d <INT>
<EXPONENT> ::= e <INTEGER>
<INTEGER> ::= + <INT> | – <INT> | d | d <INT>
<FLOAT> ::= . <FREXP>
<FREXP> ::= d <EXPONENT> | d <FREXP>
