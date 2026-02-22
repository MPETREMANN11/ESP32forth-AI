\ *************************************
\ tests for AI words
\    Filename:      tests.fs
\    Date:          22 feb 2026
\    Updated:       22 feb 2026
\    File Version:  1.0
\    MCU:           ESP32-S3 only !!
\    Forth:         ESP32forth all versions 7.0.7.+
\    Copyright:     Marc PETREMANN
\    Author:        Marc PETREMANN
\    GNU General Public License
\ **************************************


RECORDFILE /spiffs/tests.fs

3 value dataSize 

0 value input1
    align here to input1 
    10 c, 20 c, 30 c,

0 value input2
    align here to input2 
    5 c, 4 c, 3 c,

0 value output
    align here to output
    0 c, 0 c, 0 c,

input1          \ n10 : Adresse source 1
input2          \ n9  : Adresse source 2
0               \ n8  : Offset entrée 1 (souvent 0)
0               \ n7  : Offset entrée 2 (souvent 0)
output          \ n6  : Adresse de destination
0               \ n5  : Offset de sortie (souvent 0)
2147483647      \ n4  : out_mult (Facteur d'échelle en Q31, ici 0.5 pour l'exemple)
0               \ n3  : out_shift (Décalage binaire)
-128            \ n2  : Activation MIN (Clamping bas s8)
127             \ n1  : Activation MAX (Clamping haut s8)
dataSize        \ n0  : Nombre d'éléments (SIZE)
nn.mul_elementwise_s8

output 0 nn.get_element_s8 .
output 1 nn.get_element_s8 .
output 2 nn.get_element_s8 .


<EOF>


