<p align="center">
  <img src="arduinovel.png" alt="Arduinovel" />
</p>

## Requisitos

- 1x Arduino Uno R3
- 1x Display OLED SH1106 I2C
- 1x Buzzer (pino 6)
- 3x Botão Tátil (pinos 2, 3 e 4)

O Arduinovel foi testado apenas em um Arduino Uno R3, mas
deve funcionar com um Uno R4 também. Se necessário, troque
o nome da placa no arquivo de build.

O código pode funcionar com outros displays, como o SSD1106,
mas deve ter a resolução de exatamente 128x64 pixels.

Para fazer a mudança do display, deve-se modificar a seguinte 
para o display preferido, seguindo a documentação da biblioteca [u8g2](https://github.com/olikraus/u8g2):

```c
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset = */ U8X8_PIN_NONE);
```

## Upload

1. Clone o repositório do Arduinovel:

    ```bash
    git clone https://github.com/the7677/arduinovel-ptbr.git
    ```
    
2. Renomeie a pasta

    A pasta deve ser renomeada de 'arduinovel-ptbr' para 'arduinovel'.
    
    No linux:
    
    ``` bash
    mv arduinovel-ptbr/ arduinovel/
    ```
    
3. Adicione permissões e execute o script

    - Linux
    
        Execute os seguintes comandos dentro da pasta para adicionar permissões
        de execução e executar o arquivo de build:
    
        ``` bash
        cd arduinovel/
        chmod +x build.sh
        ./build.sh
        ```
        *Certifique-se de que o nome da pasta foi renomeado para 'arduinovel',
        seguindo a etapa 2.
        
    - Windows
    
        Em breve...