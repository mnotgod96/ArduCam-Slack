void PushSlack(const char *MessageBody, const char *MessageTitle, const char *MessageType, ...) {
  const char* host = "hooks.slack.com";
  const int httpsPort = 443;
  const String slack_icon_url = "https://slack.com/img/icons/app-57.png";
  int PRINTF_BUF = 100;
  int StartWordCount = 32;
  char k = 0;
  char buf[PRINTF_BUF];

  va_list args;
  va_start(args, MessageBody);
  vsnprintf(buf, sizeof(buf), MessageBody, args);
  while (MessageType[k] != '\0') {
    k++;
  }
  int CharCount = StartWordCount + k;
  k = 0;
  while (MessageTitle[k] != '\0') {
    k++;
  }
  CharCount = CharCount + k;
  k = 0;
  while (buf[k] != '\0') {
    k++;
  }
  CharCount = CharCount + k;
  
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("Setting time using SNTP");
  configTime(8 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
  // Load root certificate in DER format into WiFiClientSecure object
  bool res = client.setCACert_P(caCert, caCertLen);
  if (!res) {
    Serial.println("Failed to load root CA certificate!");
    while (true) {
      yield();
    }
  }
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
  }
  
  String postData = "payload={\"link_names\": 1, \"icon_url\": \"" + slack_icon_url + "\", \"username\": \"" + MessageTitle + "\", \"text\": \"" + buf + "\"}";

  client.print(String("POST ") + tokenKey + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Connection: close" + "\r\n" +
               "Content-Length:" + postData.length() + "\r\n" +
               "\r\n" + postData);
}
