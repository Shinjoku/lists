.data
			
zero: 					.space 4
escolha_menu:			.asciiz "Digite o numero referente a escolha:\n"
opcao1:					.asciiz "1 - Cadastrar abastecimento\n"
opcao2:					.asciiz "2 - Excluir abastecimento\n"
opcao3:					.asciiz "3 - Exibir abastecimentos\n"
opcao4:					.asciiz "4 - Exibir consumo medio\n"
opcao5:					.asciiz "5 - Exibir preco medio\n"
opcao6:					.asciiz "6 - Exibir ranking de postos\n"
saida:					.asciiz "7 - Sair\n"
msg_cadastro1:			.asciiz "Digite o dia:\n"
msg_cadastro2:			.asciiz "Digite o mes:\n"
msg_cadastro3:			.asciiz "Digite o ano:\n"
msg_cadastro4:			.asciiz "Digite o nome do posto:\n"
msg_cadastro5:			.asciiz "Digite a quilometragem:\n"
msg_cadastro6:			.asciiz "Digite o preco:\n"
msg_cadastro7:			.asciiz "Digite a quantidade:\n"
msg_print1:				.asciiz "Dia: "
msg_print1.1:			.asciiz "Mês: "
msg_print1.2:			.asciiz "Ano: "
msg_print2:				.asciiz "Nome do Posto: "
msg_print3:				.asciiz "Quilometragem total do veículo: "
msg_print4:				.asciiz "Preço: "
msg_print5:				.asciiz "Quantidade de combustível abastecido: "
msg_sucesso:			.asciiz "Operação efetuada com sucesso!"
msg_erroe:				.asciiz "Erro! A data não existe"
msg_erro:				.asciiz "Erro! O numero que foi selecionado nao e valido!\n"
msg_remdata:			.asciiz "Digite a data a ser excluida do banco de dados:\n"
#4 bytes data | 16 bytes nome | 4 bytes km | 4 bytes preco | 4 bytes qntd abs
#32 bytes no total
struct:					.space 960		#Vetor do banco de dados. Sera armazenado em $s0 para ser manipulado no programa. 30 espacos
floatZero:	.float 0.0
floatAux:	.word 0

			.text
.globl main
main:

	
	la $s0, struct						#Inicializacao do vetor. Ela sera encontrada o programa inteiro em $s0.
	add $s3,$0, $0						#Inicializacao de $s3 como 0. Este sera o contador de quantos cadastros foram feitos.
	addi $t4, $0, 99999999
	sw $t4, struct						#Definindo o primeiro espaco como "disponivel", ou seja, 0
	lwc1 $f4, floatZero					#Quilometragem
	lwc1 $f5, floatZero					#Quantidade Total
	lwc1 $f6, floatZero					#Preco Total
menu:
	jal bubbleSort
	jal print_menu
	
	li $v0, 5								#Pede opcao.
	syscall

	beq	$v0, 1, cadastrar			#Se igual.
	beq	$v0, 2, excluir
	beq	$v0, 3, exibir_abastecimento
	beq	$v0, 4, exibir_consumo
	beq	$v0, 5, exibir_preco
	beq	$v0, 6, exibir_ranking
	beq	$v0, 7, sair

	la $a0, msg_erro					#Caso o usuario digite um numero invalido
	li $v0, 4
	syscall
	j menu


#------------------------------------------------------------
cadastrar:
	addi $t1, $0, 0
	j compar
buscar_vazio:
	addi $t1, $t1, 32		#incrementa pra proxima casa
	
compar:	
	lw $t2, struct($t1)
	bne $t2, $0, buscar_vazio
	
	la $s1, struct($t1)
	jal cadastro_input

	j menu
	
#------------------------------------------------------------
excluir:

	addi $v0, $zero, 5					#input year
	syscall
	addi  $t1, $0, 10000
	mul $t0, $v0, $t1					#Conversao para armazenamento
	
	la $a0, msg_cadastro2				#printa msg de mes
	addi $v0,$0,  4
	syscall
	
	addi $v0, $zero, 5					#input month
	syscall
	addi $t1, $0, 100
	mul $v0, $t1, $v0					#Conversao para armazenamento
	add $t0, $t0, $v0
	
	la $a0, msg_cadastro1				#printa msg de dia
	li $v0, 4
	syscall
	
	addi $v0, $0, 5						#input day
	syscall
	add $t0, $t0, $v0					#Armazenamento da data convertida

	add $t3, $0, $t0
	
	add $t0, $0, $0
	add $t2, $0, $0
	
procura_e:
	lw $t1, struct($t2)
	beq $t1, $t3, equal
	addi $t2, $t2, 32
	addi $t0, $t0, 1
	bnq $s3, $t0, procura_e
	j erro.

equal:
	addi $t4, $0, 99999999
	sw $t4, struct($t2)
	
	# Msg "Sucesso"
	la, $a0, msg_sucesso
	li $v0, 4
	syscall
	
	j menu

erro:
	#Printa msg de erro do Excluir
	la $a0, msg_erroe
	li $v0, 4
	syscall
	
	j menu
	
#------------------------------------------------------------
exibir_abastecimento:
#3)Exibir abastecimentos: exibir dados de todos os abastecimentos cadastrados (ordenados
#	pela data).
	
	jal bubbleSort
	
	add $t1, $0, $0
	addi $t8, $s3, 0
	addi $t9, $0, 0

procura_p:								#Procura no vetor algum espaco disponivel.

	lw $a0, struct($t1)					#Se n for 0, printa o vetor.
	beq $t9, $t8, esc
#Data - 4 Bytes-----------------------------------
	
	add $t5, $a0,$0
	
#Conversão Data-----------------------------------
	
# Ano
	la $a0, msg_print1.2					#printa msg de ano
	addi $v0,$0,  4
	syscall
	
	addi  $t1, $0, 10000
	div $a0, $t0, $t1					#Conversao para armazenamento
	
	addi $v0, $0, 1						#Print int (Data)
	syscall
	
	mul $a0, $a0, $t1					#data - ano * 10.000
	sub $t0, $t0, $a0
	
# Mes
	la $a0, msg_print1.1					#printa msg de mes
	addi $v0,$0,  4
	syscall
	
	addi $t1, $0, 100
	div $a0, $t0, $t1					#Conversao para armazenamento
	
	addi $v0, $0, 1						#Print int (Data)
	syscall
	
	mul $a0, $a0, $t1					#data - ano * 100
	sub $t0, $t0, $a0
# Dia	
	la $a0, msg_print1					#printa msg de dia
	li $v0, 4
	syscall
	
	add $a0, $t0, $0					#Armazenamento da data convertida
	addi $v0, $0, 1						#input day
	syscall

# Fim da Conversão data-----------------------------------

	addi $t1, $t1, 4						#Incrementa contador
#String - 16 Bytes--------------------------------
	la a0, print2
	addi
	
	la $a0, struct($t1)
	addi $v0, $0, 4						#Print string (Strings)
	syscall

	addi $t1, $t1, 16						#Incrementa contador
#Quilometragem - 4 Bytes----------------------
	lwc1 $f12, struct($t1)
	addi $v0, $0, 2						#Print float (Quilometragem)
	syscall

	addi $t1, $t1, 4
#Preco - 4 Bytes---------------------------------
	lwc1 $f12, struct($t1)
	addi $v0, $0, 2						#Print float (Preco)
	syscall
	
	addi $t1, $t1, 4
#Quantidade - 4 Bytes--------------------------
	lwc1 $f12, struct($t1)
	addi $v0, $0, 2						#Print float (Preco)
	syscall
	
	addi $t1, $t1, 4
	addi $t9, $t9, 1
	j	procura_p
	
esc:	
	j menu								#Retorna para menu.

#------------------------------------------------------------
exibir_consumo:
#4)Exibir consumo medio: de acordo com os dados de abastecimento cadastrados ate o
#	momento, exibir o consumo medio do veiculo (km por litro (Km/L)).

	div.s $f12, $f4, $f5					#Divide Km/L
	
	addi $v0, $0, 2						#Printa Float
	syscall
	
	j menu								#Retorna para menu.
	
#------------------------------------------------------------
exibir_preco:
	sw   $s3, -4($sp)
	lwc1 $f9, -4($sp)
	cvt.s.w $f9, $f9
	
	lwc1 $f1, floatZero
	add.s $f12, $f6, $f1
	addi $v0, $0, 2						#Printa Float
	syscall

	div.s $f12, $f6, $f9					#Divide Preco/s3
	
	addi $v0, $0, 2						#Printa Float
	syscall
	
	j menu								#Retorna para menu.
#------------------------------------------------------------
exibir_ranking:

	j menu
	
#------------------------------------------------------------
sair:
	li $v0, 10						#Codigo para encerrar o programa
	syscall
	
#------------------------------------------------------------


print_menu:
	addi $sp, $sp, -8						#Salvando os dados
	sw $a0, 4($sp)
	sw $v0, 0($sp)
	
	addi $a0, $s3, 0
	li $v0, 1
	syscall
	
	la $a0, escolha_menu				#printa menu
	li $v0, 4
	syscall

	la $a0, opcao1
	li $v0, 4
	syscall

	la $a0, opcao2
	li $v0, 4
	syscall

	la $a0, opcao3
	li $v0, 4
	syscall

	la $a0, opcao4
	li $v0, 4
	syscall

	la $a0, opcao5
	li $v0, 4
	syscall

	la $a0, opcao6
	li $v0, 4
	syscall
	
	la $a0, saida
	li $v0, 4
	syscall
	
	lw $v0, 0($sp)						#Retornando os dados.
	lw $a0, 4($sp)
	addi $sp, $sp, 8
	
jr $ra

#------------------------------------------------------------

cadastro_input:

	addi $sp, $sp, -8						#Salvando os dados
	sw $a0, 4($sp)
	sw $v0, 0($sp)
	add $t0, $0, $zero					#Registrador que sera guardada a data.
	
	la $a0, msg_cadastro3				#printa msg de ano
	li $v0, 4
	syscall
	
	addi $v0, $zero, 5					#input year
	syscall
	addi  $t1, $0, 10000
	mul $t0, $v0, $t1					#Conversao para armazenamento
	
	la $a0, msg_cadastro2				#printa msg de mes
	addi $v0,$0,  4
	syscall
	
	addi $v0, $zero, 5					#input month
	syscall
	addi $t1, $0, 100
	mul $v0, $t1, $v0					#Conversao para armazenamento
	add $t0, $t0, $v0
	
	la $a0, msg_cadastro1				#printa msg de dia
	li $v0, 4
	syscall
	
	addi $v0, $0, 5						#input day
	syscall
	add $t0, $t0, $v0					#Armazenamento da data convertida

	
	sw $t0, 0($s1)					#Armazenando a data convertida no vet auxiliar.
	
	la $a0, msg_cadastro4				#printa msg de nome
	li $v0, 4
	syscall
	
	la $a0, 4($s1)						#Delimitacao da string
	addi $a1, $zero, 16
	
	addi $v0, $zero, 8
	syscall								#input name
	
	la $a0, msg_cadastro5				#printa msg de quilometragem
	li $v0, 4
	syscall
	
	addi $v0, $zero, 6					#input km
	syscall
	swc1 $f0, 20($s1)
	add.s  $f4, $f4, $f0					#Pega quantidade de combustivel e incrementa na variavel global de Quilometragem
	
	la $a0, msg_cadastro6				#printa msg de preco
	li $v0, 4
	syscall
	
	addi $v0, $zero, 6					#input preco
	syscall
	swc1 $f0, 24($s1)
	add.s  $f6, $f6, $f0
	
	la $a0, msg_cadastro7				#printa msg de quantidade
	li $v0, 4
	syscall
	
	addi $v0, $zero, 6					#input quantidade de combustivel
	syscall
	swc1 $f0, 28($s1)
	add.s $f5, $f5, $f0					#Pega quantidade de combustivel e incrementa na variavel global de Qntd. Combustivel
	
	lw $0, 32($s1)
	
	
	lw $v0, 0($sp)						#Retornando os dados da pilha.
	lw $a0, 4($sp)
	addi $sp, $sp, 8
	
	addi $s3, $s3, 1
	
	jr $ra

#------------------------------------------------------------

bubbleSort:   
#array em t6
#contador em s3
	#t0, t1, t2, t6, t7, s1, s2
   	addi $sp, $sp, -40
   	sw $t0, 0($sp)						#Salvando os dados
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	sw $t6, 12($sp)
	sw $t7, 16($sp)
	sw $s1, 20($sp)
	sw $s2, 24($sp)
	sw $t4, 28($sp)
	sw $t8, 32($sp)
	sw $t9, 36($sp)
	
    #  Inicializar i como 0
    #  loop
    
     
    add $t0,$zero,$zero #i

     
    #  Outer Loop
      
    bubbleLoop:
	la $t6, struct
       #Se finalizado
        beq $t0,$s3,done

         
        #Initialize upper bound of inner
        #  loop ( 10 - i - 1 ) 
         
        sub $t7,$s3,$t0
        addi $t7,$t7,-1

         
        #  Initialize incrementer for inner
        #  loop
         
        add $t1,$zero,$zero

         
        #  Inner Loop
          
        jLoop:
             #
            #  Check for sentinal val and if true
            #  branch to continue
             #
            beq $t1,$t7,continue

             
            #  Load Array[i] and Array[i+1]
            
            lw  $s1,0($t6)
            lw  $s2,32($t6)

             #####
            #  If ascii(Array[i]) > ascii(Array[i+1])
            #  then swap and store
             #####
            sgt $t2, $s1,$s2
             #####
            #  Else,  don't swap and store
             #####
            beq $t2, $zero, good
            sw  $s2,0($t6)
            sw  $s1,32($t6)
            
            #before loopinho
            sll $t8, $t1,  5 #multiplica t1 (J) por 32
    	    addi $t8, $t8, 4
    	    addi $t9, $t8, 32
    	    addi $t4, $0, 0
    loopinho:
            lb  $s1, struct($t8)
            lb  $s2, struct($t9)
            sb  $s2, struct($t8)
            sb  $s1, struct($t9)
            
            addi $t4, $t4, 1
            addi $t8, $t8, 1
            addi $t9, $t9, 1
            bne  $t4, 16, loopinho

            #fim loopinho
            
            lw	$s1, 20($t6)
	    lw	$s2, 52($t6)
	    sw	$s2, 20($t6)
	    sw	$s1, 52($t6)
	
	    lw	$s1, 24($t6)
	    lw	$s2, 56($t6)
	    sw	$s2, 24($t6)
	    sw	$s1, 56($t6)
	
	    lw	$s1, 28($t6)
	    lw	$s2, 60($t6)
	    sw	$s2, 28($t6)
	    sw	$s1, 60($t6)
        
            
            

            good:
             #####
            #  increment and Jump back 
             #####
            addi $t1,$t1,1
            addi $t6, $t6, 32
            j jLoop

        continue:
         #
        #  increment and Jump back 
         #
        addi $t0,$t0,1
        j bubbleLoop

done:

	lw $t0, 0($sp)						#Salvando os dados
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $t6, 12($sp)
	lw $t7, 16($sp)
	lw $s1, 20($sp)
	lw $s2, 24($sp)
	lw $t4, 28($sp)
	lw $t8, 32($sp)
	lw $t9, 36($sp)
	addi $sp, $sp, 28

	jr $ra
	