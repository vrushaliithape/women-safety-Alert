include <ESP_Mail_Client.h>
#include <driver/i2s.h>
#include <HTTPClient.h>
#include "config.h"



SMTPSession smtp;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("Connected to WiFi");

  setupI2S();
  smtp.debug(1);
}

void setupI2S() {
  i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 1024
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_0);
}

String getLocation() {
  String location = "Location not available";

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://ip-api.com/json");  // API to get location based on IP address
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);

      // Parse the JSON response to get location
      int latIndex = payload.indexOf("lat");
      int lonIndex = payload.indexOf("lon");

      if (latIndex != -1 && lonIndex != -1) {
        String lat = payload.substring(latIndex + 5, payload.indexOf(',', latIndex));
        String lon = payload.substring(lonIndex + 5, payload.indexOf(',', lonIndex));

        location = "Latitude: " + lat + ", Longitude: " + lon;
      }
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  }

  return location;
}

void sendEmail() {
  ESP_Mail_Session session;
  session.server.host_name = SMTP_SERVER;
  session.server.port = SMTP_PORT;
  session.login.email = SENDER_EMAIL;
  session.login.password = SENDER_PASSWORD;

  String location = getLocation();
  
  SMTP_Message message;
  message.sender.name = "ESP32";
  message.sender.email = SENDER_EMAIL;
  message.subject = "SEEMS Alert";
  message.addRecipient("Recipient", RECIPIENT_EMAIL);
  message.text.content = "VRUSHALI HAVE BEEN SEEMS IN DANGER ,HER CURRENT LOCATION AT !\n" + location;
  message.text.charSet = "us-ascii";

  if (smtp.connect(&session) && MailClient.sendMail(&smtp, &message)) {
    Serial.println("Email sent!");
  } else {
    Serial.println("Error: " + smtp.errorReason());
  }

  smtp.closeSession();
}

void loop() {
  int16_t i2sData[1024];
  size_t bytesRead;
  i2s_read(I2S_NUM_0, (void*)i2sData, sizeof(i2sData), &bytesRead, portMAX_DELAY);

  long sum = 0;
  int numSamples = bytesRead / sizeof(int16_t);
  for (int i = 0; i < numSamples; i++) {
    sum += abs(i2sData[i]);
  }

  if ((sum / numSamples) > SOUND_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    sendEmail();
    delay(5000);
    digitalWrite(LED_PIN, LOW);
  }

  delay(100);
}