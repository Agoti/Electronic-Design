lmake(){
    make
    STM32_Programmer_CLI -c port=SWD -d build/stm32test.bin 0x8000000 -s
}