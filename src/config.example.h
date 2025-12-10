// Copy this file to config.h and replace the placeholder values with your actual credentials.
// config.h is excluded from Git using the .gitignore file.

#ifndef CONFIG_EXAMPLE_H
#define CONFIG_EXAMPLE_H

// Wi-Fi credentials
#define WIFI_SSID       "YOUR_WIFI_SSID"
#define WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"

// Email (SMTP) settings
#define SMTP_SERVER     "smtp.example.com"
#define SMTP_PORT       465
#define SENDER_EMAIL    "your_email@example.com"
#define SENDER_PASSWORD "YOUR_EMAIL_APP_PASSWORD"
#define RECIPIENT_EMAIL "recipient_email@example.com"

// Hardware pins
#define LED_PIN         2
#define I2S_WS          15
#define I2S_SD          32
#define I2S_SCK         14

// Sound detection threshold
#define SOUND_THRESHOLD 6000

#endif // CONFIG_EXAMPLE_H
