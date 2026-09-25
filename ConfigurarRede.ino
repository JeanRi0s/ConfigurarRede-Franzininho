#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ip de acesso : 192.168.4.1

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

WebServer server(80);


// AP de configuração

const char* ap_ssid = "Franzininho_Config";
const char* ap_password = "12345678";

String wifi_ssid = "";
String wifi_password = "";

//Pagina Web de Autenticação
void handleRoot() {

  String html = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">

<title>Configurar WiFi</title>

<style>

body{
  font-family:Arial;
  text-align:center;
  background:#f2f2f2;
}

.container{
  width:300px;
  margin:auto;
  margin-top:50px;
  background:white;
  padding:20px;
  border-radius:10px;
  box-shadow:0px 0px 10px gray;
}

input{
  width:90%;
  padding:10px;
  margin:10px;
}

button{
  padding:10px 20px;
}

</style>

</head>

<body>

<div class="container">

<h2>Configuração WiFi</h2>

<form action="/salvar">

<input
type="text"
name="ssid"
placeholder="Nome da Rede"
required>

<input
type="password"
name="senha"
placeholder="Senha"
required>

<button type="submit">
Conectar
</button>

</form>

</div>

</body>
</html>

)rawliteral";

  server.send(200, "text/html", html);
}


// Salvar a rede WiFi

void handleSalvar() {

  wifi_ssid = server.arg("ssid");
  wifi_password = server.arg("senha");

  server.send(
    200,
    "text/html",
    "<h2>Conectando...</h2><p>Verifique o display OLED.</p>"
  );

  // OLED
  display.clearDisplay();
  display.setCursor(0,0);

  display.println("Rede recebida:");
  display.println("");
  display.println(wifi_ssid);
  display.println("");
  display.println("Conectando...");

  display.display();

  Serial.println();
  Serial.println("===============");
  Serial.println("Dados recebidos");
  Serial.println("SSID: " + wifi_ssid);
  Serial.println("===============");

  WiFi.mode(WIFI_AP_STA);

  WiFi.begin(
    wifi_ssid.c_str(),
    wifi_password.c_str()
  );

  int tentativas = 0;

  while(
    WiFi.status() != WL_CONNECTED &&
    tentativas < 20
  ) {

    delay(500);

    Serial.print(".");

    tentativas++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("WiFi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    display.clearDisplay();
    display.setCursor(0,0);

    display.println("CONECTADO!");
    display.println("");

    display.print("SSID:");
    display.println(wifi_ssid);

    display.println("");

    display.print("IP:");

    display.println(
      WiFi.localIP()
    );

    display.display();

  }
  else {

    Serial.println("Falha na conexao");

    display.clearDisplay();
    display.setCursor(0,0);

    display.println("ERRO!");
    display.println("");
    display.println("Falha ao");
    display.println("conectar");

    display.display();
  }
}

void setup() {

  Serial.begin(115200);

  // I2C OLED
  Wire.begin();

  // OLED
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C
      )) {

    Serial.println("Falha OLED");

    while(true);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.println("Franzininho");
  display.println("WiFi Setup");
  display.println("");
  display.println("Iniciando...");

  display.display();

  // AP
  WiFi.mode(WIFI_AP);

  WiFi.softAP(
    ap_ssid,
    ap_password
  );

  Serial.println();
  Serial.println("AP iniciado");

  Serial.print("IP AP: ");
  Serial.println(
    WiFi.softAPIP()
  );

  display.clearDisplay();

  display.setCursor(0,0);

  display.println("AP Criado");
  display.println("");

  display.print("SSID:");
  display.println(ap_ssid);

  display.println("");

  display.print("IP:");
  display.println(
    WiFi.softAPIP()
  );

  display.display();

  server.on("/", handleRoot);
  server.on("/salvar", handleSalvar);

  server.begin();

  Serial.println(
    "Servidor iniciado"
  );
}

void loop() {

  server.handleClient();

}