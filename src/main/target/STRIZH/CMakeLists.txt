#target_stm32f405xg(STRIZH COMPILE_DEFINITIONS "USE_HSI;INCREASE_PLL_FROM_168_TO_192MHZ" HSE_MHZ 25)

# keep only one line uncommented!

# if USE_HSI defined => internal HSI 16 MHz is used, HSE_MHZ value ignored
# if USE_HSI not defined => HSE is used according to HSE_MHZ value
# if INCREASE_PLL_FROM_168_TO_192MHZ defined => PLL is configured for 192 MHz output
# if INCREASE_PLL_FROM_168_TO_192MHZ not defined => 168 MHz

# use 168 MHz for STM32 builds
# use 192 MHz for GD32 builds

# uncomment next line for 192 MHz GD32 HSI build
target_stm32f405xg(STRIZH COMPILE_DEFINITIONS "USE_HSI;INCREASE_PLL_FROM_168_TO_192MHZ")

# uncomment next line for 192 MHz GD32 HSE build (set correct HSE_MHZ)
#target_stm32f405xg(STRIZH COMPILE_DEFINITIONS "INCREASE_PLL_FROM_168_TO_192MHZ" HSE_MHZ 25)

# uncomment next line for 168 MHz STM32 HSI build
#target_stm32f405xg(STRIZH COMPILE_DEFINITIONS "USE_HSI")

# uncomment next line for 168 MHz STM32 HSE build (set correct HSE_MHZ)
#target_stm32f405xg(STRIZH HSE_MHZ 8)
