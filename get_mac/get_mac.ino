#include <esp_mac.h>

void setup(){
  Serial.begin(115200);

  uint8_t mac_addr[6];
  esp_err_t response = esp_base_mac_addr_get(mac_addr);
  if(response == ESP_OK){
    Serial.println("This Device's Mac address: ");
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  }
  else{
    Serial.println("Fail");
  }
}

void loop(){
  delay(100)
}