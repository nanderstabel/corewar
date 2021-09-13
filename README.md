# Corewar
Corewar is an algorithmic project at Codam Coding College (42). The purpose of this project is to recode the programming game “Core War”. In this game, created by D. G. Jones and a. K. Dewdney in 1984, two or more battle programs compete for control of a virtual computer. 

This project consists of four parts:

Champions
Assembler
Virtual Machine
Visualizer (Bonus, a part of the VM)

### To compile
Clone repository and then go into the created directory and run the following command:
`make`

### Champions
Champions are battle programs written in assembly code. By combining the following instructions in specific ways one can create specific strategies that your champion can use to defeat other champions in a virtual arena:
- lfork
- sti
- fork
- lld
- ld
- add
- zjmp
- sub
- ldi
- or
- st
- aff
- live
- xor
- lldi
- and

### Assembler
Our assembler `asm` is able to compile the champion files (`.s` files) into machine language files (`.cor` files).

The assembler is written with a state machine in mind. It assembles the champion `.s` files in the following steps:
- Lexical analysis
- Syntax analysis
- Analysis of the assembly instructions
- Analysis of the instruction parameters
- Translation to byte code

An error in each one of these steps will result in a specific error message (give it a try, for example: `./asm test_folder/asm_test_folder/invalid_s_files/label_noending.s`)

### Virtual machine and Visualizer
After the champions are compiled into byte code, they are ready to battle eachother in the virtual arena (`corewar`). To make it more entertaining, we've created a visualizer using ncurses so it is easier to see what kind of strategies the different champions are utilizing (`-v` option).

To compile four champions:
`./asm Bazou.s & ./asm bee_gees.s & ./asm peanutbutter.s & ./
asm doge.s`

To run the virtual arena:
`./corewar -v Bazou.cor bee_gees.cor peanutbutter.cor doge.cor`

Sit back and watch the champions fight! If you want to see the winner right away, just run the same command without the `-v` option.

![Battle](https://user-images.githubusercontent.com/50104940/133082983-ca7303e5-3346-4d55-9948-0ddc1f5e3bf7.gif)

### Tests
This project has been thoroughly tested for all kinds of errors including memory leaks. 

To check out one of them run:
`cd test_folder/scripts/ && ./all_compile.sh ../asm_test_folder/valid_s_files/*.s && ./corewar_tester.sh -all -d 5000 -i 2500 ../vm_test_folder/valid_cor_files/*.cor`

### Details
For more details about the requirements of this project, checkout the [warning.pdf](https://github.com/nanderstabel/corewar/blob/master/warning.pdf) and [subject.pdf](https://github.com/nanderstabel/corewar/blob/master/subject.pdf)

This project has been a collaboration of:
- [moCello](https://github.com/moCello)
- [nanderstabel](https://github.com/nanderstabel)
- [RascalCalmind](https://github.com/RascalCalmind)
- [zitzak](https://github.com/zitzak)
