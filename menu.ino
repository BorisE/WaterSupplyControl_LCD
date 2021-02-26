enum mnTypes { mnTypeSubMenu, mnTypeLink, mnTypeVent, mnTypeSwitch, mnTypeParam};

typedef struct { 
  uint8_t         id;         
  const char*     menu_name;
  mnTypes         menu_type;
} Menu_Struct;


#define MenuCount 4

Menu_Struct MainMenu[MenuCount] {
  { 0, "Линия", mnTypeVent},
  { 1, "Насос", mnTypeVent},
  { 2, "Бак", mnTypeVent},
  { 3, "Насос реле", mnTypeSwitch}
};


void displayMenu (int ActiveID) {
  for (int i=0; i< MenuCount; i++) {
    int y = i*10;
    u8g2.setCursor(5, y);
    u8g2.print(MainMenu[i].menu_name);
    
    if (MainMenu[i].menu_name == mnTypeVent) {
      u8g2.print(":");
      u8g2.setCursor(100, y);
      u8g2.print("ОТКР");
    }
  }
  
}
