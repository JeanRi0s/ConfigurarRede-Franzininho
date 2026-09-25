# ConfigurarRede — Franzininho WiFi

Firmware para o **Franzininho WiFi (ESP32)** que cria um portal de configuração de rede Wi-Fi (estilo *WiFiManager*), com feedback visual em display OLED.

## Como funciona

1. Ao ligar, a placa sobe um **Access Point (AP)** próprio, chamado `Franzininho_Config`.
2. O usuário conecta o celular/PC nesse AP e acessa `192.168.4.1` no navegador.
3. Uma página web exibe um formulário para digitar o **SSID** e a **senha** da rede Wi-Fi desejada.
4. Ao enviar o formulário, a placa tenta se conectar a essa rede (modo `WIFI_AP_STA`, mantendo o AP ativo durante a tentativa).
5. O **display OLED** mostra em tempo real o status: rede recebida, tentativa de conexão, sucesso (com o IP obtido) ou falha.

## Hardware necessário

- Franzininho WiFi (ESP32)
- Display OLED SSD1306 128x64 (I2C, endereço `0x3C`)

## Bibliotecas necessárias (Arduino IDE)

- `WiFi.h` (nativa do core ESP32)
- `WebServer.h` (nativa do core ESP32)
- `Wire.h` (nativa)
- `Adafruit_GFX`
- `Adafruit_SSD1306`


## Como usar

1. Abra `ConfigurarRede/ConfigurarRede.ino` na Arduino IDE.
2. Selecione a placa ESP32 correspondente ao Franzininho WiFi e a porta serial correta.
3. Faça o upload do sketch.
4. No celular/PC, conecte-se à rede Wi-Fi:
   - **SSID:** `Franzininho_Config`
   - **Senha:** `12345678`
5. Acesse `192.168.4.1` no navegador.
6. Preencha o nome e a senha da sua rede Wi-Fi e clique em **Conectar**.
7. Acompanhe o status da conexão no display OLED (e, opcionalmente, no Monitor Serial a 115200 baud).

## Estrutura do projeto

```
ConfigurarRede/
└── ConfigurarRede.ino    #  servidor web e controle do OLED
```

## Possíveis melhorias futuras

- Salvar as credenciais em memória não volátil (Preferences/NVS), para reconectar automaticamente após reiniciar
- Botão físico para resetar a configuração salva
- Validação de campos no formulário (ex: senha mínima de 8 caracteres)
- Timeout configurável para as tentativas de conexão

## Autor

Desenvolvido por Emanuel — Engenharia de mecatrônica, Instituto Federal do Ceará.
