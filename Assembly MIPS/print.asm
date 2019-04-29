.data
msg_consumo:        .asciiz "Consumo medio: "
msg_preco:          .asciiz "Preco Medio: "

;Para duvidas sobre float
;https://www.doc.ic.ac.uk/lab/secondyear/spim/node20.html


print_linear:

	add $t1, $0, $0
	
procura_p:								;Procura no vetor algum espaco disponivel.

	lw $a0, struct($t1)						;Se n for 0, printa o vetor.
	beq $a0, $0, esc
;Data - 4 Bytes-----------------------------------
	addi $v0, $0, 1						;Print int (Data)
	syscall

	addi $t1, $t1, 4						;Incrementa contador
;String - 16 Bytes--------------------------------
	la $a0, struct($t1)
	addi $v0, $0, 4						;Print string (Strings)
	syscall

	addi $t1, $t1, 16						;Incrementa contador
;Quilometragem - 4 Bytes----------------------
	lwc1 $f12, struct($t1)
	addi $v0, $0, 2						;Print float (Quilometragem)
	syscall

	addi $t1, $t1, 4                        ;Incrementa contador
;Preco - 4 Bytes---------------------------------
	lwc1 $f12, struct($t1)
	addi $v0, $0, 2						;Print float (Preco)
	syscall
	
	addi $t1, $t1, 4                        ;Incrementa contador
;Quantidade - 4 Bytes--------------------------
	lwc1 $f12, struct($t1)
	addi $v0, $0, 2						;Print float (Preco)
	syscall
	
	addi $t1, $t1, 32                       ;Incrementa casa
	j	procura_p
	
esc:	
	j menu	

;Basicamente, quando terminar o cadastro, necessariamente precisa
;colocar a próxima word como 0, para delimitar o final dos prints, ou 
;a gente faz pela contagem do contador.
;Aparentemente ta printando errado nas funções de coisas médias, mas
;creio q é pelo meu erro de cadastro.
;====>Para printar em ordem de preco, precisa ordenar e mandar o print linear.